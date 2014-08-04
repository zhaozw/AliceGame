// Scene_Battle_Action.cpp

#include "Scene_Battle.h"
#include <string.h>
#include "MyTask_InfoEffect.h"
#include "Static_InfoEffect.h"
#include "Data_SkillInfo.h"
#include "Data_StateMessage.h"
#include "Game_AliceInfo.h"


extern Data_SkillInfo d_skillInfo;
extern Data_StateMessage d_stateMessage;
extern Game_AliceInfo g_aliceInfo;

extern MyGroup* gMyTask_InfoEffect;

bool Scene_Battle::InterpretAction(Game_BattleAction* pAction){
	if(pAction == NULL){ // �A�N�V�������s�K�؂ȏꍇ
		return false;
	}
	switch(pAction->GetType()){
	case Game_BattleAction::TYPE_DAMAGE:
		Action_Damage(pAction);
		break;
	case Game_BattleAction::TYPE_HEAL:
		Action_Heal(pAction);
		break;
	case Game_BattleAction::TYPE_CALLENEMYNAME:
		Action_CallEnemyName();
		break;
	case Game_BattleAction::TYPE_CALLVICTORY:
		Action_CallVictory();
		break;
	case Game_BattleAction::TYPE_CALLLOSE:
		Action_CallLose();
		break;
	case Game_BattleAction::TYPE_ASSERTATTACK:
		Action_AssertAttack(pAction);
		break;
	case Game_BattleAction::TYPE_ASSERTSKILL:
		Action_AssertSkill(pAction);
		break;
	case Game_BattleAction::TYPE_ASSERTGUARD:
		Action_AssertGuard(pAction);
		break;
	case Game_BattleAction::TYPE_NO_MP:
		Action_No_MP(pAction);
		break;
	case Game_BattleAction::TYPE_ADDSTATE:
		Action_Add_State(pAction);
		break;
	case Game_BattleAction::TYPE_REMOVESTATE:
		Action_Remove_State(pAction);
		break;
	case Game_BattleAction::TYPE_NONE:
	case Game_BattleAction::TYPE_UNDIFINED:
	default:
		// �^�C�v���K�؂łȂ��ꍇ
		return false;
		break;
	}
	return true;

}

bool Scene_Battle::Action_Damage(Game_BattleAction* pAction){
	Sprite_Base* pSprite = NULL;
	Sprite_BattleDoll* pDoll = NULL;
	MyTask* pTask = NULL;
	int x=0, y=0;
	// �_���[�W�����b�Z�[�W�E�B���h�E�ɕ\������
	TCHAR buf[WND_MSG_STOCKLENGTH];
	TCHAR nameBuf[BATTLEUNIT_NAME_BYTES];
	TCHAR numBuf[4]; // �����\���p
	// ���O���擾����
	pAction->GetOpponent()->GetName(nameBuf, BATTLEUNIT_NAME_BYTES);
	// ���l���擾����
	wsprintf(numBuf, _T("%d"), pAction->GetParam());
	// ���O�̑̍ق𐮂���
	strcpy_s(buf, WND_MSG_STOCKLENGTH-1, nameBuf);
	strcat_s(buf, WND_MSG_STOCKLENGTH-1, _T("��"));
	strcat_s(buf, WND_MSG_STOCKLENGTH-1, numBuf);
	strcat_s(buf, WND_MSG_STOCKLENGTH-1, _T("�̃_���[�W�I"));
	AddStockMessage(buf);
	// �_���[�W��K�p����
	pAction->GetOpponent()->Damage(pAction->GetParam());
	// �_���[�W�̐��l��\������
	if(pAction->GetOpponent()->IsDoll()){
		// �ʒu���擾
		pSprite = (Sprite_Base*)GetDollSprite((Game_BattleDoll*)pAction->GetOpponent());
		if(pSprite != NULL){
			// �^�X�N�𔭐�������
			pTask = gMyTask_InfoEffect->Call();
			pDoll = (Sprite_BattleDoll*)pSprite;
			if(pTask!=NULL){
				new (pTask) MyTask_InfoEffect(
					pDoll->GetDollX(), pDoll->GetDollY()+40,
					INFO_DAMAGENUM_DOLL, pAction->GetParam(), 0);
			}
		}
	}else{
		// �ʒu���擾
		pSprite = (Sprite_Base*)GetEnemySprite((Game_BattleEnemy*)pAction->GetOpponent());
		if(pSprite != NULL){
			// �^�X�N�𔭐�������
			pTask = gMyTask_InfoEffect->Call();
			if(pTask!=NULL){
				new (pTask) MyTask_InfoEffect(
					pSprite->GetIX(), pSprite->GetIY(),
					INFO_DAMAGENUM_ENEMY, pAction->GetParam(), 0);
			}
		}
	}
	// �X�v���C�g�ɑ΂��鏈�����s��
	if(pAction->GetOpponent()->IsDoll()){
		pSprite = (Sprite_Base*)GetDollSprite((Game_BattleDoll*)pAction->GetOpponent());
		if(pSprite != NULL){
			// �^�X�N�𔭐�������
			pSprite->SetMorphID(SPMORPH_DAMAGE_DOLL, false, 8);
		}
	}else{
		pSprite = (Sprite_Base*)GetEnemySprite((Game_BattleEnemy*)pAction->GetOpponent());
		if(pSprite != NULL){
			// �^�X�N�𔭐�������
			pSprite->SetMorphID(SPMORPH_BLINK, false, 8);
		}
	}

	
	return true;
}

