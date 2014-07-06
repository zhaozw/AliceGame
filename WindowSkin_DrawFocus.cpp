// WindowSkin_DrawFocus.cpp

#include "WindowSkin.h"
#include <DxLib.h>

void WindowSkin::DrawFocus(int x, int y, int width, int height, int time) const{
	switch(wndSkinID){
	case WNDSKIN_SIMPLE:
		DrawBox(x, y, x+width, y+height, GetColor(255,255,255), false);
		break;
	}
}