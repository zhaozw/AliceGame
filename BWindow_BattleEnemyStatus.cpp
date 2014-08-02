// BBWindow_BattleEnemyStatus.cpp

#include "BWindow_BattleEnemyStatus.h"
#include <DxLib.h>

#include "Game_BattleEnemy.h"
#include "WindowSkin.h"
#include "Scene_Battle.h"
#include "Data_EnemyParam.h"
#include "DXFont.h"

extern WindowSkins		g_wndSkins;
extern Data_EnemyParam	d_enemyParam;

BWindow_BattleEnemyStatus::BWindow_BattleEnemyStatus() : Window_Info(){
	pEnemy = NULL;
}

void BWindow_BattleEnemyStatus::Setup(Scene_Battle* _pScene){
	// �傫��������
	WINDOWAREA frame;
	WINDOWAREA content;
	int frameSize = 16;
	frame.x = 0;
	frame.y = 0;
	frame.w = WND_BATTLEENEMYSTATUS_W;
	frame.h = WND_BATTLEENEMYSTATUS_H;
	content.x = frameSize;
	content.y = frameSize;
	content.w = frame.w - frameSize * 2;
	content.h = frame.h - frameSize * 2;

	// �E�B���h�E�̃Z�b�g�A�b�v
	Window_Info::Setup(&g_wndSkins.skin[WNDSKIN_SIMPLE], frame, content);

	pScene = _pScene;
}

void BWindow_BattleEnemyStatus::OpenWithEnemy(Game_BattleEnemy* _pEnemy, BYTE pos){
	pEnemy = _pEnemy;
	/*
	SetPosition(_x, _y);
	*/
}

bool BWindow_BattleEnemyStatus::ChangeRefEnemy(Game_BattleEnemy* _pEnemy){
	if (pEnemy != _pEnemy){
		pEnemy = _pEnemy;
		ContentChanged();
		return true;
	}
	return false;
}

void BWindow_BattleEnemyStatus::Update(){
	switch(state){
	case UPDATING:
		if(CheckClose()){
			Close(true, false);
			pScene->ResetInfoWindowID();
		}
	}
	Window_Info::Update();
}

void BWindow_BattleEnemyStatus::OnOpened(){
	if(pScene){
		pEnemy = pScene->GetTargetEnemyPtr();
	}
}

void BWindow_BattleEnemyStatus::DrawContent() const{
	if(!GetActive()) return;
	if(pEnemy == NULL) return;
	// ���O�̕`��
	TCHAR buf[64];
	int width = 0;
	int cntY = frameArea.y;
	int cx = frameArea.x + frameArea.w/2;
	int param = 0;
	pEnemy->GetName(buf, 64);
	width = GetStrWidth(buf, strlen(buf), windowFont.hFont);
	cntY += 24;
	DrawStr(cx-width/2, cntY, buf, windowFont.color, windowFont.hFont);

	// HP/�ő�HP�̕`��
	cntY += 32;
	wsprintf(buf, _T("�g�o�F%d/%d"), pEnemy->GetHP(), pEnemy->GetMaxHP());
	width = GetStrWidth(buf, strlen(buf), windowFont.hFont);
	DrawStr(frameArea.x+(frameArea.w-width)/2, cntY, buf, windowFont.color, windowFont.hFont);

	// �e�p�����[�^�̕`��
	cntY += FONTSIZE_INFO+8;
	TCHAR paramName[][8] = {
		"�U��", "�h��", "�q��", "����", "�Z�I"};
	for(int i=0; i<5; i++){
		switch(i){
		case 0:
			param = pEnemy->GetAtk();
			break;
		case 1:
			param = pEnemy->GetDef();
			break;
		case 2:
			param = pEnemy->GetSpd();
			break;
		case 3:
			param = pEnemy->GetMgc();
			break;
		case 4:
			param = pEnemy->GetTec();
			break;
		}
		wsprintf(buf, _T("%s�F%d"), paramName[i], param);
		DrawStr(
			frameArea.x+40, cntY + i*(FONTSIZE_INFO+4),
			buf, windowFont.color, windowFont.hFont);
	}

}