#ifndef SCENE_BATTLE_H
#define SCENE_BATTLE_H

#include "Scene_Base.h"
#include "Static_Battle.h"
#include "Game_BattleUnit.h"
#include "Game_BattleDoll.h"
#include "Game_BattleEnemy.h"
#include "Game_UnitCommand.h"
#include "Game_BattleAction.h"
#include "Window_BattleMessage.h"
#include "BWindow_AliceCommand.h"
#include "BWindow_DollCommand.h"
#include "BWindow_DollSkill.h"
#include "BWIndow_SelectEnemy.h"
#include "BWindow_FocusedUnit.h"
#include "Window_SimpleDollStatus.h"

#include "Sprite_BattleDoll.h"
#include "Sprite_BattleEnemy.h"

#define INFOWINDOW_NONE				0
#define INFOWINDOW_DOLLINFO			1
#define INFOWINDOW_ENEMY			2

class Scene_Battle : public Scene_Base{
public:
	// �퓬�̃t�F�C�Y���L�q����B
	// ��{�I�ɁA
	// �@�t�F�C�Y�J�n���ɁASceneBattle��SetupPhaze�֐��ɂ��
	//   actionStack�ɂ��̃t�F�C�Y�̃A�N�V�������Z�b�g�����
	// �AactionStack���ォ�珈�����Ă����B
	//   �e�A�N�V�������������邲�ƂɁA�E�B���h�E�̓��e��X�v���C�g�ɕω���������̂�
	//   �����̕ω����I���܂őҋ@����B
	// �B�S�Ă�actionStack������ꂽ�Ƃ���Ŏ��̃t�F�C�Y�Ɉڍs����B
	// �Ƃ�������ɂȂ�B
	//
	// BATTLE_DO�t�F�C�Y�ɂ����ẮA
	// actionStack�x�[�X�ł͂Ȃ�Game_UnitCommand�N���X��commands�x�[�X�Ői�s����B
	// ���Ȃ킿�Acommand�̓��e�����Ԃɏ������Ă������A
	// command����Ƃ�actionStack���ǉ��E����E���Z�b�g�����B
	// �S�Ă�commands�����s���ꂽ�Ƃ���Ŏ��̃t�F�C�Y�Ɉڍs����B

	enum BATTLEPHAZE{
		BEFORE_BATTLE,		// �퓬�O�iPRE_BATTLE�̑O�ɓ���_�~�[�j
		PRE_BATTLE,			// �퓬�O
		ALICE_COMMAND,		// �A���X�̃R�}���h��I��
		ALICE_COMMAND_DO,	// �A���X�̃R�}���h�����s
		DOLLS_COMMAND,		// �l�`�̃R�}���h��I��
		ENEMIES_COMMAND,	// �G�̃R�}���h��I���i�����ɏI������j
		BEFORE_SORT,		// �f�����\�[�g�̑O�Ɋe�R�}���h�̔�����s��
		AFTER_SORT,			// �^�[���̍ŏ��i�\�[�g�̌�j
		BATTLE_DO,			// �퓬
		AFTER_TURN,			// �^�[���I����
		POST_BATTLE,		// �퓬�I��
		END_BATTLE,			// �V�[���I��(�����Ƀt�F�[�h�A�E�g���ăV�[���ړ�)
	};

private:
	// ���ݐ퓬���Ă���G�O���[�vID���w�肷��B
	WORD								enemyGroup;
	// ���݂̏󋵂�\��
	enum BATTLEPHAZE					phaze;
	// �퓬�̌��ʂ�\��
	BYTE								battleResult;
	// �����E�G���j�b�g�͒ʏ�̔z��ŕ\������
	// �������j�b�g�̔z��
	Game_BattleDoll						dolls[MAX_BATTLEDOLL];
	int									dollsNum;	// �������j�b�g�̍ő吔�i�퓬�s�\�Ҋ܂ށj
	// �G���j�b�g�̔z��
	Game_BattleEnemy					enemies[MAX_BATTLEENEMY];
	int									enemiesNum;	// �G���j�b�g�̍ő吔�i�퓬�s�\�Ҋ܂ށj
	// �U���R�}���h�̔z��
	Game_UnitCommand					commands[MAX_UNITCOMMAND+1];
	// DOLL_COMMAND�y��ENEMY_COMMAND��
	// ���݉��Ԗڂ̃R�}���h�܂œ����Ă��邩�B
	// DO_BATTLE��
	// ���ݏ������Ă���R�}���h�̃C���f�b�N�X�B
	int									commandIndex;
	// ���݂̃C���f�b�N�X�i�R�}���h�I�����Ȃǁj
	int									currentIndex;
	// ���݂�Game_UnitCommand����������t�F�C�Y
	int									commandPhaze;
	// �A�N�V�����̃X�^�b�N
	Game_BattleActionStack				actionStack;
	// ���b�Z�[�W�E�B���h�E
	Window_BattleMessage				w_battleMsg;
	// �A���X�̃R�}���h�E�B���h�E
	BWindow_AliceCommand				w_aliceCommand;
	// �l�`�̃R�}���h�E�B���h�E
	BWindow_DollCommand					w_dollCommand;
	// �l�`�̓��Z���X�g�E�B���h�E
	BWindow_DollSkill					w_dollSkill;
	// �G�̑I���E�B���h�E
	BWindow_SelectEnemy					w_selectEnemy;
	// �G�̃t�H�[�J�X�E�B���h�E
	BWindow_FocusedUnit					w_focusedEnemy;
	// �l�`�̏���\������E�B���h�E
	Window_SimpleDollStatus				w_simpleDollStatus;
	// ���\���p�E�B���h�E�̏�ԁB
	// 0�Ȃ�J���Ă��Ȃ��A����ȊO�Ȃ�J���Ă���B
	BYTE								infoWindowID;
	// �l�`�̃X�v���C�g
	Sprite_BattleDoll					s_dolls[NUM_BATTLEDOLL_FRONT];
	// �G�̃X�v���C�g
	Sprite_BattleEnemy					s_enemies[MAX_BATTLEENEMY];
public:
	// �R���X�g���N�^
	Scene_Battle();
	// ����������
	virtual bool Initialize(bool fSkipFrame);
	// �I������
	virtual bool Terminate();
	
