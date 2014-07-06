// Func_MyGraphic.cpp

#include "Func_MyGraphic.h"

#include <DxLib.h>
#include "Static_AliceDoll.h"
#include "Func_Math.h"
#include "Image.h"
#include "DXFont.h"

extern Image		g_image;
extern DXFont		g_font;

void DrawDollType(int x, int y, BYTE type, int color){
	if(type <= 0 || type > DOLL_TYPE_MAX) return;
	TCHAR str[DOLL_TYPE_MAX][32] = {
		_T("上海人形"),
		_T("戦乙女の人形"),
		_T("蓬莱人形"),
		_T("化け猫の人形"),
		_T("ゴリアテ人形"),
		_T("烏天狗の人形"),
		_T("妖精の人形"),
		_T("演奏家の人形"),
		_T("風水師の人形"),
		_T("メイドの人形"),
		_T("緑眼の人形"),
		_T("玉兎の人形"),
	};

	DrawStringToHandle(x, y, str[type-1], color, 
		g_font.hStr);
}

void DrawNameChar(int x, int y, WORD index, bool isLarge){
	if(index <= 0 || index > MAX_NAMESTRING) return;
	TCHAR str[MAX_NAMESTRING][3] = {
		_T("ア"), _T("イ"), _T("ウ"), _T("エ"), _T("オ"), 
		_T("カ"), _T("キ"), _T("ク"), _T("ケ"), _T("コ"),
		_T("サ"), _T("シ"), _T("ス"), _T("セ"), _T("ソ"),
		_T("タ"), _T("チ"), _T("ツ"), _T("テ"), _T("ト"),
		_T("ナ"), _T("ニ"), _T("ヌ"), _T("ネ"), _T("ノ"), 

		_T("ハ"), _T("ヒ"), _T("フ"), _T("ヘ"), _T("ホ"),
		_T("マ"), _T("ミ"), _T("ム"), _T("メ"), _T("モ"),
		_T("ヤ"), _T("ヰ"), _T("ユ"), _T("ヱ"), _T("ヨ"),
		_T("ラ"), _T("リ"), _T("ル"), _T("レ"), _T("ロ"),
		_T("ワ"), _T("ヲ"), _T("ン"), _T("ヴ"), _T("ー"),

		_T("ガ"), _T("ギ"), _T("グ"), _T("ゲ"), _T("ゴ"),
		_T("ザ"), _T("ジ"), _T("ズ"), _T("ゼ"), _T("ゾ"),
		_T("ダ"), _T("ヂ"), _T("ヅ"), _T("デ"), _T("ド"),
		_T("バ"), _T("ビ"), _T("ブ"), _T("ベ"), _T("ボ"),
		_T("パ"), _T("ピ"), _T("プ"), _T("ペ"), _T("ポ"),

		_T("ァ"), _T("ィ"), _T("ゥ"), _T("ェ"), _T("ォ"),
		_T("ャ"), _T("ュ"), _T("ョ"), _T("ッ"), _T("　"),

		_T("あ"), _T("い"), _T("う"), _T("え"), _T("お"),
		_T("か"), _T("き"), _T("く"), _T("け"), _T("こ"),
		_T("さ"), _T("し"), _T("す"), _T("せ"), _T("そ"),
		_T("た"), _T("ち"), _T("つ"), _T("て"), _T("と"),
		_T("な"), _T("に"), _T("ぬ"), _T("ね"), _T("の"),
		
		_T("は"), _T("ひ"), _T("ふ"), _T("へ"), _T("ほ"),
		_T("ま"), _T("み"), _T("む"), _T("め"), _T("も"),
		_T("や"), _T("ゐ"), _T("ゆ"), _T("ゑ"), _T("よ"),
		_T("ら"), _T("り"), _T("る"), _T("れ"), _T("ろ"),
		_T("わ"), _T("を"), _T("ん"), _T("　"), _T("～"),
		
		_T("が"), _T("ぎ"), _T("ぐ"), _T("げ"), _T("ご"),
		_T("ざ"), _T("じ"), _T("ず"), _T("ぜ"), _T("ぞ"),
		_T("だ"), _T("ぢ"), _T("づ"), _T("で"), _T("ど"),
		_T("ば"), _T("び"), _T("ぶ"), _T("べ"), _T("ぼ"),
		_T("ぱ"), _T("ぴ"), _T("ぷ"), _T("ぺ"), _T("ぽ"),
		
		_T("ぁ"), _T("ぃ"), _T("ぅ"), _T("ぇ"), _T("ぉ"),
		_T("ゃ"), _T("ゅ"), _T("ょ"), _T("っ"), _T("　"),

		_T("Ａ"), _T("Ｂ"), _T("Ｃ"), _T("Ｄ"), _T("Ｅ"),
		_T("Ｆ"), _T("Ｇ"), _T("Ｈ"), _T("Ｉ"), _T("Ｊ"),
		_T("Ｋ"), _T("Ｌ"), _T("Ｍ"), _T("Ｎ"), _T("Ｏ"),
		_T("Ｐ"), _T("Ｑ"), _T("Ｒ"), _T("Ｓ"), _T("Ｔ"),
		_T("Ｕ"), _T("Ｖ"), _T("Ｗ"), _T("Ｘ"), _T("Ｙ"),
		
		_T("ａ"), _T("ｂ"), _T("ｃ"), _T("ｄ"), _T("ｅ"),
		_T("ｆ"), _T("ｇ"), _T("ｈ"), _T("ｉ"), _T("ｊ"),
		_T("ｋ"), _T("ｌ"), _T("ｍ"), _T("ｎ"), _T("ｏ"),
		_T("ｐ"), _T("ｑ"), _T("ｒ"), _T("ｓ"), _T("ｔ"),
		_T("ｕ"), _T("ｖ"), _T("ｗ"), _T("ｘ"), _T("ｙ"),

		_T("Ｚ"), _T("＆"), _T("☆"), _T("　"), _T("　"),
		_T("　"), _T("　"), _T("　"), _T("　"), _T("　"),
		_T("　"), _T("　"), _T("　"), _T("　"), _T("　"),
		_T("ｚ"), _T("＆"), _T("　"), _T("　"), _T("　"),
		_T("　"), _T("　"), _T("　"), _T("　"), _T("　"),

		_T("１"), _T("２"), _T("３"), _T("４"), _T("５"),
		_T("６"), _T("７"), _T("８"), _T("９"), _T("０")};
	DrawStringToHandle(x, y, str[index-1], GetColor(255, 255, 255), 
		isLarge?g_font.hStrL:g_font.hStr);


		/*
	DrawBox(x+4, y+4, x+SIZE_NAMESTR-4, y+SIZE_NAMESTR-4,
	GetColor(
	PARAM(32*(index/6)),
	PARAM(32*(index%6)),
	PARAM(8*index)), 1);
	*/
}

