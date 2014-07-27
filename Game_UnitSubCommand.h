#ifndef GAME_UNITSUBCOMMAND_H
#define GAME_UNITSUBCOMMAND_H

#include "Game_UnitCommand.h"

// Game_UnitSubCommand�N���X
// Game_UnitCommand�N���X�̓��e��Scene_Battle�̃R�}���h���s���ɂ�����
// �������邽�߂Ɏg�p����N���X�B
// ���֐��̂��߁A�ėp�p�����[�^param�y�ь��ʂ�\���r�b�g�ϐ�result���ǉ�����Ă���B

// result�ɓ���l�̗�
#define COMMAND_RESULT_SUCCEED			0x0000	// ���ʂɐ�������
#define COMMAND_RESULT_TARGET_CHANGED	0x0001	// �����������^�[�Q�b�g�����ꂽ
#define COMMAND_RESULT_ZEROVALUE		0x0002	// �_���[�W��񕜌n�̃R�}���h�ɂ����āA
												// �^�����E�񕜂����_���[�W��0������

class Game_UnitSubCommand : public Game_UnitCommand{
protected:
	int				param;		// �ėp�p�����[�^�B
								// �ʏ�̃R�}���h�Ƃ��Ă͎g�p�����A
								// Game_BattleAction�̉��ߒ��Ɏg�p����B
	WORD			result;		// �s���̌��ʂ�\���B
								// ��Ƃ��āA�u�ōU���v�ɂ����ă_���[�W��^���邩��
								// �ŏ��ɔ��f���A���ɓŃX�e�[�g�̕t���̔��f���s���ہA
								// �ŏ��́u�_���[�W�v�������������ǂ����̌��ʂ�����B
public:
	// �R���X�g���N�^
	Game_UnitSubCommand();
	
	// �A�N�Z�T
	void	SetParam(int p){ param = p; };
	int		GetParam(){ return param; };
	void	ClearResult(){ result = COMMAND_RESULT_SUCCEED; };
	void	SetResult(BYTE r){ result |= r; };
	void	ResetResult(BYTE r){ result &= ~r; };
	WORD	GetResult(){ return result; };

};

#endif // GAME_UNITSUBCOMMAND_H