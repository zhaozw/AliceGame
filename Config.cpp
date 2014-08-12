// Config.cpp

#include "Config.h"
#include "Static_Game.h"
#include <DxLib.h>

Config::Config(){
		fullScreen = false; // �t���X�N���[��OFF
		skipFrame = false;

		SE		= DEF_VOLUME_SE; // ���ʉ� 100%
		BGM		= DEF_VOLUME_BGM; // BGM 80%

		windowSize = DEF_WNDSIZE;		// �f�t�H���g�̃E�B���h�E�T�C�Y
		screenType = DEF_SCREENTYPE;	// ����m�F����

		windowWidth = DEF_WND_WIDTH;
		windowHeight = DEF_WND_HEIGHT;
		screenWidth = DEF_SCRN_WIDTH;
		screenHeight = DEF_SCRN_HEIGHT;
}

bool Config::SetScreenMode(){
	// �E�B���h�E�T�C�Y��ύX����Ƌ��ɁA�ύX�ɐ��������E�B���h�E�̃T�C�Y���擾����
	// �t���X�N���[���̏ꍇ�A���������l��windowWidth, windowHeight�ɑ������B
	if(!fullScreen){
		if(SetGraphMode(windowWidth, windowHeight, 32) != DX_CHANGESCREEN_OK){	// ��ʃT�C�Y�̕ύX
			if(SetGraphMode(640, 480, 32) != DX_CHANGESCREEN_OK){	// ��ʃT�C�Y�̕ύX
				if(SetGraphMode(windowWidth, windowHeight, 16) != DX_CHANGESCREEN_OK){
					if(SetGraphMode(640, 480, 16) != DX_CHANGESCREEN_OK){
						if(SetGraphMode(windowWidth, windowHeight, 8) != DX_CHANGESCREEN_OK){
							if(SetGraphMode(640, 480, 8) != DX_CHANGESCREEN_OK){
								return false;
							}else{
								windowWidth = 640;
								windowHeight = 480;
							}
						}
					}else{
						windowWidth = 640;
						windowHeight = 480;
					}
				}
			}else{
				windowWidth = 640;
				windowHeight = 480;
			}
		}
	}else{
		if(SetGraphMode(screenWidth, screenHeight, 32) != DX_CHANGESCREEN_OK){	// ��ʃT�C�Y�̕ύX
			if(SetGraphMode(screenWidth, screenHeight, 16) != DX_CHANGESCREEN_OK){
				if(SetGraphMode(screenWidth, screenHeight, 8) != DX_CHANGESCREEN_OK) return false;
			}
		}
		windowWidth = screenWidth;
		windowHeight = screenHeight;
	}

	// �X�N���[�����[�h�̕ύX
	if(ChangeWindowMode(!fullScreen) != DX_CHANGESCREEN_OK){
		MessageBox(NULL, 
			TEXT("�E�B���h�E���[�h�̕ύX�Ɏ��s���܂����B\n�𑜓x��F�����Ή����Ă��Ȃ��\��������܂��B"),
			TEXT(""), MB_OK);
	}
	return true;
}

