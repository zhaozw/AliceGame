#ifndef WINDOW_TEXT_H
#define WINDOW_TEXT_H

#include "Window_Base.h"

#define WINDOWFONT_DEFCOLOR		0x00ffffff
#define WINDOWFONT_DEFICOLOR	0x00909090
#define WINDOWFONT_DEFNCOLOR	0x00404060

typedef struct WindowFont{
	int		hFont;			// �t�H���g�̃n���h���B
	int		fontSize;		// �t�H���g�T�C�Y�B
	int		lineHeight;		// ��s�̍����B
	int		color;			// �ʏ핶���̐F�B
	int		iColor;			// ��I�𕶎��̐F�B
	int		nColor;			// ��A�N�e�B�u���̕����̐F�B
	BYTE	align;			// �����̊񂹕��B
	WindowFont(){
		hFont = 0;
		fontSize = 1;
		lineHeight = 1;
		color = WINDOWFONT_DEFCOLOR;
		iColor = WINDOWFONT_DEFICOLOR;
		nColor = WINDOWFONT_DEFNCOLOR;
		align = ALIGN_LEFT;
	}
	WindowFont(int _hFont, int _fontSize, int _lineHeight,
		int _color, int _iColor, int _nColor, BYTE _align = ALIGN_CENTER){
		hFont = _hFont;
		fontSize = _fontSize;
		lineHeight = _lineHeight;
		color = _color;
		iColor = _iColor;
		nColor = _nColor;
		align = _align;
	}
	WindowFont(int _hFont, int _fontSize, int _lineHeight, BYTE _align = ALIGN_CENTER){
		hFont = _hFont;
		fontSize = _fontSize;
		lineHeight = _lineHeight;
		color = WINDOWFONT_DEFCOLOR;
		iColor = WINDOWFONT_DEFICOLOR;
		nColor = WINDOWFONT_DEFNCOLOR;
		align = _align;
	}
} WINDOWFONT;

// ������`�悷��E�B���h�E�̃N���X�B
// ���ɕ`�悷�镶���̌`�Ԃ╶���̕`��̎d���͌��܂��Ă��炸�A
// ���ۂɂ͔h�������N���X���g�p����B

class Window_Text : public Window_Base{
protected:
	WINDOWFONT	windowFont;			
public:
	// �R���X�g���N�^
	Window_Text();

	// �����F�̐ݒ�
	// �F�ݒ�́A�ʏ�F�A�I������Ă��Ȃ��A�I���ł��Ȃ��̏��Ɏw�肷��
	void SetColor(int _color, bool setAll=true){
		windowFont.color = _color; 
		if(setAll){
			windowFont.iColor = windowFont.nColor = _color;
		};
	};
	void SetIColor(int _color, bool setNColor=true){
		windowFont.iColor = _color;
		if(setNColor){
			windowFont.nColor = _color;
		};
	};
	void SetNColor(int _color){
		windowFont.nColor = _color;
	};
	void SetAllColor(int _color, int _iColor, int _nColor){
		windowFont.color = _color;
		windowFont.iColor = _iColor;
		windowFont.nColor = _nColor;
	}; 
		
	// �t�H���g�̎w��
	void SetFont(int _hFont, int _fontSize, int _lineHeight){
		windowFont.hFont = _hFont;
		windowFont.fontSize = _fontSize;
		windowFont.lineHeight = _lineHeight;
	};

	// ���e�̕��т𑵂��鎞�̕`��ʒu�̂���̐ݒ�
	// content : ����
	// strSize : ������̒����i�ȗ��j
	// _hFont : hFont�ƈقȂ�t�H���g���g�p����ۂ̃t�H���g�̃n���h��
	// �Ȃ���DrawContent���Ŏg�p���悤�Ƃ����Error��f���ւ��ۂ��֐��B
	// ��const�ɂ��Ă����Ȃ��Ɣh���N���X����g�p�������ɃG���[���o��B
	//   �����o��ύX�����ƍ���Ƃ����Ƃ��H
	int GetDrawDeltaX(TCHAR* content, int strSize = -1, int _hFont = 0) const;
};

#endif // WINDOW_TEXT_H