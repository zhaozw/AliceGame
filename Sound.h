#ifndef SOUND_H
#define SOUND_H

#include <Windows.h>

class Sound;

// �Q�[���Ŏg�p����BGM�̍ő吔���`����B
#define MYGAME_MAX_BGM	10

// �Q�[���Ŏg�p����BGM��ID��񋓂���B
#define BGM_DUMMY		0
#define BGM_MENU		1
#define BGM_BATTLE		2

// �Q�[���Ŏg�p����SE�̍ő吔���`����B
#define MYGAME_MAX_SE	30

// �Q�[���Ŏg�p����SE��ID��񋓂���B
#define SE_DUMMY		0

//==================================================
// BGM�N���X
// 
// �摜�̃n���h�����܂Ƃ߂ĕێ�����O���[�o���ϐ��B

class BGM{
	friend class Sound;
	int handle; // �Ȃ̃n���h��
	int loopPos; // ���[�v�ʒu
	bool noLoop;
	int playPos; // �Ȃ̌��݂̍Đ��ʒu
public:
	// �R���X�g���N�^
	BGM();
	int GetHandle(){ return handle; };
	int GetLoopPos(){ return loopPos; };
};

//==================================================
// Sound�N���X
// 
// �摜�̃n���h�����܂Ƃ߂ĕێ�����O���[�o���ϐ��B
// �O���[�o���ϐ�g_sound����Q�Ƃ����B
// 

class Sound{
private:
	// BGM�Q��[�߂�n���h���B
	BGM	bgm[MYGAME_MAX_BGM];
	// SE�Q��[�߂�n���h���B
	int se[MYGAME_MAX_SE];
public:
	// �R���X�g���N�^�B
	// �S�Ẵn���h����-1��������B
	Sound();

	// ���[�h�B
	// ���s������false��Ԃ��B
	bool LoadMusic();
	bool LoadSound();

	// BGM���AID�A�t�@�C�����A���[�v�ʒu���w�肵�ēǂݍ��ށB
	bool LoadBGM(WORD id, LPTSTR fileName, int loopPos, bool noLoop=false);

	// BGM�̍Đ����s���B
	bool PlayBGM(WORD bgmID, bool recall);

	// BGM�̍Đ����~�߂�B
	void StopBGM(WORD bgmID);

	// BGM�̍Đ����ꎞ�I�ɒ�~������B
	

	// �SBGM�̍Đ����~�߂�B
	void StopAllBGM();

	// BGM�̃{�����[����ύX����B
	void SetVolumeBGM(WORD bgmID,int param);

	// SE�̍Đ����s���B
	bool PlaySE(WORD seID, float volRate, bool reCall=true, bool stop=false);

};

bool CallMusic(int hMsc, bool reset, bool noLoop);

bool CallSound(int hSnd, float volRate, bool reCall, bool stop);

long CalcDB(int sound_val); 



#endif // SOUND_H