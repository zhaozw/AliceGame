#ifndef STATIC_SKILL_H
#define STATIC_SKILL_H

// 全スキルの数。
#define MAX_SKILL			32

// スキルの文字（バイト）数。
#define MAX_SKILL_BYTES			24		

// スキルで出るサブメッセージの数
#define MAX_SKILL_SUBMESSAGE		128

// スキルの列挙
#define SKILL_NONE				0	// 何もスキルがない状態
#define SKILL_WAIT				1	// 様子を見ている
#define SKILL_ALLRANGE			2	// 全体攻撃
#define SKILL_LOADOFF_ATTACK	3	// 先制攻撃
#define SKILL_HEAL1				4	// 味方一体の回復
#define SKILL_WIDESHOT			5	// ばらまき弾
#define SKILL_KUNAISHOT			6	// クナイ弾(技巧依存)
#define SKILL_KNIFESHOT			7	// ナイフ弾(防御無視)
#define SKILL_REIGEKI			8	// 霊撃(属性無視)
#define SKILL_PHOTONSHOT		9	// 光弾(魔力依存)
#define SKILL_REPAIR			10	// 修復
#define SKILL_REPAIR_ALL		11	// 全体修復
#define SKILL_MJOLLNIR			12	// ミョルニル(攻撃依存)
#define SKILL_REPAIR_QUICK		13	// 高速修復
#define SKILL_HEAL				14	// 修復と同じ効果
#define SKILL_QUICKHEAL			15	// 高速修復と同じ効果
#define SKILL_SUN_ENCHANT		16	// 自軍一体を永久的に太陽属性に変化させる
#define SKILL_MOON_ENCHANT		17	// 自軍一体を永久的に月属性に変化させる
#define SKILL_STAR_ENCHANT		18	// 自軍一体を永久的に星属性に変化させる
#define SKILL_NEUTRAL_ENCHANT	19	// 自軍一体を永久的に無属性に変化させる
#define SKILL_ATTR_ENCHANT		20	// 自軍一体の属性をランダムに変化させる



#endif // STATIC_SKILL_H