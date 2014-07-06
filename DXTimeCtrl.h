#ifndef DXTIMECTRL_H
#define DXTIMECTRL_H

#include "DxLib.h"
#include "Static_Game.h"

//////////////////////////////////////////////////
// DXTimeCtrl�N���X
// DX���C�u�����ɂ����ăt���[�����[�g������s�Ȃ��B
// Scene�֘A�̃N���X�̃����o�B

class DXTimeCtrl{
	////////////////////////////////////
	// �����Ŏg�p����p�����[�^
	
	// ���z�I��1�t���[��������̎���
	int idealTime; 
	// ���ۂ̎���
	int frameTime;
	// ���݂̎��Ԃ��擾
	int curTime;
	// �x��Ă��鎞��
	int waitTime;
	// �A���Ŕ�΂����t���[����
	int skipNum;
	// �t���[�����[�g�v���p�̃J�E���^
	// (FPS�̒l�ɂȂ������Ƀt���[�����[�g�l���X�V����)
	int rateCounter;
	// �t���[��������̎��Ԃ̐ώZ
	int rateTime;
	// �O��̃t���[�����[�g�l(����1���܂ł̒l��10�{��������)
	// ��Ƃ���58.2fps�̎���582
	int lastFrameRate;
	// ���������̉��o
	int delayPerFrame;

	////////////////////////////////////
	// �O�Ɍ�����p�����[�^
	
	// �x��Ă��鎞�ɕ`����ȗ����邩�ǂ���
	bool fSkipFrame;
	// �`�悷�邩�ǂ���
	bool drawFlag;
	
public:
	// �R���X�g���N�^
	DXTimeCtrl();

	// �f�X�g���N�^
	~DXTimeCtrl();
	
	// ���Ԃ̐�����s�Ȃ�
	void Regulate();
	// �ꍇ�ɂ���Ď��ԑ҂����s�Ȃ�
	void Wait();
	
	// �`��t���O��true��false��
	bool GetDrawFlag(){ return drawFlag; };
	// fSkipFrame�ɒl���Z�b�g����
	void SetSkipFrame(bool b){ fSkipFrame = b; };
	// �l�����Z�b�g
	void Reset();
	// ���������̉��o���s��
	void SetArtificialDelay(int _delayPerFrame){ delayPerFrame = _delayPerFrame; };
	
	// FPS�l��`�悷��
	// (DX���C�u�����̕����`��𗘗p�A���オ(x,y)
	void DrawFPS(int x, int y, int size=24);
};

#endif