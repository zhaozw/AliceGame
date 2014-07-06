// Data_EnemyGroup.cpp

#include "Data_EnemyGroup.h"
#include "CsvReader.h"

#define MAX_ENEMYGROUPFILE		999

// �O���[�v�̏�����
Data_EnemyGroup_Each::Data_EnemyGroup_Each(){
	Refresh();
}

void Data_EnemyGroup_Each::Refresh(){
	refID = 0;
	for(int n=0; n<MAX_BATTLEENEMY; n++){
		enemy[n].refID = 0;
		enemy[n].drawX = 0;
		enemy[n].drawY = 0;
	}
}


Data_EnemyGroup::Data_EnemyGroup(){
}

bool Data_EnemyGroup::Load(){
	return LoadDataFromCsv();
}

bool Data_EnemyGroup::LoadDataFromCsv(){
	// ���X�g�̉��
	groupList.Release();
	// Csv��ǂݍ��ރN���X
	CsvReader				reader;
	// �t�@�C������ێ�����
	TCHAR					fileName[MAX_PATH];
	// �O���[�v�̓��e���ꎞ�I�ɕێ�����ϐ�
	Data_EnemyGroup_Each	tmpGroup;
	// �t�@�C�������݂��Ȃ��ꍇ�����x���������烋�[�v�𔲂���
	int						nEmptyFile = 0;
	// ���Ԗڂ̓G�C���f�b�N�X�܂Ŗ��܂��Ă��邩
	int						index = 0;

	for(int n=1; n<=MAX_ENEMYGROUPFILE; n++){
		sprintf_s(fileName, MAX_PATH-1, "dat_egroup\\group%03d.csv", n);
		// csv�t�@�C����ǂݍ���ŃO���[�v�Ɋi�[����
		if(reader.Open(fileName)){
			nEmptyFile = 0; // ��t�@�C�����̃��Z�b�g
			index = 0;
			tmpGroup.Refresh();
			// �_�~�[�s
			reader.NextLine();
			// �O���[�vID���擾����
			if(reader.Read() == CSV_READ_NOERROR){
				if(reader.GetIntValue(0, 0) == 0){
					continue;
				}
				tmpGroup.SetRefID((WORD)reader.GetIntValue(0, 0));
			}
			// �_�~�[�s
			reader.NextLine();
			// �G��ID�Ƃ��̕`��ʒu���擾����
			for(int i=0; i<MAX_BATTLEENEMY; i++){
				if(reader.Read() == CSV_READ_NOERROR){
					if(reader.GetIntValue(0, 0) != 0){
						tmpGroup.SetEnemyRefID(index, (WORD)reader.GetIntValue(0, 0));
						tmpGroup.SetEnemyDrawX(index, (WORD)reader.GetIntValue(1, 0));
						tmpGroup.SetEnemyDrawY(index, (WORD)reader.GetIntValue(2, 0));
						index++;
					}
				}
			}
			// �擾�����O���[�v���f�[�^�x�[�X�ɃZ�b�g����
			groupList.AddData(tmpGroup);
		}else{
			nEmptyFile++;
			if(nEmptyFile > 100){
				// ��t�@�C�����������ꍇ�A���[�v�𔲂���
				break;
			}
		}
	}
	return true;
}

Data_EnemyGroup_Each* Data_EnemyGroup::GetEnemyGroup(WORD _refID){
	// �f�[�^�x�[�X���Q�Ƃ��A�w�肷��refID�������Ă�����̂�Ԃ��B
	// �Y��������̂��Ȃ��ꍇ��NULL��Ԃ��B
	Data_EnemyGroup_Each* pResult = NULL;
	int maxSize = groupList.GetSize();
	for(int n=0; n<maxSize; n++){
		pResult = groupList.GetPointerByIndex(n);
		if(pResult != NULL){
			if(pResult->GetRefID() == _refID){
				// �~����ID�ƈ�v������̂�����΂����Ԃ�
				return pResult;
			}
		}
	}
	return NULL;
}

