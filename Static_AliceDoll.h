#ifndef STATIC_ALICEDOLL_H
#define STATIC_ALICEDOLL_H

// 種類関連
#define DOLL_TYPE_UNDIFINED			0		// 未定義。存在しない状態。
#define DOLL_TYPE_SHANGHAI			1		// 上海人形
#define DOLL_TYPE_MAIDEN			2		// 戦乙女の人形
#define DOLL_TYPE_HOURAI			3		// 蓬莱人形
#define DOLL_TYPE_CAT				4		// 化け猫の人形
#define DOLL_TYPE_GIANT				5		// ゴリアテ人形
#define DOLL_TYPE_TENGU				6		// 烏天狗の人形
#define DOLL_TYPE_FAIRY				7		// 妖精の人形
#define DOLL_TYPE_MUSICIAN			8		// 演奏家の人形
#define DOLL_TYPE_HUUSUI			9		// 風水師の人形
#define DOLL_TYPE_MAID				10		// メイドの人形
#define DOLL_TYPE_GREEN				11		// 緑眼の人形
#define DOLL_TYPE_RABBIT			12		// 玉兎の人形

#define DOLL_TYPE_PER_GROUP			3		// 1グループあたりの人形の数
#define DOLL_GROUP_NUM				4		// グループ数
#define DOLL_TYPE_MAX	(DOLL_TYPE_PER_GROUP*DOLL_GROUP_NUM) // 人形の種類の総数

#define DOLL_GROUP_UNDIFINED		0		// 
#define DOLL_GROUP_BALANCE			1		// バランス型
#define DOLL_GROUP_ATTACKER			2		// 前衛型
#define DOLL_GROUP_MAGICIAN			3		// 魔法型
#define DOLL_GROUP_SUPPORTER		4		// サポート型

#define DOLL_GROUP_UNDIFINED_STR	"未定義"
#define DOLL_GROUP_BALANCE_STR		"バランス型"
#define DOLL_GROUP_ATTACKER_STR		"前衛型"
#define DOLL_GROUP_MAGICIAN_STR		"魔法型"
#define DOLL_GROUP_SUPPORTER_STR	"サポート型"

// 属性関連
#define DOLL_ATTR_NONE				0		// 無属性
#define DOLL_ATTR_SUN				1		// 太陽 色系統は赤。
#define DOLL_ATTR_MOON				2		// 月 色系統は青。
#define DOLL_ATTR_STAR				3		// 星 色系統は黄色。
#define DOLL_ATTR_NUM				4		// 全属性数。無属性も含める。
#define DOLL_ATTR_RANDOM			4		// 敵グループの情報として、ランダム値。

// 属性のかけら関連
#define DOLL_ATTRSTONE_NUM			6		// 人形が持つ属性のかけらの数
#define DOLL_ATTRSTONE_CREATE		3		// 人形作成時の属性のかけらの数

// 表情
#define DOLL_FACE_NORMAL			0		// 通常
#define DOLL_FACE_ATTACK			1		// 攻撃
#define DOLL_FACE_DAMAGE			2		// ダメージ
#define DOLL_FACE_FUN				3		// 笑顔
#define DOLL_FACE_HAPPY				4		// 勝利
#define DOLL_FACE_NUM				5		// 全表情数。


// レベル関連
#define DOLL_LEVEL_MAX				8		// レベルの最大値
#define DOLL_POTENTIALLEVEL_MAX		1400	// 内部レベルの最大値
#define DOLL_GLOBALLEVEL_MAX		1600	// グローバルレベルの最大値
#define DOLL_LEVEL_FACTOR			20		// レベルがグローバルレベルに加算される時の係数
#define DOLL_EXP_MAX				99999999	// 最大経験値

// パラメータ関連
#define DOLL_PARAM_MAX				5		// 全ステータスの数
#define DOLL_PARAM_HP				0		// 体力
#define DOLL_PARAM_ATK				1		// 攻撃
#define DOLL_PARAM_SPD				2		// 敏捷
#define DOLL_PARAM_MGC				3		// 魔力
#define DOLL_PARAM_TEC				4		// 技巧

// スキル関連
#define DOLL_SKILL_MAX				8		// 覚える技の数


#endif // STATIC_ALICEDOLL_H