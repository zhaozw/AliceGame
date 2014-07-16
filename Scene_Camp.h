#ifndef SCENE_CAMP_H
#define SCENE_CAMP_H

#define CAMP_MENU_START		0	// �_���W�����ֈړ�
#define CAMP_MENU_EDIT		1	// �`�[���Ґ�
#define CAMP_MENU_CREATE	2	// �l�`�̍쐬
#define CAMP_MENU_SAVE		3	// �f�[�^�̕ۑ�
#define CAMP_MENU_EXIT		4	// �Q�[������߂�
#define MAX_CAMP_MENU		(CAMP_MENU_EXIT+1)

// �L�����v�̃X�e�[�g
#define SCNSTATE_CAMP_CHOOSEMENU		0		// ���j���[�̑I��
#define SCNSTATE_CAMP_ASKQUITGAME		1		// �Q�[�����I�����邩�ǂ����̊m�F

// GUI�Ɏg�p����
// �A�j��1 : ���ɂ����A�t�H�[�J�X���O���Ɩ߂�
// �A�j��2 : ����A�t�H�[�}�X�Ɋւ�炸��u�̃A�j��
#define CAMP_ANIME1_TIME	1000
#define CAMP_ANIME2_TIME	10
#define CAMP_INFO_TIME		120

// ��ʉ����ɕ\���������ID
#define CAMP_INFO_NONE		0	// �����\������Ă��Ȃ�
#define CAMP_INFO_SAVE		1	// �u�Z�[�u���܂����v
#define CAMP_INFO_REST		2	// �u�x�e���Ė��͂��񕜂��܂����v
#define MAX_CAMP_INFO		2	// ���̍ő吔�B����ɗp����BNONE�͊܂߂Ȃ��B

#include "Scene_Base.h"
#include "Selectable.h"
#include "Window_Yesno.h"

class Scene_Camp : public Scene_Base{
public:

private:
	Selectable		s_main;
	WORD			menu_anime1[MAX_CAMP_MENU];
	BYTE			menu_anime2[MAX_CAMP_MENU];
	// ��ʉ����ɕ\���������ID�B
	BYTE			infoIndex;
	// ��ʉ����ɕ\�������񂪂���ꍇ�A��񂪏o�����Ă���̎��ԁB
	BYTE			infoTime;
	// �Q�[���I���̊m�F�E�B���h�E
	Window_Yesno	w_yesno;

public:
	// �R���X�g���N�^
	Scene_Camp();
	// ����������
	virtual bool Initialize(bool fSkipFrame);
	// �I������
	virtual bool Terminate();
	// �E�B���h�E�̏�����
	bool InitWindow();
	
	// �X�V����
	virtual int Update();
	// �`�揈��
	virtual void Draw() const;

	// ��ʉ��ɏ��𗬂��B
	void SetInfo(BYTE index){
		if(index <= MAX_CAMP_INFO){
			infoIndex = index;
			infoTime = 1;
		}
	}

};

#endif // SCENE_CAMP_H