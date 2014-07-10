// Scene_Battle.cpp

#include "Scene_Battle.h"

#include "Func_MyGraphic.h"
#include "TempData.h"
#include "DXFont.h"
#include "DXInput.h"
#include "KeyConfig.h"

extern TempData		g_temp;
extern DXFont		g_font;
extern DXInput		g_input;
extern KeyConfig	g_key;

Scene_Battle::Scene_Battle():Scene_Base(){
	phaze = PRE_BATTLE;
	subPhaze = ASSERT_ACTION;
	enemyGroup = 0;
	dollsNum = 0;
	enemiesNum = 0;
}

bool Scene_Battle::Initialize(bool fSkipFrame){
	Scene_Base::Initialize(fSkipFrame);
	// �e�ϐ��̏�����
	phaze = BEFORE_BATTLE;
	subPhaze = ASSERT_ACTION;
	enemyGroup = g_temp.enemyGroup;
	// �G�Ɩ����̏�����
	for(int n=0; n<MAX_BATTLEDOLL; n++){
		dolls[n].Reset();
	}
	dollsNum = 0;

	for(int n=0; n<MAX_BATTLEENEMY; n++){
		enemies[n].Reset();
	}
	enemiesNum = 0;

	for(int n=0; n<MAX_UNITCOMMAND; n++){
		commands[n].Reset();
	}

	currentIndex = 0;
	// �����ƓG�̃Z�b�g�A�b�v
	if(!SetupDolls()){
		return false;
	}
	if(!SetupEnemy()){
		return false;
	}
	// �E�B���h�E�̃Z�b�g�A�b�v
	if(!SetupWindow()){
		return false;
	}
	// �X�v���C�g�̃Z�b�g�A�b�v
	if(!SetupSprite()){
		return false;
	}
	return true;

}

bool Scene_Battle::Terminate(){

	return true;
}

int Scene_Battle::Update(){
	bool result = true;
	// ���̃A�N�V�����Ɉڍs�����������������Ă��邩�ǂ����̔���
	if(CheckNextAction()){
		// ���̃A�N�V���������s����
		result = ExecuteAction();

		// ���̃t�F�C�Y�Ɉڍs����
		if(!result){
			NextPhaze();
		}	
	}
	// �E�B���h�E��X�v���C�g�Ȃǂ̃A�b�v�f�[�g���s���B
	UpdateObjects();

	return SCENE_NONE;

}

void Scene_Battle::UpdateObjects(){
	// �o�g�����b�Z�[�W�E�B���h�E�̃A�b�v�f�[�g
	w_battleMsg.UpdateA();
	w_aliceCommand.UpdateA();
	w_dollCommand.UpdateA();
	w_selectEnemy.UpdateA();
	w_focusedEnemy.UpdateA();
}

bool Scene_Battle::AttachDollPtrToSprite(){
	Game_BattleDoll*	pDoll	= NULL;
	int					index	= 0;
	bool				result	= true;
	for(int i=0; i<NUM_BATTLEDOLL_FRONT; i++){
		s_dolls[i].ResetDollPtr();
		index = GetFrontIndex(i);
		pDoll = GetDollPtr(index);
		if(pDoll == NULL && i <= dollsNum){
			result = false;
		}
		s_dolls[i].SetDollPtr(pDoll);
	}
	return result;
}

void Scene_Battle::Draw(){
	// �X�v���C�g�̕`��
	DrawDollsSprite();
	DrawEnemiesSprite();

	// �o�g�����b�Z�[�W�E�B���h�E�̕`��
	w_battleMsg.Draw();
	w_aliceCommand.Draw();
	w_dollCommand.Draw();
	w_selectEnemy.Draw();
	w_focusedEnemy.Draw();

}

bool Scene_Battle::SetupWindow(){
	// �o�g�����b�Z�[�W�E�B���h�E
	w_battleMsg.Setup(this);
	w_aliceCommand.MySetup();
	w_dollCommand.MySetup(this);
	w_selectEnemy.MySetup(this);
	w_focusedEnemy.MySetup(this);
	return true;
}

bool Scene_Battle::SetupSprite(){
	// �l�`�X�v���C�g
	for(int i=0; i<NUM_BATTLEDOLL_FRONT; i++){
		s_dolls[i].SetPosition(i);
		s_dolls[i].SetVisible(true);
	}
	if(!AttachDollPtrToSprite()) return false;
	// �G�X�v���C�g
	for(int i=0; i<MAX_BATTLEENEMY; i++){
		s_enemies[i].AttachBattleEnemy(&enemies[i]);
	}
	return true;
}

int Scene_Battle::GetFrontIndex(WORD position){
	int cntCount = 0;
	for(int n=0; n<MAX_BATTLEDOLL; n++){
		if(dolls[n].GetFront()){
			if(cntCount == position){
				return n;
			}else{
				cntCount++;
			}
		}
	}
	return -1;
}


BYTE Scene_Battle::OpenSelectEnemyWindow(){
	return w_selectEnemy.Open();
}


