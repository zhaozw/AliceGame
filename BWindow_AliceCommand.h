#ifndef BWINDOW_ALICECOMMAND_H
#define BWINDOW_ALICECOMMAND_H

#include "Window_Selectable.h"

#define BWND_ALICECOMMAND_X		20
#define BWND_ALICECOMMAND_Y		400
#define BWND_ALICECOMMAND_W		300
#define BWND_ALICECOMMAND_H		200
#define BWND_ALICECOMMAND_PX	16
#define BWND_ALICECOMMAND_PY	16

class BWindow_AliceCommand : public Window_Selectable{
private:

public:
	BWindow_AliceCommand();

	// �Z�b�g�A�b�v
	// (���O�E�B���h�E�̏o�����͑S�Ăقړ���)
	void MySetup();

	// ���e�̃A�b�v�f�[�g���s���B
	virtual void Update();			// �N���X���Ƃɔh������A�b�v�f�[�g�֐��B

	// ���e�̕`����s���B
	virtual void DrawContent() const;

};

#endif // BWINDOW_ALICECOMMAND_H
