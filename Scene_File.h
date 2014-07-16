#ifndef SCENE_FILE_H
#define SCENE_FILE_H

#include "Scene_Base.h"
#include "Selectable.h"
#include "Game_FileHeader.h"
#include "Func_AliceFile.h"
#include "Window_Yesno.h"

#define DRAW_FILE_BASEY		60
#define	DRAW_FILE_WIDTH		350
#define	DRAW_FILE_HEIGHT	100
#define	DRAW_FILE_MARGINY	20
#define DRAW_FILE_WLH		(DRAW_FILE_HEIGHT+DRAW_FILE_MARGINY)
#define	DRAW_SELECTED_WIDTH		350
#define	DRAW_SELECTED_HEIGHT	500
#define FILESELECT_SCROLL_TIME		(DELAY_DIGDIR2+1)
#define FILESELECT_FILE_PER_PAGE	4

#define SCNSTATE_FILE_CHOOSEFILE		0		// �t�@�C���̑I��
#define SCNSTATE_FILE_ASKOVERWRITE		1		// �t�@�C�����㏑�����邩��₤	

class Scene_File : public Scene_Base{
private:
	// ���݂̃��[�h�B����������Game_Temp����R�s�[����B
	int mode;
	// �t�@�C���Ԃ��ړ����Ă���t���O�B
	// 0:��~��
	// 1:���~��
	// 2:�㏸��
	BYTE moving;
	int movingTime;
	// ���݉�ʓ��ɕ\������Ă���t�@�C���̈�ԏ�̃C���f�b�N�X�B
	// ������Ԃł�0�B
	int drawIndex;
	// �t�@�C����I������I�����B
	Selectable		s_file;
	// �u�͂��v�u�������v��\������E�B���h�E�B
	Window_Yesno	w_yesno;
	// �e�t�@�C���̃t�@�C���w�b�_�̃R�s�[�B
	Game_FileHeader header[MAX_SAVEFILE];
	// �e�t�@�C���̃f�[�^�����ɑ��݂��邩�ۂ��B
	bool isFile[MAX_SAVEFILE];
public: 
	// �R���X�g���N�^
	Scene_File();
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

	// ��ʒu���w�肵�ăZ�[�u�t�@�C���̓��e��`�悷��
	void DrawSaveFile(int x, int y, BYTE index,
		bool isActive, bool canSelect) const;
	// ��ʒu���w�肵�ăf�[�^�̂Ȃ��t�@�C���̓��e��`�悷��
	void DrawEmptyFile(int x, int y, BYTE index,
		bool isActive, bool canSelect) const;
	// ��ʒu���w�肵�ďڍׂȃt�@�C���̓��e��`�悷��
	void DrawSelectedFile(int x, int y, BYTE index) const;

};

#endif // SCENE_FILE_H