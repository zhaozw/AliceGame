#ifndef DATA_ENEMYDRAW_H
#define DATA_ENEMYDRAW_H

#include <Windows.h>
#include "VectorList.h"
#include "Static_AliceDoll.h"

// �ǂݍ��ݐ�̃t�@�C����
#define		CSVFILE_ENEMYDRAW			_T("dat\\enemydraw.csv")
#define		DATFILE_ENEMYDRAW			_T("dat\\enemydraw.dat")

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

typedef struct Data_EnemyDraw_Data{
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
	// �R���X�g���N�^
	Data_EnemyDraw_Data(){
		refID = -1;
		cx = cy = 0;
		iWidth = iHeight = 1;
		baseExRate = 1.0;
		for(int i=0; i<DOLL_ATTR_NUM; i++){
			hImg[i] = -1;
		}
	}
	// �A�N�Z�T
	/*
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
	*/
} DATA_ENEMYDRAW_DATA;

class Data_EnemyDraw{
private:
	VectorList<DATA_ENEMYDRAW_DATA>		drawList;
public:
	// �R���X�g���N�^
	Data_EnemyDraw();
	
	// �f�[�^�̓ǂݍ���
	bool Load();
	bool LoadDataFromCsv();
	bool LoadDataFromDat();

	// �f�[�^�̈Í���
	bool EncodeCsv();

	// ���X�g���J������
	void ReleaseList(){ drawList.Release(); };

	// Image�N���X�ƃn���h�������т���B
	int	GetImgHandleByRefID(WORD refID, BYTE attr);

	// �x�N�g���̒�����refID���Y������l��Ԃ��B
	Data_EnemyDraw_Data* GetEnemyDraw(WORD refID);

	// �傫����Ԃ��B
	int GetSize(){ return drawList.GetSize(); };
};

#endif // DATA_ENEMYDRAW_H