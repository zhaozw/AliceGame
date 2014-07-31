#ifndef WINDOW_LINEINFO_H
#define WINDOW_LINEINFO_H

#include "Window_Text.h"
#include "DXFont.h"

// ��s�̏���ێ�����N���X�B
// ���Ȃ�ȗ�������Ă���A�t�H���g��E�B���h�E�T�C�Y�i�����j�͌Œ�B
// ���̃N���X�̂܂܎g���Ă��ǂ����A�g���ɂ�����Δh�������Ă��ǂ��B

#define WND_LINEINFO_BYTES		128
#define WND_LINEINFO_HEIGHT		(FONTSIZE_INFO+32)

class Window_LineInfo : public Window_Text{
protected:
	TCHAR			text[WND_LINEINFO_BYTES];
public:
	// �R���X�g���N�^
	Window_LineInfo();
	
	// �Z�b�g�A�b�v
	void Setup(int x, int y, int w, BYTE align);

	// �\�����镶����ݒ肷��
	void SetText(LPTSTR str, int length);

	// �`��
	virtual void DrawContent() const;

};


#endif // WINDOW_LINEINFO_H
