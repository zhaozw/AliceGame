#ifndef BWINDOW_DOLLSKILL_H
#define BWINDOW_DOLLSKILL_H

#include "Window_Selectable.h"

#define BWND_DOLLSKILL_X		150
#define BWND_DOLLSKILL_Y		400
#define BWND_DOLLSKILL_W		500
#define BWND_DOLLSKILL_H		200
#define BWND_DOLLSKILL_PX		16
#define BWND_DOLLSKILL_PY		16

class Scene_Battle;
class Game_BattleDoll;

// BWindow_DollSkill�N���X
// �퓬���ɐl�`�̓��Z�ꗗ��\������N���X�B

class BWindow_DollSkill : public Window_Selectable{
private:
	// ���̃E�B���h�E��ێ�����V�[���ւ̃|�C���^�B
	Scene_Battle*		pScene;
	// �Q�Ƃ��Ă���l�`�ւ̃n���h��
	Game_BattleDoll*		pOwner;
public:
	BWindow_DollSkill();

	// �Z�b�g�A�b�v
	void MySetup(Scene_Battle* _pScene);

	// �l�`�ւ̃n���h����n���B
	void SetDoll(Game_BattleDoll* p){ pOwner = p; };

	// �J�������̋���
	virtual void OnOpened();

	// ���e�̃A�b�v�f�[�g���s���B
	virtual void Update();			// �N���X���Ƃɔh������A�b�v�f�[�g�֐��B

	// ���e�̕`����s���B
	virtual void DrawContent() const;

};

#endif // BWINDOW_DOLLSKILL_H