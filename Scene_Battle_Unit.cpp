// Scene_Battle_Unit.cpp
// バトルシーンのうち、ユニットに対する演算を行う関数を定義する。

#include "Scene_Battle.h"

void Scene_Battle::SetDollParams(int index,
	int hp, int maxhp, int atk, int spd, int mgc, int tec){
		if(index < 0 || index >= MAX_BATTLEDOLL) return;
		dolls[index].SetParam(hp, maxhp, atk, 0, spd, mgc, tec);
}

void Scene_Battle::SetEnemyParams(int index,
	int hp, int maxhp, int atk, int def, int spd, int mgc, int tec){
		if(index < 0 || index >= MAX_BATTLEENEMY) return;
		enemies[index].SetParam(hp, maxhp, atk, def, spd, mgc, tec);
}
