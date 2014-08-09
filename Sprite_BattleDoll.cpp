// Sprite_BattleDoll.cpp

#include "Sprite_BattleDoll.h"
#include <DxLib.h>
#include "Image.h"
#include "DXFont.h"
#include "Func_Graphics.h"
#include "Scene_Battle.h"

extern		Image	g_image;
extern		DXFont	g_font;
extern		int		hDrawWindow;

Sprite_BattleDoll::Sprite_BattleDoll(){
	Sprite_Base();
	enabled		=	false;
	pDoll		=	NULL;
	width		=	SPRITE_BATTLEDOLL_WIDTH;
	height		=	SPRITE_BATTLEDOLL_HEIGHT;
	drawScreen	=	0;
	pScene		=	NULL;
}

bool Sprite_BattleDoll::SetupDrawScreen(){
	// 透明度ありの描画用スクリーンを作成
	drawScreen	= MakeScreen(
		SPRITE_BATTLEDOLL_SCREENWIDTH,
		SPRITE_BATTLEDOLL_SCREENHEIGHT, 1);
	// エラーの場合はfalse
	return drawScreen != -1;
}

void Sprite_BattleDoll::Update(){
	if(enabled){
		// 
		Sprite_Base::Update();
	}
}

#define BATTLEDOLL_HPGAUGE_HEIGHT	12

void Sprite_BattleDoll::Draw() const{
	if(enabled){
		DrawFrame();
		if(visible){
			DrawDoll();
		}
		DrawInfo();
	}
}

void Sprite_BattleDoll::DrawFrame() const{
	// フレームの描画
	DrawBox(
		GetIX(), GetIY(),
		GetIX()+SPRITE_BATTLEDOLL_WIDTH,
		GetIY()+SPRITE_BATTLEDOLL_HEIGHT, GetColor(255, 255, 255), 0);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 192);
	DrawBox(
		GetIX()+1, GetIY()+1,
		GetIX()+SPRITE_BATTLEDOLL_WIDTH-1,
		GetIY()+SPRITE_BATTLEDOLL_HEIGHT-1, GetColor(0, 0, 0), 1);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
}

void Sprite_BattleDoll::DrawDoll() const{
	// 人形の描画

	// 描画対象を変更
	SetDrawScreen(drawScreen);

	// 人形を描画する
	int koma = DOLL_FACE_NORMAL;
	// 表情の判定
	if(pDoll->IsDead()){
		koma = DOLL_FACE_DAMAGE;
	}else if(pDoll->GetHPRate() < 0.25){
		koma = DOLL_FACE_DAMAGE;
	}else if(pScene->GetCommandDollPtr() == pDoll){
		koma = DOLL_FACE_ATTACK;
	}else if(pScene->GetBattleResult() == BATTLERESULT_VICTORY){
		koma = DOLL_FACE_HAPPY;
	}
	
	// 人形の描画
	DrawGraph(
		SPRITE_BATTLEDOLL_MARGIN,
		SPRITE_BATTLEDOLL_MARGIN,
		g_image.icon.doll[pDoll->GetDollType()-1][koma][pDoll->GetAmendedAttr()], 1);
    // パラメータによって白くする
	if(pDoll->IsDead()){
	  GraphFilter(drawScreen, DX_GRAPH_FILTER_HSB, 0, 0, -255, -96);
	}

	// 描画対象を元に戻す
	SetDrawScreen(hDrawWindow);
	// 人形を描画する
	DrawRotaGraph3(
		GetX()+SPRITE_BATTLEDOLL_WIDTH/2,
		GetY()+SPRITE_BATTLEDOLL_HEIGHT/2 + 20,
		SPRITE_BATTLEDOLL_SCREENWIDTH/2,
		SPRITE_BATTLEDOLL_SCREENHEIGHT/2, 
		param.xScale*SPRITE_BATTLEDOLL_DRAWWIDTH/SPRITE_BATTLEDOLL_SCREENWIDTH,
		param.yScale*SPRITE_BATTLEDOLL_DRAWHEIGHT/SPRITE_BATTLEDOLL_SCREENHEIGHT,
		param.angle, 
		drawScreen, 1);
}

void Sprite_BattleDoll::DrawInfo() const{
	TCHAR	hpStr[16];
	TCHAR	nameStr[BATTLEUNIT_NAME_BYTES];
	int		tmpY;
	int		fontColor = 0;
	float	rate = 1.0;
	tmpY = GetIY();
	// 名前の描画
	pDoll->GetName(nameStr, BATTLEUNIT_NAME_BYTES);
	fontColor = GetColor(255,255,255);
	DrawStringToHandle(
		GetIX() 
		+ GetCenteringDX(
		nameStr, strlen(nameStr), g_font.hInfo, SPRITE_BATTLEDOLL_WIDTH),
		tmpY, nameStr, 
		fontColor, g_font.hInfo);
	tmpY += (FONTSIZE_INFO+4);
	// HPバーの描画
	rate = (float)pDoll->GetHP()/pDoll->GetMaxHP();
	switch(pDoll->GetAmendedAttr()){
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
		GetIX()+10, tmpY+2,
		GetIX()+10+(SPRITE_BATTLEDOLL_WIDTH-20),
		tmpY+2+BATTLEDOLL_HPGAUGE_HEIGHT,
		GetColor(64, 64, 64), 1);
	DrawBox(
		GetIX()+10, tmpY+2,
		GetIX()+10+rate*(SPRITE_BATTLEDOLL_WIDTH-20),
		tmpY+2+BATTLEDOLL_HPGAUGE_HEIGHT,
		fontColor, 1);
	tmpY += BATTLEDOLL_HPGAUGE_HEIGHT+4;
	// HP/最大HPの描画
	wsprintf(hpStr, _T("%d/%d"), pDoll->GetHP(), pDoll->GetMaxHP());
	DrawStringToHandle(
		GetIX() 
		+ GetRightAlignDX(
		hpStr, strlen(hpStr), g_font.hTinyInfo, SPRITE_BATTLEDOLL_WIDTH) - 10,
		tmpY, hpStr,
		GetColor(255, 255, 255), g_font.hTinyInfo);
	tmpY += (FONTSIZE_TINYINFO+4);
	// 仮にアイコンを描画
	// DrawGraph(GetIX(), GetIY(), g_image.icon.state[0], 1);
}