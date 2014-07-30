#ifndef DATA_ENEMYGROUP_H
#define DATA_ENEMYGROUP_H

#include "Static_Battle.h"
#include "VectorList.h"

// �G�O���[�v���̓G��̂�\���\����
typedef struct EnemyInGroup{
	WORD		refID;		// �GID�BData_EnemyParam�N���X�̎Q��ID���w�肷��B
	int			drawX;		// �`��ʒu�̒��S�B
	int			drawY;		// ��{�I��y���W�̏����Ńf�[�^���L�^����B
	EnemyInGroup(){
		refID = 0;
		drawX = 0;
		drawY = 0;
	}
} ENEMYINGROUP;

// �G�O���[�v���\���N���X�B
// Data_EnemyGroup�N���X��FlexList�Ƃ��ĕێ������B
class Data_EnemyGroup_Each{
private:
	// �G�O���[�vID�B�}�b�v�Ȃǂ���Q�Ƃ����B
	WORD		refID;		
	// �e�G�L�����B
	ENEMYINGROUP		enemy[MAX_BATTLEENEMY];
public:
	// �R���X�g���N�^
	Data_EnemyGroup_Each();
	void Refresh();
	// �A�N�Z�T
	void	SetRefID(WORD _refID){ refID = _refID; };
	WORD	GetRefID(){ return refID; };
	void	SetEnemyRefID(int index, WORD _refID){
		if(IsIndex(index)) enemy[index].refID = _refID;
	}
	WORD	GetEnemyRefID(int index){
		if(IsIndex(index)) return enemy[index].refID;
		return 0;
	}
	void	SetEnemyDrawX(int index, int _drawX){
		if(IsIndex(index)) enemy[index].drawX = _drawX;
	}
	WORD	GetEnemyDrawX(int index){
		if(IsIndex(index)) return enemy[index].drawX;
		return 0;
	}
	void	SetEnemyDrawY(int index, int _drawY){
		if(IsIndex(index)) enemy[index].drawY = _drawY;
	}
	WORD	GetEnemyDrawY(int index){
		if(IsIndex(index)) return enemy[index].drawY;
		return 0;
	}
	bool	IsIndex(int index){ return index >= 0 && index < MAX_BATTLEENEMY; };
};

// �G�O���[�v�̃f�[�^��ێ�����N���X�B
// �O���[�o���ϐ�d_enemyGroup����Q�Ƃ����B
class Data_EnemyGroup{
private:
	// �G�O���[�v�̔z��
	VectorList<Data_EnemyGroup_Each>		groupList;

public:
	// �R���X�g���N�^
	Data_EnemyGroup();
	// ���[�h
	bool Load();
	bool LoadDataFromCsv();

	// Vector���X�g���Ӑ}�I�ɊJ������
	void ReleaseList(){ groupList.Release(); };

	// �G�O���[�v�ւ̃|�C���^���擾����B
	// �f�[�^�x�[�X���Q�Ƃ��A�w�肷��refID�������Ă�����̂�Ԃ��B
	// �Y��������̂��Ȃ��ꍇ��NULL��Ԃ��B
	Data_EnemyGroup_Each* GetEnemyGroup(WORD _refID);
};

#endif // DATA_ENEMYGROUP_H