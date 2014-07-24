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

// �g�p������@�Ƃ��ẮA�܂�SetContent�ɂ��\��������e���w��A
// ����SetGridSize�܂���SetRowByContentSize�őI�����̏c���̑傫�������߁A
// ����Setup�ASetup_AutoMargin�ȂǂŃE�B���h�E�̈ʒu��傫�������߂�B
// �\������x�ɓ��e���قȂ�ꍇ�́A���񂱂̏����𓥂ނ��A
// �E�B���h�E�T�C�Y���Œ�̏ꍇ��Setup�n�֐��͍ēx�s���K�v�͂Ȃ��B
// Setup�n�֐������Window_Base::Setup���Ăяo�����B
// �Ȃ��A�������͂ݏo���ꍇ�Ȃǂ̋~�ϑ[�u�͂Ȃ��i�k�߂ĕ\�����Ă��ꂽ��͂��Ȃ��j�B

#define WND_SELECTABLE_CONTENT		32
#define WND_SELECTABLE_STRLENGTH	32
#define WND_SELECTABLE_TITLELENGTH	32
#define WND_SELECTABLE_DEFPADDING	0
#define WND_SELECTABLE_DEFLINESPACE	4	// �t�H���g�ɑ΂���s�̍����̍��̃f�t�H���g�l�B
										// �E�B���h�E�T�C�Y�̌v�Z�Ɏg�p����B

#define WND_SELECTABLE_RESULT_NONE		-1	// �܂��I������Ă��Ȃ�
#define WND_SELECTABLE_RESULT_CANCEL	-2	// �L�����Z���{�^���������ꂽ

typedef struct Window_Selectable_Content{
	TCHAR	title[WND_SELECTABLE_TITLELENGTH];
	bool	useTitle;		// �I�����Ƀ^�C�g����\�����邩�ۂ��B
	int		hTitleFont;		// �^�C�g���ɗp����t�H���g�B
	int		titleHeight;	// �^�C�g����`�悷��̂ɗp���鍂���B
	TCHAR	data[WND_SELECTABLE_CONTENT][WND_SELECTABLE_STRLENGTH];
	Window_Selectable_Content(){
		strcpy_s(title, WND_SELECTABLE_TITLELENGTH-1, _T(""));
		useTitle = false;
		hTitleFont = 0;
		titleHeight = 0;
		for(int n=0; n<WND_SELECTABLE_CONTENT; n++){
			strcpy_s(data[n], WND_SELECTABLE_STRLENGTH-1, _T(""));
		}
	};
} WINDOW_SELECTABLE_CONTENT;

class Window_Selectable : public Window_Text{
protected:
	Selectable2D					select;
	WINDOW_SELECTABLE_CONTENT		content;
	// ���e�̃T�C�Y�Ɋւ���
	int		row;			// �s�̐�
	int		column;			// ��̐�
	int		item_width;		// ���ڂ̕�
							// �}�[�W���̑傫���͍��ڂ̕��Ɠ��e�̕����玩���I�Ɍ��܂�B

	// �֐��̌��ʂɊւ���
	int		result;			// �I�����E�B���h�E�̌���
							// �L�����Z���̏ꍇ��-1��Ԃ�
	bool	cancelable;		// �L�����Z���\���ۂ�
							// CheckCancelable�֐���
	bool	autoClose;		// �I������I�񂾌�A�����ŃE�B���h�E����邩
public:
	// �R���X�g���N�^�B
	Window_Selectable();

	// ���e��ݒ肷��B
	// �A�������āA���̑I�������I���\���ǂ������ݒ肷��B
	void	SetContent(WINDOW_SELECTABLE_CONTENT _content);	// �S���w�肷��ꍇ
															// CheckActiveSelect���s��
	void	SetContent(
		LPTSTR _content, BYTE index, bool active=true);		// ����w�肷��ꍇ
															// useTitle��true�ɂȂ�
	virtual void GetContent(LPTSTR str, BYTE index) const;

	// �E�B���h�E�̓��e��S�ăN���A����B
	// �������N���A���邾���ŁA�傫���Ȃǂ͕ύX���Ȃ��B
	void	ClearContent();	

	int		GetContentMaxDrawWidth() const;					// ���ڂ̕`��T�C�Y�̂���
															// �ł��傫���l���擾
	// �E�B���h�E�̃^�C�g����ݒ肷��B
	void	SetTitle(LPTSTR title, int hTitleFont = 0);
	void	GetTitle(LPTSTR str) const;
	
	// �I�����̉��̐��Əc�̐���ݒ肷��B
	void	SetGridSize(int _column, int _row){
		column = _column; row = _row;
		select.column = _column; select.row = _row;
	}

	// �I�����̏c�̐������݂̓��e���猈�肷��B
	void	SetRowByContentSize(int _column);

	// ���e�̓����Ă���I������true�A
	// �����Ă��Ȃ��I������false�ɂ���B
	// ���e�������Ă��邯�ǑI���o���Ȃ��A�Ȃǂ�
	// �����Őݒ肷��K�v������B
	void	CheckActiveSelect();

	// �E�B���h�E�̃Z�b�g�A�b�v���s���B
	// ���̎����ɓ��e�̓Z�b�g����Ă��āA
	// column�l�y��row�l�����܂��Ă���B
	// �����ł͑傫���Ȃǂ����߂�B
	void	Setup(
		WindowSkin* _pSkin, 
		WINDOWAREA _frameArea,
		WINDOWAREA _contentArea,
		WINDOWFONT _font,
		int itemWidth
		);

	void	Setup(
		WindowSkin* _pSkin, 
		WINDOWAREA _frameArea,
		int _px, int _py,
		WINDOWFONT _font,
		int itemWidth
		);
	
	// ���e�̃Z�b�g�A�b�v���s���B
	// ���ڂ̃T�C�Y�ɉ����č��ڂ̃T�C�Y�������Œ������Ă����B
	void	Setup_AutoMargin(
		WindowSkin* _pSkin, 
		WINDOWAREA _frameArea,
		int _px, int _py,
		WINDOWFONT _font
		);

	// ���e�̃Z�b�g�A�b�v���s���B
	// ���ڂ̃T�C�Y�ɉ����ăE�B���h�E�̑傫����ς���Ƃ�������ȃZ�b�g�A�b�v�B
	// ��ʒ����ɏo��E�B���h�E�ȂǂɎg�p����B
	// ���̊֐������s����O��SetGridSize�֐����s���K�v������B
	/*
	void	Setup_FlexSize(WindowSkin* _pSkin, int _x, int _y, 
		Window_Selectable_Content _content, int _column,
		int _hFont, int _fontHeight, int _lineHeight,
		bool _cancelable = false, bool _useTitle = false,
		BYTE _align = ALIGN_LEFT);
		*/

	// ���ʂ��擾����B
	int		GetResult() const { return result; };
	bool	Choosed() const { return result != WND_SELECTABLE_RESULT_NONE; };
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