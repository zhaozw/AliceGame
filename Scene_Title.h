#ifndef SCENE_TITLE_H
#define SCENE_TITLE_H

#include "Scene_Base.h"
#include "Selectable.h"

#define TITLE_MENU_NEWGAME		0	// �ŏ�����n�߂�
#define TITLE_MENU_CONTINUE		1	// ��������n�߂�
#define TITLE_MENU_EXIT			2	// �Q�[�����I������
#define MAX_TITLE_MENU			(TITLE_MENU_EXIT+1)	// ���j���[�̑���


class Scene_Title : public Scene_Base{
public:
	Selectable		s_main;	// ���j���[�̑I�����

private:

public:
	// �R���X�g���N�^
	Scene_Title();
	// ����������
	virtual bool Initialize(bool fSkipFrame);
	// �I������
	virtual bool Terminate();
	
	// �X�V����
	virtual int Update();
	// �`�揈��
	virtual void Draw();

};

#endif // SCENE_TITLE_H