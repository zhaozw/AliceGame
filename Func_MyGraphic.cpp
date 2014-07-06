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
		_T("��C�l�`"),
		_T("�퉳���̐l�`"),
		_T("�H���l�`"),
		_T("�����L�̐l�`"),
		_T("�S���A�e�l�`"),
		_T("�G�V��̐l�`"),
		_T("�d���̐l�`"),
		_T("���t�Ƃ̐l�`"),
		_T("�����t�̐l�`"),
		_T("���C�h�̐l�`"),
		_T("�Ί�̐l�`"),
		_T("�ʓe�̐l�`"),
	};

	DrawStringToHandle(x, y, str[type-1], color, 
		g_font.hStr);
}

void DrawNameChar(int x, int y, WORD index, bool isLarge){
	if(index <= 0 || index > MAX_NAMESTRING) return;
	TCHAR str[MAX_NAMESTRING][3] = {
		_T("�A"), _T("�C"), _T("�E"), _T("�G"), _T("�I"), 
		_T("�J"), _T("�L"), _T("�N"), _T("�P"), _T("�R"),
		_T("�T"), _T("�V"), _T("�X"), _T("�Z"), _T("�\"),
		_T("�^"), _T("�`"), _T("�c"), _T("�e"), _T("�g"),
		_T("�i"), _T("�j"), _T("�k"), _T("�l"), _T("�m"), 

		_T("�n"), _T("�q"), _T("�t"), _T("�w"), _T("�z"),
		_T("�}"), _T("�~"), _T("��"), _T("��"), _T("��"),
		_T("��"), _T("��"), _T("��"), _T("��"), _T("��"),
		_T("��"), _T("��"), _T("��"), _T("��"), _T("��"),
		_T("��"), _T("��"), _T("��"), _T("��"), _T("�["),

		_T("�K"), _T("�M"), _T("�O"), _T("�Q"), _T("�S"),
		_T("�U"), _T("�W"), _T("�Y"), _T("�["), _T("�]"),
		_T("�_"), _T("�a"), _T("�d"), _T("�f"), _T("�h"),
		_T("�o"), _T("�r"), _T("�u"), _T("�x"), _T("�{"),
		_T("�p"), _T("�s"), _T("�v"), _T("�y"), _T("�|"),

		_T("�@"), _T("�B"), _T("�D"), _T("�F"), _T("�H"),
		_T("��"), _T("��"), _T("��"), _T("�b"), _T("�@"),

		_T("��"), _T("��"), _T("��"), _T("��"), _T("��"),
		_T("��"), _T("��"), _T("��"), _T("��"), _T("��"),
		_T("��"), _T("��"), _T("��"), _T("��"), _T("��"),
		_T("��"), _T("��"), _T("��"), _T("��"), _T("��"),
		_T("��"), _T("��"), _T("��"), _T("��"), _T("��"),
		
		_T("��"), _T("��"), _T("��"), _T("��"), _T("��"),
		_T("��"), _T("��"), _T("��"), _T("��"), _T("��"),
		_T("��"), _T("��"), _T("��"), _T("��"), _T("��"),
		_T("��"), _T("��"), _T("��"), _T("��"), _T("��"),
		_T("��"), _T("��"), _T("��"), _T("�@"), _T("�`"),
		
		_T("��"), _T("��"), _T("��"), _T("��"), _T("��"),
		_T("��"), _T("��"), _T("��"), _T("��"), _T("��"),
		_T("��"), _T("��"), _T("��"), _T("��"), _T("��"),
		_T("��"), _T("��"), _T("��"), _T("��"), _T("��"),
		_T("��"), _T("��"), _T("��"), _T("��"), _T("��"),
		
		_T("��"), _T("��"), _T("��"), _T("��"), _T("��"),
		_T("��"), _T("��"), _T("��"), _T("��"), _T("�@"),

		_T("�`"), _T("�a"), _T("�b"), _T("�c"), _T("�d"),
		_T("�e"), _T("�f"), _T("�g"), _T("�h"), _T("�i"),
		_T("�j"), _T("�k"), _T("�l"), _T("�m"), _T("�n"),
		_T("�o"), _T("�p"), _T("�q"), _T("�r"), _T("�s"),
		_T("�t"), _T("�u"), _T("�v"), _T("�w"), _T("�x"),
		
		_T("��"), _T("��"), _T("��"), _T("��"), _T("��"),
		_T("��"), _T("��"), _T("��"), _T("��"), _T("��"),
		_T("��"), _T("��"), _T("��"), _T("��"), _T("��"),
		_T("��"), _T("��"), _T("��"), _T("��"), _T("��"),
		_T("��"), _T("��"), _T("��"), _T("��"), _T("��"),

		_T("�y"), _T("��"), _T("��"), _T("�@"), _T("�@"),
		_T("�@"), _T("�@"), _T("�@"), _T("�@"), _T("�@"),
		_T("�@"), _T("�@"), _T("�@"), _T("�@"), _T("�@"),
		_T("��"), _T("��"), _T("�@"), _T("�@"), _T("�@"),
		_T("�@"), _T("�@"), _T("�@"), _T("�@"), _T("�@"),

		_T("�P"), _T("�Q"), _T("�R"), _T("�S"), _T("�T"),
		_T("�U"), _T("�V"), _T("�W"), _T("�X"), _T("�O")};
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
		_T("����`"),
		_T("�o�����X�^"),
		_T("�O�q�^"),
		_T("���@�^"),
		_T("�T�|�[�g�^"),
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
	// �g�������m��Ȃ��̂ō폜���Ȃ��ŁI
	TCHAR str[MAX_NAMESTRING][3] = {
		_T("�A"), _T("�C"), _T("�E"), _T("�G"), _T("�I"), 
		_T("�J"), _T("�L"), _T("�N"), _T("�P"), _T("�R"),
		_T("�T"), _T("�V"), _T("�X"), _T("�Z"), _T("�\"),
		_T("�^"), _T("�`"), _T("�c"), _T("�e"), _T("�g"),
		_T("�i"), _T("�j"), _T("�k"), _T("�l"), _T("�m"), 

		_T("�n"), _T("�q"), _T("�t"), _T("�w"), _T("�z"),
		_T("�}"), _T("�~"), _T("��"), _T("��"), _T("��"),
		_T("��"), _T("��"), _T("��"), _T("��"), _T("��"),
		_T("��"), _T("��"), _T("��"), _T("��"), _T("��"),
		_T("��"), _T("��"), _T("��"), _T("��"), _T("�["),

		_T("�K"), _T("�M"), _T("�O"), _T("�Q"), _T("�S"),
		_T("�U"), _T("�W"), _T("�Y"), _T("�["), _T("�]"),
		_T("�_"), _T("�a"), _T("�d"), _T("�f"), _T("�h"),
		_T("�o"), _T("�r"), _T("�u"), _T("�x"), _T("�{"),
		_T("�p"), _T("�s"), _T("�v"), _T("�y"), _T("�|"),

		_T("�@"), _T("�B"), _T("�D"), _T("�F"), _T("�H"),
		_T("��"), _T("��"), _T("��"), _T("�b"), _T("�@"),

		_T("��"), _T("��"), _T("��"), _T("��"), _T("��"),
		_T("��"), _T("��"), _T("��"), _T("��"), _T("��"),
		_T("��"), _T("��"), _T("��"), _T("��"), _T("��"),
		_T("��"), _T("��"), _T("��"), _T("��"), _T("��"),
		_T("��"), _T("��"), _T("��"), _T("��"), _T("��"),
		
		_T("��"), _T("��"), _T("��"), _T("��"), _T("��"),
		_T("��"), _T("��"), _T("��"), _T("��"), _T("��"),
		_T("��"), _T("��"), _T("��"), _T("��"), _T("��"),
		_T("��"), _T("��"), _T("��"), _T("��"), _T("��"),
		_T("��"), _T("��"), _T("��"), _T("�@"), _T("�`"),
		
		_T("��"), _T("��"), _T("��"), _T("��"), _T("��"),
		_T("��"), _T("��"), _T("��"), _T("��"), _T("��"),
		_T("��"), _T("��"), _T("��"), _T("��"), _T("��"),
		_T("��"), _T("��"), _T("��"), _T("��"), _T("��"),
		_T("��"), _T("��"), _T("��"), _T("��"), _T("��"),
		
		_T("�`"), _T("�a"), _T("�b"), _T("�c"), _T("�d"),
		_T("�e"), _T("�f"), _T("�g"), _T("�h"), _T("�i"),
		_T("�j"), _T("�k"), _T("�l"), _T("�m"), _T("�n"),
		_T("�o"), _T("�p"), _T("�q"), _T("�r"), _T("�s"),
		_T("�t"), _T("�u"), _T("�v"), _T("�w"), _T("�x"),
		
		_T("��"), _T("��"), _T("��"), _T("��"), _T("��"),
		_T("��"), _T("��"), _T("��"), _T("��"), _T("��"),
		_T("��"), _T("��"), _T("��"), _T("��"), _T("��"),
		_T("��"), _T("��"), _T("��"), _T("��"), _T("��"),
		_T("��"), _T("��"), _T("��"), _T("��"), _T("��"),

		_T("�y"), _T("�@"), _T("�@"), _T("�@"), _T("�@"),
		_T("��"), _T("�@"), _T("�@"), _T("�@"), _T("�@"),
		_T("�@"), _T("�@"), _T("�@"), _T("�@"), _T("�@"),
		_T("�@"), _T("�@"), _T("�@"), _T("�@"), _T("�@"),
		_T("�@"), _T("�@"), _T("�@"), _T("�@"), _T("�@"),

		_T("�P"), _T("�Q"), _T("�R"), _T("�S"), _T("�T"),
		_T("�U"), _T("�V"), _T("�W"), _T("�X"), _T("�O")};
		*/
