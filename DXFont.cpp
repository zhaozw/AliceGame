// DXFont.cpp

#include <Windows.h>

#include "DXFont.h"
#include "DxLib.h"

DXFont::DXFont(){
	hInfo = 0;
}

bool DXFont::Load(){
	// �t�H���g��
	TCHAR	fontName[64];

	// �O���t�H���g���g�p����ꍇ�͂����œǂݍ���ł���
	// AddFontResourceEx(_T("�t�H���g��"), FR_PRIVATE, NULL);

	// �g�p����t�H���g���w�肷��
	// �Y������t�H���g�����݂��Ȃ��ꍇ�̂��߂ɗD�揇�ʏ��ɂ����������Ă���
	// �l�r �����Ƃl�r �S�V�b�N�͓��{����ł���ΕK�����݂���͂�
	TCHAR fontNames[4][64] = {
		// _T("�t�H���g��"), // �O���t�H���g���g���ꍇ
		_T("HGS���ȏ���"),
		_T("HGS����B"),
		_T("HG����B"),
		_T("�l�r ����")};

	for(int i=0; i<4; i++){
		if(EnumFontNameEx2(fontName, 1, fontNames[i]) == 1){
			strcpy_s(fontName, 63, fontNames[i]);
			break;
		}
	}

	// �t�H���g�̍쐬
	hInfo = CreateFontToHandle(fontName, FONTSIZE_INFO,
		-1, DX_FONTTYPE_ANTIALIASING, -1, -1, 0);
	hStr = CreateFontToHandle(fontName, FONTSIZE_STR,
		-1, DX_FONTTYPE_ANTIALIASING, -1, -1, 0);
	hStrL = CreateFontToHandle(fontName, FONTSIZE_STR_L,
		-1, DX_FONTTYPE_ANTIALIASING, -1, -1, 0);
	hTinyInfo = CreateFontToHandle(fontName, FONTSIZE_TINYINFO,
		-1, DX_FONTTYPE_ANTIALIASING, -1, -1, 0);

	// �t�H���g�̃��[�h
	if(hInfo == -1) return false;
	if(hStr == -1) return false;
	if(hStrL == -1) return false;
	if(hTinyInfo == -1) return false;

	/*
	if((hInfo = CreateFontToHandle(fontName, FONTSIZE_INFO,
		-1, DX_FONTTYPE_ANTIALIASING)) == -1) return false;
		*/

	return true;
}

bool DXFont::Release(){

	// �O���t�H���g���g�p�����ꍇ�͂����ŊJ������
	// RemoveFontResourceEx(_T("�t�H���g��"), FR_PRIVATE, NULL);

	return true;
}