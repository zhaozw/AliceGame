#ifndef WINDOW_BASE_H
#define WINDOW_BASE_H

#include <Windows.h>
#include "WindowSkin.h"
#include "Static_Game.h"

// �ł���{�I�ȃE�B���h�E�������N���X�B
// �e�E�B���h�E�N���X�ɔh�����邪�A���̃N���X���͉̂������e��`�悵�Ȃ��B
// �J����e�X�V�Ȃǂ̏�Ԃ������A��Ԃɍ��킹�ăE�B���h�E�g��`�悷��@�\�����B

// Open�֐��̖߂�l
#define WNDOPEN_SUCCEED		0	// �J�����Ƃɐ�������
#define WNDOPEN_FAILED		1	// �J�����ƂɎ��s����
#define WNDOPEN_OPENED		2	// ���ɊJ���Ă���

// Close�֐��̖߂�l
#define WNDCLOSE_SUCCEED	0	// ���邱�Ƃɐ�������
#define WNDCLOSE_FAILED		1	// ���邱�ƂɎ��s����
#define WNDCLOSE_CLOSED		2	// ���ɕ����Ă���

typedef struct WindowArea{
	int x;
	int y;
	int w;
	int h;
	WindowArea(){
		x = 0;
		y = 0;
		w = 0;
		h = 0;
	};
	WindowArea(int _x, int _y, int _w, int _h){
		x = _x;
		y = _y;
		w = _w;
		h = _h;
	};
} WINDOWAREA;

class Window_Base{
public:
	// �E�B���h�E�̏�Ԃ�\��enum�^�̕ϐ��B
	// �A�N�e�B�u���ǂ����Ȃǂ�ێ����邪�A�\��/��\���ɂ��Ă͂���Ƃ͕ʂɊǗ�����B
	enum WINDOWSTATE{
		CLOSED,			// �E�B���h�E��������ԁB��\���B
		OPENING,		// �E�C���h�E���J�������Ă����ԁB
						// WindowSkin�ɒ�߂�ꂽ���Ԃ��o�ƊJ������ԂɂȂ�B
		CLOSING,		// �E�B���h�E���������Ă����ԁB
		UPDATING,		// �E�B���h�E���J���Ă��邪�A���e���X�V���Ă����ԁB
		IDLE,			// �E�B���h�E�̓��e���X�V���I�������ԁB�O������̓��͑҂��B
		SUSPENDED,		// �E�B���h�E���J���؂����u�Ԃ̏�ԁB
						// Window�̃N���X�ɂ����IDLE�Ɉڍs���邩UPDATING�Ɉڍs���邩���ς��B
		UNKNOWN = -1,	// ���ł��Ȃ���ԁB
	};
protected:
	// �E�B���h�E�X�L���ւ̎Q��
	WindowSkin* pSkin;
	// �E�B���h�E�̏��
	WINDOWSTATE state;
	// �q�E�B���h�E
	// ���̃E�B���h�E����h�����Ă���ɃE�B���h�E���o�Ă��鎞�A
	// �h���E�B���h�E�̃|�C���^��������B
	Window_Base*	pChildWindow;
	// �ʒu�Ƒ傫��
	// x, y : ��ʑS�̂ɂ�����E�B���h�E�̈ʒu
	// w, h : �E�B���h�E�̑傫��
	WINDOWAREA		frameArea;
	// ���e�̈ʒu�ƃT�C�Y
	// x, y : �t���[���̍��ォ����e�̈ʒu�܂ł̍��W�̂���
	// w, h : �E�B���h�E�̓��e�̑傫��
	WINDOWAREA		contentArea;
	// �E�B���h�E���\����Ԃ���\����Ԃ�
	bool visible;
	// �E�B���h�E�����݂��Ă��鎞�Ԃ̒���
	// enabled�ɂȂ��Ă���̎���
	int activeCount;
	// �E�B���h�E���q�E�B���h�E�������ۂ��B
	// false�ɂȂ�ƁAUpdateA�֐��ōX�V�����͍s���Ȃ��B
	bool haveChild;
	// �E�B���h�E�̊J���
	// openLevel��WindowSkin��openTime�Ɠ������Ȃ��������J����������ԁB
	int openLevel;
	// �E�B���h�E��Update_Common���ꂽ��
	// (��{�I�ɂ̓E�B���h�E�̏�������sceneTime�ƈ�v)
	int count;

public:
	// �R���X�g���N�^
	Window_Base();
	void Initialize();

	// �E�B���h�E�̃Z�b�g�A�b�v�i�ʒu�E�X�L���E�T�C�Y�̐ݒ�j���s��
	bool Setup(WindowSkin* pSkin,
		WINDOWAREA _frameArea, int _px, int _py,
		bool _visible);
	bool Setup(WindowSkin* pSkin,
		WINDOWAREA _frameArea, WINDOWAREA _contentArea,
		bool _visible);

