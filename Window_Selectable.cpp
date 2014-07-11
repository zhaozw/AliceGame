// Window_Selectable.cpp

#include "Window_Selectable.h"

Window_Selectable::Window_Selectable() : Window_Text(),
	select(1, 1){
		useTitle = false;
		hTitleFont = 0;
		padding_bottom = 0;
		column = 1;
		row = 1;
		result = WND_SELECTABLE_RESULT_NONE;
		content_padding_x = 0;
		autoClose = true;
}

void Window_Selectable::Setup(
	WindowSkin* _pSkin, int _x, int _y, 
	Window_Selectable_Content _content,
	int _column,
	int _hFont, int _fontSize, int _lineHeight,
	bool _cancelable, bool _useTitle, BYTE _align){
		pSkin = _pSkin;
		x = _x;
		y = _y;
		content = _content;		// ���e�̃R�s�[
		hFont = _hFont;			// �t�H���g
		fontSize = _fontSize;	// �t�H���g�T�C�Y
		lineHeight = _lineHeight; // �s�̍���
		column = _column;
		cancelable = _cancelable; // �L�����Z���\���ۂ�
		useTitle = _useTitle;	// �^�C�g�����g�p���邩
		align = _align;
		// ��������͎����ݒ荀��
		SetAbbrParam();
		SetDefParam();
}

void Window_Selectable::SetTitle(LPTSTR _title, int _hTitleFont){
	strcpy_s(content.title, WND_SELECTABLE_TITLELENGTH-1, _title);
	hTitleFont = (_hTitleFont!=0) ? _hTitleFont : hFont;
	if(strlen(_title) > 0){
		useTitle = true;
	}
}

void Window_Selectable::GetTitle(LPTSTR str) const{
	strcpy_s(str, WND_SELECTABLE_TITLELENGTH-1, content.title);
}

void Window_Selectable::SetContent(LPTSTR _content, BYTE _index){
	strcpy_s(content.data[_index], WND_SELECTABLE_STRLENGTH-1, _content);
}

void Window_Selectable::GetContent(LPTSTR str, BYTE index) const{
	if(index < 0 || index >= WND_SELECTABLE_CONTENT) return;
	strcpy_s(str, WND_SELECTABLE_TITLELENGTH-1, content.data[index]);
}

void Window_Selectable::ClearContent(){
	for(int n=0; n<WND_SELECTABLE_CONTENT; n++){
		SetContent(_T(""), n);
	}
}

void Window_Selectable::SetAbbrParam(){
	titleHeight = 1.5*lineHeight;
	hTitleFont = hFont;
	padding_x = padding_y = pSkin->GetFrameSize() + WND_SELECTABLE_DEFPADDING;
	padding_bottom = padding_y 
		+ WND_SELECTABLE_DEFPADDING - WND_SELECTABLE_DEFLINESPACE;
	content_padding_x = 1.2*lineHeight;
	content_margin_x = content_padding_x;
}

void Window_Selectable::SetDefParam(bool autoSize){
	// ���݂̃p�����[�^�����ɃE�B���h�E�̕��ƍ����A�I�����̐����v�Z����
	int titleWidth=0, maxWidth = 0;
	int contentNum = 1;
	titleWidth = max(maxWidth, GetDrawStringWidthToHandle(
		content.title, strlen(content.title), hTitleFont)) + padding_x*2;
	for(int n=0; n<WND_SELECTABLE_CONTENT; n++){
		// �E�B���h�E�̕��𒲂ׂ�
		maxWidth = max(maxWidth, 
			GetDrawStringWidthToHandle(
			content.data[n], strlen(content.data[n]), hFont));
		if(strlen(content.data[n]) > 0){
			// ���g�̓����Ă��鍀�ڂ̐��𒲂ׂ�
			contentNum = n+1;
		}
	}
	// ���ڐ�(�s��)�̎擾
	row = (contentNum + (column-1)) / column;
	// ���ڃT�C�Y�̎擾
	content_width = maxWidth;
	if(autoSize){ // �T�C�Y�̕ύX���s���ꍇ
		// �E�B���h�E���̐ݒ�
		width = max(titleWidth,
			content_width*column+content_margin_x*(column-1)
			+(padding_x+content_padding_x)*2);
		// �p�f�B���O�̍Đݒ�
		if(titleWidth == width){
			content_padding_x = (width 
				- (content_width*column+content_margin_x*(column-1) + padding_x*2))/2;
		}
		// �E�B���h�E�����̐ݒ�
		height = padding_y+lineHeight*row+padding_bottom+(useTitle?titleHeight:0);
	}
	select.row = row;
	select.column = column;
	// �R���e���c�̑傫���̎w��
	SetContentSize();
}

void Window_Selectable::DrawContent() const{
	int cell;
	int ddx=0;	// ���������E�E�����̎��̕`��ʒu�̂���
	if(GetActive()){
		TCHAR buf[WND_SELECTABLE_TITLELENGTH];
		int cntX = 0;
		int cntY = y+padding_y;
		// �^�C�g����`�悷��ꍇ
		if(useTitle){
			GetTitle(buf);
			DrawStringToHandle(
				x + padding_x + GetDrawDeltaX(buf, -1, hTitleFont), cntY, 
				buf, color, hTitleFont);
			cntY += titleHeight;
		}

		// �e�I�����̕`��
		for(int h=0; h<row; h++){
			for(int w=0; w<column; w++){
				cell = w+h*column;
				GetContent(buf, cell);
				cntX = x + padding_x + content_padding_x
					+ (content_width+content_margin_x)*w;
				switch(align){
				case 0:
					ddx = 0;
					break;
				case 1:
					ddx = (content_width - 
						GetDrawStringWidthToHandle(buf, strlen(buf), hFont))/2;
					break;
				case 2:
					ddx = content_width - 
						GetDrawStringWidthToHandle(buf, strlen(buf), hFont);
					break;
				}
				DrawStringToHandle(
					cntX+ddx, cntY, 
					buf,
					select.isActive[cell] ? ((select.index == cell) 
					? color : iColor) : nColor,
					hFont);
				if(cell == select.index){
					// �t�H�[�J�X�̕`��
					pSkin->DrawFocus(cntX, cntY,
						content_width,
						fontSize, count);
				}
			}
			cntY += lineHeight;
		}
	}
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
}

void Window_Selectable::OnOpened(){
	result = WND_SELECTABLE_RESULT_NONE;
}

void Window_Selectable::Update(){
	// ���ʃA�b�v�f�[�g
	Update_Common();
	// �I�����ɃE�B���h�E����邩�̔���
	CheckAutoClose();
	switch(state){
	case UPDATING:
		// �X�V
		switch(select.Move()){
		case SELECT2D_CHOOSE:
			result = select.index;
			if(autoClose){
				state = IDLE;
				Close();
			}
			break;
		case SELECT2D_CANCEL:
			if(cancelable){
				result = WND_SELECTABLE_RESULT_CANCEL;
				Close();
			}
			break;
		}
		break;
	case SUSPENDED:
		// SUSPENDED��Ԃ̔���
		state = UPDATING;
		break;
	}
}

