#ifndef KEYCONFIG_H
#define KEYCONFIG_H

// �f�t�H���g�̃L�[�����w��
#include <DxLib.h>

// �萔
#define MAX_BUTTON			5
// �f�t�H���g�̃L�[�z�u
#define DEF_INPUT_0		(PAD_INPUT_A) // �V���b�g�{�^��
#define DEF_INPUT_1		(PAD_INPUT_B) // �ᑬ�{�^��
#define DEF_INPUT_2		(PAD_INPUT_C) // �{���{�^��
#define DEF_INPUT_3		(PAD_INPUT_X) // Ex�V���b�g�{�^��
#define DEF_INPUT_4		(PAD_INPUT_START) // �ꎞ��~�{�^��

//=========================================
// KeyConfig�N���X
// �{�^������Ɋւ���R���t�B�O�̕����v�f�B

class KeyConfig{
public:
	int		input[MAX_BUTTON];		// �L�[���蓖�āB
									// 0: �V���b�g�A����
									// 1: �ᑬ�ړ�
									// 2: �{���A�L�����Z��
									// 3: �`�F���W�{�^��
									// 4: �ꎞ��~

	// �R���X�g���N�^
	KeyConfig();

	// �l��ǂݍ���
	bool LoadKeyConfig();

	// �l��ۑ�����
	bool SaveKeyConfig();

	// �L�[���Ɛ����l�̐؂�ւ�
	int KeyToInt(TCHAR i);
	TCHAR IntToKey(int i);

	// �L�[�ݒ�������ɖ߂��B
	void ResetConfig();
};

#endif // KEYCONFIG_H