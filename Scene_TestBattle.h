#ifndef SCENE_TESTBATTLE_H
#define SCENE_TESTBATTLE_H

#include "Scene_Base.h"
#include "Selectable.h"
#include "Window_HintMessage.h"

#define MAX_TESTBATTLE			10
#define MAX_TESTBATTLE_MENU		3
#define TESTBATTLE_SELECT_NUM	(MAX_TESTBATTLE+MAX_TESTBATTLE_MENU)

class Scene_TestBattle : public Scene_Base{
protected:
	Selectable				s_main;	// ���j���[�̑I�����
	Window_HintMessage		w_hint;
	float					backX;	// �w�i�摜�̕`��ʒu�̎w�W
	float 					backY;

public:
	// �R���X�g���N�^
	Scene_TestBattle();
	// ����������
	virtual bool Initialize(bool fSkipFrame);
	// �I������
	virtual bool Terminate();
	
	// �X�V����
	virtual int Update();

	// �`�揈��
	virtual void Draw() const;
	
	// �q���g�E�B���h�E���J��
	bool OpenHintWindow();


};


#endif // SCENE_TESTBATTLE_H