	// �X�V����
	virtual int Update();
	// �`�揈��
	virtual void Draw() const;

	//=========================================
	// �V�[���S�̂̐���
	// Scene_Battle.cpp�ɋL�q����B

	// �E�B���h�E�̏��������s���B
	bool SetupWindow();

	// �X�v���C�g�̏��������s���B
	bool SetupSprite();

	// ���̃A�N�V�����ɐi�ނ��ǂ����̔�����s���B
	// �E�B���h�E��X�v���C�g�Q���`�F�b�N���āA
	// �S�đҋ@��ԂɂȂ��Ă��邩�ǂ������m�F����B
	bool CheckNextAction();

	// ���̃A�N�V���������s����B
	// �������A�N�V���������s���ꂽ�ꍇ��true���A
	// ���Ɏ��s����ׂ��A�N�V�������Ȃ������̃t�F�C�Y�Ɉڍs����ꍇ��false��Ԃ��B
	bool ExecuteAction();

	// ���̃t�F�C�Y�Ɉڍs����B
	void NextPhaze();

	// �V�[�����I������B
	// �ǂ̃V�[���Ɉړ����邩�͗l�X�ȕϐ��ɂ���Č��߂�B
	int GetNextScene();

	// ���̃t�F�C�Y�Ɉڍs�����ۂ̏����B
	// �֐�NextPhaze������s�����B
	// �e�t�F�C�Y���ƂɎ��s����A�N�V�������Z�b�g����B
	void SetupPreBattle();		// PRE_BATTLE�ɂȂ�����
	void SetupAliceCommand();	// �A���X�̃R�}���h�E�B���h�E���J��
	void SetupAliceCommandDo(); // �A���X�̃R�}���h�����s����
	void SetupDollsCommand();	// �l�`�̃R�}���h�E�B���h�E���J�� 
	void SetupEnemiesCommand();	// �G�̃R�}���h�����肷��B(�����ɏI���)
	void SetupBeforeSort();		// �\�[�g�O�̃R�}���h������s���B
	void SetupAfterSort();		// �\�[�g��A�^�[���J�n���B�X�e�[�g�̔���ȂǁB
	void SetupBattleDo();		// �퓬�B
	void SetupAfterTurn();		// �^�[���I�����B�X�e�[�g�̔���ȂǁB
	void SetupPostBattle();		// �퓬�I�����BbattleResult�̓��e�ɂ���ĕ���B


