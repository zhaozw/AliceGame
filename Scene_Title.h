#ifndef SCENE_TITLE_H
#define SCENE_TITLE_H

#include "Scene_Base.h"
#include "Selectable.h"
#include "Static_Game.h"

#define TITLE_MENU_NEWGAME		0	// �ŏ�����n�߂�
#define TITLE_MENU_CONTINUE		1	// ��������n�߂�
#define TITLE_MENU_STOCKDOLLS	2	// �L���̒��̐l�`
#define TITLE_MENU_RECORDS		3	// �g���t�B�[
#define TITLE_MENU_TESTBATTLE	4	// �e�X�g�o�g����ʂɖ߂�
#define TITLE_MENU_OPTION		5	// �I�v�V����
#define TITLE_MENU_EXIT			6	// �Q�[�����I������
#define MAX_TITLE_MENU			(TITLE_MENU_EXIT+1)	// ���j���[�̑���

#define TITLE_PHAZE_START		0
#define TITLE_PHAZE_MAIN		1
#define TITLE_PHAZE_CHAPTER		2
#define TITLE_PHAZE_OPTION		3


class Scene_Title : public Scene_Base{
private:
	Selectable		s_main;		// ���j���[�̑I�����
	Selectable		s_chapter;	// �u�͂��߂���v�̃`���v�^�[�̑I��
	WORD			phaze;		// �t�F�C�Y
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
	virtual void Draw() const;

};

#endif // SCENE_TITLE_H