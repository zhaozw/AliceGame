#ifndef FUNC_MYGRAPHIC_H
#define FUNC_MYGRAPHIC_H

#include <Windows.h>
#include "DXFont.h"

// Func_Graphics�Ɋ܂܂Ȃ��A���̃Q�[�����L�̕`��֐����L�q����B

// �g�p���镶���̍ő吔�B
#define MAX_NAMESTRING		255 // 17�s�~5�����~3��

// �����̃T�C�Y
#define SIZE_NAMESTR		(FONTSIZE_STR)
#define SIZE_NAMESTR_L		(FONTSIZE_STR_L)

// ��΂̂�����̃f�t�H���g�T�C�Y
#define SIZE_ATTRSTONE		48

// �����A�C�R���̃T�C�Y
#define SIZE_ATTRICON		24

// �l�`�̃C���X�g�̉摜�T�C�Y
#define WIDTH_DOLLILLUST	512
#define HEIGHT_DOLLILLUST	512

// �l�`�̃A�C�R���̉摜�T�C�Y
#define WIDTH_DOLLICON		96
#define HEIGHT_DOLLICON		128

// �X�e�[�^�X��ʗp�ɐl�`�̎�ނ�`�悷��B
void DrawDollType(int x, int y, BYTE type, int color);

// ���O�Ɏg�p�ł��镶����`�悷��B
// isLarge : �`��o���镶���̃T�C�Y�͓��ށB
void DrawNameChar(int x, int y, WORD index, bool isLarge);

// �����A�C�R����`�悷��B
void DrawAttrIcon(int x, int y, BYTE attr);

// �����̕�΂�`�悷��B
void DrawAttrStone(int cx, int cy, BYTE group, BYTE attr, float exRate=1.0, int time=0);

// �l�`�̃^�C�v���̕������w�肵���t�H���g�ŕ`�悷��B
void DrawGroupName(int x, int y, BYTE group, int hFont);

// �l�`�C���X�g�̕`����s���B
// �w�肷����W�͕`��̒��S�B
// type : �l�`�̎��
// attr : �l�`�̑���
// exRate : �g�嗦
// rot : ��]�p
void DrawDollIllust(int cx, int cy, BYTE type, BYTE attr, float exRate, float rot);
void DrawDollIllust2(int cx, int cy, BYTE type, BYTE attr,
	float exRateX, float exRateY, float rot);

// �l�`�A�C�R���̕`����s���B
// �������̎�ނ�����B
// ����̍��W���w�肵�Ēʏ�`��B
void DrawDollIcon(int x, int y, BYTE type, BYTE attr, BYTE face);
// ����ƉE���̍��W���w�肵�Ċg��k���`��B
void DrawDollIconExtend(int x1, int y1, int x2, int y2, BYTE type, BYTE attr, BYTE face);
// ���S�̍��W���w�肵�ĉ�]�g��`��
void DrawDollIconRot(int cx, int cy, 
	BYTE type, BYTE attr, BYTE face, float exRate, float rot); 

#endif // FUNC_MYGRAPHIC_H