	// �K�v�ȃI�u�W�F�N�g�Q�̃A�b�v�f�[�g���s���B
	void UpdateObjects();
	
	// �l�`�̔z�񂪕ς�����ۂɁA�l�`�X�v���C�g�ɐl�`�����蓖�Ē����B
	bool AttachDollPtrToSprite();

	// �퓬���I����Ă��Ȃ����𔻒f����B
	bool CheckBattleResult();

	// ���E�B���h�E�����B
	// ���݂�infoWindow�̒l�ɉ����A�J����Ă�����̂����B
	void CloseInfoWindow();

	//=========================================
	// �A�N�Z�T�֘A
	// �\�[�X�t�@�C���ɋL�q������̂�Scene_Battle.cpp�ɋL�q����B
	int GetDollsNum(){ return dollsNum; } ;
	int GetEnemiesNum(){ return enemiesNum; };

	// �l�`�̃|�C���^���擾����B
	Game_BattleDoll*	GetDollPtr(int index){
		if(index < 0 || index >= MAX_BATTLEDOLL) return NULL;
		if(dolls[index].GetIsUsed()){
			return &dolls[index];
		}else{
			return NULL;
		}
	}

	// �G�L�����̃|�C���^���擾����B
	Game_BattleEnemy*	GetEnemyPtr(int index){
		if(index < 0 || index >= MAX_BATTLEENEMY) return NULL;
		if(enemies[index].GetIsUsed()){
			return &enemies[index];
		}else{
			return NULL;
		}
	}

	// �O���i�Ԗڂɋ���l�`���AGame_BattleDoll�̔z��̒��ł͉��Ԗڂ����擾����B
	int	GetFrontIndex(WORD position);

	// �O��̎w�肵�����Ԃ̐l�`�̃|�C���^��Ԃ��B
	// checkCanTarget��true�ɂ���ƁA�l�`���퓬�s�\�ł������ꍇNULL��Ԃ��B
	Game_BattleDoll*	GetFrontDollPtr(WORD index, bool checkCanTarget=false);
	// �O��̐l�`��̂������_���ŕԂ��B
	Game_BattleDoll*	GetRandomDollPtr();
	// �G�L������̂̃|�C���^�������_���ŕԂ��B
	Game_BattleEnemy*	GetRandomEnemyPtr();

	// �l�`�ւ̃|�C���^��n���ƁA
	// ���̐l�`�̃X�v���C�g�̃|�C���^��Ԃ��B
	Sprite_BattleDoll* GetDollSprite(Game_BattleDoll* dollPtr);

	// �G�ւ̃|�C���^��n���ƁA
	// ���̓G�̃X�v���C�g�̃|�C���^��Ԃ��B
	Sprite_BattleEnemy* GetEnemySprite(Game_BattleEnemy* enemyPtr);




	// �e��E�B���h�E���J���B
	// ���̃E�B���h�E����̎Q�ƂȂǂ̌`�B

	// �G�I���E�B���h�E
	BYTE	OpenSelectEnemyWindow();
	int		GetSelectEnemyIndex(){ return w_selectEnemy.GetSelectIndex(); };
	BWindow_SelectEnemy*	GetWndSelectEnemyPtr(){ return &w_selectEnemy; };
	BYTE	OpenFocusedEnemyWindow();
	int		GetFocusedEnemyIndex(){ return w_focusedEnemy.GetSelectIndex(); };
	BWindow_FocusedUnit*	GetWndFocusedUnitPtr(){ return &w_focusedEnemy; };
	BYTE	OpenDollSkillWindow();
	int		GetDollSkillIndex(){ return w_dollSkill.GetSelectIndex(); };
	BWindow_DollSkill*		GetWndDollSkillPtr(){ return &w_dollSkill; };

	// ���b�Z�[�W�E�B���h�E�ւ̃��b�Z�[�W�̒ǉ��B
	bool AddStockMessage(LPTSTR str){
		return w_battleMsg.AddStockMsg(str, strlen(str));
	}

	//=========================================
	// �O���f�[�^�̌Ăяo���E�f�[�^�A�W�֘A
	// Scene_Battle_Data.cpp�ɋL�q����B
	// �l�`���Ăяo���i�����p�[�e�B���Z�b�g����j�֐��B

