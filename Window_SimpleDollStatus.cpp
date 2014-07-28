// Window_SimpleDollStatus.cpp

#include "Window_SimpleDollStatus.h"
#include "Game_BattleDoll.h"
#include "Game_AliceDoll.h"

Window_SimpleDollStatus::Window_SimpleDollStatus() : Window_Info(){
	pBattleDoll = NULL;
	pCampDoll = NULL;
}

void Window_SimpleDollStatus::OpenWithBattleDoll(Game_BattleDoll* _pDoll){
	pBattleDoll = _pDoll;
}

void Window_SimpleDollStatus::OpenWithCampDoll(Game_AliceDoll* _pDoll){
	pCampDoll = _pDoll;
}

bool Window_SimpleDollStatus::ChangeRefBattleDoll(Game_BattleDoll* _pDoll){
	if (pBattleDoll != _pDoll){
		pBattleDoll = _pDoll;
		ContentChanged();
		return true;
	}
	return false;
}

bool Window_SimpleDollStatus::ChangeRefCampDoll(Game_AliceDoll* _pDoll){
	if (pCampDoll != _pDoll){
		pCampDoll = _pDoll;
		ContentChanged();
		return true;
	}
	return false;
}

void Window_SimpleDollStatus::Update(){
	Window_Info::Update();
}

void Window_SimpleDollStatus::DrawContent() const{
	if (isBattle){
		DrawContent_Battle();
	}else{
		DrawContent_Camp();
	}

}

void Window_SimpleDollStatus::DrawContent_Battle() const{


}

void Window_SimpleDollStatus::DrawContent_Camp() const{
}