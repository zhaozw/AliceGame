// Sound.cpp

#include "Sound.h"
#include "DxLib.h"
#include "Static_Game.h"
#include "Config.h"
#include <math.h>

// ���ʂ̐ݒ�
extern Config g_cfg;


BGM::BGM(){
	handle = -1;
	loopPos = 0;
	noLoop = false;
	playPos = 0;
}

Sound::Sound(){
	// ���ʉ��̏�����
	for(int n=0; n<MYGAME_MAX_SE; n++){
		se[n] = 0;
	}
}

bool Sound::LoadMusic(){
	// �eBGM�̓ǂݍ��݂��s���B
	if(!LoadBGM(BGM_DUMMY, _T("bgm\\dummy.ogg"), 1)) return false;
	if(!LoadBGM(BGM_MENU, _T("bgm\\Menu.ogg"), 1)) return false;
	if(!LoadBGM(BGM_BATTLE, _T("bgm\\Battle.ogg"), 1)) return false;
	return true;
}

bool Sound::LoadSound(){
	// �eSE�̓ǂݍ��݂��s���B
	se[MYSE_DUMMY] = LoadSoundMem(TEXT("se\\dummy.ogg"));
	se[MYSE_CALL_DOLLCOMMAND] = LoadSoundMem(TEXT("se\\call_dollcommand.ogg"));
	se[MYSE_MESSAGE_NEWPAGE] = LoadSoundMem(TEXT("se\\message_newpage.ogg"));
	se[MYSE_CALL_ENEMYACTION] = LoadSoundMem(TEXT("se\\call_enemyaction.ogg"));


	for(int n=0; n<MYGAME_MAX_SE; n++){
		if(se[n] == -1){
			return false;
		}
	}
	return true;
}

bool Sound::LoadBGM(WORD id, LPTSTR fileName, int loopPos, bool noLoop){
	if((bgm[id].handle =
		LoadSoundMem(fileName)) == -1){
#ifdef MYGAME_USE_CRT_LOG
			_RPTF1(_CRT_WARN, "%s�̓ǂݍ��݂Ɏ��s���܂����B\n", fileName);
#endif // MYGAME_USE_CRT_LOG
			return false;
	}
	bgm[id].loopPos = loopPos;
	bgm[id].noLoop = noLoop;
	if(loopPos < 0) bgm[id].noLoop = true;	
	return true;
}

bool Sound::PlayBGM(WORD bgmID, bool recall){
	if(bgmID >= MYGAME_MAX_BGM) return false;
	// �J��Ԃ��ʒu�̊��蓖��
	SetLoopPosSoundMem(bgm[bgmID].loopPos, bgm[bgmID].handle);
	return CallMusic(bgm[bgmID].handle, recall, bgm[bgmID].noLoop);
}

void Sound::StopBGM(WORD bgmID){
	if(CheckSoundMem(bgm[bgmID].handle)){
		StopSoundMem(bgm[bgmID].handle);
	}
}

void Sound::StopAllBGM(){
	for(WORD i=0; i<MYGAME_MAX_BGM; i++){
		StopBGM(i);
	}
}

void Sound::SetVolumeBGM(WORD bgmID,int param){
	if(param == 0) return;
	int volume = 255*param/MAX_VOLUME;
	if(CheckSoundMem(bgm[bgmID].handle)){
		SetVolumeSoundMem(CalcDB(volume), bgm[bgmID].handle);
	}
}

bool Sound::PlaySE(WORD seID, float volRate, bool reCall, bool stop){
	if(g_cfg.SE == 0) return false;
	if(seID >= MYGAME_MAX_SE) return false;
	return CallSound(se[seID], volRate, reCall, stop);
}


bool CallMusic(int hMsc, bool reset, bool noLoop){
	if(g_cfg.BGM == 0) return true;
	int volume = 255*g_cfg.BGM/(MAX_VOLUME-1);
	SetVolumeSoundMem(CalcDB(volume), hMsc);
	if(CheckSoundMem(hMsc)){
		if(reset){
			StopSoundMem(hMsc);
		}else{
			return true;
		}
	}
	PlaySoundMem(hMsc, noLoop?DX_PLAYTYPE_LOOP:DX_PLAYTYPE_BACK);
	return true;
}


bool CallSound(int hSnd, float volRate, bool reCall, bool stop){
	if(g_cfg.SE == 0) return true;
	int volume = volRate*255*g_cfg.SE/MAX_VOLUME;
	// stop���w�肵���ꍇ�͉��t���~�߂�
	if(stop) StopSoundMem(hSnd);
	// !reCall(���ɖ��Ă��鎞�͖炳�Ȃ�)����
	// ���ݖ��Ă���ꍇ�͖炳�Ȃ�
	if(!reCall && CheckSoundMem(hSnd)) return true;
	// �{�����[���̐ݒ�
	SetVolumeSoundMem(CalcDB(volume), hSnd);
	PlaySoundMem(hSnd, DX_PLAYTYPE_BACK);
	return true;
}

long CalcDB(int sound_val){ 
	int par;
	par = 100 * sound_val / 255;
	return ( par == 0 ) ? 0 : ( (int)( log10f( (float)par ) * 5000.0f ) );
}