bool Scene_Battle::Action_Heal(Game_BattleAction* pAction){
	Sprite_Base* pSprite = NULL;
	Sprite_BattleDoll* pDoll = NULL;
	MyTask* pTask = NULL;
	int x=0, y=0;
	// �_���[�W�����b�Z�[�W�E�B���h�E�ɕ\������
	TCHAR buf[WND_MSG_STOCKLENGTH];
	TCHAR nameBuf[BATTLEUNIT_NAME_BYTES];
	TCHAR numBuf[4]; // �����\���p
	// ���O���擾����
	pAction->GetOpponent()->GetName(nameBuf, BATTLEUNIT_NAME_BYTES);
	// ���l���擾����
	wsprintf(numBuf, _T("%d"), pAction->GetParam());
	// ���O�̑̍ق𐮂���
	strcpy_s(buf, WND_MSG_STOCKLENGTH-1, nameBuf);
	strcat_s(buf, WND_MSG_STOCKLENGTH-1, _T("�̗̑͂�"));
	strcat_s(buf, WND_MSG_STOCKLENGTH-1, numBuf);
	strcat_s(buf, WND_MSG_STOCKLENGTH-1, _T("�񕜂����I"));
	AddStockMessage(buf);
	// �_���[�W��K�p����
	pAction->GetOpponent()->Heal(pAction->GetParam());
	/*
	// �_���[�W�̐��l��\������
	if(pAction->GetOpponent()->IsDoll()){
		// �ʒu���擾
		pSprite = (Sprite_Base*)GetDollSprite((Game_BattleDoll*)pAction->GetOpponent());
		if(pSprite != NULL){
			// �^�X�N�𔭐�������
			pTask = gMyTask_InfoEffect->Call();
			pDoll = (Sprite_BattleDoll*)pSprite;
			if(pTask!=NULL){
				new (pTask) MyTask_InfoEffect(
					pDoll->GetDollX(), pDoll->GetDollY()+40,
					INFO_DAMAGENUM_DOLL, pAction->GetParam(), 0);
			}
		}
	}else{
		// �ʒu���擾
		pSprite = (Sprite_Base*)GetEnemySprite((Game_BattleEnemy*)pAction->GetOpponent());
		if(pSprite != NULL){
			// �^�X�N�𔭐�������
			pTask = gMyTask_InfoEffect->Call();
			if(pTask!=NULL){
				new (pTask) MyTask_InfoEffect(
					pSprite->GetIX(), pSprite->GetIY(),
					INFO_DAMAGENUM_ENEMY, pAction->GetParam(), 0);
			}
		}
	}
	*/
	/*
	// �X�v���C�g�ɑ΂��鏈�����s��
	if(pAction->GetOpponent()->IsDoll()){
		pSprite = (Sprite_Base*)GetDollSprite((Game_BattleDoll*)pAction->GetOpponent());
		if(pSprite != NULL){
			// �^�X�N�𔭐�������
			pSprite->SetMorphID(SPMORPH_DAMAGE_DOLL, false, 8);
		}
	}else{
		pSprite = (Sprite_Base*)GetEnemySprite((Game_BattleEnemy*)pAction->GetOpponent());
		if(pSprite != NULL){
			// �^�X�N�𔭐�������
			pSprite->SetMorphID(SPMORPH_BLINK, false, 8);
		}
	}
	*/

	
	return true;
}


