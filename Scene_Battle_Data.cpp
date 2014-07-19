// Scene_Battle_Data.cpp

#include "Scene_Battle.h"
#include "Data_EnemyGroup.h"
#include "Data_EnemyParam.h"
#include "Game_AliceDoll.h"
#include "CsvReader.h"

// �f�[�^�x�[�X
extern Data_EnemyGroup d_enemyGroup;
extern Data_EnemyParam	d_enemyParam;

bool Scene_Battle::SetupDolls(){
	if(!LoadPresetDolls(1)){
		return false;
	}
	return true;
}

bool Scene_Battle::SetupEnemy(){
	// �G�O���[�vID����f�[�^�x�[�X��ǂݍ��ށB
	if(!LoadEnemyGroup()){
		return false;
	}
	return true;
}

bool Scene_Battle::LoadDefaultDolls(int defaultID){
	return true;
}

bool Scene_Battle::LoadPresetDolls(int defaultID){
	TCHAR		fileName[MAX_PATH];
	CsvReader	reader;
	Game_AliceDoll_Essence	tmpDoll;
	TCHAR		tmpName[BATTLEUNIT_NAME_BYTES];
	BYTE		tmpAttr = DOLL_ATTR_NONE;
	int			tmpInt = 0;
	wsprintf(fileName, _T("dat_battle\\preset_dolls%02d.csv"), defaultID);
	if(!reader.Open(fileName)){
		return false;
	}
	// �ŏ��̓�s�͋�s
	reader.Read();
	reader.Read();
	// �l�`�̐������x���͑S��0�A�S�ē������x���ŋ������Ǘ�����
	for(int n=0; n<DOLL_PARAM_MAX; n++){
		tmpDoll.SetGrowthLevel(n, 0);
	}
	// �l�`�̖��O�̓f�[�^�x�[�X���璼�ړǂݍ��ށB
	strcpy_s(tmpName, BATTLEUNIT_NAME_BYTES, _T(""));

	// �e�l�`�̃f�[�^��ǂݍ���
	for(int n=0; n<MAX_BATTLEDOLL; n++){
		reader.Read();
		// �^�C�vID���K�؂��ǂ����Ŕ��f
		tmpInt = reader.GetIntValue(0);
		if(tmpInt < 0 || tmpInt > DOLL_TYPE_MAX){
			break;
		}
		// �^�C�vID
		tmpDoll.SetType((BYTE)tmpInt);
		// ���O
		reader.GetValue(1, tmpName, BATTLEUNIT_NAME_BYTES);
		// ���x��
		tmpDoll.SetLevel((WORD)reader.GetIntValue(2));
		// �e�p�����[�^
		for(int i=0; i<DOLL_PARAM_MAX; i++){
			tmpDoll.SetPotentialLevel(i, (DWORD)reader.GetIntValue(3+i));
		}
		// ����
		// �S�Ă̑����΂𓯂��ɂ���
		// ������0�̏ꍇ�͑S�Ă̐΂�2���ɂ���
		tmpAttr = (BYTE)reader.GetIntValue(3+DOLL_PARAM_MAX);
		if(tmpAttr == DOLL_ATTR_NONE){
			for(int j=0; j<DOLL_ATTR_NUM-1; j++){
				for(int i=0; i<2; i++){
					tmpDoll.SetAttrStone(i+j*2, (BYTE)(j+1));
				}
			}
		}else{
			for(int i=0; i<DOLL_ATTRSTONE_NUM; i++){
				tmpDoll.SetAttrStone(i, tmpAttr);
			}
		}
		// ���ZID�̃Z�b�g
		reader.Read();
		for(int i=0; i<DOLL_SKILL_MAX; i++){
			tmpDoll.SetSkillID(i, (WORD)reader.GetIntValue(i));
		}
		// Game_AliceDoll_Essence����Game_BattleDoll�ɓ��e���C���|�[�g
		dolls[n].SetParamFromReference(&tmpDoll, false);

		// ���O�����͕ʂŃR�s�[
		dolls[n].SetName(tmpName, strlen(tmpName));

		// �g�p����Ă���
		dolls[n].SetIsUsed(true);

		// �l�`�̐����w��B
		dollsNum = n+1;
	}
	return true;
}

bool Scene_Battle::LoadEnemyGroup(){
	// �G���j�b�g��ID�ł���enemyGroup(WORD)�l���g�p����B
	Data_EnemyGroup_Each* pEnemyGroup = NULL;
	WORD tmpRefID;
	pEnemyGroup = d_enemyGroup.GetEnemyGroup(enemyGroup);
	if(pEnemyGroup == NULL){
		// �Y������refID�����G�O���[�v�����݂��Ȃ�(�G���[)
		return false;
	}
	for(int n=0; n<MAX_BATTLEENEMY; n++){
		tmpRefID = pEnemyGroup->GetEnemyRefID(n);
		if(tmpRefID != 0){
			// ID����G���쐬����
			LoadEnemyData(n, tmpRefID,
				pEnemyGroup->GetEnemyDrawX(n), pEnemyGroup->GetEnemyDrawY(n));
			// �G�̐������
			enemiesNum = n+1;
		}else{
			// �GID����B�f�[�^�̎�荞�݂��I������
			break;
		}
	}
	return true;
}

bool Scene_Battle::LoadEnemyData(WORD index, WORD enemyID, int drawX, int drawY){
	TCHAR tmpName[BATTLEUNIT_NAME_BYTES];
	Data_EnemyParam_Each* pEnemyParam = NULL;
	// �G�̏����擾
	pEnemyParam = d_enemyParam.GetEnemyParam(enemyID);
	if(pEnemyParam == NULL){
		// ���݂��Ȃ��G���Q�Ƃ��Ă���(�G���[)
		return false;
	}
	// ID
	enemies[index].SetDataID(enemyID);
	// ���O
	pEnemyParam->GetName(tmpName, BATTLEUNIT_NAME_BYTES); // �v����
	enemies[index].SetName(tmpName, strlen(tmpName));
	// �p�����[�^
	enemies[index].SetParam(
		pEnemyParam->GetHP(), pEnemyParam->GetHP(),
		pEnemyParam->GetAtk(), pEnemyParam->GetDef(),
		pEnemyParam->GetSpd(), pEnemyParam->GetMgc(),
		pEnemyParam->GetTec());
	// ����
	enemies[index].SetAttr(pEnemyParam->GetAttr());
	// �`��ʒu
	enemies[index].SetDrawPos(drawX, drawY);
	// �o���l
	enemies[index].SetExp(pEnemyParam->GetExp());
	// ���̑��Œ�l
	enemies[index].SetFront(true);
	enemies[index].SetPosition(index);
	enemies[index].SetSelfTurn();
	enemies[index].SetIsUsed(true);
	return true;
}
