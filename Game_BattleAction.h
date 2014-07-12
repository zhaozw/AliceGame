#ifndef GAME_BATTLEACTION_H
#define GAME_BATTLEACTION_H

#include <Windows.h>

// Game_BattleAction�N���X
// �o�g���ɂ����Ĕ���������ۂ̓���������N���X�B
// ��Ƃ��āA�N������N���̃_���[�W�Ȃǂ�\���B
// Scene_Battle����X�^�b�N�\���ŗ��p�����B

// �Q�Ƃ�n���B
class Game_BattleUnit;

class Game_BattleAction{
public:
	// �񋓎q���L�q����B
	enum ActionType{
		TYPE_NONE,			// �X�^�b�N��0�Ԗڂ̗v�f�����^�C�v
		TYPE_DAMAGE,
		TYPE_CALLENEMYNAME,	// �퓬�J�n���A�G�̖��O��񋓂���B
		TYPE_UNDIFINED,
	};
private:
	// �����o
	
	// �s�������郆�j�b�g�ւ̎Q��
	Game_BattleUnit*	pActor;	
	// �s��������郆�j�b�g�ւ̎Q��
	Game_BattleUnit*	pOpponent;
	// �s���̎��
	ActionType			type;
	// �e��t���O
	DWORD				flags;
	// �e��p�����[�^�B
	int					param;

public:
	// �R���X�g���N�^
	Game_BattleAction();

	// ������Z�q
	// �����o��S�ăR�s�[����B
	Game_BattleAction &operator=(const Game_BattleAction &o);  // ������Z�q

	// ���e������������B
	// �X�^�b�N�����o���ꂽ���Ɏ��s����B
	void Clear();

	// �A�N�Z�T
	void SetActor(Game_BattleUnit* p){ pActor = p; };
	Game_BattleUnit* GetActor(){ return pActor; };
	void SetOpponent(Game_BattleUnit* p){ pOpponent = p; };
	Game_BattleUnit* GetOpponent(){ return pOpponent; };
	void SetType(enum ActionType t){ type = t; };
	enum ActionType GetType(){ return type; };
	void SetFlags(DWORD p){ flags = p; };
	DWORD GetFlags(){ return flags; };
	void SetFlag(DWORD flag){ flags |= flag; };
	void ResetFlag(DWORD flag){ flags |= ~flag; };
	bool GetFlag(DWORD flag){ return (flags &= flag) != 0; } ;
	void SetParam(int p){ param = p; };
	int GetParam(){ return param; };

	// �������ǂ����̔���
	bool IsEmpty(){ return type == TYPE_UNDIFINED; };

};

// Game_BattleAction�N���X�̃X�^�b�N�������N���X�B
// Scene_Battle�N���X�̕ϐ�actionStack�Ƃ��ĕێ������B
// �{���̓������Ƃ��g�������������̂����A�����ɂ̓��x���������̂�
// �Œ蒷�̗̈���m�ۂ��Ă����ăX�^�b�N�̂ӂ������B
// 0�Ԗڂ̗v�f�ɂ́A�G���[���N�����Ƃ��ɕԂ��l����ɕێ����Ă����B

// �X�^�b�N�̍ő吔�B
#define MAX_BATTLEACTIONSTACK	32

class Game_BattleActionStack{
private:
	Game_BattleAction		data[MAX_BATTLEACTIONSTACK+1];
	int						cntIndex;	// ���݂̃X�^�b�N�̈ʒu�B
public:
	// �R���X�g���N�^
	Game_BattleActionStack();

	// ���ݎw���Ă���f�[�^��Ԃ��B
	// �f�[�^�̍폜�͍s��Ȃ��B
	Game_BattleAction GetCntData();

	// �f�[�^����v�b�V���i�ǉ��j���A�C���f�b�N�X�����炷�B
	// ��̓I�ɂ́AGame_BattleAction�N���X�̎��̂�n���ƒl��S�ăR�s�[����
	// ���e���X�^�b�N�ɒǉ�����B
	// ����������true�A���s������false��Ԃ��B
	bool Push(Game_BattleAction action);

	// �f�[�^����|�b�v�i���o���j���A�C���f�b�N�X�����炷�B
	// ��̓I�ɂ́AGame_BattleAction�N���X�̎��̂�Ԃ��B
	// �f�[�^�������ꍇ��C���f�b�N�X�����������ꍇ�ɂ�0�Ԗڂ̗v�f��Ԃ��B
	Game_BattleAction Pop();

	// �f�[�^������o�����A�C���f�b�N�X�͂��炳�Ȃ��B
	// �f�[�^�������ꍇ��C���f�b�N�X�����������ꍇ�ɂ�0�Ԗڂ̗v�f��Ԃ��B
	Game_BattleAction Pop_NoRemove();

	// �f�[�^�ւ̃|�C���^��n���A�C���f�b�N�X�����炷�B
	// �߂�l�́A����������true�A���s������false�ɂȂ�B
	// �n�����|�C���^���΂�delete���Ă͂����Ȃ��B
	// �f�[�^�������ꍇ��C���f�b�N�X�����������ꍇ�ɂ�0�Ԗڂ̗v�f��Ԃ��B
	// bool PopPtr(Game_BattleAction* pAction);

	// ���݃X�^�b�N����Ă���f�[�^�̌���Ԃ��B
	int	GetSize(){ return cntIndex; };

	// �S�Ẵf�[�^���N���A����B
	void ClearAll();
};

#endif // GAME_BATTLEACTION