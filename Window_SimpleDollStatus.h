#ifndef WINDOW_SIMPLEDOLLINFO_H
#define WINDOW_SIMPLEDOLLINFO_H

#include "Window_Info.h"

class Game_BattleDoll;
class Game_AliceDoll;

#define DRAWPTN_ALLSTATUS		0	// �퓬�Ɋւ��邷�ׂẴX�e�[�^�X��\���B

//===================================
// Window_SimpleDollStatus�N���X
// 
// �l�`�̃p�����[�^���V���v���ɕ\������N���X�B
// �����̃V�[������Q�Ƃ���邱�Ƃ�z�肵�A
// ����̃V�[���ւ̃|�C���^�͕ێ����Ȃ��B
// Setup���ɐݒ肷��drawPattern�̒l�ɂ��
// �E�B���h�E�̑傫����`����e���ς��B
// �ʒu�̐ݒ�ɂ��Ă�SetPosition�֐�����s���A�������͍s��Ȃ��B
// ���́A�o�g���V�[���ɂ�����l�`�̃X�e�[�^�X�\����
// ����ȊO�̃V�[���ɂ�����l�`�̃X�e�[�^�X�\���i���҂̓N���X���قȂ�j��
// ���ʂ��ĕ\������A�N���o�e�B�b�N�ȃN���X�B

class Window_SimpleDollStatus : public Window_Info{
private:
	// �Q�Ƃ��Ă���l�`�B
	// �퓬�V�[���ł����pBattleDoll,
	// �L�����v�V�[���ł����pCampDoll���g�p����B
	Game_BattleDoll*		pBattleDoll;
	Game_AliceDoll*			pCampDoll;
	// �`��p�^�[���B
	// �\�������������ɕς���ꍇ�ɗp����B
	BYTE					drawPtn;
	// �퓬�V�[���ł����true�B
	bool					isBattle;

public:
	// �R���X�g���N�^
	Window_SimpleDollStatus();

	// �Z�b�g�A�b�v�B
	// �`��p�^�[���Ǝg�p����V�[�����Z�b�g����B
	// �E�B���h�E�̑傫���͕`��p�^�[���ɂ�莩���I�Ɍ��܂�B
	// �E�B���h�E�̈ʒu�̓E�B���h�E���J���Ƃ��Ɍ��肷��B
	void Setup(BYTE _drawPtn, bool _isBattle);

	// �Q�Ƃ���l�`���w�肵�ĊJ���B
	void OpenWithBattleDoll(Game_BattleDoll* pDoll, int _x, int _y);
	void OpenWithCampDoll(Game_AliceDoll* pDoll, int _x, int _y);

	// �Q�Ƃ��Ă���l�`��ύX����B
	// ���̎Q�ƂƈقȂ�ꍇ�A�\���������Ă���ďo��������B
	bool ChangeRefBattleDoll(Game_BattleDoll* pDoll);
	bool ChangeRefCampDoll(Game_AliceDoll* pDoll);

	// �X�V�B
	virtual void Update();

	// ���e�̕`��B
	virtual void DrawContent() const;

	// ���e�̕`��i�퓬�V�[���̏ꍇ�j
	virtual void DrawContent_Battle() const;

	// ���e�̕`��i�퓬�V�[���ȊO�̏ꍇ�j
	virtual void DrawContent_Camp() const;


};


#endif // WINDOW_SIMPLEDOLLINFO
