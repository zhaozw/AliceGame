// Window_Yesno.cpp

#include "Window_Yesno.h"


Window_Yesno::Window_Yesno() : Window_Selectable(){
}

void Window_Yesno::Setup(
	WindowSkin* _pSkin,
	WINDOWAREA	_frameArea,
	WINDOWAREA	_contentArea,
	WINDOWFONT	_font,
	bool horizontal){
		Window_Selectable_Content content;
		strcpy_s(content.data[WINDOW_YESNO_YES], WND_SELECTABLE_STRLENGTH-1, _T("‚Í‚¢"));
		strcpy_s(content.data[WINDOW_YESNO_NO], WND_SELECTABLE_STRLENGTH-1, _T("‚¢‚¢‚¦"));
		SetContent(content);
		SetGridSize(
			horizontal?2:1,
			horizontal?1:2);
		Window_Selectable::Setup(pSkin, _frameArea, _contentArea, 
			_font, _contentArea.w/(horizontal?2:1));
}
