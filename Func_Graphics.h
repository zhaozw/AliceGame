#ifndef FUNC_GRAPHICS_H
#define FUNC_GRAPHICS_H

#include <Windows.h>
#include <DxLib.h>

struct MYCOLOR3{
	MYCOLOR3(int r, int g, int b){
		R = r;
		G = g;
		B = b;
	}
	int R;
	int G;
	int B;
};


// int�^�̔z���n���Ǝw�肵���ʒu�ɐ��l�̕`����s���B
// �߂�l : �`�悵�����B
int const DrawIntArray(int x, int y, int* image, int* nArray, int num, int wid,
	BYTE align=2, bool useComme=true, bool zerofill=false, float rate=1.0f);

// ���_��`�悷��B
void const DrawScore(int score, int score8dig, int x, int y, int* image,
	int wid, BYTE align=2, bool zerofill=false, bool useComme=true,
	int dig=10, float rate=1.0f);

// ������`�悷��B
void const DrawNum(int num, int x, int y, int* image,
	int wid, int dig, 
	BYTE align=2, bool zerofill=false, bool useComme=true,
	float rate=1.0f);

// A�`Z�̕��т����摜��p���āADX���C�u�����ŉ摜��`�悷��B
// �̈�̃`�F�b�N�Ȃǂ͍s��Ȃ����߁A�v���ӁB
void DrawStr(LPTSTR text, int x, int y, int wid, int* image);

// �ǂݍ��񂾃t�H���g��p���āA�O���f�[�V�����t���̕�����`�悷��B
// �����ŕ`��͈͂��w�肵�������`��𕡐���s�����Ƃɂ���������B
// ��G�c�ȃO���f�[�V�����Ȃ̂Ŏg�p���͔�������v����B
// �܂��A�g�p���SetDrawArea�������ɂȂ�B
// (�S�̂ɕ`�悷��悤�ɂȂ�)�B
// ���̂��߁A
void DrawGradStrToHandle(const TCHAR* text, int hFont, int x, int y, int size, 
						 MYCOLOR3* upColor, MYCOLOR3* btmColor, int step,
						 int wndWid=800, int wndHei=600, int edgeColor=0);

// ���F�֐��̂�����F�B
// ���F�֐�����Ăяo�����B
int GetRainbow(int i);
int GetRainbowR(int i);
int GetRainbowG(int i);
int GetRainbowB(int i);
#define RAINBOW_PARAM_CYCLE 1536

// ���F�֐�
// �w�肵���l�ɂ���ē��F�ɕω�����F��Ԃ��B
int GetRainbowColor(int i);

// �摜��[����t�F�[�h������B
// hImg �摜�̃n���h��
// x, y �`��̍���̈ʒu�B
// width, height �摜�̕��ƍ����B
// grad �s�N�Z��������̓����x�̕ω��B
// zeropoint �����x��0�ɂȂ�_�B
// horizon �������Ƀt�F�[�h���A�c�����Ƀt�F�[�h���B
// reverse �ʏ�͍����E�㑤�������������Areverse��true���ƉE���E�������������ɂȂ�B
// blendmode �摜�̍������[�h�B
void DrawFadeGraph(int hImg, int x, int y, int width, int height,
					float grad, int zeropoint, int blendmode,
					bool horizon=true, bool reverse=false);

// �摜��g��ɕ`�悷��B
// count �g��������p�̃J�E���g�B�ʏ�existTime���g�p�B
// hImg �摜�̃n���h���B
// x, y �`��̍���̈ʒu�B
// height �摜�̍����B
// width �摜�̕��B
// span �摜�̗h�ꕝ�B
// speed �摜���h��鑬�x�B
// pitch �摜�̔g������B
void DrawWaveGraph(int count, int hImg, int x, int y, int height, int width,
				   float span, float speed, float pitch);

// �摜�𗬂��悤�Ƀt�F�[�h�C��������B
// �摜�����������ɐ؂蕪���A����ʒu����܂��͉��ɂ��镔����
// �������x�������ɂ���B
// hImg : �摜�̃n���h��
// x, y : �摜�̊�ʒu
// borderY : �摜�̕ό`���n�܂�摜�̈ʒu�B
//			 0���Ɗ��S�ɕό`���Ȃ��Awid���ƑS�Ă̗̈�ɂ��ĕό`����B
// wid, hei : �摜�̃T�C�Y
// fromTop : �摜���ォ��i�ցj�t�F�[�h���邩�B
// deltaGrad : �摜�̕ό`�Ɏg�p����W���B
// alphaGrad : �摜�̓����x�̌W���B
// alphaBase : �摜�̓����x�̊�{�l�B
void DrawFlowGraph(int hImg, int x, int y, int borderY, int wid, int hei,
					 bool fromTop, float deltaGrad, float alphaGrad, int blendMode, float alphaBase=1.0f);

// ������𒆉������������ꍇ�́A
// ���ォ�炸�炷�ׂ�x�ψʂ����߂�B
// str		: �����������镶����
// strLen	: ������̒���
// hFont	: �t�H���g�n���h��
// width	: ����������̈�̕�
int GetRightAlignDX(LPTSTR str, int strLen, int hFont, int width);
int	GetCenteringDX(LPTSTR str, int strLen, int hFont, int width);



#endif // FUNC_GRAPHICS_H