// Data_EnemyDraw.cpp

#include "Data_EnemyDraw.h"
#include "CsvReader.h"
#include "Image.h"

#define MAX_ENEMYDRAWFILE		100

extern Image		g_image;

Data_EnemyDraw_Each::Data_EnemyDraw_Each(){
	Refresh();
}

void Data_EnemyDraw_Each::Refresh(){
	refID = 0;
	// �`��̒��S�ʒu
	cx=0;
	cy=0;
	// �摜�̃T�C�Y
	iWidth=1,
	iHeight=1;
	// ��{�I�ȕ`��̔{��
	baseExRate=1.0;
	// �摜�̃n���h��(��������)
	for(int n=0; n<DOLL_ATTR_NUM; n++){
		hImg[n] = 0;
	}
}

Data_EnemyDraw::Data_EnemyDraw(){
	drawList.Release();
}


bool Data_EnemyDraw::Load(){
#ifndef USE_ENCODED_CSV
	return LoadDataFromCsv();
#else // USE_ENCODED_CSV
	return LoadDataFromDat();
#endif // USE_ENCODED_CSV
}

bool Data_EnemyDraw::LoadDataFromCsv(){
	// ���X�g�̉��
	drawList.Release();
	// Csv��ǂݍ��ރN���X
	CsvReader				reader;
	// �t�@�C������ێ�����
	TCHAR					fileName[MAX_PATH];
	// �O���[�v�̓��e���ꎞ�I�ɕێ�����ϐ�
	Data_EnemyDraw_Each		tmpDraw;

	strcpy_s(fileName, MAX_PATH-1, DATFILE_ENEMYDRAW);
	if(reader.Open(fileName)){
		// �_�~�[�s
		reader.NextLine();
		// csv�t�@�C����ǂݍ���ŃO���[�v�Ɋi�[����
		for(int n=0; n<MAX_ENEMYDRAWFILE; n++){
			tmpDraw.Refresh();
			// ���t�@�����X�pID���擾����
			if(reader.Read() == CSV_READ_NOERROR){
				if(reader.GetIntValue(1, 0) == 0){
					continue;
				}
				tmpDraw.SetRefID((WORD)reader.GetIntValue(1, 0));
			}
			// �摜�T�C�Y���擾
			tmpDraw.SetIWidth(reader.GetIntValue(2, 1));
			tmpDraw.SetIHeight(reader.GetIntValue(3, 1));
			// �`���ʒu���擾
			tmpDraw.SetCX(reader.GetFloatValue(4, 0));
			tmpDraw.SetCY(reader.GetFloatValue(5, 0));
			// �g��{�����擾
			tmpDraw.SetExRate(reader.GetFloatValue(6, 1.0));

			// �摜���擾
			for(int n=0; n<DOLL_ATTR_NUM; n++){
				tmpDraw.SetHImg(n, GetImgHandleByRefID(tmpDraw.GetRefID(), n));
			}
			// 
			// �擾�����O���[�v���f�[�^�x�[�X�ɃZ�b�g����
			drawList.AddData(tmpDraw);
		}
	}else{
		return false;
	}
	return true;
}

bool Data_EnemyDraw::LoadDataFromDat(){
	return true;
}

bool Data_EnemyDraw::EncodeCsv(){
	if(!LoadDataFromCsv()) return false;
	return true;
}

int Data_EnemyDraw::GetImgHandleByRefID(WORD refID, BYTE attr){
	// �G��ID�y�ё����Ɖ摜�̑Ή������߂�B
	// �����摜���Q�Ƃ��Ă��Ă����܂�Ȃ��B
	switch(refID){
	case ENEMYDRAW_SMALLFAIRY:
		return g_image.enemy.fairy[attr];
		break;
	case ENEMYDRAW_FAIRY:
		return g_image.enemy.fairy[attr];
		break;
	case ENEMYDRAW_L_SNAIL:
		return g_image.enemy.snail[attr];
		break;
	case ENEMYDRAW_F_BUTTERFLY:
		return g_image.enemy.butterfly[attr];
		break;
	case ENEMYDRAW_SHIKABANE:
		return g_image.enemy.skeleton[attr];
		break;
	case ENEMYDRAW_WINDCROW:
		return g_image.enemy.crow[attr];
		break;
	case ENEMYDRAW_HARPY:
		return g_image.enemy.harpy[attr];
		break;
	case ENEMYDRAW_HEALFAIRY:
		return g_image.enemy.fairy[attr];
		break;
	case ENEMYDRAW_INNOCENTBONE:
		return g_image.enemy.skeleton[attr];
		break;
	case ENEMYDRAW_NECROMANCER:
		return g_image.enemy.cardinal;
		break;
	default:
		break;
	}
	return 0;
}

Data_EnemyDraw_Each* Data_EnemyDraw::GetEnemyDraw(WORD _refID){
	// �f�[�^�x�[�X���Q�Ƃ��A�w�肷��refID�������Ă�����̂�Ԃ��B
	// �Y��������̂��Ȃ��ꍇ��NULL��Ԃ��B
	Data_EnemyDraw_Each* pResult = NULL;
	int maxSize = drawList.GetSize();
	for(int n=0; n<maxSize; n++){
		pResult = drawList.GetPointerByIndex(n);
		if(pResult != NULL){
			if(pResult->GetRefID() == _refID){
				// �~����ID�ƈ�v������̂�����΂����Ԃ�
				return pResult;
			}
		}
	}
	return NULL;
}