bool Scene_Battle::Action_CallEnemyName(){
	// ���ꂼ��̓G�ɂ��ă��b�Z�[�W�E�B���h�E�ɓ��e�𑗂�
	TCHAR buf[WND_MSG_STOCKLENGTH];
	TCHAR nameBuf[BATTLEUNIT_NAME_BYTES];
	for(int n=0; n<enemiesNum; n++){
		// ���O���擾����
		enemies[n].GetName(nameBuf, BATTLEUNIT_NAME_BYTES);
		// ���O�̑̍ق𐮂���
		strcpy_s(buf, WND_MSG_STOCKLENGTH-1, nameBuf);
		strcat_s(buf, WND_MSG_STOCKLENGTH-1, _T("�����ꂽ�I"));
		w_battleMsg.AddStockMsg(buf, strlen(buf));
		// w_battleMsg.SetText
	}
	return true;
}

bool Scene_Battle::Action_CallVictory(){
	TCHAR buf[WND_MSG_STOCKLENGTH];
	strcpy_s(buf, WND_MSG_STOCKLENGTH-1, _T("���������I"));
	w_battleMsg.AddStockMsg(buf, strlen(buf));
	return true;
}

bool Scene_Battle::Action_CallLose(){
	TCHAR buf[WND_MSG_STOCKLENGTH];
	strcpy_s(buf, WND_MSG_STOCKLENGTH-1, _T("�S�ł����c�B"));
	w_battleMsg.AddStockMsg(buf, strlen(buf));
	return true;
}

bool Scene_Battle::Action_AssertAttack(Game_BattleAction* pAction){
	// ���b�Z�[�W�E�B���h�E�ɓ��e�𑗂�
	TCHAR buf[WND_MSG_STOCKLENGTH];
	TCHAR nameBuf[BATTLEUNIT_NAME_BYTES];
	// ���O���擾����
	pAction->GetActor()->GetName(nameBuf, BATTLEUNIT_NAME_BYTES);
	// ���O�̑̍ق𐮂���
	strcpy_s(buf, WND_MSG_STOCKLENGTH-1, nameBuf);
	strcat_s(buf, WND_MSG_STOCKLENGTH-1, _T("�̍U���I"));
	w_battleMsg.AddStockMsg(buf, strlen(buf));
	// �X�v���C�g�ɑ΂��鏈�����s��
	Sprite_Base* pSprite;
	if(pAction->GetActor()->IsDoll()){
	}else{
		pSprite = (Sprite_Base*)GetEnemySprite((Game_BattleEnemy*)pAction->GetActor());
		if(pSprite != NULL){
			// �^�X�N�𔭐�������
			pSprite->SetMorphID(SPMORPH_ENEMYATTACK, false);
		}
	}
	return true;
}

bool Scene_Battle::Action_AssertSkill(Game_BattleAction* pAction){
	// ���b�Z�[�W�E�B���h�E�ɓ��e�𑗂�
	TCHAR buf[WND_MSG_STOCKLENGTH];
	strcpy_s(buf, WND_MSG_STOCKLENGTH-1, _T(""));
	d_skillInfo.GetAssertMessage(buf, pAction->GetParam(), pAction->GetActor());
	if(strlen(buf)>0){
		w_battleMsg.AddStockMsg(buf, strlen(buf));
	}
	// �X�v���C�g�ɑ΂��鏈�����s��
	Sprite_Base* pSprite;
	if(pAction->GetActor()->IsDoll()){
	}else{
		pSprite = (Sprite_Base*)GetEnemySprite((Game_BattleEnemy*)pAction->GetActor());
		if(pSprite != NULL){
			// �^�X�N�𔭐�������
			pSprite->SetMorphID(SPMORPH_ENEMYATTACK, false);
		}
	}
	return true;
}

