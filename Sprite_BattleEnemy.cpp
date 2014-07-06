// Sprite_BattleEnemy.cpp

#include "Sprite_BattleEnemy.h"
#include <DxLib.h>
#include "Data_EnemyDraw.h"

extern Data_EnemyDraw		d_enemyDraw;

Sprite_BattleEnemy::Sprite_BattleEnemy(){
	Sprite_Base::Sprite_Base();
	pEnemy = NULL;
	refID = 0;
	cx = cy = 0;
	baseExRate = 0;
	hImg = 0;
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
	SetPos(pEnemy->GetDrawX(), pEnemy->GetDrawY());
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
	hImg = pDrawData->GetHImg();
}

void Sprite_BattleEnemy::Update(){
	if(pEnemy->GetDataID() != refID){
		UpdateRefID();
	}
}

void Sprite_BattleEnemy::Draw() const{
	if(refID == 0) return;
	if(hImg == 0) return;
	if(pEnemy == NULL) return;
	DrawRotaGraph2F(GetX(), GetY(), cx, cy, baseExRate, 0, hImg, 1, 0);
}