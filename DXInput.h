#ifndef DXINPUT_H
#define DXINPUT_H

#include <iostream>
#include <fstream>

///////////////////////////////////////////////////
// DXInput�N���X
//
// ���͂��Ǘ�����N���X�B
// �O���[�o���ϐ�g_key�Akey2�ɂ��ꂼ��
// 1P�A2P�̃L�[���͏�Ԃ��L�^����B

#define DELAY_DIGDIR 30	// �\���L�[��1�񉟂��F��
#define DELAY_DIGDIR2 6	// �������ςȂ��̃f�B���C

// �\���L�[�̕�����int�l�ŕ\���ꍇ�B
// DX���C�u�����̒l�Ƃ͑Ή����Ă��Ȃ��B
#define DIGDIR_DOWN 2
#define DIGDIR_LEFT 4
#define DIGDIR_RIGHT 6
#define DIGDIR_UP 8

// �A�i���O���͂�臒l��ݒ肷��B
#define DEF_INPUT_MIN		30
#define DEF_INPUT_MAX		90

class DXInput{

public: 
	int key;				// �����Ă���L�[
	int pushedKey;			// �����ꂽ�L�[
	int analogX, analogY;	// �A�i���O�̏\���L�[��� 
	int digitalDir;			// �\���L�[�̕�����8�����œ����

	// �\���L�[��1�񉟂���F�����邽�߂̒l
	// ��x���͂������true�ɂȂ�A����off�ɂȂ��false�ɂȂ�B
	// �������Apushed_time�ȏ㉟��������ƈȍ~��
	// �������ςȂ��Œf���I��1�񉟂�����͂���
	bool pushed;
	int pushed_time;

	DXInput();
	void getInput(bool is2P);		// key, pushedKey�̎擾�B2P�̏ꍇ��is2P = true
};

#endif