bool Scene_Battle::CheckNextAction(){
	switch(phaze){
	case BEFORE_BATTLE:
		// �������܎��̃t�F�C�Y�Ɉڍs����
		return true;
		break;
	case PRE_BATTLE:
		// �E�B���h�E��I�u�W�F�N�g���S�đҋ@��ԂɂȂ��Ă��邱�Ƃ��m�F���Ă��玟�ցB
		if(!w_battleMsg.IsReady()){
			return false;
		}
		return true;
		break;
	case ALICE_COMMAND:
		// �A���X�̃R�}���h�E�B���h�E�����Ă��邱�Ƃ��m�F���Ă��玟�ցB
		if(w_aliceCommand.GetState() == Window_Base::CLOSED){
			return true;
		}
		break;
	case ALICE_COMMAND_DO:
		// �E�B���h�E��I�u�W�F�N�g���S�đҋ@��ԂɂȂ��Ă��邱�Ƃ��m�F���Ă��玟�ցB
		if(!w_battleMsg.IsReady()){
			return false;
		}
		return true;
		break;
	case DOLLS_COMMAND:
		// �E�B���h�E�����Ă��āA���C���f�b�N�X��
		// �I����Ԃł���Ύ���
		if(w_dollCommand.GetState() == Window_Base::CLOSED){
			// ���͂������ʂ�ۑ�����
			if(currentIndex > 0){
				commands[currentIndex].Reset();

			}
			// ���݉��Ԗڂ̐l�`�̃R�}���h��I�����Ă��邩(�ŏ���0)
			currentIndex++;
			// �S�Ă̐l�`�̃R�}���h���I�����玟��
			if(currentIndex >= NUM_BATTLEDOLL_FRONT){
				return true;
			}else{
				w_dollCommand.Open();
			}
		}
		break;
	}
	return false;
}


bool Scene_Battle::ExecuteAction(){
	Game_BattleAction nextAction;
	switch(phaze){
	case BEFORE_BATTLE:
		// �������܎��̃t�F�C�Y�Ɉڍs����B
		return false;
		break;
	case PRE_BATTLE:
		// �A�N�V�����X�^�b�N�̓��e�����Ɏ��s����B
		nextAction = actionStack.Pop();
		if(nextAction.IsEmpty()){
			return false;
		}
		InterpretAction(&nextAction);
		break;
	case ALICE_COMMAND:
		// �������܎��̃t�F�C�Y�Ɉڍs����B
		return false;
		break;
	case ALICE_COMMAND_DO:
		// �A�N�V�����X�^�b�N�̓��e�����Ɏ��s����B
		nextAction = actionStack.Pop();
		if(nextAction.IsEmpty()){
			return false;
		}
		InterpretAction(&nextAction);
		break;
	case DOLLS_COMMAND:
		// �������܎��̃t�F�C�Y�Ɉڍs����B
		return false;
		break;
	}
	return true;
}

void Scene_Battle::NextPhaze(){
	// �ω��O��phaze�l��switch����
	switch(phaze){
	case BEFORE_BATTLE:
		phaze = PRE_BATTLE;
		break;
	case PRE_BATTLE:
		phaze = ALICE_COMMAND;
		break;
	case ALICE_COMMAND:
		phaze = ALICE_COMMAND_DO;
		break;
	case ALICE_COMMAND_DO:
		phaze = DOLLS_COMMAND;
		break;
	}

	// �A�N�V�����X�^�b�N�̉��
	actionStack.ClearAll();

	// �R�}���h�̉��
	ClearCommands();

	// �ω����phaze�l��switch����
	switch(phaze){
	case BEFORE_BATTLE:
		break;
	case PRE_BATTLE:
		SetupPreBattle();
		break;
	case ALICE_COMMAND:
		SetupAliceCommand();
		break;
	case ALICE_COMMAND_DO:
		SetupAliceCommandDo();
		break;
	case DOLLS_COMMAND:
		SetupDollsCommand();
		break;
	}
}

void Scene_Battle::SetupPreBattle(){
	Game_BattleAction action;
	// �X�^�b�N�Ȃ̂ŋt���ɐς�ł����B

	// �e�L�����N�^�[�̃X�e�[�g�ɉ�������ԕ\���B
	
	// �e�G�L�����̖��O��\���B
	action.SetType(Game_BattleAction::TYPE_CALLENEMYNAME);
	action.SetActor(NULL);
	action.SetOpponent(NULL);
	action.SetFlags(0x00000000);
	action.SetParam(0);
	actionStack.Push(action);
	ExecuteAction(); // �ŏ���1�t���[����IDLE�ɂȂ�Ȃ��悤��
}

void Scene_Battle::SetupAliceCommand(){
	// �A���X�̃R�}���h�E�B���h�E���J��
	w_aliceCommand.Open();
}

void Scene_Battle::SetupAliceCommandDo(){
	Game_BattleAction action;
	switch(w_aliceCommand.GetResult()){
	case ALICE_COMMAND_BATTLE:
		// �������Ȃ�
		break;
	case ALICE_COMMAND_UNITCHANGE:
		break;
	case ALICE_COMMAND_SPECIAL:
		break;
	case ALICE_COMMAND_ESCAPE:
		// �_�~�[�̃R�����g�����
		action.SetType(Game_BattleAction::TYPE_CALLENEMYNAME);
		action.SetActor(NULL);
		action.SetOpponent(NULL);
		action.SetFlags(0x00000000);
		action.SetParam(0);
		actionStack.Push(action);
		break;
	}
}

void Scene_Battle::SetupDollsCommand(){
	// �R�}���h���͂𑣂��E�B���h�E���J��
	// �ŏ��ɃC���N�������g���s����0�ɂȂ�̂�-1����n�߂�B
	currentIndex = -1;

}

