// Sprite_BattleDoll.cpp

#include "Sprite_BattleDoll.h"
#include <DxLib.h>
#include "Image.h"
#include "DXFont.h"
#include "Func_Graphics.h"

extern		Image	g_image;
extern		DXFont	g_font;

Sprite_BattleDoll::Sprite_BattleDoll(){
	Sprite_Base();
	enabled		=	false;
	pDoll		=	NULL;
	width		=	SPRITE_BATTLEDOLL_WIDTH;
	height		=	SPRITE_BATTLEDOLL_HEIGHT;
}

void Sprite_BattleDoll::Update(){
}

#define BATTLEDOLL_HPGAUGE_HEIGHT	12

void Sprite_BattleDoll::Draw() const{
	TCHAR	hpStr[16];
	TCHAR	nameStr[BATTLEUNIT_NAME_BYTES];
	int		tmpY;
	int		fontColor = 0;
	float	rate = 1.0;
	if(visible && enabled){
		DrawBox(
			GetX(), GetY(),
			GetX()+SPRITE_BATTLEDOLL_WIDTH,
			GetY()+SPRITE_BATTLEDOLL_HEIGHT, GetColor(255, 255, 255), 0);
	}
	if(enabled){
		tmpY = GetY();
		pDoll->GetName(nameStr, BATTLEUNIT_NAME_BYTES);
		/*
		switch(pDoll->GetAttr()){
		case DOLL_ATTR_NONE:
			fontColor = GetColor(255, 255, 255);
			break;
		case DOLL_ATTR_SUN:
			fontColor = GetColor(255, 127, 63);
			break;
		case DOLL_ATTR_MOON:
			fontColor = GetColor(96, 192, 255);
			break;
		case DOLL_ATTR_STAR:
			fontColor = GetColor(255, 96, 255);
			break;
		}
		*/
		fontColor = GetColor(255,255,255);
		DrawStringToHandle(
			GetX() 
			+ GetCenteringDX(
			nameStr, strlen(nameStr), g_font.hInfo, SPRITE_BATTLEDOLL_WIDTH),
			tmpY, nameStr, 
			fontColor, g_font.hInfo);
		// –¼‘O‚Ì•`‰æ
		tmpY += (FONTSIZE_INFO+4);
		// HPƒo[‚Ì•`‰æ
		rate = (float)pDoll->GetHP()/pDoll->GetMaxHP();
		switch(pDoll->GetAttr()){
		case DOLL_ATTR_NONE:
			fontColor = GetColor(192, 192, 192);
			break;
		case DOLL_ATTR_SUN:
			fontColor = GetColor(255, 0, 0);
			break;
		case DOLL_ATTR_MOON:
			fontColor = GetColor(0, 0, 255);
			break;
		case DOLL_ATTR_STAR:
			fontColor = GetColor(255, 255, 0);
			break;
		}
		DrawBox(
			GetX()+10, tmpY+2,
			GetX()+10+(SPRITE_BATTLEDOLL_WIDTH-20),
			tmpY+2+BATTLEDOLL_HPGAUGE_HEIGHT,
			GetColor(64, 64, 64), 1);
		DrawBox(
			GetX()+10, tmpY+2,
			GetX()+10+rate*(SPRITE_BATTLEDOLL_WIDTH-20),
			tmpY+2+BATTLEDOLL_HPGAUGE_HEIGHT,
			fontColor, 1);
		tmpY += BATTLEDOLL_HPGAUGE_HEIGHT+4;
		// HP/Å‘åHP‚Ì•`‰æ
		wsprintf(hpStr, _T("%d/%d"), pDoll->GetHP(), pDoll->GetMaxHP());
		DrawStringToHandle(
			GetX() 
			+ GetRightAlignDX(
			hpStr, strlen(hpStr), g_font.hTinyInfo, SPRITE_BATTLEDOLL_WIDTH) - 10,
			tmpY, hpStr,
			GetColor(255, 255, 255), g_font.hTinyInfo);
		tmpY += (FONTSIZE_TINYINFO+4);
		// ‰¼‚ÉƒAƒCƒRƒ“‚ð•`‰æ
		// DrawGraph(GetX(), GetY(), g_image.icon.state[0], 1);
	}
}