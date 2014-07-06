#ifndef CONFIG_H
#define CONFIG_H

#include <Windows.h>
#include "Static_Game.h"

//========================================
// �R���t�B�O�Ɋւ���萔

// �E�B���h�E�T�C�Y�̗�
#define WNDSIZE_W0			320
#define WNDSIZE_H0			240
#define WNDSIZE_W1			512
#define WNDSIZE_H1			384
#define WNDSIZE_W2			640
#define WNDSIZE_H2			480
#define WNDSIZE_W3			800
#define WNDSIZE_H3			600
#define WNDSIZE_W4			960
#define WNDSIZE_H4			720

// �f�t�H���g�̃E�B���h�E�T�C�Y
#define DEF_WNDSIZE			2
#define DEF_SCREENTYPE		2
#define DEF_WND_WIDTH		(WND_WIDTH)
#define DEF_WND_HEIGHT		(WND_HEIGHT)
#define DEF_SCRN_WIDTH		640
#define DEF_SCRN_HEIGHT		480

#define MAX_VOLUME			100
#define DEF_VOLUME_SE		100
#define DEF_VOLUME_BGM		80

//========================================
// Config�N���X
// �Q�[���S�̂Ɋւ��ݒ�������N���X�B
// ��ɃI�v�V�����ŕύX�\�ȏ����Ǘ�����B
// ini�t�@�C���𒼐ڂ����邱�Ƃ��o���邪�A���[�h�̍ۂ�
// �l���`�F�b�N���邽�ߕs���Ȓl�͓�����Ȃ��B
// 
class Config{
	//========================================
	// �ϐ�
public:
	//=========================================
	// ��ʐݒ�֘A
	bool	fullScreen;	// �t���X�N���[���̎���true�B
						// �R���t�B�O�ł͒��ڎw�肵�Ȃ��B
	int		windowWidth; // �E�B���h�E���[�h�ł̕`��𑜓x
	int		windowHeight;
	int		screenWidth; // �t���X�N���[�����̕`��𑜓x�B
	int		screenHeight;
	TCHAR	windowSize; // �E�B���h�E�T�C�Y���w�肷��ID�B
							// 0 : 320�~240
							// 1 : 512�~384
							// 2 : 640�~480
							// 3 : 800�~600(�f�t�H���g)
							// 4 : 960�~720
	TCHAR	screenType; // �Q�[���J�n���̐ݒ�B
						// 0 : ����I������B
						// 1 : �t���X�N���[���B
						// 2 : �E�B���h�E���[�h�B

	// ���ʊ֘A
	unsigned char SE;				// 0�`100�Ŏw��B���ʉ��̉��ʂ�ݒ肷��B
	unsigned char BGM;				// 0�`100�Ŏw��BBGM�̉��ʂ�ݒ肷��B

	// �R�}�����E���������̐ݒ�
	bool skipFrame;

	//========================================
	// �֐�
	Config();

	bool SetScreenMode();	// �t���X�N���[�����̉�ʃ��[�h�𒲐�
	void SetWindowSize();	// �E�B���h�E�T�C�Y�̒l����̓I�Ȓl�ɕϊ�����B
	bool LoadConfig();
	bool SaveConfig();
};

#endif // CONFIG_H