void DrawAttrIcon(int x, int y, BYTE attr){
	switch(attr){
	case DOLL_ATTR_NONE:
		DrawBox(x+4, y+4, x+SIZE_ATTRICON-4, y+SIZE_ATTRICON-4,
			GetColor(192, 192, 192), 1);
		break;
	case DOLL_ATTR_SUN:
		DrawBox(x+4, y+4, x+SIZE_ATTRICON-4, y+SIZE_ATTRICON-4,
			GetColor(255, 96, 96), 1);
		break;
	case DOLL_ATTR_MOON:
		DrawBox(x+4, y+4, x+SIZE_ATTRICON-4, y+SIZE_ATTRICON-4,
			GetColor(96, 255, 255), 1);
		break;
	case DOLL_ATTR_STAR:
		DrawBox(x+4, y+4, x+SIZE_ATTRICON-4, y+SIZE_ATTRICON-4,
			GetColor(255, 255, 0), 1);
		break;
	}
};

void DrawAttrStone(int cx, int cy, BYTE group, BYTE attr, float exRate, int time){
	if(group <= 0) return;
	if(group > DOLL_GROUP_NUM) return;
	if(attr > DOLL_ATTR_NUM) return;
	DrawExtendGraph(
		(int)(cx - exRate/2*SIZE_ATTRSTONE), (int)(cy - exRate/2*SIZE_ATTRSTONE),
		(int)(cx + exRate/2*SIZE_ATTRSTONE), (int)(cy + exRate/2*SIZE_ATTRSTONE),
		g_image.icon.attrstone[attr][group-1], 1);

}

