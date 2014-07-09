#ifndef WINDOW_SELECTABLE_H
#define WINDOW_SELECTABLE_H

#include "Window_Text.h"
#include "Selectable2D.h"
#include "Static_Game.h"
#include <Windows.h>
#include <string.h>

// �I������\������E�B���h�E�B
// �ό��̃��X�g�������̂Ƃ͈قȂ�A
// �P���ɕ������`�悷��B
// �����ɓ񎟌���Selectable2D��ێ����A�c���̑I�����ɑΉ�����B
// �܂��A���ڐ��͍ő��8�A�e���ڂ̕����T�C�Y��32�܂łɐ��������B

#define WND_SELECTABLE_CONTENT		32
#define WND_SELECTABLE_STRLENGTH	32
#define WND_SELECTABLE_TITLELENGTH	32
#define WND_SELECTABLE_DEFPADDING	0
#define WND_SELECTABLE_DEFLINESPACE	4	// �t�H���g�ɑ΂���s�̍����̍��̃f�t�H���g�l�B
										// �E�B���h�E�T�C�Y�̌v�Z�Ɏg�p����B

#define WND_SELECTABLE_RESULT_NONE		-1	// �܂��I������Ă��Ȃ�
#define WND_SELECTABLE_RESULT_CANCEL	-2	// �L�����Z���{�^���������ꂽ

struct Window_Selectable_Content{
	TCHAR title[WND_SELECTABLE_TITLELENGTH];
	TCHAR data[WND_SELECTABLE_CONTENT][WND_SELECTABLE_STRLENGTH];
	Window_Selectable_Content(){
		strcpy_s(title, WND_SELECTABLE_TITLELENGTH-1, _T(""));
		for(int n=0; n<WND_SELECTABLE_CONTENT; n++){
			strcpy_s(data[n], WND_SELECTABLE_STRLENGTH-1, _T(""));
		}
	};
};

class Window_Selectable : public Window_Text{
protected:
	Selectable2D select;
	Window_Selectable_Content content;
	// Setup�Őݒ肳��鍀��
	// BYTE align;			// �����̊񂹕��B
	// int	lineHeight;		// ���ڂ��Ƃ̊Ԋu�B 
	// int hFont;			// �t�H���g�̃n���h��
	bool useTitle;		// �I�����Ƀ^�C�g����\�����邩�ۂ��B
	bool cancelable;	// �L�����Z���\���ۂ�
	// Setup���Ɏ����Őݒ肳��鍀��
	int hTitleFont;		// �^�C�g���ɗp����t�H���g�B
	int titleHeight;	// �^�C�g����`�悷��̂ɗp���鍂���B
	int padding_bottom;	// ���ڂƘg���̊Ԃɂ��錄�ԁB
						// �E�B���h�E�T�C�Y�̐ݒ�Ɏg�p����B
	int row;			// �s�̐�
	int column;			// ��̐�
	int result;			// �I�����E�B���h�E�̌���
	int content_padding_x;		// �I�����ڂɂ��Ẵp�f�B���O
	int content_margin_x;		// �񂪕�������ꍇ�̍��ړ��m�̕�
	int content_width;			// ���ڂ̕��B�����v�Z�����B
	// int color;
	bool autoClose;		// �I������I�񂾌�A�����ŃE�B���h�E����邩
public:
	// �R���X�g���N�^�B
	Window_Selectable();

	// ���e�̃Z�b�g�A�b�v���s���B
	void Setup(WindowSkin* _pSkin, int _x, int _y, 
		Window_Selectable_Content _content, int _column,
		int _hFont, int _fontHeight, int _lineHeight,
		bool _cancelable = false, bool _useTitle = false,
		BYTE _align = ALIGN_LEFT);

	// �E�B���h�E�̃^�C�g����ݒ肷��B
	void SetTitle(LPTSTR title, int hTitleFont = 0);
	void GetTitle(LPTSTR str) const;
	// �E�B���h�E�̓��e��ݒ肷��B
	void SetContent(LPTSTR content, BYTE index);
	virtual void GetContent(LPTSTR str, BYTE index) const;
	// ���ʂ��擾����B
	int GetResult() const { return result; };
	bool Choosed() const { return result != WND_SELECTABLE_RESULT_NONE; };
	// �ȗ����̃p�����[�^���v�Z���đ������
	void SetAbbrParam();
	// �f�t�H���g�̃E�B���h�E�T�C�Y�Ȃǂ̐ݒ��K�p����B
	void SetDefParam(bool autoSize=true);
	// �C���f�b�N�X�̏����l�����߂�B
	void SetSelectIndex(WORD index){ select.index = index; };
	int GetSelectIndex(){ return select.index; };

	// �J���ꂽ���̏����B
	// �I�����ꂽ���ڂ̏��������s���B
	virtual void OnOpened();

	// ���e�̍X�V���s���B
	virtual void Update();

	// �����ŕ��邩�ǂ����̔�����s��
	virtual void CheckAutoClose(){};

	// ���e�̕`����s���B
	// �N���X���Ƃɔh������B
	virtual void DrawContent() const;

};

#endif // WINDOW_SELECTABLE_H