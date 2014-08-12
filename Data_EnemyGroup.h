#ifndef DATA_ENEMYGROUP_H
#define DATA_ENEMYGROUP_H

#include "Static_Battle.h"
#include "VectorList.h"
#include "Static_AliceDoll.h"

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
typedef struct Data_EnemyGroup_Each_Data{
	// �G�O���[�vID�B�}�b�v�Ȃǂ���Q�Ƃ����B
	WORD				refID;		
	// �e�G�L�����B
	ENEMYINGROUP		enemy[MAX_BATTLEENEMY];
} DATA_ENEMYGROUP_EACH_DATA;

// �G�O���[�v���\���N���X�B
// Data_EnemyGroup�N���X��FlexList�Ƃ��ĕێ������B
class Data_EnemyGroup_Each{
private:
	DATA_ENEMYGROUP_EACH_DATA		data;
public:
	// �R���X�g���N�^
	Data_EnemyGroup_Each();
	void Refresh();
	// �A�N�Z�T
	void	SetRefID(WORD _refID){ data.refID = _refID; };
	WORD	GetRefID(){ return data.refID; };
	void	SetEnemyRefID(int index, WORD _refID){
		if(IsIndex(index)) data.enemy[index].refID = _refID;
	}
	WORD	GetEnemyRefID(int index){
		if(IsIndex(index)) return data.enemy[index].refID;
		return 0;
	}
	void	SetEnemyDrawX(int index, int _drawX){
		if(IsIndex(index)) data.enemy[index].drawX = _drawX;
	}
	WORD	GetEnemyDrawX(int index){
		if(IsIndex(index)) return data.enemy[index].drawX;
		return 0;
	}
	void	SetEnemyDrawY(int index, int _drawY){
		if(IsIndex(index)) data.enemy[index].drawY = _drawY;
	}
	WORD	GetEnemyDrawY(int index){
		if(IsIndex(index)) return data.enemy[index].drawY;
		return 0;
	}
	void	SetEnemyAttr(int index, BYTE _attr){
		if(IsIndex(index)) data.enemy[index].attr = _attr;
	}
	BYTE	GetEnemyAttr(int index){
		if(IsIndex(index)) return data.enemy[index].attr;
		return DOLL_ATTR_NONE;
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


	// �傫����Ԃ��B
	int GetSize(){ return groupList.GetSize(); };
};

#endif // DATA_ENEMYGROUP_H