// Window_Base.h

#include "Window_Base.h"
#include <DxLib.h>

WINDOWAREA GetWindowArea(int _x, int _y, int _w, int _h){
	WINDOWAREA area;
	area.x = _x;
	area.y = _y;
	area.w = _w;
	area.h = _h;
	return area;
}

Window_Base::Window_Base() : frameArea(), contentArea(){
	// �S�Ẵ����o�̏�����
	Initialize();
}

void Window_Base::Initialize(){
	state = CLOSED;
	openLevel = 0;
	visible = false;
	activeCount = 0;
	pSkin = NULL;
	count = 0;
	haveChild = false;
}

bool Window_Base::Setup(WindowSkin* pSkin,
	WINDOWAREA _frameArea, WINDOWAREA _contentArea,
	bool _visible){
		frameArea = _frameArea;
		contentArea = _contentArea;
		visible = _visible;
		AttachSkin(pSkin);
		haveChild = false;
		return true;
}

bool Window_Base::Setup_FixPadding(WindowSkin* _pSkin,
	WINDOWAREA _frameArea, int _px, int _py,
	bool _visible){
		AttachSkin(_pSkin);
		frameArea = _frameArea;
		SetContentSizeByMargin(_px, _py);
		visible = _visible;
		haveChild = false;
		return true;
}

bool Window_Base::Setup_FixContentWidth(WindowSkin* pSkin,
	WINDOWAREA _frameArea, int _contentWidth, int _py,
	bool _visible){
		AttachSkin(pSkin);
		frameArea = _frameArea;
		SetContentSizeByContentWidth(_contentWidth, _py);
		visible = _visible;
		haveChild = false;
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
		// ���ɊJ����Ă����Ԃ̎��͂ǂ�����Ă��J���Ȃ�
		success = false;
		result = WNDOPEN_OPENED;
		break;
	case UNKNOWN:
		result = WNDOPEN_FAILED;
		break;
	}

	if(success){
		if(sudden){
			// �J���ꂽ��Ԃɂ���
			state = SUSPENDED;
			openLevel = GetOpenTime();
			OnOpened();
		}else{
			// �J���n�߂���Ԃɂ���
			// openLevel�͂�����Ȃ�
			state = OPENING;
			OnOpened();
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
		// Close���߂𕁒ʂɎ󂯎��B��̏��
		succeed = true;
		result = WNDCLOSE_SUCCEED;
		break;
	case UNKNOWN:
		result = WNDOPEN_FAILED;
		break;
		
	}

	if(succeed){
		if(sudden){
			// �J���ꂽ��Ԃɂ���
			state = CLOSED;
			openLevel = 0;
		}else{
			// ���n�߂���Ԃɂ���
			// openLevel�͂�����Ȃ�
			state = CLOSING;
		}
	}

	return result;
}

void Window_Base::UpdateA(){
	if(!haveChild){
		Update();
	}else{
		if(pChildWindow == NULL){
			return;
		}
		// �q�E�B���h�E���J���Ă���ꍇ
		if(pChildWindow->GetState() == CLOSED && pChildWindow != NULL){
			OnChildIsClosed();
			haveChild = false;
		}
	}
}

void Window_Base::Update(){
	// SUSPENDED��Ԃ̔���
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
		// ����ꂽ��ԁB
		// �O�����牽������Ȃ����艽���X�V���Ȃ��B
		break;
	case OPENING:
		// �J�������ԁB
		// ���S�ɊJ�����Ƃ����SUSPENDED�̏�ԂɂȂ�B
		openLevel++;
		if(openLevel >= GetOpenTime()){
			openLevel = GetOpenTime();
			state = SUSPENDED;
		}
		break;
	case CLOSING:
		// �������ԁB
		// ���S�ɕ����Ƃ����CLOSED�̏�ԂɂȂ�B
		openLevel--;
		if(openLevel <= 0){
			openLevel = 0;
			state = CLOSED;
		}
		break;
	}
	// activeCount�̍X�V
	if(GetActive()){
		activeCount++;
	}else{
		activeCount = 0;
	}
	// count�̍X�V
	count++;
	return GetActive();
}

void Window_Base::DrawFrame() const{
	if(pSkin == NULL || openLevel<=0){
		return;
	}
	// ���g�̏���n���ĕ`�悵�Ă��炤
	pSkin->Draw(
		frameArea.x, frameArea.y,
		frameArea.w, frameArea.h, openLevel);
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
		frameArea.x = pos;
		break;
	case ALIGN_CENTER:
		frameArea.x = pos - frameArea.w/2;
		break;
	case ALIGN_RIGHT:
		frameArea.x = pos - frameArea.w;
		break;
	}
}

void Window_Base::SetPositionV(int pos, BYTE align){
	switch(align){
	case ALIGN_LEFT:
		frameArea.y = pos;
		break;
	case ALIGN_CENTER:
		frameArea.y = pos - frameArea.h/2;
		break;
	case ALIGN_RIGHT:
		frameArea.y = pos - frameArea.h;
		break;
	}
}

BYTE Window_Base::OpenChildWindow(Window_Base* _pChild, bool sudden){
	BYTE result;
	haveChild = false;
	if(_pChild == NULL) return WNDOPEN_FAILED;
	pChildWindow = _pChild;
	result = pChildWindow->Open(false, sudden);
	if(result == WNDOPEN_SUCCEED){
		haveChild = true;
	}
	return result;
}