void DrawGroupName(int x, int y, BYTE group, int hFont){
	TCHAR name[DOLL_GROUP_NUM+1][32] = {
		_T("未定義"),
		_T("バランス型"),
		_T("前衛型"),
		_T("魔法型"),
		_T("サポート型"),
	};
	if(group >= DOLL_GROUP_NUM) return;
	DrawStringToHandle(x, y, name[group], GetColor(255, 255, 255), hFont);

}

void DrawDollIllust(int cx, int cy, BYTE type, BYTE attr, float exRate, float rot){
	if(type > DOLL_TYPE_MAX) return;
	if(attr > DOLL_ATTR_NUM) return; 
	DrawRotaGraph(cx, cy, exRate, rot, g_image.illust.doll[type-1][attr], 1);
}

void DrawDollIllust2(int cx, int cy, BYTE type, BYTE attr,
	float exRateX, float exRateY, float rot){
	if(type > DOLL_TYPE_MAX) return;
	if(attr > DOLL_ATTR_NUM) return; 
	DrawRotaGraph3(cx, cy, WIDTH_DOLLILLUST/2, HEIGHT_DOLLILLUST/2,
		exRateX, exRateY, rot, g_image.illust.doll[type-1][attr], 1);
}

void DrawDollIcon(int x, int y, BYTE type, BYTE attr, BYTE face){
	if(type > DOLL_TYPE_MAX) return;
	if(attr > DOLL_ATTR_NUM) return; 
	if(face > DOLL_FACE_NUM) return;
	DrawGraph(x, y, g_image.icon.doll[type-1][attr][face], 1);
}

void DrawDollIconExtend(int x1, int y1, int x2, int y2, BYTE type, BYTE attr, BYTE face){
	if(type > DOLL_TYPE_MAX) return;
	if(attr > DOLL_ATTR_NUM) return; 
	if(face > DOLL_FACE_NUM) return;
	DrawExtendGraph(x1, y1, x2, y2, g_image.icon.doll[type-1][attr][face], 1);
}

void DrawDollIconRot(int cx, int cy, 
	BYTE type, BYTE attr, BYTE face, float exRate, float rot){
	if(type >= DOLL_TYPE_MAX) return;
	if(attr > DOLL_ATTR_NUM) return; 
	if(face > DOLL_FACE_NUM) return;
	DrawRotaGraph(cx, cy, exRate, rot, g_image.icon.doll[type-1][attr][face], 1);
}

