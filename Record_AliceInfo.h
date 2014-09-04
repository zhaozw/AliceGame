#ifndef Record_AliceInfo_H
#define Record_AliceInfo_H

#include <Windows.h>
#include "Static_AliceInfo.h"
#include "Static_AliceDoll.h"

// �A���X���g�̏������N���X�B
// �O���[�o���ϐ�r_aliceInfo����Q�Ƃ����B

struct Record_AliceInfo_Data{
	int chapter;		// ���̃t�@�C���Ńv���C���̏�
	int level;			// �A���X�̃��x���B
	int exp;			// �A���X�̐ώZ�o���l�B
	int mp;				// �A���X�̖���
	int maxMP;			// �ő喂��
	int day;			// �o�ߓ���
	int time;			// ���݂̓����ɂ����鎞��(0��00����0�Ƃ������A������)
	int timeToEat;		// ���ɗ���������܂ł̎���
	int pieceNum[DOLL_GROUP_NUM][DOLL_ATTR_NUM-1];		// ���ЃA�C�e���̐�
	bool dollRecepe[DOLL_TYPE_MAX+1];		// �l�`���쐬�\���ǂ���
	DWORD playTime;		// �v���C����(�b)
	DWORD savedYMD;		// �Z�[�u�����N�E���E��
	DWORD savedHMS;		// �Z�[�u�������ԁE���E�b
	
	Record_AliceInfo_Data(){
		chapter = 0;
		level = 0;
		mp = MAX_MP;
		maxMP = MAX_MP;
		day = 0;
		time = 0;
		timeToEat = 0;
		for(int j=0; j<DOLL_GROUP_NUM; j++){
			for(int i=0; i<(DOLL_ATTR_NUM-1); i++){
				pieceNum[j][i] = 10;
			}
		}
		dollRecepe[0] = false;
		for(int j=0; j<DOLL_GROUP_NUM; j++){
			for(int i=0; i<DOLL_TYPE_PER_GROUP; i++){
				// �e�^�C�v��ԃ��x���̒Ⴂ�l�`��������
				dollRecepe[i+j*DOLL_TYPE_PER_GROUP+1] = (i==0);
			}
		}
		playTime = 0;
		savedYMD = 0;
		savedHMS = 0;
	};
};

class Record_AliceInfo{
public:
	Record_AliceInfo_Data		data; // �f�[�^�ۑ��p�Ƀf�[�^�p�\���̂��쐬
	// �ۑ����Ȃ�
	DWORD					lastSavedWinTime;	// �Ō�ɃZ�[�u�������̃E�B���h�E�Y�̎���
public:
	Record_AliceInfo();

	// �o�C�g�񂩂�f�[�^�ɓ��e���R�s�[����
	bool LoadFromBytes(LPVOID pBytes, DWORD fileSize);
	// ���݂̌������Ԃ�������B
	void GetCntTime(bool load=false);

	// MP��ݒ肷��B
	void SetMP(int p){ data.mp = p; data.maxMP = max(data.maxMP, p); };
	// MP�𑝂₷�B����Ȃǂ̔�����g�p����B
	// �w�肵���l�������₹�Ȃ������ꍇ�Ffalse
	bool AddMP(int p);
	// MP�����炷�B�����Ȃǂ̔�����g�p����B
	// �w�肵���l�������点�Ȃ������ꍇ�Ffalse
	bool SubMP(int p);
};

#endif // Record_AliceInfo_H