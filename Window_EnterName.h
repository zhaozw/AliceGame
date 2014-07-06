#ifndef WINDOW_ENTERNAME_H
#define WINDOW_ENTERNAME_H

#include "Window_Base.h"
#include "Selectable2D.h"

// nameType�ɓ���l
#define NAMETYPE_DOLLNAME		1	// �l�`�̖��O�̓���

// �����Ղ̑傫��
#define WINDOW_NAME_COLUMN		11	// 5+5+1
#define WINDOW_NAME_ROW			9	// 5+3+1

// �E�B���h�E�̃T�C�Y�ƃp�f�B���O
#define WND_ENTERNAME_WIDTH		500
#define WND_ENTERNAME_HEIGHT	420
#define WND_ENTERNAME_PX		40
#define WND_ENTERNAME_PY		40

#define WND_ENTERNAME_PAGE_KATA			0 // �J�^�J�i
#define WND_ENTERNAME_PAGE_HIRA			1 // �Ђ炪��
#define WND_ENTERNAME_PAGE_ALPHABET		2 // �A���t�@�x�b�g�E����

// ���O����͂���E�B���h�E�̃N���X�B
// ���͂������O�̓O���[�o���ϐ�g_temp�ɑ�������B
// ���͂ł��閼�O�̕����̓J�^�J�i�A�Ђ炪�ȁA�p���L����3�y�[�W�ŕ\�������B
// �����I�ɂ͊e������BYTE�^�̔z��ŊǗ������B

class Window_EnterName : public Window_Base{
private:
	// ���͂��閼�O�̃^�C�v�B
	WORD nameType;
	// ���ݕ\�����Ă���y�[�W�B
	BYTE page;
	// �I����
	Selectable2D s_chars;
public:
	// �A�N�Z�T
	void SetNameType(WORD t){ nameType = t; };

	// �Z�b�g�A�b�v
	// (���O�E�B���h�E�̏o�����͑S�Ăقړ���)
	void MySetup(WORD _nameType);

	// �R���X�g���N�^
	Window_EnterName();

	// �J�[�\���̈ʒu�ƕ����̃C���f�b�N�X��Ή�������B
	WORD GetNameIndex(int pos_x, int pos_y, BYTE page) const;
	// �`�悷�ׂ��ʒu���擾����B
	int GetDrawX(int pos_x, int pos_y) const;
	int GetDrawY(int pos_x, int pos_y) const;

	// ���e�̃A�b�v�f�[�g���s���B
	virtual void Update();			// �N���X���Ƃɔh������A�b�v�f�[�g�֐��B

	// ���e�̕`����s���B
	virtual void DrawContent() const;

	// ���O�E�B���h�E�̓��ꕶ����`�悷��B
	void DrawSpecialChar(int x, int y, BYTE index, bool isLarge) const;
};

#endif // WINDOW_ENTERNAME_H