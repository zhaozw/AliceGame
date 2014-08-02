// Window_Selectable.cpp

#include "Window_Selectable.h"
#include "DXFont.h"

Window_Selectable::Window_Selectable() : Window_Text(),
	content(), select(1, 1){
		column = 1;
		row = 1;
		item_width = 0;
		result = WND_SELECTABLE_RESULT_NONE;
		cancelable = false;
		autoClose = true;
		canChooseInactive = false;
}

void Window_Selectable::SetContent(WINDOW_SELECTABLE_CONTENT _content){
	content = _content;
	CheckActiveSelect();
}

void Window_Selectable::SetContent(LPTSTR _content, BYTE _index, bool active){
	strcpy_s(content.data[_index], WND_SELECTABLE_STRLENGTH-1, _content);
	select.isActive[_index] = active;
}

void Window_Selectable::ClearContent(){
	for(int n=0; n<WND_SELECTABLE_CONTENT; n++){
		SetContent(_T(""), n, false);
	}
}

void Window_Selectable::GetContent(LPTSTR str, BYTE index) const{
	if(index < 0 || index >= WND_SELECTABLE_CONTENT) return;
	strcpy_s(str, WND_SELECTABLE_TITLELENGTH-1, content.data[index]);
}

int Window_Selectable::GetContentMaxDrawWidth() const{
	int result = 0;
	for(int n=0; n<WND_SELECTABLE_CONTENT; n++){
		if(strlen(content.data[n]) > 0){
			result = max(result, 
				GetDrawStringWidthToHandle(
				content.data[n], strlen(content.data[n]), windowFont.hFont)); 
		}
	}
	return result;
}

void Window_Selectable::SetTitle(LPTSTR _title, int _hTitleFont, int _titleHeight){
	strcpy_s(content.title, WND_SELECTABLE_TITLELENGTH-1, _title);
	content.hTitleFont = (_hTitleFont!=0) ? _hTitleFont : windowFont.hFont;
	content.titleHeight = _titleHeight;
	content.useTitle = (strlen(_title) > 0);
}


int Window_Selectable::GetContentSize() const{
	int num = 0;
	for(int n=0; n<WND_SELECTABLE_CONTENT; n++){
		if(strlen(content.data[n]) > 0){
			// 中身の入っている項目の数を調べる
			num = n+1;
		}
	}
	return num;
}

void Window_Selectable::SetRowByContentSize(int _column){
	int num = GetContentSize();
	column = _column;
	if(num == 0){
		row = 1;
	}else{
		row = (num + column - 1) / column;
	}
	SetGridSize(column, row);
}


void Window_Selectable::CheckActiveSelect(){
	for(int n=0; n<WND_SELECTABLE_CONTENT; n++){
		// 中身の入っている項目を選択可能にする
		select.isActive[n] = (strlen(content.data[n]) > 0);
	}
}

void Window_Selectable::Setup(
	WindowSkin* _pSkin, 
	WINDOWAREA _frameArea,
	WINDOWAREA _contentArea,
	WINDOWFONT _font,
	int _item_margin_x){
		windowFont = _font;
		Window_Text::Setup(_pSkin, _frameArea, _contentArea, true);
		item_width = (_contentArea.w - _item_margin_x*(column-1))/column;
}

void Window_Selectable::Setup_FixPadding(
	WindowSkin* _pSkin, 
	WINDOWAREA _frameArea,
	int _px, int _py,
	WINDOWFONT _font,
	int _item_margin_x){
		windowFont = _font;
		Window_Text::Setup_FixPadding(_pSkin, _frameArea, _px, _py, true);
		item_width = (contentArea.w - _item_margin_x*(column-1))/column;
}

void Window_Selectable::Setup_FixContentWidth(
	WindowSkin* _pSkin, 
	WINDOWAREA _frameArea,
	int _content_width, int _py, 
	WINDOWFONT _font,
	int _item_margin_x){
		windowFont = _font;
		Window_Text::Setup_FixContentWidth(_pSkin, _frameArea,
			_content_width, _py, true);
		item_width = (contentArea.w - _item_margin_x*(column-1))/column;
}

void Window_Selectable::Setup_FixContentWidth_Auto(
	WindowSkin* _pSkin, 
	WINDOWAREA _frameArea,
	int _py, WINDOWFONT _font,
	int _item_margin_x){
		windowFont = _font;
		item_width = GetContentMaxDrawWidth();
		Window_Text::Setup_FixContentWidth(
			_pSkin, _frameArea,
			item_width + _item_margin_x*(column-1), _py, true);
}


void Window_Selectable::GetTitle(LPTSTR str) const{
	strcpy_s(str, WND_SELECTABLE_TITLELENGTH-1, content.title);
}

bool Window_Selectable::CheckInactive() const{
	return select.IsInactive();
}

bool Window_Selectable::GetIsEmpty(int i) const{
	if(i < 0 || i >= WND_SELECTABLE_CONTENT) return true;
	return strlen(content.data[i]) <= 0;
}


void Window_Selectable::OnOpened(){
	result = WND_SELECTABLE_RESULT_NONE;
}

