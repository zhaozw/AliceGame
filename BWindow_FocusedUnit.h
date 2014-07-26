#ifndef BWINDOW_FOCUSEDENEMY_H
#define BWINDOW_FOCUSEDENEMY_H

#include "Window_Base.h"
#include "Game_BattleDoll.h"
#include "Game_BattleEnemy.h"
#include "Selectable.h"

#define		BWND_FOCUSEDENEMY_WIDTH			200
#define		BWND_FOCUSEDENEMY_HEIGHT		100

#define		BWND_FOCUS_TARGET_NONE			0
#define		BWND_FOCUS_TARGET_ONE_ENEMY		1	// �G���
#define		BWND_FOCUS_TARGET_ALL_ENEMIES	2	// �G�S��
#define		BWND_FOCUS_TARGET_ONE_DOLL		3	// �������
#define		BWND_FOCUS_TARGET_ALL_DOLLS		4	// �����S��
#define		BWND_FOCUS_TARGET_ALL_UNITS		5	// �G�����S��
#define		BWND_FOCUS_TARGET_FIXED_DOLL	6	// ������́i�J�[�\���ړ��s�j
#define		BWND_FOCUS_TARGET_FIXED_ENEMY	7	// �G��́i�J�[�\���ړ��s�j

#define		BWND_FOCUS_TYPE_UNDIFINED		0
#define		BWND_FOCUS_TYPE_ATTACK			1	// �U����
#define		BWND_FOCUS_TYPE_SKILL			2	// �X�L���̑ΏۑI����

#define		BWND_FOCUS_FLAG_EXCLUDE_DEAD	0x01	// �퓬�s�\�̃L�����N�^�[��
													// �I��s�ɂ��A����
													// ����\�����Ȃ�
#define		BWND_FOCUS_FLAG_EXCLUDE_ALIVE	0x02	// �퓬�\�ȃL�����N�^�[��
													// �I��s�ɂ��A����
													// ����\�����Ȃ�


// �t�H�[�J�X���Ă���G�̏���\������B
// �����I�ɂ�Selectable�����E�B���h�E�ł���B

class Scene_Battle;
class Game_BattleEnemy;

class BWindow_FocusedUnit : public Window_Base{
protected:
	// �I����
	Selectable				s_target;
	// �o�g���V�[���ւ̎Q��
	Scene_Battle*			pScene;
	// ���̃E�B���h�E��ێ����Ă���l�`
	Game_BattleUnit*		pOwner;
	// ���ݎQ�Ƃ��Ă���G�L����
	// �����̏ꍇ��NULL���g�p����
	Game_BattleUnit*		pTarget;
	// �I���̃^�C�v
	BYTE					focusTarget;
	// �ǂ̃^�C�~���O�ŊJ���ꂽ�E�B���h�E��
	BYTE					focusType;
	// �I���Ɋւ���t���O
	BYTE					flags;
public:
	// �R���X�g���N�^
	BWindow_FocusedUnit();


	// �Z�b�g�A�b�v
	// (���O�E�B���h�E�̏o�����͑S�Ăقړ���)
	void MySetup(Scene_Battle* _pScene);

	// �J�������̋���
	virtual void OnOpened();

	// �I�����̗L��/������G�L�����ɍ��킹�čs���B
	void CheckEnemyEnabled();

	// �I�����̗L��/�����𖡕��L�����ɍ��킹�čs���B
	void CheckDollEnabled();

	// �C���f�b�N�X�l���ς�����Ƃ��A
	// �ʒu�y�ѕ\�����e�̍X�V���s���B
	void OnIndexChanged();

	// �I�����̃C���f�b�N�X���w�肷��B
	// �I���ł���G�����Ȃ��ꍇ�Afalse��Ԃ��B
	bool SetDefaultEnemyIndex();

	// �I�����̃C���f�b�N�X���w�肷��B
	// �I���ł��閡�������Ȃ��ꍇ�Afalse��Ԃ��B
	bool SetDefaultDollIndex();

	// ���e�̃A�b�v�f�[�g���s���B
	virtual void Update();			// �N���X���Ƃɔh������A�b�v�f�[�g�֐��B

	// ���e�̕`����s���B
	virtual void DrawContent() const;

	// �w�肵���G�L�����ɂ��Ă̕`����s���B
	virtual void DrawCntEnemy(Game_BattleEnemy* pTarget) const;

	// �w�肵���l�`�i�ꏊID�j�ɂ��Ă̕`����s���B
	virtual void DrawCntDoll(BYTE index) const;

	// �A�N�Z�T
	int GetSelectIndex() const { return s_target.index; };
	/*
	bool GetFocusAll(){ return focusAll; };
	void SetFocusAll(bool b){ focusAll = b; };
	Game_BattleEnemy* GetEnemyPtr(){ return pEnemy; };

	*/

	// �^�[�Q�b�g�̎�ނƃ^�C�~���O���w�肵�ĊJ���B
	void OpenWithParam(Game_BattleUnit* _pOwner, Game_BattleUnit* _pTarget,
		BYTE _focusTarget, BYTE _focusType, BYTE _flags=0x00);

	// �J��������s���O��ɕʓr�p�����[�^�̎w�肪����ꍇ�A
	// �e�p�����[�^�̎w����s���B
	void SetParam(Game_BattleUnit* _pOwner, Game_BattleUnit* _pTarget,
		BYTE _focusTarget, BYTE _focusType, BYTE _flags=0x00);

	Game_BattleUnit* GetOwner(){ return pOwner; };
	Game_BattleUnit* GetTarget(){ return pTarget; };
	Game_BattleUnit* GetTargetAsCommandTarget();	// Game_BattleCommand�ɓn���p�B

	static BYTE ConvertTargetTypeToFocusType(BYTE targetType);
};



#endif // BWINDOW_FOCUSEDENEMY_H