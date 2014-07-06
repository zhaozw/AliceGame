// WindowSkin_AttachImage.cpp

#include "WindowSkin.h"
#include "Image.h"

extern Image g_image;

// ウィンドウのリソースのロード
bool WindowSkins::AttachImages(){
	if(!skin[WNDSKIN_SIMPLE].AttachImage(
		g_image.window.simple, WNDSKIN_SIMPLE, 16,
		WindowSkin::FT_EXTEND, WindowSkin::OT_EXPAND_Y, 5)){
		return false;
	}
	return true;
}