bool Scene_Battle::Action_AssertGuard(Game_BattleAction* pAction){
	// ���b�Z�[�W�E�B���h�E�ɓ��e�𑗂�
	TCHAR buf[WND_MSG_STOCKLENGTH];
	TCHAR nameBuf[BATTLEUNIT_NAME_BYTES];
	// ���O���擾����
	pAction->GetActor()->GetName(nameBuf, BATTLEUNIT_NAME_BYTES);
	// ���O�̑̍ق𐮂���
	strcpy_s(buf, WND_MSG_STOCKLENGTH-1, nameBuf);
	strcat_s(buf, WND_MSG_STOCKLENGTH-1, _T("�͐g������Ă���I"));
	w_battleMsg.AddStockMsg(buf, strlen(buf));
	return true;
}

bool Scene_Battle::Action_No_MP(Game_BattleAction* pAction){
	// ���b�Z�[�W�E�B���h�E�ɓ��e�𑗂�
	TCHAR buf[WND_MSG_STOCKLENGTH];
	strcpy_s(buf, WND_MSG_STOCKLENGTH-1, _T("�������A�A���X�̖��͂�����Ȃ��I"));
	w_battleMsg.AddStockMsg(buf, strlen(buf));
	return true;
}

bool Scene_Battle::Action_Add_State(Game_BattleAction* pAction){
	Game_BattleUnit* pTarget = pAction->GetOpponent();
	if(pTarget == NULL) return false;
	// �X�e�[�g�̕t��
	int param = 0, param2 = 0;
	// �X�e�[�g���ƂɁAparam��param2�̑���̎d�����قȂ�
	switch(pAction->GetParam()){
	case STATE_TMPATTR_NONE:
	case STATE_TMPATTR_SUN:
	case STATE_TMPATTR_MOON:
	case STATE_TMPATTR_STAR:
		param = (int)(pAction->GetFlags());
		break;
	default:
		// param�l���g�p���Ȃ�
		break;
	}
	pTarget->AddState(pAction->GetParam(), param, param2);
	// ���b�Z�[�W�E�B���h�E�ɓ��e�𑗂�
	TCHAR buf[WND_MSG_STOCKLENGTH];
	if(!d_stateMessage.GetStateMessage(buf, pAction->GetParam(),
		pTarget->IsDoll() 
		? STATEMESSAGE_INDEX_DOLL_ADDED 
		: STATEMESSAGE_INDEX_ENEMY_ADDED,
		pTarget)){
			// ���b�Z�[�W�����݂��Ȃ��ꍇ
			return true;
	}
	if(strlen(buf) > 0){
		w_battleMsg.AddStockMsg(buf, strlen(buf));
	}
	// �X�v���C�g���X�V����
	if(pTarget->IsDoll()){
		// GetDollSprite((Game_BattleDoll*)pTarget)->UpdateRefID();
	}else{
		GetEnemySprite((Game_BattleEnemy*)pTarget)->UpdateRefID();
	}
	return true;
}

bool Scene_Battle::Action_Remove_State(Game_BattleAction* pAction){
	Game_BattleUnit* pTarget = pAction->GetActor();
	if(pTarget == NULL) return false;
	// �X�e�[�g�̉���
	pAction->GetActor()->RemoveState(pAction->GetParam());
	// ���b�Z�[�W�E�B���h�E�ɓ��e�𑗂�
	TCHAR buf[WND_MSG_STOCKLENGTH];
	if(!d_stateMessage.GetStateMessage(buf, pAction->GetParam(),
		STATEMESSAGE_INDEX_REMOVED, pAction->GetActor())){
			// ���b�Z�[�W�����݂��Ȃ��ꍇ
			return true;
	}
	if(strlen(buf) > 0){
		w_battleMsg.AddStockMsg(buf, strlen(buf));
	}
	// �X�v���C�g���X�V����
	if(pTarget->IsDoll()){
		// GetDollSprite((Game_BattleDoll*)pTarget)->UpdateRefID();
	}else{
		GetEnemySprite((Game_BattleEnemy*)pTarget)->UpdateRefID();
	}
	return true;
}