	// �ʒu���蓮�Ō��߂�
	void SetPosition(int _x, int _y){
		frameArea.x = _x;
		frameArea.y = _y;
	};

	// �T�C�Y���蓮�Ō��߂�
	void SetSize(int _w, int _h){
		frameArea.w = _w;
		frameArea.h = _h;
	};

	// �E�B���h�E�̈ʒu�Ƒ傫�������߂�
	void SetFrameArea(WINDOWAREA _area){
		frameArea = _area;
	};
	void SetFrameArea(int _x, int _y, int _w, int _h){
		SetPosition(_x, _y);
		SetSize(_w, _h);
	};

	// �T�C�Y�����߂���ŗ]�������߂�Ɠ��e�̑傫���������Ō��߂�B
	void SetContentSizeByMargin(int _px, int _py){
		contentArea.x = _px;
		contentArea.y = _py;
		contentArea.w = frameArea.w - _px*2;
		contentArea.h = frameArea.h - _py;
	};


	// �E�B���h�E���J���B
	// force :	�������J��(���Ă���Œ��Ȃǂł��J���B)
	//			�����false�ɂ���Ə�Ԃ�CLOSED�̎��̂݊J���悤�ɂ���B
	// sudden : �A�j���[�V������p�����ɂ����Ȃ�J���B
	// �߂�l�ɂ͌��ʂ�Ԃ��B
	BYTE Open(bool force=false, bool sudden=false);

	// �E�B���h�E���J�����Ƃ��Ɏ��s����֐��B
	// (�����ɂ͊J�����Ƃ����u�ԂɎ��s����̂ŁA
	// �����œ��e�̏��������Ȃǂ��\)
	// �e�N���X�Ŕh������B
	virtual void OnOpened(){};

	// �q�E�B���h�E������ꂽ���Ɏ��s����֐��B
	// �e�N���X�Ŕh������B
	virtual void OnChildIsClosed(){};

	// �E�B���h�E�����B
	// force :	����������(�J���Ă���Œ�����e�̍X�V���ł�����)�B
	//			�����false�ɂ���Ə�Ԃ�IDLE�̎��̂ݕ���悤�ɂ���B
	// sudden :	�A�j���[�V������p�����ɂ����Ȃ����B
	BYTE Close(bool force=false, bool sudden=false);

	// ���e�̃A�b�v�f�[�g���s���B
	void UpdateA();			// �q�E�B���h�E���Ȃ��ꍇ�̂݃A�b�v�f�[�g����B
							// ��{�I��Update�֐��͂�������g�p����B
	virtual void Update();	// �N���X���Ƃɔh������A�b�v�f�[�g�֐��B
	bool Update_Common();	// ��{�I�ɋ��ʂ̃A�b�v�f�[�g�֐��B
							// Update���s��Ȃ���Ԃ̎���false��Ԃ��B

	// ���e�̕`����s���B
	// �N���X���Ƃɔh������B
	virtual void DrawContent() const;
	// �E�B���h�E�X�L���ւ̎Q�Ƃ𗘗p���Ęg�̕`����s���B
	// ��{�I�ɃN���X���Ƃɂ͔h�����Ȃ��B
	void DrawFrame() const;  
	// �E�B���h�E�S�̂̕`����s���B
	void Draw() const{ if(visible){ DrawFrame(); DrawContent(); }; };

	// �����̐ݒ�
	void SetVisible(bool b){ visible = b; };
	bool GetVisible() const{ return visible; };
	// �A�N�Z�T
	WINDOWSTATE GetState() const{ return state; } ; 
	bool GetActive() const; // activeCount�𑝉��������Ԃɂ��邩
	int GetOpenTime() const; // �X�L����openTime���擾����B
	// �G���A�֌W�̃A�N�Z�T
	int GetPositionX() const{ return frameArea.x; };
	int GetPositionY() const{ return frameArea.y; };

	// �X�L���̃Z�b�g���s��
	bool AttachSkin(WindowSkin* _pSkin){ pSkin = _pSkin; return true; };
	
	// ����ʒu�ɑ�����
	void SetPositionH(int pos, BYTE align=ALIGN_CENTER);
	void SetPositionV(int pos, BYTE valign=ALIGN_CENTER);

	// �q�E�B���h�E�̃|�C���^���w�肵�ăE�B���h�E���J���B
	// �E�B���h�E���J���Ǝ����I��isActive��false�ƂȂ�A
	// ����Ǝ����I��true�ɂȂ�B
	// �߂�l�F�q�E�B���h�E���J��������
	BYTE OpenChildWindow(Window_Base* _pChild, bool sudden = false);
};

#endif // WINDOW_BASE_H