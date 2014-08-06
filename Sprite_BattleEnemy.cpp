// Sprite_BattleEnemy.cpp

#include "Sprite_BattleEnemy.h"
#include <DxLib.h>
#include "Data_EnemyDraw.h"
#include "Static_AliceDoll.h"
#include "Func_Graphics.h"
#include "Image.h"
#include "DXFont.h"

extern Data_EnemyDraw		d_enemyDraw;
extern Image				g_image;
extern DXFont				g_font;

// モーフで何かやったあと際描画先を戻すのに必要なのでextern
extern int hDrawWindow;

Sprite_BattleEnemy::Sprite_BattleEnemy(){
	Sprite_Base::Sprite_Base();
	pEnemy = NULL;
	refID = 0;
	cx = cy = 0;
	baseExRate = 0;
	hImg = 0;
	enabled = false;
	visible = false;

    morphSettleFlag = false;
    morphSettleID = SPMORPH_NONE;
    morphScreen = -1;
}

bool Sprite_BattleEnemy::AttachBattleEnemy(Game_BattleEnemy* _pEnemy){
	if(_pEnemy == NULL) return false;
	// 参照の確立
	pEnemy = _pEnemy;
	// 参照が存在しなければデータは更新しない
	if(pEnemy->GetDataID() == 0) return false;
	// refIDを元に描画データを取得する
	UpdateRefID();
	// 描画位置をセットする
	SetPos((float)pEnemy->GetDrawX(), (float)pEnemy->GetDrawY());
	// 有効に
	enabled = true;
	visible = true;
	return true;
}

void Sprite_BattleEnemy::UpdateRefID(){
	// 各データをIDから取得する
	refID = pEnemy->GetDataID();
	// 参照用のデータがあるか
	if(refID == 0) return;
	// 参照用のデータを取得
	Data_EnemyDraw_Each* pDrawData = d_enemyDraw.GetEnemyDraw(refID);
	// データの存在を確認
	if(pDrawData == NULL) return;
	// 中心の描画位置を指定
	cx = pDrawData->GetCX();
	cy = pDrawData->GetCY();
	// 画像サイズと表示倍率からスプライトの大きさを取得
	SetSize(
		(int)(pDrawData->GetIWidth()*pDrawData->GetExRate()),
		(int)(pDrawData->GetIHeight()*pDrawData->GetExRate()));
	// 画像の表示倍率を取得
	baseExRate = pDrawData->GetExRate();
	// 画像のハンドルを取得
	hImg = pDrawData->GetHImg(pEnemy->GetAmendedAttr());
}

void Sprite_BattleEnemy::Update(){
	if(pEnemy->GetDataID() != refID){
		UpdateRefID();
	}

    // モーフが実行された瞬間の初期化処理
    if (GetMorphing() && !morphSettleFlag){
        switch (morphID){
        case SPMORPH_ENEMYATTACK:
            [&](){
                if (morphScreen == -1){
                    int w, h;
                    GetGraphSize(hImg, &w, &h);
                    morphScreen = MakeScreen(w, h, true);
                }
            }();
            break;
        }

        morphSettleID = morphID;
        morphSettleFlag = true;
    }

	Sprite_Base::Update();

    // モーフが実行されていなければ後始末を行う
    // GetMorphinig()がfalseにならずにそのまま次が実行される場合後始末ができないバグの温床
    if (!GetMorphing() && morphSettleFlag){
        MorphSettle();
    }
}

void Sprite_BattleEnemy::Draw() const{
	if(refID == 0) return;
	if(hImg == 0) return;
	if(pEnemy == NULL) return;
	// 透明度
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, param.opacity);
	if(visible){
		// 表示状態の判定
		if(!param.hide){
            // モーフ専用の処理があればそちらへ渡す
            switch (morphID){
            case SPMORPH_ENEMYATTACK:
                MorphEnemyAttack();
                break;

            default :
                // 本体の描画
                DrawRotaGraph3F(
                    GetX(), GetY(), cx, cy,
                    baseExRate*param.xScale, baseExRate*param.yScale, param.angle,
                    hImg, 1, 0);
                break;
            }
		}
		// HPの描画
		DrawHPGauge((int)GetX(), (int)GetY());
	}
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
}

#define BATTLEENEMY_HPGAUGE_WIDTH	120
#define BATTLEENEMY_HPGAUGE_HEIGHT	10