void Window_Selectable::Update(){
	// 共通アップデート
	Update_Common();
	// 選択時にウィンドウを閉じるかの判定
	CheckAutoClose();
	// キャンセル可能かどうかの判定
	CheckCancelable();
	switch(state){
	case UPDATING:
		// 更新
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
		// SUSPENDED状態の判定
		state = UPDATING;
		break;
	}
}


void Window_Selectable::DrawContent() const{
	TCHAR buf[WND_SELECTABLE_TITLELENGTH];
	WINDOWAREA tmpArea;
	BYTE color;
	int contentSize = 0;
	if(GetActive()){
		int cntX = frameArea.x + contentArea.x;
		int cntY = frameArea.y + contentArea.y;
		// タイトルを描画する場合
		if(content.useTitle){
			GetTitle(buf);
			DrawStringToHandle(
				cntX + GetDrawDeltaX(buf, -1, content.hTitleFont), 
				cntY, 
				buf,
				windowFont.color, content.hTitleFont);
			cntY += content.titleHeight;
		}

		// 各選択肢の描画
		contentSize = GetContentSize();
		for(int n=0; n<contentSize; n++){
			tmpArea = GetDrawArea(n);
			color = select.isActive[n] ? ((select.index == n) 
			? WND_SELECTABLE_COLOR_SELECTED : WND_SELECTABLE_COLOR_ACTIVE) 
			: WND_SELECTABLE_COLOR_INACTIVE,
			DrawContentItem(n, color);
			if(n == select.index){
				// フォーカスの描画
				pSkin->DrawFocus(
					tmpArea.x, tmpArea.y,
					tmpArea.w, tmpArea.h, count);
			}
		}
		/*
		for(int h=0; h<row; h++){
			for(int w=0; w<column; w++){
				cell = w+h*column;
				GetContent(buf, cell);
				cntX = frameArea.x + contentArea.x 
					 + (item_width+item_margin_x)*w;
				switch(windowFont.align){
				case 0:
					ddx = 0;
					break;
				case 1:
					ddx = (item_width - 
						GetDrawStringWidthToHandle(buf, strlen(buf), windowFont.hFont))/2;
					break;
				case 2:
					ddx = item_width - 
						GetDrawStringWidthToHandle(buf, strlen(buf), windowFont.hFont);
					break;
				}
				DrawStringToHandle(
					cntX+ddx, cntY, 
					buf,
					select.isActive[cell] ? ((select.index == cell) 
					? windowFont.color : windowFont.iColor) : windowFont.nColor,
					windowFont.hFont);
				if(cell == select.index){
					// フォーカスの描画
					pSkin->DrawFocus(
						cntX, cntY,
						item_width,
						windowFont.fontSize, count);
				}
			}
			cntY += windowFont.lineHeight;
		}
		*/
	}
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
}

WINDOWAREA Window_Selectable::GetDrawArea(int i) const{
	WINDOWAREA area;
	int tmpX=0, tmpY=0;
	tmpX = frameArea.x + contentArea.x;
	tmpY = frameArea.y + contentArea.y;
	if(content.useTitle){
		tmpY += content.titleHeight;
	}
	int line=0, pos=0;
	line = i/column;	// インデックスが該当する行数
	pos = i%column;		// インデックスが該当する桁の位置
	int item_margin_x = (column <= 1) ? 0 
		: (contentArea.w - column * item_width)/(column-1);
	tmpX += (item_width+item_margin_x)*pos;
	tmpY += windowFont.lineHeight*line;
	// 値の代入
	area.x = tmpX;
	area.y = tmpY;
	area.w = item_width;
	area.h = windowFont.fontSize;
	return area;
}

int Window_Selectable::GetItemColor(BYTE itemType) const{
	switch(itemType){
	case WND_SELECTABLE_COLOR_SELECTED:
		return GetTextColor();
		break;
	case WND_SELECTABLE_COLOR_ACTIVE:
		return GetIColor();
		break;
	case WND_SELECTABLE_COLOR_INACTIVE:
		return GetNColor();
		break;
	}
	return 0;
}

void Window_Selectable::DrawContentItem(int index, BYTE fontColor) const{
	TCHAR buf[WND_SELECTABLE_TITLELENGTH];
	WINDOWAREA tmpArea;
	int ddx=0;	// 中央揃え・右揃えの時の描画位置のずれ

	tmpArea = GetDrawArea(index);
	GetContent(buf, index);
	switch(windowFont.align){
	case 0:
		ddx = 0;
		break;
	case 1:
		ddx = (tmpArea.w - GetStrWidth(buf, strlen(buf), windowFont.hFont))/2;
		break;
	case 2:
		ddx = tmpArea.w - GetStrWidth(buf, strlen(buf), windowFont.hFont);
		break;
	}
	int color = fontColor;
	switch(color){
	case WND_SELECTABLE_COLOR_SELECTED:
		color = windowFont.color;
		break;
	case WND_SELECTABLE_COLOR_ACTIVE:
		color = windowFont.iColor;
		break;
	case WND_SELECTABLE_COLOR_INACTIVE:
		color = windowFont.nColor;
		break;
	}
	DrawStringToHandle(
		tmpArea.x+ddx, tmpArea.y, 
		buf, color,
		windowFont.hFont);
}