	// �����̐l�`�̃Z�b�g�A�b�v���s���B
	bool SetupDolls();
	// �G�p�[�e�B�̃Z�b�g�A�b�v���s���B
	bool SetupEnemy();
	// �f�o�b�O�p�B�\�[�X�R�[�h�Œ��ڎw�肷��B
	bool LoadDefaultDolls(int defaultID);	
	// �f�[�^�x�[�X�t�@�C������ID���w�肵�ēǂݍ��ށB
	// �t�@�C���p�X��dat_battle\\preset_dolls%02d.csv
	bool LoadPresetDolls(int presetID);
	// �O���[�vID���w�肵�ăf�[�^�x�[�X����ǂݍ��ށB
	// SetupEnemy����g�p�����B
	bool LoadEnemyGroup();
	// Game_BattleEnemy�̗v�f��Ɏw�肵���GID�̏���ǂݍ��ށB
	// ���łɕ`��ʒu���Z�b�g����B
	// LoadEnemyGroup����g�p�����B
	bool LoadEnemyData(WORD index, WORD enemyID, int drawX, int drawY);

	//=========================================
	// ���j�b�g�֘A
	// Scene_Battle_Unit.cpp�ɋL�q����B
	// �\�͒l���w�肷��B
	// index : �z��̗v�f�ԍ�
	// hp, maxhp, atk, spd, mgc, tec : �e�p�����[�^
	// �l�`�̃p�����[�^�Ȃǂ��w�肷��A�N�Z�T�B
	void SetDollParams(int index, int hp, int maxhp, int atk, int spd, int mgc, int tec);
	// �G�̃p�����[�^�Ȃǂ��w�肷��A�N�Z�T�B
	void SetEnemyParams(
		int index, int hp, int maxhp, int atk, int def, int spd, int mgc, int tec);	

	//=========================================
	// Game_BattleAction�̓��e�̏����B
	// Scene_Battle_Action.cpp�ɋL�q����B
	bool InterpretAction(Game_BattleAction* pAction);

	bool Action_Damage(Game_BattleAction* pAction);
	bool Action_Heal(Game_BattleAction* pAction);
	bool Action_CallEnemyName();
	bool Action_CallVictory();
	bool Action_CallLose();
	bool Action_AssertAttack(Game_BattleAction* pAction);
	bool Action_AssertSkill(Game_BattleAction* pAction);
	bool Action_AssertGuard(Game_BattleAction* pAction);

	//=========================================
	// Game_UnitCommand�̓��e�̏����B
	// Scene_Battle_Command.cpp�ɋL�q����B

	// commandPhaze :
	// �Ⴆ�Βʏ�U���ɂ���A
	// ���ۂ̍U���O�ɍs���锻��i�h������Ă���L�����N�^�[�̖h��͕␳�Ƃ��j��
	// �U����ɍs���锻��i���̍U���̂݃p���[�A�b�v�̃X�e�[�g�Ȃǁj������B
	// ���UnitCommand�̉��߂��A�������̃t�F�C�Y���ƂɊǗ����邽�߂�
	// �p�����[�^�BStatic_Battle.h����COMMANDPHAZE_xxx�萔�Q�Œ�`�����B
	// 
	char InterpretCommand(Game_UnitCommand* pCmd, int commandPhaze=COMMANDPHAZE_NOPHAZE);
	// commandPhaze�ɂ���ĕ��򂷂�
	// �߂�l :
	// -1 : �G���[
	// 0 : �����������s��Ȃ�����/�R�}���h���s��҂K�v���Ȃ��i�����Ɏ��̃t�F�C�Y�ցj
	// 1 : �������s�����i�R�}���h���s��҂j
	// �����������s�����ꍇ��true���A
	// �����������s��Ȃ������ꍇ��false��Ԃ��B
	char InterpretCommand_NoPhaze(Game_UnitCommand* pCmd);
	char InterpretCommand_Before_Sort(Game_UnitCommand* pCmd);
	char InterpretCommand_After_Sort(Game_UnitCommand* pCmd);
	char InterpretCommand_Fix_Command(Game_UnitCommand* pCmd);
	char InterpretCommand_Fix_Target(Game_UnitCommand* pCmd);
	char InterpretCommand_Assert(Game_UnitCommand* pCmd);
	char InterpretCommand_Pre_Action(Game_UnitCommand* pCmd);
	char InterpretCommand_Action(Game_UnitCommand* pCmd);
	char InterpretCommand_Check_Death(Game_UnitCommand* pCmd);
	char InterpretCommand_Post_Action(Game_UnitCommand* pCmd);

