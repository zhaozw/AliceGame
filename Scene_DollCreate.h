#ifndef SCENE_DOLLCREATE_H
#define SCENE_DOLLCREATE_H

#include "Scene_Base.h"
#include "Selectable2D.h"
#include "Selectable.h"
#include "Static_AliceDoll.h"
#include "Window_Yesno.h"


#define EACHGROUP_WIDTH			300
#define EACHGROUP_HEIGHT		120
#define EACHGROUP_MARGIN		10


// �V�[���̃X�e�[�g
#define SCNSTATE_DOLLCREATE_CHOOSETYPE		0	// �ǂ̃^�C�v�̐l�`���̑I��
#define SCNSTATE_DOLLCREATE_CHOOSESTONE		1	// �����̌��Ђ̑I��
#define SCNSTATE_DOLLCREATE_ASKCREATE		2	// �l�`���쐬���邩�ǂ����̊m�F

class Scene_DollCreate : public Scene_Base{
public:
	Window_Yesno		w_yesno;					// �쐬�����̊m�F�E�B���h�E
	Selectable			s_group;					// �l�`�̃^�C�v��I��
	Selectable			s_type[DOLL_GROUP_NUM];		// �l�`�̎�ނ�I��
	Selectable			s_attr;						// �l�`�̑�����I��
	// Selectable2D		s_test;
	BYTE				attrStones[DOLL_ATTRSTONE_CREATE];		// �����̕��
	BYTE				cntAttrStone;				// ���݂̈ʒu

private:
public:
	// �R���X�g���N�^
	Scene_DollCreate();
	// ����������
	virtual bool Initialize(bool fSkipFrame);
	bool InitWindow();
	// �I������
	virtual bool Terminate();

	// �X�V����
	virtual int Update();
	// �`�揈��
	virtual void Draw();


	// �e�^�C�v�ɂ��Ă̏���`�悷��B
	void DrawEachGroup(int x, int y, BYTE group, bool focused);

	// �estate�̐�����`�悷��B
	void DrawAccount();
	
	// �����̕�΂�`�悷��B
	void DrawAttrStones();

	// ��ΑI�����̘g��`�悷��B
	void DrawAttrStoneFocus(int x, int y);

	// �����̕�΂̃Z�b�g�����Z�b�g����B
	void ResetAttrStones();

	// �����̕�΂��w�肵���ʒu�ɃZ�b�g����B
	void SetAttrStone(BYTE group, BYTE attr, int pos);

	// �w�肵���ʒu�̑����̕�΂��������B
	void ResetAttrStone(int pos);

	// ���ݓo�^����Ă����������TempData�ɐl�`�f�[�^��������B
	void RegisterNewDoll();
};

#endif // SCENE_DOLLCREATE_H