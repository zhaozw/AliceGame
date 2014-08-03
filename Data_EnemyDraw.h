#ifndef DATA_ENEMYDRAW_H
#define DATA_ENEMYDRAW_H

#include <Windows.h>
#include "VectorList.h"
#include "Static_AliceDoll.h"

// refID���ǂ̓G�ɑΉ����邩�̒萔���X�g
#define		ENEMYDRAW_SMALLFAIRY		1
#define		ENEMYDRAW_FAIRY				2
#define		ENEMYDRAW_L_SNAIL			3
#define		ENEMYDRAW_F_BUTTERFLY		4
#define		ENEMYDRAW_SHIKABANE			5
#define		ENEMYDRAW_WINDCROW			6
#define		ENEMYDRAW_HARPY				7
#define		ENEMYDRAW_HEALFAIRY			8
#define		ENEMYDRAW_INNOCENTBONE		9
#define		ENEMYDRAW_NECROMANCER		10


// �G�O���t�B�b�N�̕`��ʒu�ƕ`��n���h����ێ�����N���X�B
// �O���[�o���ϐ�g_enemyDraw����Q�Ƃ����B

class Data_EnemyDraw_Each{
private:
	// �Q��ID
	WORD	refID;
	// �`��̒��S�ʒu
	float	cx, cy;
	// �摜�̃T�C�Y
	int		iWidth, iHeight;
	// ��{�I�ȕ`��̔{��
	float	baseExRate;
	// �摜�̃n���h��(��������)
	int		hImg[DOLL_ATTR_NUM];
public:
	// �R���X�g���N�^
	Data_EnemyDraw_Each();
	// ������
	void Refresh();

	// �A�N�Z�T
	WORD	GetRefID(){ return refID; };
	void	SetRefID(WORD id){ refID = id; };
	float	GetCX(){ return cx; };
	float	GetCY(){ return cy; };
	void	SetCX(float x){ cx = x; };
	void	SetCY(float y){ cy = y; };
	int		GetHImg(BYTE attr){ return hImg[attr]; };
	void	SetHImg(BYTE attr, int h){ hImg[attr] = h; };
	int		GetIWidth(){ return iWidth; };
	int		GetIHeight(){ return iHeight; };
	void	SetIWidth(int i){ iWidth = i; };
	void	SetIHeight(int i){ iHeight = i; };
	float	GetExRate(){ return baseExRate; };
	void	SetExRate(float r){ baseExRate = r; };



};

class Data_EnemyDraw{
private:
	VectorList<Data_EnemyDraw_Each>		drawList;
public:
	// �R���X�g���N�^
	Data_EnemyDraw();
	
	// �f�[�^�̓ǂݍ���
	bool Load();
	bool LoadDataFromCsv();

	// ���X�g���J������
	void ReleaseList(){ drawList.Release(); };

	// Image�N���X�ƃn���h�������т���B
	int	GetImgHandleByRefID(WORD refID, BYTE attr);

	// �x�N�g���̒�����refID���Y������l��Ԃ��B
	Data_EnemyDraw_Each* GetEnemyDraw(WORD refID);

	// �傫����Ԃ��B
	int GetSize(){ return drawList.GetSize(); };
};

#endif // DATA_ENEMYDRAW_H