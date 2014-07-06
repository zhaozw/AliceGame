#ifndef BWINDOW_SELECTENEMY_H
#define BWINDOW_SELECTENEMY_H

#include "Window_Selectable.h"
#include "Game_BattleEnemy.h"


#define BWND_SELECTENEMY_X		200
#define BWND_SELECTENEMY_Y		300
#define BWND_SELECTENEMY_W		300
#define BWND_SELECTENEMY_H		200
#define BWND_SELECTENEMY_PX	16
#define BWND_SELECTENEMY_PY	16

class BWindow_SelectEnemy : public Window_Selectable{
private:
	// �G�O���[�v�ւ̎Q��
	Game_BattleEnemy*		pEnemies;
	// �G�̍ő吔
	int						enemyNum;
public:
	// �R���X�g���N�^
	BWindow_SelectEnemy();


	// �Z�b�g�A�b�v
	// (���O�E�B���h�E�̏o�����͑S�Ăقړ���)
	void MySetup(Game_BattleEnemy* _pEnemies);


	// ���e�̃A�b�v�f�[�g���s���B
	virtual void Update();			// �N���X���Ƃɔh������A�b�v�f�[�g�֐��B
	void UpdateEnemyNum();

	// ���e�̕`����s���B
	virtual void DrawContent() const;

};



#endif // BWINDOW_SELECTENEMY_H