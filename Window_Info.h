#ifndef WINDOW_INFO_H
#define WINDOW_INFO_H

#include "Window_Text.h"
#include "DXInput.h"

// ContentChanged�����s����Ă���opacity�����ɖ߂�܂ł̎���
#define CONTENT_CHANGED_DELAY	12

//===============================================================
// ���֘A�̃E�B���h�E���쐬����B
// ���E�B���h�E�L�[�������ƊJ���ē��e��\�����A
// ����L�[�E�L�����Z���L�[�E���E�C���h�E�L�[�̂����ꂩ���������ƕ���B
// ���̃N���X�͒��ۃN���X�ł͂Ȃ����A���̃N���X���̂͋@�\���������A�e�N���X�ɔh������B
// ��{�I�ɁA�h���N���X���܂߂ē����t�H���g���g�p����B

class Window_Info : public Window_Text{
protected:
	// �\������e�L�X�g�̕s�����x�B
	// �J�[�\���ύX�Ńe�L�X�g���ς��������
	// ��U�����x�������ĕ`�悷�邱�Ƃɂ��
	// �Ώۂ��ς�������Ƃ����₷������B
	int opacity;

	// ContentChanged�����s����Ă���̎��ԁB
	int changedTime;
public:
	// �R���X�g���N�^
	Window_Info();

	// ���e�̃Z�b�g�A�b�v�B
	// �t�H���g�̓f�t�H���g�̂��̂��g�p���邽�ߎw�肷��K�v���Ȃ��B
	// �E�B���h�E�̃Z�b�g�A�b�v���s���B
	// ���̎����ɓ��e�̓Z�b�g����Ă��āA
	// column�l�y��row�l�����܂��Ă���B
	// �����ł͑傫���Ȃǂ����߂�B
	bool	Setup(
		WindowSkin* _pSkin,
		WINDOWAREA _frameArea,
		WINDOWAREA _contentArea
		);

	// ���̃E�B���h�E����������V�[������Ăяo�����B
	// ���E�B���h�E�Ăяo���L�[��������Ă���ꍇ�A�E�B���h�E���J���B
	// �J�����ꍇ��true��Ԃ��B���̊֐����̂�Open���s���B
	// �J�������ɓ��삪�K�v�ȏꍇ��OnOpened�֐���p����B
	bool OpenIfCalled();

	// �e�h���N���X�Ŏ��s����B
	// ����L�[���L�����Z���L�[�������ꂽ���ɕ���B
	// true�̎�����B���̊֐����̂�Close�͍s��Ȃ��B
	// (�e�N���X�ɂ�苓�����قȂ邽��)
	bool CheckClose();

	// �\���L�[�̓��͂��l�����Ŏ擾����B
	// �l��DIGDIR_XXX�ŕԂ��B
	// g_input�̊֐����Ă�ł��邾���B
	BYTE GetDigDir();

	// �E�B���h�E���J�����܂ܓ��e���ς�����ꍇ�Ɏ��s����B
	// opacity�̒l����U0�ɂ��A���������Č��ɖ߂��B
	// �e�N���X��SetDrawBlendMode�֐����g�p���Ȃ��ƈӖ����Ȃ��̂Œ��ӁB
	void ContentChanged();

	// ���e�̍X�V(�J���ꂽ��̓���y��CheckClose�A
	// ���e���؂�ւ�����ۂ̕s�����x�̒������s��)
	virtual void Update();

	// ���e�̕`��(���e�Ȃ�)
	virtual void DrawContent() const{};


};

#endif // WINDOW_INFO_H