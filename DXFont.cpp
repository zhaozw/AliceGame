// DXFont.cpp

#include <Windows.h>

#include "DXFont.h"
#include "DxLib.h"

DXFont::DXFont(){
	hInfo = 0;
	hStr = 0;
	hStrL = 0;
	hTinyInfo = 0;
}

bool DXFont::Load(){
	// �t�H���g��
	TCHAR	fontName[64];
	TCHAR	fontNamePop[64];

	// �O���t�H���g���g�p����ꍇ�͂����œǂݍ���ł���
	// AddFontResourceEx(_T("�t�H���g��"), FR_PRIVATE, NULL);

	// �g�p����t�H���g���w�肷��
	// �Y������t�H���g�����݂��Ȃ��ꍇ�̂��߂ɗD�揇�ʏ��ɂ����������Ă���
	// �l�r �����Ƃl�r �S�V�b�N�͓��{����ł���ΕK�����݂���͂�
	TCHAR fontNames[4][64] = {
		// _T("�t�H���g��"), // �O���t�H���g���g���ꍇ
		_T("HG�޼��M"),
		_T("HGS�޼��M"),
		_T("���C���I"),
		_T("�l�r �S�V�b�N")};
	for(int i=0; i<4; i++){
		if(EnumFontNameEx2(fontName, 1, fontNames[i]) == 1){
			strcpy_s(fontName, 63, fontNames[i]);
			break;
		}
	}
	// �|�b�v�ȃt�H���g���g�p����ꍇ
	TCHAR fontNamesPop[4][64] = {
		// _T("�t�H���g��"), // �O���t�H���g���g���ꍇ
		_T("HG�n�p�p�߯�ߑ�"),
		_T("HG�ۺ޼��M-PRO"),
		_T("���C���I"),
		_T("�l�r �S�V�b�N"),
	};
	for(int i=0; i<4; i++){
		if(EnumFontNameEx2(fontNamePop, 1, fontNamesPop[i]) == 1){
			strcpy_s(fontNamePop, 63, fontNamesPop[i]);
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
	hTalk = CreateFontToHandle(fontNamePop, FONTSIZE_TALK,
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