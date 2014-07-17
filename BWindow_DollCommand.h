#ifndef BWINDOW_DOLLCOMMAND_H
#define BWINDOW_DOLLCOMMAND_H

#include "Window_Selectable.h"
#include "Game_BattleDoll.h"

#define BWND_DOLLCOMMAND_X		100
#define BWND_DOLLCOMMAND_Y		400
#define BWND_DOLLCOMMAND_W		300
#define BWND_DOLLCOMMAND_H		200
#define BWND_DOLLCOMMAND_PX	16
#define BWND_DOLLCOMMAND_PY	16

#define BWND_DOLLCOMMAND_ATTACK		0
#define BWND_DOLLCOMMAND_SKILL		1
#define BWND_DOLLCOMMAND_GUARD		2

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
public:
	// �R���X�g���N�^
	BWindow_DollCommand();

	// �J���x�Ƀ��t���b�V������
	void		Refresh();

	// �A�N�Z�T
	int			GetCommandIndex(){ return commandIndex; };
	int			GetSubIndex(){ return subIndex; };

	// �q�E�B���h�E���������̋���
	virtual void OnChildIsClosed();

	// �Z�b�g�A�b�v
	void MySetup(Scene_Battle* _pScene);

	// ���s�҂��w�肵�ăE�B���h�E���J��
	void OpenWithActor(Game_BattleDoll* pDoll);

	// ���e�̃A�b�v�f�[�g���s���B
	virtual void Update();			// �N���X���Ƃɔh������A�b�v�f�[�g�֐��B

	//
	virtual void CheckAutoClose();

	// ���e�̕`����s���B
	virtual void DrawContent() const;

	// �E�B���h�E�����Ƃ��A���݂̃R�}���h���e������
	// Scene_Battle�N���X�̃A�N�V�����X�^�b�N�ɓ��e��ǉ�����B
	bool SetCommandAndClose();

	// �E�B���h�E�����֐��̏㏑��
	virtual BYTE Close(bool force=false, bool sudden=false);

};


#endif // BWINDOW_DOLLCOMMAND_H