	//=========================================
	// �퓬���̏����Z
	// Scene_Battle_Calc.cpp�ɋL�q����B

	// �R�}���h��ǉ�����B
	bool SetCommand(Game_UnitCommand cmd);
	
	// �R�}���h�����菜���B
	bool RemoveOneCommand();

	// �G�̃R�}���h�������Œǉ�����B
	// ������SetEnemyCommand���g�p����B
	bool SetEnemyCommands();

	// ���݃A�N�e�B�u�ȃR�}���h�E�B���h�E���L�����Z���o���邩���擾����B
	bool GetCommandWindowIsCancelable(int currentIndex);

	// �|�C���^���g�p���A�G�̃R�}���h���Z�o����B
	Game_UnitCommand GetEnemyCommand(Game_BattleEnemy* pEnemy);

	// �w�肵���G�̂���R�}���h�̗D�揇�ʂ�Ԃ��B
	// (�C���f�b�N�X�ɑ�������R�}���h�����݂��Ȃ��ꍇ�A
	//  �܂��A�s�������𖞂����Ȃ��ꍇ��0��Ԃ��B)
	int GetEnemyCommandPriority(Game_BattleEnemy* pEnemy, int index);

	// �S�Ă̍s���̒��ōő�̗D��x�����s���̗D��x�̒l��Ԃ��B
	int GetEnemyCommandMaxPriority(Game_BattleEnemy* pEnemy);

	// �w�肵���G�̂���R�}���h����
	// ���s����R�}���h���쐬����B
	Game_UnitCommand MakeEnemyCommand(Game_BattleEnemy* pEnemy, int index);

	// �퓬�s���̃\�[�g���s���B
	bool SortUnitCommands();
	
	// commands�̓��e��S�ăN���A����B
	void ClearCommands();

	// InterpretCommand_Action���ł̂ݎg�p�����B
	// �g�p�ҁA�^�[�Q�b�g�A�p�����[�^��^���邱�Ƃ�
	// �_���[�W��^����s���̐��ۂ𔻒f����B
	// �߂�l�����̔��f�B
	BYTE CheckDamageAction(Game_BattleUnit* pActor, Game_BattleUnit* pTarget, int param);
	

	// �_���[�W�v�Z�B
	// �I�v�V�������w�肷�邱�ƂŁA�ʏ�U���ȊO�̃_���[�W�v�Z�ɂ��Ή�����B
	int CalcDamage(Game_BattleUnit* pAttacker, Game_BattleUnit* pOpponent, int param);

	// �񕜌v�Z�B
	// �I�v�V�������w�肷�邱�ƂŁA�X�L���ȊO�̉񕜗ʌv�Z�ɂ��Ή�����B
	int CalcHeal(Game_BattleUnit* pAttacker, Game_BattleUnit* pOpponent, int param);

	// ���鑮���ɑ΂��Ă��鑮�����L�����s������Ԃ��B
	// 0 : ����
	// 1 : �L��
	// 2 : �s��
	BYTE GetAttrAffinity(BYTE attackerAttr, BYTE opponentAttr);

	// �����_���[�W�̔{�����v�Z����B
	float GetAttrRate(BYTE attackerAttr, BYTE opponentAttr);

	// ���j�b�g�ɃX�e�[�g�����蓖�Ă�B
	// pUnit		: ���蓖�Ă郆�j�b�g
	// stateRefID	: �X�e�[�g��ID
	// showMessage	: ���b�Z�[�W��\�����邩�ۂ�
	// level		: �X�e�[�g���x��
	BYTE AddStateToUnit(Game_BattleUnit* pUnit, WORD stateRefID,
		bool showMessage=true, int level=1);

	// �X�e�[�g�̃^�[���o�߂���������B
	// �ꊇ���ă^�[���I�����ɍs���B
	void UpdateStateTurn();

	//=========================================
	// �`��
	// ���L�̊֐���Scene_Battle_Draw.cpp�ɋL�q����B

	// �w�i��`�悷��B
	void DrawBG() const;

	// �l�`�̃X�v���C�g��`�悷��B
	void DrawDollsSprite() const;
	// �G�L�����̃X�v���C�g��`�悷��B
	void DrawEnemiesSprite() const;

	// ��ʑO�i�Ȃǂ�`�悷��B
	void DrawBattleInfo() const;

};

#endif // SCENE_BATTLE_H