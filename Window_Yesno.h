#ifndef WINDOW_YESNO_H
#define WINDOW_YESNO_H

#include "Window_Selectable.h"

#define WINDOW_YESNO_YES		0
#define WINDOW_YESNO_NO			1

// �u�͂��v�u�������v��\������E�B���h�E�B
// Window_Selectable�������₷���悤�Ɍ���I�ɂ������́B
// Update�֐��ADrawContent�֐��Ƃ���Window_Selectable�������p���B
class Window_Yesno : public Window_Selectable{
private:
public:
	// �R���X�g���N�^
	Window_Yesno();

	// ���e�̃Z�b�g�A�b�v���s���B
	void Setup(
		WindowSkin* _pSkin, int _x, int _y, 
		int _hFont, int _fontSize,int _lineHeight,
		bool _useTitle = false, BYTE _align = ALIGN_CENTER, bool horizontal = true);

	// 

};

#endif // WINDOW_YESNO_H