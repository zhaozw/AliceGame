// Window_Yesno.cpp

#include "Window_Yesno.h"


Window_Yesno::Window_Yesno() : Window_Selectable(){
}

void Window_Yesno::Setup(
	WindowSkin* _pSkin, int _x, int _y,
	int _hFont, int _fontSize, int _lineHeight,
	bool _useTitle, BYTE _align, bool horizontal){
		Window_Selectable_Content content;
		Window_Selectable::Setup(_pSkin, _x, _y, content,
			horizontal?2:1,
			_hFont, _fontSize,
			_lineHeight, false, _useTitle, _align); 
		SetContent(_T("�͂�"), WINDOW_YESNO_YES);
		SetContent(_T("������"), WINDOW_YESNO_NO);
		// ���̌�ꍇ�ɂ���Ă̓^�C�g���Ȃǂ�ݒ肵����SetDefParam���s����
		// ���e�Ƃ̊֘A�t�����s���B
}