void Sprite_BattleEnemy::DrawHPGauge(int x, int y) const{
	// 枠を描画
	DrawBox(
		x-BATTLEENEMY_HPGAUGE_WIDTH/2,
		y-BATTLEENEMY_HPGAUGE_HEIGHT/2,
		x+BATTLEENEMY_HPGAUGE_WIDTH/2,
		y+BATTLEENEMY_HPGAUGE_HEIGHT/2,
		GetColor(16, 16, 16), 1);
	DrawBox(
		x-BATTLEENEMY_HPGAUGE_WIDTH/2,
		y-BATTLEENEMY_HPGAUGE_HEIGHT/2,
		x+BATTLEENEMY_HPGAUGE_WIDTH/2,
		y+BATTLEENEMY_HPGAUGE_HEIGHT/2,
		GetColor(255,255,255), 0);
	// ゲージを描画
	float rate = (float)pEnemy->GetHP()/pEnemy->GetMaxHP();
	int color = 0;
	switch(pEnemy->GetAmendedAttr()){
	case DOLL_ATTR_NONE:
		color = GetColor(192, 192, 192);
		break;
	case DOLL_ATTR_SUN:
		color = GetColor(255, 0, 0);
		break;
	case DOLL_ATTR_MOON:
		color = GetColor(0, 0, 255);
		break;
	case DOLL_ATTR_STAR:
		color = GetColor(255, 255, 0);
		break;
	}
	int left = x-BATTLEENEMY_HPGAUGE_WIDTH/2 + 2;
	DrawBox(
		x-BATTLEENEMY_HPGAUGE_WIDTH/2 + 2,
		y-BATTLEENEMY_HPGAUGE_HEIGHT/2 + 2,
		left + (int)(rate*(BATTLEENEMY_HPGAUGE_WIDTH-4)),
		y+BATTLEENEMY_HPGAUGE_HEIGHT/2 - 2,
		color, 1);
	// HPを数値で描画
	TCHAR	hpStr[16];
	wsprintf(hpStr, _T("%d/%d"), pEnemy->GetHP(), pEnemy->GetMaxHP());
	DrawStringToHandle(
		(int)(GetX()-BATTLEENEMY_HPGAUGE_WIDTH/2
		+ GetRightAlignDX(
		hpStr, strlen(hpStr), g_font.hTinyInfo, BATTLEENEMY_HPGAUGE_WIDTH))+1,
		(int)(GetY()+BATTLEENEMY_HPGAUGE_HEIGHT/2)+2, hpStr,
		GetColor(0, 0, 0), g_font.hTinyInfo);
	DrawStringToHandle(
		(int)(GetX()-BATTLEENEMY_HPGAUGE_WIDTH/2
		+ GetRightAlignDX(
		hpStr, strlen(hpStr), g_font.hTinyInfo, BATTLEENEMY_HPGAUGE_WIDTH)),
		(int)(GetY()+BATTLEENEMY_HPGAUGE_HEIGHT/2), hpStr,
		GetColor(255, 255, 255), g_font.hTinyInfo);
}

// モーフの後処理関数
void Sprite_BattleEnemy::MorphSettle()
{
    // 必要ならswitch文に処理を追加
    /*
    switch (morphSettleID){
    default :
        break;
    }
    */

    // 使用したスクリーンを削除
    if (morphScreen){
        DeleteGraph(morphScreen);
        morphScreen = -1;
    }

    // 後始末が済んだ
    morphSettleID = SPMORPH_NONE;
    morphSettleFlag = false;

    return;
}

// SPMORPH_ENEMYATTACK専用描画関数
void Sprite_BattleEnemy::MorphEnemyAttack() const
{
    if (morphScreen == -1){
        DrawRotaGraph3F(
            GetX(), GetY(), cx, cy,
            baseExRate*param.xScale, baseExRate*param.yScale, param.angle,
            hImg, 1, 0);
        return;
    }

    // モーフ用スクリーンを初期化＋hImgを描画
    SetDrawScreen(morphScreen);
    ClearDrawScreen();
    DrawGraph(0, 0, hImg, true);

    // パラメータによって白くする
    GraphFilter(morphScreen, DX_GRAPH_FILTER_HSB, 0, 0, 0, param.param);

    SetDrawScreen(hDrawWindow);
    
    // 本体の描画
    DrawRotaGraph3F(
        GetX(), GetY(), cx, cy,
        baseExRate*param.xScale, baseExRate*param.yScale, param.angle,
        morphScreen, 1, 0);



    return;
}