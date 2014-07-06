// KeyConfig.cpp

#include "KeyConfig.h"
#include "Static_Game.h"

KeyConfig::KeyConfig(){
	ResetConfig();
}

bool KeyConfig::LoadKeyConfig(){
	TCHAR ini_file[MAX_PATH+1];
	TCHAR buf[256];
	TCHAR buf2[16];
	//==========================================
	// �t�@�C���̌Ăяo��

	// �t�@�C�������擾
	// ini�t�@�C������R���t�B�O����ǂݏo���B
	GetCurrentDirectory(MAX_PATH + 1 , ini_file);
	strcat_s(ini_file, MAX_PATH-strlen(ini_file)-1, "\\");
	strcat_s(ini_file, MAX_PATH-strlen(ini_file)-1, FILE_CONFIG);

	bool result = true;


	do{ // �G���[�`�F�b�N
		// �L�[�R���t�B�O�̐ݒ�
		for(int i=0; i<5 && result; i++){
			// �L�[�R���t�B�O�̎擾
			// �f�t�H���g�l��I�̓_�~�[
			sprintf_s(buf2, 16, "button%1d", i);
			GetPrivateProfileString(_T("config"), buf2,
				_T("I"), buf, sizeof(buf), ini_file);
			input[i] = KeyToInt(buf[0]);
			if(input[i] == 0){ // �G���[�����������ꍇ
				result = false;
			}
		}

		if(!result){
			ResetConfig();
		}
	}while(0);

	// �����t�@�C���ɕs�����������ꍇ�͐ݒ��ۑ����A���b�Z�[�W���o��
	if(!result){
		if(!SaveKeyConfig()) return false;
	}

	return true;
}

bool KeyConfig::SaveKeyConfig(){
	//==========================================
	// �t�@�C���̍쐬
	TCHAR ini_file[MAX_PATH+1];
	TCHAR buf[256];
	TCHAR buf2[16];

	// �t�@�C�������擾
	// ini�t�@�C������R���t�B�O����ǂݏo���B
	GetCurrentDirectory(MAX_PATH + 1 , ini_file);
	strcat_s(ini_file, MAX_PATH-strlen(ini_file)-1, "\\");
	strcat_s(ini_file, MAX_PATH-strlen(ini_file)-1, FILE_CONFIG);

	// �L�[�R���t�B�O
	strcpy_s(buf, 255, TEXT("")); // �N���A
	buf[1] = '\0'; // ��������1�����̃f�[�^������
	for(int i=0; i<5; i++){
		buf[0] = IntToKey(input[i]); // �V���b�g�{�^��
		if(buf[0] == 'I') return false;
		sprintf_s(buf2, 16, "button%1d", i);
		WritePrivateProfileString(TEXT("config"), buf2, buf, ini_file);
	}
	return true;
}

int KeyConfig::KeyToInt(TCHAR c){
	// �L�[�Ɛ���(PAD_INPUT_..)��Ή�������
	switch(c){
		case 'A':
			return (int)PAD_INPUT_A;
			break;
		case 'B':
			return (int)PAD_INPUT_B;
			break;
		case 'C':
			return (int)PAD_INPUT_C;
			break;
		case 'X':
			return (int)PAD_INPUT_X;
			break;
		case 'Y':
			return (int)PAD_INPUT_Y;
			break;
		case 'Z':
			return (int)PAD_INPUT_Z;
			break;
		case 'L':
			return (int)PAD_INPUT_L;
			break;
		case 'R':
			return (int)PAD_INPUT_R;
			break;
		case 'E':
			return (int)PAD_INPUT_START;
			break;
		case 'M':
			return (int)PAD_INPUT_M;
			break;
		case 'S':
			// ��Shift�L�[��11�Ԗڂ̃{�^���ɑΉ�
			return (int)PAD_INPUT_11;
			break;
		case 'T':
			// �EShift�L�[��12�Ԗڂ̃{�^���ɑΉ�
			return (int)PAD_INPUT_12;
			break;
		default: // �G���[
			return 0;
			break;
	}
	// �G���[
	return 0;
}

TCHAR KeyConfig::IntToKey(int n){
	switch(n){
		case PAD_INPUT_A:
			return 'A';
			break;
		case PAD_INPUT_B:
			return 'B';
			break;
		case PAD_INPUT_C:
			return 'C';
			break;
		case PAD_INPUT_X:
			return 'X';
			break;
		case PAD_INPUT_Y:
			return 'Y';
			break;
		case PAD_INPUT_Z:
			return 'Z';
			break;
		case PAD_INPUT_L:
			return 'L';
			break;
		case PAD_INPUT_R:
			return 'R';
			break;
		case PAD_INPUT_START:
			return 'E';
			break;
		case PAD_INPUT_M:
			return 'M';
			break;
		case PAD_INPUT_11:
			return 'S';
			break;
		case PAD_INPUT_12:
			return 'T';
			break;
		default:
			return 'I';
			break;
	}
	return 'I';
}

void KeyConfig::ResetConfig(){
	input[0] = DEF_INPUT_0;
	input[1] = DEF_INPUT_1;
	input[2] = DEF_INPUT_2;
	input[3] = DEF_INPUT_3;
	input[4] = DEF_INPUT_4;
}