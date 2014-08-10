#ifndef WINDOWSKIN_H
#define WINDOWSKIN_H

#include <Windows.h>

#define DEF_FRAME_SIZE 16
#define NUM_WND_IMG_ARRAY 10

// WindowSkin�N���X
// �E�B���h�E�X�L���i�E�B���h�E�̌����ځj�ɂ��Ă̏���ێ�����N���X�B
// WindowSkins�N���X�̃O���[�o���ϐ��ł���g_wndSkins���錾����A
// ���̃����o�ϐ��ł���skin�Ƃ���WindowSkin��񋓂���`�ŕێ�����B
// �eWindowSkin�ւ̎Q�Ƃ��E�C���h�E���ێ����邱�ƂŎQ�Ƃ��s���B

#define MAX_WNDSKIN					3
#define WNDSKIN_SIMPLE				0
#define WNDSKIN_NONE				1
#define WNDSKIN_BALLOON				2

class Window_Base;
class WindowSkin;


// �E�B���h�E�X�L��
#define MAX_WNDIMGINDEX					9
#define WNDIMGINDEX_TOPLEFT				0
#define WNDIMGINDEX_TOP					1
#define WNDIMGINDEX_TOPRIGHT			2
#define WNDIMGINDEX_LEFT				3
#define WNDIMGINDEX_CENTER				4
#define WNDIMGINDEX_RIGHT				5
#define WNDIMGINDEX_BOTTOMLEFT			6
#define WNDIMGINDEX_BOTTOM				7
#define WNDIMGINDEX_BOTTOMRIGHT			8
#define WNDIMGINDEX_NOFRAME				0
#define WNDIMGINDEX_HEADER_CENTER		3

class WindowSkin{
public:
	enum FRAMETYPE{
		FT_NOIMAGE,		// �摜�Ȃ�
		FT_EXTEND,		// �g�͂��̂܂ܕ`��A���g�͈����L�΂�
		FT_NOFRAME,		// �g�Ȃ��A���S�摜�������L�΂�
		FT_HEADER,		// ��[�̂ݓƗ��A���C�������͈����L�΂��ŕ\��
	}; 

	enum WNDOPENTYPE{
		OT_NONE,		// ���S�ɊJ�����Ƃ������`��A���͕`�悵�Ȃ�
		OT_FADE,		// ���̏�Ƀt�F�[�h�C��
		OT_EXPAND_Y,	// �c�����ɊJ��
	};
private:
	// ���܂������Ԃŕ��ׂ�ꂽ�摜�̔z��ւ̎Q�ƁB
	int *wndImgArray;
	// �E�B���h�E�X�L����ID�B
	// �I�����ڂ̕`��ȂǂɎg�p����B
	BYTE wndSkinID;
	// �g�̑����B
	int frameSize;
	// �摜�̑g�ݍ��킹���̃^�C�v�B
	enum FRAMETYPE frameType;
	// �E�B���h�E���J���Ƃ��̃A�j���[�V�����̎d���̃^�C�v�B
	enum WNDOPENTYPE openType;
	// �E�B���h�E���J���̂ɗv���鎞�ԁB
	int openTime;
public:
	// �R���X�g���N�^
	WindowSkin();
	// �摜�����蓖�Ă�
	bool AttachImage(int* _img, BYTE _wndSkinID, int _frameSize,
		FRAMETYPE _type, WNDOPENTYPE _oType, int _openTime);

	// �`��
	// �����̃|�C���^��const�����邱�Ƃɂ��
	// �l��ύX�ł��Ȃ�����B
	void Draw(int _x, int _y, int _w, int _h, int _openLevel) const;
	void Draw_FT_Extend(int _cx, int _cy, int _w, int _h, float _exRateX, float _exRateY) const;
	void Draw_FT_NoFrame(int _cx, int _cy, int _w, int _h, float _exRateX, float _exRateY) const;
	void Draw_FT_Header(int _cx, int _cy, int _w, int _h, float _exRateX, float _exRateY) const;

	// �I������Ă��鍀�ڂ̃n�C���C�g�̕`��
	void DrawFocus(int x, int y, int width, int height, int time) const;

	// �A�N�Z�T
	int GetFrameSize(){ return frameSize; };
	int GetOpenTime(){ return openTime; };

};

class WindowSkins{
public:
	WindowSkin skin[MAX_WNDSKIN];
	// �E�B���h�E�X�L���ւ̊��蓖�Ă��s���B
	bool AttachImages();
};


#endif // WINDOWSKIN_H