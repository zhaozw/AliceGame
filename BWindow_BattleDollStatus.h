#ifndef BWINDOW_BATTLEDOLLSTATUS_H
#define BWINDOW_BATTLEDOLLSTATUS_H

#include "Window_SimpleDollStatus.h"

class Scene_Battle;

//==============================================================
// BWindow_BattleDollStatus�N���X
// 
// �퓬�V�[���Ŏg�p����A�l�`�̃X�e�[�^�X��\������E�B���h�E�B
// Scene_Battle�ւ̃|�C���^�����B

class BWindow_BattleDollStatus : public Window_SimpleDollStatus{
protected:
	Scene_Battle* pScene;

public:
	// �R���X�g���N�^
	BWindow_BattleDollStatus();

	// �Z�b�g�A�b�v
	void Setup(Scene_Battle* _pScene);

	// ���e�̍X�V
	virtual void Update();
};


#endif // BWINDOW_BATTLEDOLLSTATUS_H