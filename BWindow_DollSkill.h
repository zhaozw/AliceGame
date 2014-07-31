#ifndef BWINDOW_DOLLSKILL_H
#define BWINDOW_DOLLSKILL_H

#include "Window_Selectable.h"
#include "Window_LineInfo.h"

#define BWND_DOLLSKILL_W		500
#define BWND_DOLLSKILL_H		150
#define BWND_DOLLSKILL_X		150
#define BWND_DOLLSKILL_Y		(WND_HEIGHT-WND_LINEINFO_HEIGHT-BWND_DOLLSKILL_H)
#define BWND_DOLLSKILL_PX		16
#define BWND_DOLLSKILL_PY		16

class Scene_Battle;
class Game_BattleDoll;
class Game_BattleUnit;

class BWindow_DollCommand;

// BWindow_DollSkill�N���X
// �퓬���ɐl�`�̓��Z�ꗗ��\������N���X�B

class BWindow_DollSkill : public Window_Selectable{
private:
	// ���̃E�B���h�E��ێ�����V�[���ւ̃|�C���^�B
	Scene_Battle*		pScene;
	// �Q�Ƃ��Ă���l�`�ւ̃n���h��
	Game_BattleDoll*	pOwner;
	// �^�[�Q�b�g�I���E�B���h�E�̑I��l
	// �S�̑I���������肵���ꍇ��NULL�ɂȂ�
	Game_BattleUnit*	pTarget;
	// �R�}���h�E�B���h�E�ւ̃|�C���^
	BWindow_DollCommand* pWndCommand;
public:
	BWindow_DollSkill();

	// �Z�b�g�A�b�v
	// BWindow_DollCommand��n���̂́A���E�B���h�E�ɃA�N�Z�X���邽�߁B
	void MySetup(Scene_Battle* _pScene, BWindow_DollCommand* _pWndCommand);

	// �l�`�ւ̃n���h����n���B
	void SetDoll(Game_BattleDoll* p){ pOwner = p; };

	// �J�������̋���
	virtual void OnOpened();

	// �q���������̋���
	virtual void OnChildIsClosed();

	// �C���f�b�N�X���ω������A�܂��͊J�����Ƃ��̋���
	void OnIndexChanged();

	// ���e�̃A�b�v�f�[�g���s���B
	virtual void Update();			// �N���X���Ƃɔh������A�b�v�f�[�g�֐��B

	// ���ڂ�I����A�����ŕ��邩�ǂ����̔�����s��
	virtual void CheckAutoClose(){ autoClose = false; };

	// ���݂̍��ڂ��L�����Z���\�ł��邩�ǂ����̔�����s��
	// �X�L���E�B���h�E�͏�ɃL�����Z���\�B
	virtual void CheckCancelable(){ cancelable = true; };

	// ���e�̕`����s���B
	virtual void DrawContent() const;

	// �^�[�Q�b�g���擾����B
	Game_BattleUnit* GetTarget(){ return pTarget; };

};

#endif // BWINDOW_DOLLSKILL_H