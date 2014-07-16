// Scene_Sample.cpp
// ��{�I�ɂ͌��݂̃f�[�^��\�����邾���̃V�[���B
// �����L���O���肵���ꍇ�̓����N�C�����\������B

#include "Scene_Sample.h"

// �ǉ��w�b�_�t�@�C��
#include "MyTask.h"
#include "MyTask_Sample.h"

#include "Static_Game.h"
#include "DXInput.h"
#include "KeyConfig.h"
#include "GlobalData.h"

#include "Player_Sample.h"

extern DXInput g_input;
extern KeyConfig g_key;
extern GlobalData g_dat;

extern MyGroup* gMyTask_Sample;


Scene_Sample::Scene_Sample():Scene_Base(){
}

bool Scene_Sample::Initialize(bool fSkipFrame){
	Scene_Base::Initialize(fSkipFrame);

	return true;
}

bool Scene_Sample::Terminate(){

	return true;
}

int Scene_Sample::Update(){
	// �^�X�N�𖈃t���[���ǉ�����
	MyTask* pTask = gMyTask_Sample->Call();
	if(pTask!=NULL){
		new (pTask) MyTask_Sample();
	}

	if(g_input.pushedKey & g_key.input[BTN_CHOOSE]){
		ReserveScene(SCENE_END, 120);
	}

	// �^�X�N�𖈃t���[���X�V����
	Update_MyTask_Sample();

	// ���@�Ƃ̐ڐG�̔���
	Check_MyTask_Sample_Burst(player.GetX(), player.GetY());

	// �G���m�̘A�������̔���
	Check_MyTask_Sample_Chain_Burst();

	// �I�u�W�F�N�g�ł͂Ȃ�
	player.Update();

	return SCENE_NONE;
}

void Scene_Sample::Draw() const{
	// ���_�̕`��
	DrawBox(0, WND_HEIGHT-20, g_dat.score, WND_HEIGHT-15, GetColor(132, 132, 132), 1);

	int div = 32;
	// �c��
	for(int lx = 0; lx < WND_WIDTH; lx += div){
		DrawLine(lx, 0, lx, WND_HEIGHT, GetColor(64, 64, 64), 1);
	}
	// ����
	for(int ly = 0; ly < WND_HEIGHT; ly += div){
		DrawLine(0, ly, WND_WIDTH, ly, GetColor(64, 64, 64), 1);
	}

	Draw_MyTask_Sample();

	DrawReserveFade();



	// �I�u�W�F�N�g�ł͂Ȃ�
	player.Draw();
}

