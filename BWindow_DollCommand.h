#ifndef BWINDOW_DOLLCOMMAND_H
#define BWINDOW_DOLLCOMMAND_H

#include "Window_Selectable.h"
#include "Game_BattleDoll.h"

#define BWND_DOLLCOMMAND_X		60
#define BWND_DOLLCOMMAND_Y		380
#define BWND_DOLLCOMMAND_W		180
#define BWND_DOLLCOMMAND_H		200
#define BWND_DOLLCOMMAND_PX		24
#define BWND_DOLLCOMMAND_PY		24

#define BWND_DOLLCOMMAND_ATTACK		0
#define BWND_DOLLCOMMAND_SKILL		1
#define BWND_DOLLCOMMAND_GUARD		2

#define BWND_DOLLCOMMAND_PHAZE_NONE		0	// �G���[
#define BWND_DOLLCOMMAND_PHAZE_MAIN		1	// �R�}���h�I��
#define BWND_DOLLCOMMAND_PHAZE_SKILL	2	// �X�L���I��
#define BWND_DOLLCOMMAND_PHAZE_TARGET	3	// �^�[�Q�b�g�I��

class Scene_Battle;

class BWindow_DollCommand : public Window_Selectable{
private:
	// ���̃E�B���h�E��ێ�����V�[���ւ̃|�C���^�B
	Scene_Battle*		pScene;
	// ���̃E�B���h�E�ŃR�}���h��I�����Ă���l�`�ւ̃|�C���^�B
	Game_BattleDoll*	pActor;
	// ���ʂ�Scene_Battle�Ȃǂɓn�����߂ɕێ����Ă����C���f�b�N�X
	int			commandIndex;
	// �T�u�R�}���h�̌��ʂ��󂯎��C���f�b�N�X
	int			subIndex;
	// �I�������^�[�Q�b�g�̃C���f�b�N�X��ێ�����
	int			targetIndex;
	// �L�����Z���\���ۂ�
	bool		cancelable;
	// �E�B���h�E�̃t�F�C�Y�B
	BYTE		phaze;
public:
	// �R���X�g���N�^
	BWindow_DollCommand();

	// �J���x�Ƀ��t���b�V������
	void		Refresh();

	// �A�N�Z�T
	int			GetCommandIndex(){ return commandIndex; };
	int			GetSubIndex(){ return subIndex; };
	BYTE		GetPhaze(){ return phaze; };
	void		SetPhaze(BYTE p){ phaze = p; }; // �O������A�N�Z�X����ꍇ

	// �q�E�B���h�E���������̋���
	virtual void OnChildIsClosed();

	// �Z�b�g�A�b�v
	void MySetup(Scene_Battle* _pScene);

	// ���s�҂��w�肵�ăE�B���h�E���J��
	void OpenWithActor(Game_BattleDoll* pDoll, bool cancelable);

	// �R�}���h�I���̉ۂ��w��
	virtual void OnOpened();

	// ���e�̃A�b�v�f�[�g���s���B
	virtual void Update();			// �N���X���Ƃɔh������A�b�v�f�[�g�֐��B

	// �����ŕ��邩�͏ꍇ�ɂ���ĕς��B
	virtual void CheckAutoClose();

	// ���݂̍��ڂ��L�����Z���\�ł��邩�ǂ����̔�����s��
	// �L�����Z���\���ǂ����͊J�����Ɍ��܂�B
	virtual void CheckCancelable(){};

	// ���e�̕`����s���B
	virtual void DrawContent() const;

	// �E�B���h�E�����Ƃ��A���݂̃R�}���h���e������
	// Scene_Battle�N���X�̃A�N�V�����X�^�b�N�ɓ��e��ǉ�����B
	bool SetCommandAndClose();

	// �E�B���h�E�����֐��̏㏑��
	virtual BYTE Close(bool force=false, bool sudden=false);

	// �Z�̃^�[�Q�b�g�^�C�v��targetType�ɕϊ�����
	// (�l�`�����猩���l�ɕϊ�����)
	static BYTE ConvertSkillTargetToTarget(BYTE skillTarget);

};


#endif // BWINDOW_DOLLCOMMAND_H