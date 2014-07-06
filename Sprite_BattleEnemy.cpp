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
	// �Q�Ƃ̊m��
	pEnemy = _pEnemy;
	// �Q�Ƃ����݂��Ȃ���΃f�[�^�͍X�V���Ȃ�
	if(pEnemy->GetDataID() == 0) return false;
	// refID�����ɕ`��f�[�^���擾����
	UpdateRefID();
	// �`��ʒu���Z�b�g����
	SetPos(pEnemy->GetDrawX(), pEnemy->GetDrawY());
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