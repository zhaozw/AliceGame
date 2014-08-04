#ifndef STATIC_SPRITE_H
#define STATIC_SPRITE_H

// 主に戦闘画面のスプライトを表示するクラス。
 
// morphIDに指定される定数群
// 動作なし。動き終わった後は自動的にこれになる。
#define		SPMORPH_NONE			0
// 消滅する。
// このアクションの終了後、visible値がfalseになる。
#define		SPMORPH_DISAPPEAR		1
// 選択された状態になる。
// SPMORPH_DISACTIVATEとセットで使う。
#define		SPMORPH_ACTIVATE		2
// 選択状態を解除する。
// SPMORPH_ACTIVATEの後で実行する。
#define		SPMORPH_DISACTIVATE		3
// 一度だけ点滅する。
// 正確には、この状態になった瞬間一回消え、その後また出てくる。
// param値 = 消えるフレーム数
#define		SPMORPH_BLINK			4
// 敵が攻撃するのエフェクト。
// 白く光る？
#define		SPMORPH_ENEMYATTACK		5
// 人形がダメージを受ける際のエフェクト。
#define		SPMORPH_DAMAGE_DOLL		100


// param.effectに指定される定数群
#define		SPEFFECT_NONE			0


#endif // STATIC_SPRITE_H