bool Config::LoadConfig(){
	TCHAR ini_file[MAX_PATH+1];
	TCHAR buf[256];
	int bufInt;
	//==========================================
	// �t�@�C���̌Ăяo��

	// �t�@�C�������擾
	// ini�t�@�C������R���t�B�O����ǂݏo���B
	GetCurrentDirectory(MAX_PATH + 1 , ini_file);
	strcat_s(ini_file, MAX_PATH-strlen(ini_file)-1, "\\");
	strcat_s(ini_file, MAX_PATH-strlen(ini_file)-1, FILE_CONFIG);

	bool result = false;
	bool kresult = true;

	do{ // �G���[�`�F�b�N
		// �E�B���h�E�T�C�Y���擾
		GetPrivateProfileString(TEXT("config"), TEXT("windowSize"),
			TEXT("-1"), buf, sizeof(buf), ini_file);
		bufInt = atoi(buf);
		if(bufInt <= -1 || bufInt >= 5){
			windowSize = 3;
			break;
		}
		windowSize = bufInt;

		// �E�B���h�E���[�h���擾
		GetPrivateProfileString(TEXT("config"), TEXT("screenType"),
			TEXT("-1"), buf, sizeof(buf), ini_file);
		bufInt = atoi(buf);
		if(bufInt <= -1 || bufInt >= 3){
			screenType = 0;
			break;
		}
		screenType = bufInt;

		// SE�̉���
		GetPrivateProfileString(TEXT("config"), TEXT("SE"),
			TEXT("Error"), buf, sizeof(buf), ini_file);
		bufInt = atoi(buf);
		if(bufInt <= 0 || bufInt >= MAX_VOLUME){
			SE = DEF_VOLUME_SE;
			break;
		}else{
			SE = bufInt;
		}

		// BGM�̉���
		// �G���[�̏ꍇ�͖炷
		GetPrivateProfileString(TEXT("config"), TEXT("BGM"),
			TEXT("Error"), buf, sizeof(buf), ini_file);
		bufInt = atoi(buf);
		if(bufInt <= 0 || bufInt >= MAX_VOLUME){
			SE = DEF_VOLUME_BGM;
			break;
		}else{
			SE = bufInt;
		}
		result = true; // �G���[�Ȃ������܂ŗ����ꍇ


	}while(0);

	// �t���X�N���[�����ǂ����̔���
	int iMsg;
	switch(screenType){
		case 0: // �I��
			iMsg = MessageBox(NULL, 
			"�t���X�N���[���ŋN�����܂����H", "�N���I�v�V����",
			MB_YESNO | MB_ICONQUESTION);
			fullScreen = (iMsg == IDYES);
			break;
		case 1: // �t���X�N���[��
			fullScreen = true;
			break;
		case 2: // �E�B���h�E
			fullScreen = false;
			break;
	}

	// �����t�@�C���ɕs�����������ꍇ�͐ݒ��ۑ����A���b�Z�[�W���o��
	if(!result){
		if(!SaveConfig()) return false;
#ifdef MYGAME_CALL_DIALOG_OPTION
		MessageBox(NULL, "�ݒ�̓I�v�V��������ύX�ł��܂��B", "�N���I�v�V����", MB_OK);
#endif // MYGAME_CALL_DIALOG_OPTION
	}

	// �E�B���h�E�T�C�Y�̐ݒ�
	SetWindowSize();

	return true;
}

void Config::SetWindowSize(){
	// �E�B���h�E�T�C�Y�����Z
	switch(windowSize){
		case 0:
			windowWidth = WNDSIZE_W0;
			windowHeight = WNDSIZE_H0;
			break;
		case 1:
			windowWidth = WNDSIZE_W1;
			windowHeight = WNDSIZE_H1;
			break;
		case 2:
			windowWidth = WNDSIZE_W2;
			windowHeight = WNDSIZE_H2;
			break;
		case 3:
			windowWidth = WNDSIZE_W3;
			windowHeight = WNDSIZE_H3;
			break;
		case 4:
			windowWidth = WNDSIZE_W4;
			windowHeight = WNDSIZE_H4;
			break;
	}
}

bool Config::SaveConfig(){
	//==========================================
	// �t�@�C���̍쐬
	TCHAR ini_file[MAX_PATH+1];
	TCHAR buf[256];

	// �t�@�C�������擾
	// ini�t�@�C������R���t�B�O����ǂݏo���B
	GetCurrentDirectory(MAX_PATH + 1 , ini_file);
	strcat_s(ini_file, MAX_PATH-strlen(ini_file)-1, "\\");
	strcat_s(ini_file, MAX_PATH-strlen(ini_file)-1, FILE_CONFIG);

	// �E�B���h�E�T�C�Y
	wsprintf(buf, "%d", windowSize);
	WritePrivateProfileString(TEXT("config"), TEXT("windowSize"), buf, ini_file);
	// �E�B���h�E�^�C�v
	wsprintf(buf, "%d", screenType);
	WritePrivateProfileString(TEXT("config"), TEXT("screenType"), buf, ini_file);
	// ���ʉ�
	wsprintf(buf, "%d", SE);
	WritePrivateProfileString(TEXT("config"), TEXT("SE"), buf, ini_file);
	// BGM
	wsprintf(buf, "%d", BGM);
	WritePrivateProfileString(TEXT("config"), TEXT("BGM"), buf, ini_file);

	return true;
}
