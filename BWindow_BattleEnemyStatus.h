#ifndef BWINDOW_BATTLEENEMYSTATUS_H
#define BWINDOW_BATTLEENEMYSTATUS_H

#include "Window_Info.h"
#include "Game_BattleEnemy.h"

class Scene_Battle;

#define WND_BATTLEENEMYSTATUS_W				216
#define WND_BATTLEENEMYSTATUS_H				240
#define WND_BATTLEENEMYSTATUS_POS_LEFT_X	0
#define WND_BATTLEENEMYSTATUS_POS_RIGHT_X	(WND_WIDTH-WND_BATTLEENEMYSTATUS_W)
#define WND_BATTLEENEMYSTATUS_POS_Y			80	

//===================================
// BWindow_BattleEnemyStatus�N���X
// 
// �G�L�����̃p�����[�^��\������N���X�B
// Scene_Battle���Ŏg�p�����B

class BWindow_BattleEnemyStatus : public Window_Info{
protected:
	// �V�[���B
	Scene_Battle*			pScene;
	// �Q�Ƃ��Ă���l�`�B
	// �퓬�V�[���ł����pBattleDoll,
	// �L�����v�V�[���ł����pCampDoll���g�p����B
	Game_BattleEnemy*		pEnemy;

public:
	// �R���X�g���N�^
	BWindow_BattleEnemyStatus();

	// �Z�b�g�A�b�v�B
	// �E�B���h�E�̑傫���͕`��p�^�[���ɂ�莩���I�Ɍ��܂�B
	// �E�B���h�E�̈ʒu�̓E�B���h�E���J���Ƃ��Ɍ��肷��B
	void Setup(Scene_Battle* _pScene);

	// �Q�Ƃ���l�`���w�肵�ĊJ���B
	// pos : �E�B���h�E�̕\���ʒu�B
	void OpenWithEnemy(Game_BattleEnemy* pEnemy, BYTE pos);

	// �Q�Ƃ��Ă���l�`��ύX����B
	// ���̎Q�ƂƈقȂ�ꍇ�A�\���������Ă���ďo��������B
	bool ChangeRefEnemy(Game_BattleEnemy* pEnemy);

	// �X�V�B
	virtual void Update();

	// �J�������Ɏ��s����֐��B
	virtual void OnOpened();

	// ���e�̕`��B
	virtual void DrawContent() const;

	// �A�N�Z�T
	Game_BattleEnemy* GetEnemyPtr(){ return pEnemy; };
};

#endif // BWINDOW_BATTLEENEMYSTATUS_H
