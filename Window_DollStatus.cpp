// Window_DollStatus.cpp

#include "Window_DollStatus.h"
#include <Windows.h>
#include <DxLib.h>
#include "DXFont.h"
#include "WindowSkin.h"
#include "Func_MyGraphic.h"

extern WindowSkins g_wndSkins;

Window_DollStatus::Window_DollStatus() : Window_Text(){
	pDoll = NULL;
};

bool Window_DollStatus::Setup(int _x, int _y){
	Window_Base::Setup(&g_wndSkins.skin[WNDSKIN_SIMPLE], _x, _y, 
		WND_DOLLSTATUS_WIDTH, WND_DOLLSTATUS_HEIGHT,
		WND_DOLLSTATUS_PX, WND_DOLLSTATUS_PY,
		false);
	return true;
}

bool Window_DollStatus::SetDoll(Game_AliceDoll_Essence* p){
	if(p==NULL) return false;
	pDoll = p;
	return true;
}

void Window_DollStatus::Update(){
	if(state == SUSPENDED){
		state = IDLE;
	}
	Update_Common();
}

void Window_DollStatus::DrawContent() const{
	if(pDoll == NULL) return;
	// 名前の描画
	if(GetActive()){
		// 種類名の描画
		DrawDollType(x+padding_x, y+padding_y,
			pDoll->GetType(), GetColor(255,255,255));
	}
}
