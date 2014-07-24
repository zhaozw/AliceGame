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


#endif // STATIC_SKILL_H