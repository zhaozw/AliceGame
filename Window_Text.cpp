// Window_Text.cpp

#include "Window_Text.h"

#include <string.h>
#include <DxLib.h>
#include "Static_Game.h"

Window_Text::Window_Text() : Window_Base(){
	align = 0;
	lineHeight = 0;
	hFont = 0;
	fontSize = 18;
	color = iColor = nColor = GetColor(255, 255, 255);
}

int Window_Text::GetDrawDeltaX(LPTSTR content, int strSize, int _hFont) const{
	int size = strSize > 0 ? strSize : strlen(content);
	int font = _hFont != 0 ? _hFont : hFont;
	int drawWidth = GetDrawStringWidthToHandle(content, strSize, hFont);
	switch(align){
	case ALIGN_LEFT:
		return 0;
		break;
	case ALIGN_CENTER:
		return (content_width - drawWidth)/2;
		break;
	case ALIGN_RIGHT:
		return content_width - drawWidth;
		break;
	}
	return 0;
}