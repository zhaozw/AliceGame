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
}

Data_EnemyDraw::Data_EnemyDraw(){
	drawList.Release();
}


bool Data_EnemyDraw::Load(){
	return LoadDataFromCsv();
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

	strcpy_s(fileName, MAX_PATH-1, _T("dat_enemy\\enemydraw.csv"));
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
			tmpDraw.SetHImg(GetImgHandleByRefID(tmpDraw.GetRefID()));
			if(tmpDraw.GetHImg() == 0){
				continue;
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

int Data_EnemyDraw::GetImgHandleByRefID(WORD refID){
	switch(refID){
	case ENEMYDRAW_ELF:
		return g_image.enemy.elf;
		break;
	case ENEMYDRAW_FIREELF:
		return g_image.enemy.elf;
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
