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
#include "BWIndow_SelectEnemy.h"
#include "BWindow_FocusedEnemy.h"
#include "Sprite_BattleDoll.h"
#include "Sprite_BattleEnemy.h"

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
		BEFORE_TURN,		// �^�[���̍ŏ�
		BATTLE_DO,			// �퓬
		AFTER_TURN,			// �^�[���I����
		POST_BATTLE,		// �퓬�I��
	};

	// �퓬�̃T�u�t�F�C�Y���L�^����B
	enum SUBPHAZE{
		ASSERT_ACTION,		// �s���̐錾
		BEFORE_ACTION,		// �s����K�p����O
		PERFORM_ACTION,		// �s���̓K�p
		AFTER_ACTION,		// �s���̓K�p��
		CHECK_ACTION,		// �s���̌��ʃo�g���[���ω������Ԃ̊m�F
	};

private:
	// ���ݐ퓬���Ă���G�O���[�vID���w�肷��B
	WORD								enemyGroup;
	// ���݂̏󋵂�\��
	enum BATTLEPHAZE					phaze;
	enum SUBPHAZE						subPhaze;
	// �����E�G���j�b�g�͒ʏ�̔z��ŕ\������
	// �������j�b�g�̔z��
	Game_BattleDoll						dolls[MAX_BATTLEDOLL];
	int									dollsNum;	// �������j�b�g�̍ő吔�i�퓬�s�\�Ҋ܂ށj
	// �G���j�b�g�̔z��
	Game_BattleEnemy					enemies[MAX_BATTLEENEMY];
	int									enemiesNum;	// �G���j�b�g�̍ő吔�i�퓬�s�\�Ҋ܂ށj
	// �U���R�}���h�̔z��
	Game_UnitCommand					commands[MAX_UNITCOMMAND];
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
	// �G�̑I���E�B���h�E
	BWindow_SelectEnemy					w_selectEnemy;
	// �G�̃t�H�[�J�X�E�B���h�E
	BWindow_FocusedEnemy				w_focusedEnemy;
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
	virtual void Draw();

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

	// ���̃t�F�C�Y�Ɉڍs�����ۂ̏����B
	// �֐�NextPhaze������s�����B
	// �e�t�F�C�Y���ƂɎ��s����A�N�V�������Z�b�g����B
	void SetupPreBattle();		// PRE_BATTLE�ɂȂ�����
	void SetupAliceCommand();	// �A���X�̃R�}���h�E�B���h�E���J��
	void SetupAliceCommandDo(); // �A���X�̃R�}���h�����s����
	void SetupDollsCommand();	// �l�`�̃R�}���h�E�B���h�E���J�� 
	void SetupEnemiesCommand();	// �G�̃R�}���h�����肷��B(�����ɏI���)
	void SetupBeforeTurn();		// �^�[���J�n���B�X�e�[�g�̔���ȂǁB
	void SetupBattleDo();		// �퓬�B
	void SetupAfterTurn();		// �^�[���I�����B�X�e�[�g�̔���ȂǁB


	// �K�v�ȃI�u�W�F�N�g�Q�̃A�b�v�f�[�g���s���B
	void UpdateObjects();
	
	// �l�`�̔z�񂪕ς�����ۂɁA�l�`�X�v���C�g�ɐl�`�����蓖�Ē����B
	bool AttachDollPtrToSprite();

	//=========================================
	// �A�N�Z�T�֘A
	// �\�[�X�t�@�C���ɋL�q������̂�Scene_Battle.cpp�ɋL�q����B
	int GetDollsNum(){ return dollsNum; } ;
	int GetEnemiesNum(){ return enemiesNum; };

	// �l�`�̃|�C���^���擾����B
	Game_BattleDoll*	GetDollPtr(int index){
		if(index < 0 || index >= MAX_BATTLEDOLL) return NULL;
		return &dolls[index];
	}

	// �G�L�����̃|�C���^���擾����B
	Game_BattleEnemy*	GetEnemyPtr(int index){
		if(index < 0 || index >= MAX_BATTLEENEMY) return NULL;
		return &enemies[index];
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



	// �e��E�B���h�E���J���B
	// ���̃E�B���h�E����̎Q�ƂȂǂ̌`�B

	// �G�I���E�B���h�E
	BYTE	OpenSelectEnemyWindow();
	int		GetSelectEnemyIndex(){ return w_selectEnemy.GetSelectIndex(); };
	BWindow_SelectEnemy*	GetWndSelectEnemyPtr(){ return &w_selectEnemy; };
	BYTE	OpenFocusedEnemyWindow();
	int		GetFocusedEnemyIndex(){ return w_focusedEnemy.GetSelectIndex(); };
	BWindow_FocusedEnemy*	GetWndFocusedEnemyPtr(){ return &w_focusedEnemy; };

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
	bool Action_CallEnemyName();

	//=========================================
	// Game_BattleAction�̓��e�̏����B
	// Scene_Battle_Action.cpp�ɋL�q����B

	// commandPhaze :
	// �Ⴆ�Βʏ�U���ɂ���A
	// ���ۂ̍U���O�ɍs���锻��i�h������Ă���L�����N�^�[�̖h��͕␳�Ƃ��j��
	// �U����ɍs���锻��i���̍U���̂݃p���[�A�b�v�̃X�e�[�g�Ȃǁj������B
	// ���UnitCommand�̉��߂��A�������̃t�F�C�Y���ƂɊǗ����邽�߂�
	// �p�����[�^�BStatic_Battle.h����COMMANDPHAZE_xxx�萔�Q�Œ�`�����B
	// 
	bool InterpretCommand(Game_UnitCommand* pCmd, int commandPhaze=COMMANDPHAZE_NOPHAZE);
	// commandPhaze�ɂ���ĕ��򂷂�
	bool InterpretCommand_NoPhaze(Game_UnitCommand* pCmd);
	bool InterpretCommand_Pre_Action(Game_UnitCommand* pCmd);
	bool InterpretCommand_Action(Game_UnitCommand* pCmd);
	bool InterpretCommand_Post_Action(Game_UnitCommand* pCmd);

	//=========================================
	// �퓬���̏����Z
	// Scene_Battle_Calc.cpp�ɋL�q����B

	// �R�}���h��ǉ�����B
	bool SetCommand(Game_UnitCommand cmd);
	
	// �G�̃R�}���h�������Œǉ�����B
	// ������SetEnemyCommand���g�p����B
	bool SetEnemyCommands();

	// �|�C���^���g�p���A�G�̃R�}���h���Z�o����B
	Game_UnitCommand GetEnemyCommand(Game_BattleEnemy* pEnemy);

	// �퓬�s���̃\�[�g���s���B
	bool SortUnitCommands();
	
	// commands�̓��e��S�ăN���A����B
	void ClearCommands();

	//=========================================
	// �`��
	// ���L�̊֐���Scene_Battle_Draw.cpp�ɋL�q����B

	// �l�`�̃X�v���C�g��`�悷��B
	void DrawDollsSprite() const;
	// �G�L�����̃X�v���C�g��`�悷��B
	void DrawEnemiesSprite() const;

};

#endif // SCENE_BATTLE_H