/*
	// 使うかも知れないので削除しないで！
	TCHAR str[MAX_NAMESTRING][3] = {
		_T("ア"), _T("イ"), _T("ウ"), _T("エ"), _T("オ"), 
		_T("カ"), _T("キ"), _T("ク"), _T("ケ"), _T("コ"),
		_T("サ"), _T("シ"), _T("ス"), _T("セ"), _T("ソ"),
		_T("タ"), _T("チ"), _T("ツ"), _T("テ"), _T("ト"),
		_T("ナ"), _T("ニ"), _T("ヌ"), _T("ネ"), _T("ノ"), 

		_T("ハ"), _T("ヒ"), _T("フ"), _T("ヘ"), _T("ホ"),
		_T("マ"), _T("ミ"), _T("ム"), _T("メ"), _T("モ"),
		_T("ヤ"), _T("ヰ"), _T("ユ"), _T("ヱ"), _T("ヨ"),
		_T("ラ"), _T("リ"), _T("ル"), _T("レ"), _T("ロ"),
		_T("ワ"), _T("ヲ"), _T("ン"), _T("ヴ"), _T("ー"),

		_T("ガ"), _T("ギ"), _T("グ"), _T("ゲ"), _T("ゴ"),
		_T("ザ"), _T("ジ"), _T("ズ"), _T("ゼ"), _T("ゾ"),
		_T("ダ"), _T("ヂ"), _T("ヅ"), _T("デ"), _T("ド"),
		_T("バ"), _T("ビ"), _T("ブ"), _T("ベ"), _T("ボ"),
		_T("パ"), _T("ピ"), _T("プ"), _T("ペ"), _T("ポ"),

		_T("ァ"), _T("ィ"), _T("ゥ"), _T("ェ"), _T("ォ"),
		_T("ャ"), _T("ュ"), _T("ョ"), _T("ッ"), _T("　"),

		_T("あ"), _T("い"), _T("う"), _T("え"), _T("お"),
		_T("か"), _T("き"), _T("く"), _T("け"), _T("こ"),
		_T("さ"), _T("し"), _T("す"), _T("せ"), _T("そ"),
		_T("た"), _T("ち"), _T("つ"), _T("て"), _T("と"),
		_T("な"), _T("に"), _T("ぬ"), _T("ね"), _T("の"),
		
		_T("は"), _T("ひ"), _T("ふ"), _T("へ"), _T("ほ"),
		_T("ま"), _T("み"), _T("む"), _T("め"), _T("も"),
		_T("や"), _T("ゐ"), _T("ゆ"), _T("ゑ"), _T("よ"),
		_T("ら"), _T("り"), _T("る"), _T("れ"), _T("ろ"),
		_T("わ"), _T("を"), _T("ん"), _T("　"), _T("～"),
		
		_T("が"), _T("ぎ"), _T("ぐ"), _T("げ"), _T("ご"),
		_T("ざ"), _T("じ"), _T("ず"), _T("ぜ"), _T("ぞ"),
		_T("だ"), _T("ぢ"), _T("づ"), _T("で"), _T("ど"),
		_T("ば"), _T("び"), _T("ぶ"), _T("べ"), _T("ぼ"),
		_T("ぱ"), _T("ぴ"), _T("ぷ"), _T("ぺ"), _T("ぽ"),
		
		_T("Ａ"), _T("Ｂ"), _T("Ｃ"), _T("Ｄ"), _T("Ｅ"),
		_T("Ｆ"), _T("Ｇ"), _T("Ｈ"), _T("Ｉ"), _T("Ｊ"),
		_T("Ｋ"), _T("Ｌ"), _T("Ｍ"), _T("Ｎ"), _T("Ｏ"),
		_T("Ｐ"), _T("Ｑ"), _T("Ｒ"), _T("Ｓ"), _T("Ｔ"),
		_T("Ｕ"), _T("Ｖ"), _T("Ｗ"), _T("Ｘ"), _T("Ｙ"),
		
		_T("ａ"), _T("ｂ"), _T("ｃ"), _T("ｄ"), _T("ｅ"),
		_T("ｆ"), _T("ｇ"), _T("ｈ"), _T("ｉ"), _T("ｊ"),
		_T("ｋ"), _T("ｌ"), _T("ｍ"), _T("ｎ"), _T("ｏ"),
		_T("ｐ"), _T("ｑ"), _T("ｒ"), _T("ｓ"), _T("ｔ"),
		_T("ｕ"), _T("ｖ"), _T("ｗ"), _T("ｘ"), _T("ｙ"),

		_T("Ｚ"), _T("　"), _T("　"), _T("　"), _T("　"),
		_T("ｚ"), _T("　"), _T("　"), _T("　"), _T("　"),
		_T("　"), _T("　"), _T("　"), _T("　"), _T("　"),
		_T("　"), _T("　"), _T("　"), _T("　"), _T("　"),
		_T("　"), _T("　"), _T("　"), _T("　"), _T("　"),

		_T("１"), _T("２"), _T("３"), _T("４"), _T("５"),
		_T("６"), _T("７"), _T("８"), _T("９"), _T("０")};
		*/
