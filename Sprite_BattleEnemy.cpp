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

Sprite_BattleEnemy::Sprite_BattleEnemy(){
	Sprite_Base::Sprite_Base();
	pEnemy = NULL;
	refID = 0;
	cx = cy = 0;
	baseExRate = 0;
	hImg = 0;
	enabled = false;
	visible = false;
}

bool Sprite_BattleEnemy::AttachBattleEnemy(Game_BattleEnemy* _pEnemy){
	if(_pEnemy == NULL) return false;
	// �Q�Ƃ̊m��
	pEnemy = _pEnemy;
	// �Q�Ƃ����݂��Ȃ���΃f�[�^�͍X�V���Ȃ�
	if(pEnemy->GetDataID() == 0) return false;
	// refID�����ɕ`��f�[�^���擾����
	UpdateRefID();
	// �`��ʒu���Z�b�g����
	SetPos((float)pEnemy->GetDrawX(), (float)pEnemy->GetDrawY());
	// �L����
	enabled = true;
	visible = true;
	return true;
}

void Sprite_BattleEnemy::UpdateRefID(){
	// �e�f�[�^��ID����擾����
	refID = pEnemy->GetDataID();
	// �Q�Ɨp�̃f�[�^�����邩
	if(refID == 0) return;
	// �Q�Ɨp�̃f�[�^���擾
	Data_EnemyDraw_Each* pDrawData = d_enemyDraw.GetEnemyDraw(refID);
	// �f�[�^�̑��݂��m�F
	if(pDrawData == NULL) return;
	// ���S�̕`��ʒu���w��
	cx = pDrawData->GetCX();
	cy = pDrawData->GetCY();
	// �摜�T�C�Y�ƕ\���{������X�v���C�g�̑傫�����擾
	SetSize(
		(int)(pDrawData->GetIWidth()*pDrawData->GetExRate()),
		(int)(pDrawData->GetIHeight()*pDrawData->GetExRate()));
	// �摜�̕\���{�����擾
	baseExRate = pDrawData->GetExRate();
	// �摜�̃n���h�����擾
	hImg = pDrawData->GetHImg(pEnemy->GetAttr());
}

void Sprite_BattleEnemy::Update(){
	if(pEnemy->GetDataID() != refID){
		UpdateRefID();
	}

	Sprite_Base::Update();
}

void Sprite_BattleEnemy::Draw() const{
	if(refID == 0) return;
	if(hImg == 0) return;
	if(pEnemy == NULL) return;
	// �����x
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, param.opacity);
	if(visible){
		// �\����Ԃ̔���
		if(!param.hide){
			// �{�̂̕`��
			DrawRotaGraph3F(
				GetX(), GetY(), cx, cy,
				baseExRate*param.xScale, baseExRate*param.yScale, param.angle,
				hImg, 1, 0);
		}
		// HP�̕`��
		DrawHPGauge((int)GetX(), (int)GetY());
	}
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
}

#define BATTLEENEMY_HPGAUGE_WIDTH	120
#define BATTLEENEMY_HPGAUGE_HEIGHT	10

void Sprite_BattleEnemy::DrawHPGauge(int x, int y) const{
	// �g��`��
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
	// �Q�[�W��`��
	float rate = (float)pEnemy->GetHP()/pEnemy->GetMaxHP();
	int color = 0;
	switch(pEnemy->GetAttr()){
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
	// HP�𐔒l�ŕ`��
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