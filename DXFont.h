#ifndef DXFONT_H
#define DXFONT_H

// �t�H���g�T�C�Y�̗�
#define FONTSIZE_INFO		24
#define FONTSIZE_STR		24
#define FONTSIZE_STR_L		32
#define FONTSIZE_TINYINFO	16
#define FONTSIZE_TALK		28

// �֐����̒Z�k
#ifndef ABBR_GETDRAWSTRINGWIDTHTOHANDLE
#define ABBR_GETDRAWSTRINGWIDTHTOHANDLE
#define GetStrWidth GetDrawStringWidthToHandle
#endif // ABBR_GETDRAWSTRINGWIDTHTOHANDLE

#ifndef ABBR_DRAWSTRINGTOHANDLE
#define ABBR_DRAWSTRINGTOHANDLE
#define DrawStr DrawStringToHandle
#endif // ABBR_DRAWSTRINGTOHANDLE

//==================================================
// DXFont�N���X
// 
// �摜�̃n���h�����܂Ƃ߂ĕێ�����O���[�o���ϐ��B
// �O���[�o���ϐ�g_image����Q�Ƃ����B
// 

class DXFont{
public:
	// �t�H���g�̃n���h����񋓂���B
	int hInfo;
	int hStr;		// �����B���O�̕`��ɂ��p����B
	int hStrL;		// �傫���T�C�Y�̕����B���O�̕`��ɂ��p����B
	int hTinyInfo;	// �퓬����HP�`��ȂǁB�����������B
	int hTalk;		// ��b���ȂǁB
public:
	// �R���X�g���N�^�B
	// �S�Ẵn���h����-1��������B
	DXFont();

	// ���[�h�B
	// ���s������false��Ԃ��B
	bool Load();

	// �t�H���g�̉���B
	// ���s������false��Ԃ��B
	bool Release();
};

#endif // DXFONT_H