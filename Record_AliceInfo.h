#ifndef Record_AliceInfo_H
#define Record_AliceInfo_H

#include <Windows.h>
#include "Static_AliceInfo.h"
#include "Static_AliceDoll.h"

// �A���X���g�̏������N���X�B
// �O���[�o���ϐ�r_aliceInfo����Q�Ƃ����B

typedef struct Record_AliceInfo_Data{
	WORD chapter;		// ���̃t�@�C���Ńv���C���̏�
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
} RECORD_ALICEINFO_DATA;

class Record_AliceInfo{
private:
	RECORD_ALICEINFO_DATA	data; // �f�[�^�ۑ��p�Ƀf�[�^�p�\���̂��쐬
	// �ۑ����Ȃ�
	DWORD					lastSavedWinTime;	// �Ō�ɃZ�[�u�������̃E�B���h�E�Y�̎���
public:
	Record_AliceInfo();

	// �o�C�g�񂩂�f�[�^�ɓ��e���R�s�[����
	bool LoadFromBytes(LPVOID pBytes, DWORD fileSize);
	// ���݂̌������Ԃ�������B
	void GetCntTime(bool load=false);

	// �A�N�Z�T
	WORD GetChapter(){ return data.chapter;};
	void SetChapter(WORD _chapter){ data.chapter = _chapter; };

	// �l�`���쐬�\���ǂ������擾����
	bool GetHaveDollRecepe(int index){ return data.dollRecepe[index]; };

	// �l�`�쐬�̂��߂̐΂̐����擾����
	int GetPieceNum(int group, int attr){ return data.pieceNum[group][attr]; };
	// �΂𑝌�������B
	void AddPieceNum(int group, int attr, int num=1){ data.pieceNum[group][attr] += num; };
	bool ReducePieceNum(int group, int attr, int num=1){
		data.pieceNum[group][attr] -= num;
		if(data.pieceNum[group][attr] < 0){
			data.pieceNum[group][attr] = 0;
			return false;
		}
		return true;
	};

	// MP��ݒ肷��B
	void SetMP(int p){ data.mp = p; data.maxMP = max(data.maxMP, p); };
	// MP�𑝂₷�B����Ȃǂ̔�����g�p����B
	// �w�肵���l�������₹�Ȃ������ꍇ�Ffalse
	bool AddMP(int p);
	// MP�����炷�B�����Ȃǂ̔�����g�p����B
	// �w�肵���l�������点�Ȃ������ꍇ�Ffalse
	bool SubMP(int p);
	// MP���擾����B
	int GetMP(){ return data.mp; };

	// ���Ԃ��擾����
	DWORD GetSavedYMD(){ return data.savedYMD; };
	DWORD GetSavedHMS(){ return data.savedHMS; };

	// �v���C���Ԃ��擾����
	DWORD GetPlayTime(){ return data.playTime; };

	// �f�[�^�̍\���̑S�̂�n���B
	RECORD_ALICEINFO_DATA GetData(){ return data; };
};

#endif // Record_AliceInfo_H