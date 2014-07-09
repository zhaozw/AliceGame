// Window_Base.h

#include "Window_Base.h"
#include <DxLib.h>


Window_Base::Window_Base(){
	// 全てのメンバの初期化
	Initialize();
}

void Window_Base::Initialize(){
	x = y = width = height = padding_x = padding_y = 0;
	state = CLOSED;
	openLevel = 0;
	visible = false;
	activeCount = 0;
	pSkin = NULL;
	count = 0;
}

bool Window_Base::Setup(WindowSkin* pSkin, int _x, int _y, int _w, int _h, int _px, int _py, bool _visible){
	x = _x;
	y = _y;
	width = _w;
	height = _h;
	padding_x = _px;
	padding_y = _py;
	visible = _visible;
	AttachSkin(pSkin);
	SetContentSize();
	return true;
}

BYTE Window_Base::Open(bool force, bool sudden){
	bool success = false;
	BYTE result = WNDOPEN_FAILED;
	switch(state){
	case CLOSED:
		success = true;
		result = WNDOPEN_SUCCEED;
		break;
	case OPENING:
	case CLOSING:
		if(force){
			success = true;
			result = WNDOPEN_SUCCEED;
		}else{
			result = WNDOPEN_FAILED;
		}
		break;
	case UPDATING:
	case IDLE:
	case SUSPENDED:
		// 既に開かれている状態の時はどうやっても開かない
		success = false;
		result = WNDOPEN_OPENED;
		break;
	case UNKNOWN:
		result = WNDOPEN_FAILED;
		break;
	}

	if(success){
		if(sudden){
			// 開かれた状態にする
			state = SUSPENDED;
			openLevel = GetOpenTime();
		}else{
			// 開き始めた状態にする
			// openLevelはいじらない
			state = OPENING;
		}
	}

	return result;
}

BYTE Window_Base::Close(bool force, bool sudden){
	bool succeed = false;
	BYTE result = WNDCLOSE_FAILED;

	switch(state){
	case CLOSED:
		result = WNDCLOSE_CLOSED;
		break;
	case OPENING:
	case CLOSING:
		if(force){
			succeed = true;
			result = WNDCLOSE_SUCCEED;
		}else{
			result = WNDCLOSE_FAILED;
		}
		break;
	case UPDATING:
	case SUSPENDED:
		if(force){
			succeed = true;
			result = WNDCLOSE_SUCCEED;
		}else{
			result = WNDCLOSE_FAILED;
		}
		break;
	case IDLE:
		// Close命令を普通に受け取る唯一の状態
		succeed = true;
		result = WNDCLOSE_SUCCEED;
		break;
	case UNKNOWN:
		result = WNDOPEN_FAILED;
		break;
		
	}

	if(succeed){
		if(sudden){
			// 開かれた状態にする
			state = CLOSED;
			openLevel = 0;
		}else{
			// 閉じ始めた状態にする
			// openLevelはいじらない
			state = CLOSING;
		}
	}

	return result;
}

void Window_Base::UpdateA(){
	if(haveChild){
		Update();
	}else{
		if(pChildWindow->GetState() == CLOSED){
			haveChild = true;
		}
	}
}

void Window_Base::Update(){
	// SUSPENDED状態の判定
	switch(state){
	case SUSPENDED:
		state = IDLE;
		break;
	}
	Update_Common();
}

bool Window_Base::Update_Common(){
	switch(state){
	case CLOSED:
		// 閉じられた状態。
		// 外部から何かされない限り何も更新しない。
		break;
	case OPENING:
		// 開きつつある状態。
		// 完全に開いたところでSUSPENDEDの状態になる。
		openLevel++;
		if(openLevel >= GetOpenTime()){
			openLevel = GetOpenTime();
			state = SUSPENDED;
		}
		break;
	case CLOSING:
		// 閉じつつある状態。
		// 完全に閉じたところでCLOSEDの状態になる。
		openLevel--;
		if(openLevel <= 0){
			openLevel = 0;
			state = CLOSED;
		}
		break;
	}
	// activeCountの更新
	if(GetActive()){
		activeCount++;
	}else{
		activeCount = 0;
	}
	// countの更新
	count++;
	return GetActive();
}

void Window_Base::DrawFrame() const{
	if(pSkin == NULL || openLevel<=0){
		return;
	}
	// 自身の情報を渡して描画してもらう
	pSkin->Draw(x, y, width, height, openLevel);
}

void Window_Base::DrawContent() const{
}

bool Window_Base::GetActive() const{
	if(state == SUSPENDED) return true;
	if(state == IDLE) return true;
	if(state == UPDATING) return true;
	return false;
}

int Window_Base::GetOpenTime() const{
	return pSkin->GetOpenTime();
}

void Window_Base::SetPositionH(int pos, BYTE align){
	switch(align){
	case ALIGN_LEFT:
		x = pos;
		break;
	case ALIGN_CENTER:
		x = pos - width/2;
		break;
	case ALIGN_RIGHT:
		x = pos - width;
		break;
	}
}

void Window_Base::SetPositionV(int pos, BYTE align){
	switch(align){
	case ALIGN_LEFT:
		y = pos;
		break;
	case ALIGN_CENTER:
		y = pos - height/2;
		break;
	case ALIGN_RIGHT:
		y = pos - height;
		break;
	}
}

BYTE Window_Base::OpenChildWindow(Window_Base* _pChild){
	BYTE result;
	haveChild = false;
	if(_pChild == NULL) return WNDOPEN_FAILED;
	pChildWindow = _pChild;
	result = pChildWindow->Open();
	if(result == WNDOPEN_SUCCEED){
		haveChild = true;
	}
	return result;
}