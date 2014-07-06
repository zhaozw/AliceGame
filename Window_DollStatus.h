#ifndef WINDOW_DOLLSTATUS_H
#define WINDOW_DOLLSTATUS_H

#include "Window_Text.h"
#include "Game_AliceDoll.h"

#define WND_DOLLSTATUS_WIDTH		300
#define WND_DOLLSTATUS_HEIGHT		500
#define WND_DOLLSTATUS_PX			32
#define WND_DOLLSTATUS_PY			32

class Window_DollStatus : public Window_Text{
private:
	// �X�e�[�^�X��\������l�`�ւ̎Q�ƁB
	Game_AliceDoll_Essence*	pDoll;
public:
	// �R���X�g���N�^
	Window_DollStatus();

	// �E�B���h�E�̃Z�b�g�A�b�v
	bool Setup(int _x, int _y);
	// �l�`�̃Z�b�g�B�\���ɕK�v�ȃp�����[�^�Ȃǂ̌v�Z���s���B
	bool SetDoll(Game_AliceDoll_Essence* p);

	// ���e�̍X�V���s���B
	virtual void Update();

	// ���e�̕`����s���B
	// �N���X���Ƃɔh������B
	virtual void DrawContent() const;
};

#endif // WINDOW_DOLLSTATUS_H