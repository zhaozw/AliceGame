#ifndef BWINDOW_FOCUSEDENEMY_H
#define BWINDOW_FOCUSEDENEMY_H

#include "Window_Base.h"
#include "Game_BattleDoll.h"
#include "Game_BattleEnemy.h"
#include "Selectable.h"

#define		BWND_FOCUSEDENEMY_WIDTH			200
#define		BWND_FOCUSEDENEMY_HEIGHT		100

// �t�H�[�J�X���Ă���G�̏���\������B
// �����I�ɂ�Selectable�����E�B���h�E�ł���B

class Scene_Battle;
class Game_BattleEnemy;

class BWindow_FocusedEnemy : public Window_Base{
protected:
	// �I����
	Selectable				s_enemy;
	// �o�g���V�[���ւ̎Q��
	Scene_Battle*			pScene;
	// ���̃E�B���h�E��ێ����Ă���l�`
	Game_BattleDoll*		pDoll;
	// ���ݎQ�Ƃ��Ă���G�L����
	Game_BattleEnemy*		pEnemy;
	// �G�S�̂Ƀt�H�[�J�X�������
	// (�E�B���h�E��œG�S�̂�\������)
	bool					focusAll;
public:
	// �R���X�g���N�^
	BWindow_FocusedEnemy();


	// �Z�b�g�A�b�v
	// (���O�E�B���h�E�̏o�����͑S�Ăقړ���)
	void MySetup(Scene_Battle* _pScene);

	// 
	void SetDoll(Game_BattleDoll* _pDoll){
		pDoll = _pDoll;
	}

	// �J�������̋���
	virtual void OnOpened();

	// �I�����̗L��/������G�L�����ɍ��킹�čs���B
	void CheckEnemyEnabled();

	// �C���f�b�N�X�l���ς�����Ƃ��A
	// �ʒu�y�ѕ\�����e�̍X�V���s���B
	void OnIndexChanged();

	// �I�����̃C���f�b�N�X���w�肷��B
	// �I���ł���G�����Ȃ��ꍇ�Afalse��Ԃ��B
	bool SetDefaultIndex();

	// ���e�̃A�b�v�f�[�g���s���B
	virtual void Update();			// �N���X���Ƃɔh������A�b�v�f�[�g�֐��B

	// ���e�̕`����s���B
	virtual void DrawContent() const;

	// �w�肵���G�L�����ɂ��Ă̕`����s���B
	virtual void DrawCntEnemy(Game_BattleEnemy*) const;

	// �A�N�Z�T
	int GetSelectIndex() const { return s_enemy.index; };
	bool GetFocusAll(){ return focusAll; };
	void SetFocusAll(bool b){ focusAll = b; };
	Game_BattleEnemy* GetEnemyPtr(){ return pEnemy; };

};



#endif // BWINDOW_FOCUSEDENEMY_H