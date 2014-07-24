// Window_EnterName.cpp
#include "Window_EnterName.h"
#include <DxLib.h>
#include "TempData.h"
#include "WindowSkin.h"
#include "DXFont.h"
#include "Func_MyGraphic.h"


extern TempData				g_temp;
extern DXFont				g_font;
extern WindowSkins			g_wndSkins;

Window_EnterName::Window_EnterName() : Window_Base(), 
	s_chars(WINDOW_NAME_COLUMN, WINDOW_NAME_ROW){

}

void Window_EnterName::MySetup(WORD _nameType){
	WINDOWAREA frameArea(0, 0, WND_ENTERNAME_WIDTH, WND_ENTERNAME_HEIGHT);
	Setup(&g_wndSkins.skin[WNDSKIN_SIMPLE],
		frameArea, WND_ENTERNAME_PX, WND_ENTERNAME_PY, true);
	nameType = _nameType;
	page = 0;
	SetPositionH(WND_WIDTH/2);		// 画面中央に揃える
	SetPositionV(WND_HEIGHT/2);
}

WORD Window_EnterName::GetNameIndex(int pos_x, int pos_y, BYTE page) const{
	int index;
	index = pos_x%5+1;
	index += pos_y*5;
	if(pos_x >= 5){
		if(pos_y < 5){
			index += 25;
		}else if(pos_y == 7){
			index = 0;
		}else if(pos_y >= 8){
			index += 40;
		}else{
			index += 40;
		}
	}else{
		if(pos_y >= 8){
			index += 35;
		}else if(pos_y >= 5){
			index += 25;
		}
	}
	index += page*MAX_NAMESTRING/3;
	return index;
}

int Window_EnterName::GetDrawX(int pos_x, int pos_y) const{
	int baseX = frameArea.x + contentArea.x + pos_x*1.2*FONTSIZE_STR;
	if(pos_x >= 5) baseX += 0.5*FONTSIZE_STR;
	if(pos_x >= 10) baseX += 0.5*FONTSIZE_STR;
	return baseX;
}

int Window_EnterName::GetDrawY(int pos_x, int pos_y) const{
	int baseY = frameArea.y + contentArea.y + 64 + pos_y*1.3*FONTSIZE_STR;
	if(pos_y >= 5) baseY += 0.6*FONTSIZE_STR;
	// if(pos_y >= 8) baseY += 0.6*FONTSIZE_STR;
	return baseY;
}

void Window_EnterName::Update(){
	switch(s_chars.Move()){
	case SELECT2D_CHOOSE:
		if(s_chars.GetColumn(s_chars.index) == 10){
			switch(s_chars.GetRow(s_chars.index)){
			case 0:
				// 決定
				break;
			case 1:
				// 一字戻る
				break;
			case 2:
				// カタカナ
				page = 0;
				break;
			case 3:
				// ひらがな
				page = 1;
				break;
			case 4:
				// 英数・記号
				page = 2;
				break;
			}
		}
		break;
	case SELECT2D_CANCEL:
		break;
	}
	Update_Common();
}

void Window_EnterName::DrawContent() const{
	WORD index;
	// 照準の描画
	int dx = GetDrawX(s_chars.GetColumn(s_chars.index), s_chars.GetRow(s_chars.index));
	int dy = GetDrawY(s_chars.GetColumn(s_chars.index), s_chars.GetRow(s_chars.index));
	int width = s_chars.GetColumn(s_chars.index) == WINDOW_NAME_COLUMN-1 ? 
		FONTSIZE_STR*5+2 : FONTSIZE_STR;
	if(GetActive()){
		DrawBox(dx, dy, 
			dx+width,
			dy+FONTSIZE_STR, GetColor(255,255,255), 0);  
		for(int j=0; j<WINDOW_NAME_ROW; j++){
			for(int i=0; i<WINDOW_NAME_COLUMN-1; i++){
				index = GetNameIndex(i, j, page);
				DrawNameChar(
					GetDrawX(i, j), GetDrawY(i, j),
					index, false);
			}
			DrawSpecialChar(
				GetDrawX(WINDOW_NAME_COLUMN-1, j),
				GetDrawY(WINDOW_NAME_COLUMN-1, j), 
				j, false);
		}
	}
}

void Window_EnterName::DrawSpecialChar(int x, int y, BYTE index, bool isLarge) const{
	if(index < 0) return;
	if(index >= WINDOW_NAME_ROW) return;
	TCHAR str[WINDOW_NAME_ROW][18] = {
		_T("決定"),
		_T("一字消す"),
		_T("カタカナ"),
		_T("ひらがな"),
		_T("英数・記号"),
		_T("かわいい"),
		_T("かっこいい"),
		_T("どくとく"),
		_T("親と同じ")};

	DrawStringToHandle(x, y, str[index], GetColor(255, 255, 255), 
		isLarge?g_font.hStrL:g_font.hStr);

}