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
		content = _content;		// 内容のコピー
		hFont = _hFont;			// フォント
		fontSize = _fontSize;	// フォントサイズ
		lineHeight = _lineHeight; // 行の高さ
		column = _column;
		cancelable = _cancelable; // キャンセル可能か否か
		useTitle = _useTitle;	// タイトルを使用するか
		align = _align;
		// ここからは自動設定項目
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
	// 現在のパラメータを元にウィンドウの幅と高さ、選択肢の数を計算する
	int titleWidth=0, maxWidth = 0;
	int contentNum = 1;
	titleWidth = max(maxWidth, GetDrawStringWidthToHandle(
		content.title, strlen(content.title), hTitleFont)) + padding_x*2;
	for(int n=0; n<WND_SELECTABLE_CONTENT; n++){
		// ウィンドウの幅を調べる
		maxWidth = max(maxWidth, 
			GetDrawStringWidthToHandle(
			content.data[n], strlen(content.data[n]), hFont));
		if(strlen(content.data[n]) > 0){
			// 中身の入っている項目の数を調べる
			contentNum = n+1;
		}
	}
	// 項目数(行数)の取得
	row = (contentNum + (column-1)) / column;
	// 項目サイズの取得
	content_width = maxWidth;
	if(autoSize){ // サイズの変更を行う場合
		// ウィンドウ幅の設定
		width = max(titleWidth,
			content_width*column+content_margin_x*(column-1)
			+(padding_x+content_padding_x)*2);
		// パディングの再設定
		if(titleWidth == width){
			content_padding_x = (width 
				- (content_width*column+content_margin_x*(column-1) + padding_x*2))/2;
		}
		// ウィンドウ高さの設定
		height = padding_y+lineHeight*row+padding_bottom+(useTitle?titleHeight:0);
	}
	select.row = row;
	select.column = column;
	// コンテンツの大きさの指定
	SetContentSize();
}

void Window_Selectable::DrawContent() const{
	int cell;
	int ddx=0;	// 中央揃え・右揃えの時の描画位置のずれ
	if(GetActive()){
		TCHAR buf[WND_SELECTABLE_TITLELENGTH];
		int cntX = 0;
		int cntY = y+padding_y;
		// タイトルを描画する場合
		if(useTitle){
			GetTitle(buf);
			DrawStringToHandle(
				x + padding_x + GetDrawDeltaX(buf, -1, hTitleFont), cntY, 
				buf, color, hTitleFont);
			cntY += titleHeight;
		}

		// 各選択肢の描画
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
					// フォーカスの描画
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
	// 共通アップデート
	Update_Common();
	// 選択時にウィンドウを閉じるかの判定
	CheckAutoClose();
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

