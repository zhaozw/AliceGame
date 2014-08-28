#ifndef GAME_BGEFFECT_H
#define GAME_BGEFFECT_H

#include <Windows.h>

// typeID�̗񋓁B
#define GAME_BG_TYPE_NONE				0	// �w�i�Ȃ��B�����`�悵�Ȃ��B
#define GAME_BG_TYPE_DUMMY				1	// �_�~�[�w�i�B�`�F�b�N�摜����ׂĕ\���B

//================================================
// Game_BGEffect�N���X
// 
// �G�t�F�N�g�̂��������w�i�̃N���X�B
// �퓬��ʂ̔w�i�A�}�b�v��ʂ̔w�i�Ȃǂŗ��p����B
// 

class Game_BGEffect{
private:
	// �w�i�̃^�C�vID�B
	WORD		typeID;

	// �����^�C�vID���g�p���Ȃ���w�i������ɕω������������̔ėp�p�����[�^�B
	// �g������typeID�ɂ���ĈقȂ�B
	int			param;

	// ���Ԃ̃p�����[�^�B
	// SetTypeID���s���ۂ�0�ɂȂ�AUpdate���Ăяo�����x�ɑ�����B
	// �g�����ǂ����E�g������typeID�ɂ���ĈقȂ�B
	// ����G�t�F�N�g�̊���Ԃ�ς������ꍇ�́A
	// SetRandTime�֐������s����ƓK���Ȓl��time�ɑ�������B
	int			time;

	// �ό`�̊�Ɏg�����W�B
	// ������ėp�I�Ȃ��̂ł���A�g������typeID�ɂ���ĈقȂ�B
	// SetPosition�֐��Ŏw�肷��B
	float		posX;
	float		posY;

	// �J��Ԃ��Ɏg�p����l�ŁA
	// �摜�̕��ƍ����ȂǂɎg�p����B
	// �g������typeID�ɂ���ĈقȂ��Ă��悢�B
	float		loopWidth;
	float		loopHeight;


public:

	// �R���X�g���N�^
	Game_BGEffect();

	// �^�C�vID��ύX����B
	// �^�C�vID���Ƃ̏������������܂ށB
	bool SetTypeID(WORD id);

	// �^�C�vID���擾����B
	WORD GetTypeID(){ return typeID; };

	// �p�����[�^��ύX����B
	void SetParam(int p){ param = p; };

	// �p�����[�^���擾����B
	int GetParam(){ return param; };

	// �^�C�vID�ƃp�����[�^���܂Ƃ߂ăZ�b�g����B
	bool SetTypeID(WORD id, int param){ SetParam(param); return SetTypeID(id); };

	// ���������s���B
	// �^�C�vID���Ƃ̏������͂��̊֐��ł͂Ȃ�SetTypeID���ōs���B
	bool Initialize();

	// �I���������s���B
	bool Terminate();

	// �^�C�vID���Ƃ̉��Z�������s���B
	// ���̃I�u�W�F�N�g��������N���X���疈�t���[�����s�����B
	void Update();

	// �^�C�vID���Ƃ̕`�揈�����s���B
	// ���̃I�u�W�F�N�g��������N���X���疈�t���[�����s�����B
	void Draw() const;

	// �K���Ȏ��Ԃ�������B
	void SetRandTime();

	// ��ʒu��������B
	void SetPosition(float _x, float _y){ posX = _x; posY = _y; };


};

#endif // GAME_BGEFFECT_H