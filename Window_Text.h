#ifndef WINDOW_TEXT_H
#define WINDOW_TEXT_H

#include "Window_Base.h"

// ������`�悷��E�B���h�E�̃N���X�B
// ���ɕ`�悷�镶���̌`�Ԃ╶���̕`��̎d���͌��܂��Ă��炸�A
// ���ۂɂ͔h�������N���X���g�p����B
class Window_Text : public Window_Base{
protected:
	BYTE align;			// �����̊񂹕��B
	int	lineHeight;		// ���ڂ��Ƃ̊Ԋu�B 
	int hFont;			// �t�H���g�̃n���h��
	int fontSize;		// �t�H���g�̑傫��
	int color;			// �t�H���g�̐F
	int iColor;			// �I������Ă��Ȃ��e�L�X�g�̃t�H���g�̐F�B
	int nColor;			// �I���ł��Ȃ��e�L�X�g�̃t�H���g�̐F�B
public:
	// �R���X�g���N�^
	Window_Text();

	// �����F�̐ݒ�
	// �F�ݒ�́A�ʏ�F�A�I������Ă��Ȃ��A�I���ł��Ȃ��̏��Ɏw�肷��
	void SetColor(int _color, bool setAll=true){
		color = _color; if(setAll){ iColor = nColor = _color; }; };
	void SetIColor(int _color, bool setNColor=true){
		iColor = _color; if(setNColor){ nColor = _color; }; };
	void SetNColor(int _color){ nColor = _color; }
	void SetAllColor(int _color, int _iColor, int _nColor){
		color = _color; iColor = _iColor; nColor = _nColor; }; 
		
	// �t�H���g�̎w��
	void SetFont(int _hFont, int _fontSize, int _lineHeight){
		hFont = _hFont; fontSize = _fontSize; lineHeight = _lineHeight;
	};

	// ���e�̕��т𑵂��鎞�̕`��ʒu�̂���̐ݒ�
	// content : ����
	// strSize : ������̒����i�ȗ��j
	// _hFont : hFont�ƈقȂ�t�H���g���g�p����ۂ̃t�H���g�̃n���h��
	// ��const�ɂ��Ă����Ȃ��Ɣh���N���X����g�p�������ɃG���[���o��B
	//   �����o��ύX�����ƍ���Ƃ����Ƃ��H
	int GetDrawDeltaX(LPTSTR content, int strSize = -1, int _hFont = 0) const;
};

#endif // WINDOW_TEXT_H