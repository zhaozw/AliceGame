#ifndef DATA_ENEMYGROUP_H
#define DATA_ENEMYGROUP_H

#include "Static_Battle.h"
#include "VectorList.h"
#include "Static_AliceDoll.h"

#define CSVFILE_ENEMYGROUP _T("dat_egroup\\group%03d.csv")
#define DATFILE_ENEMYGROUP _T("dat\\enemygroup.dat")

// �G�O���[�v���̓G��̂�\���\����
typedef struct EnemyInGroup{
	WORD		refID;		// �GID�BData_EnemyParam�N���X�̎Q��ID���w�肷��B
	int			drawX;		// �`��ʒu�̒��S�B
	int			drawY;		// ��{�I��y���W�̏����Ńf�[�^���L�^����B
	BYTE		attr;		// �����B-1�̏ꍇ�̓����_���Ō��܂�B
	EnemyInGroup(){
		refID	= 0;
		drawX	= 0;
		drawY	= 0;
		attr	= DOLL_ATTR_RANDOM;
	}
} ENEMYINGROUP;

// �G�O���[�v���\���\���́B
typedef struct Data_EnemyGroup_Data{
	// �G�O���[�vID�B�}�b�v�Ȃǂ���Q�Ƃ����B
	WORD				refID;		
	// �e�G�L�����B
	ENEMYINGROUP		enemy[MAX_BATTLEENEMY];
	Data_EnemyGroup_Data(){
		refID = 0;
		for(int n=0; n<MAX_BATTLEENEMY; n++){
			enemy[n] = ENEMYINGROUP();
		}
	}
} DATA_ENEMYGROUP_DATA;

// �G�O���[�v�̃f�[�^��ێ�����N���X�B
// �O���[�o���ϐ�d_enemyGroup����Q�Ƃ����B
class Data_EnemyGroup{
private:
	// �G�O���[�v�̔z��
	VectorList<Data_EnemyGroup_Data>		groupList;

public:
	// �R���X�g���N�^
	Data_EnemyGroup();
	// ���[�h
	bool Load();
	bool LoadDataFromCsv();
	bool LoadDataFromDat();

	bool EncodeCsv();

	// Vector���X�g���Ӑ}�I�ɊJ������
	void ReleaseList(){ groupList.Release(); };

	// �G�O���[�v�ւ̃|�C���^���擾����B
	// �f�[�^�x�[�X���Q�Ƃ��A�w�肷��refID�������Ă�����̂�Ԃ��B
	// �Y��������̂��Ȃ��ꍇ��NULL��Ԃ��B
	Data_EnemyGroup_Data* GetEnemyGroup(WORD _refID);


	// �傫����Ԃ��B
	int GetSize(){ return groupList.GetSize(); };
};

#endif // DATA_ENEMYGROUP_H