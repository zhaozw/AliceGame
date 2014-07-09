#ifndef SELECTABLE2D_H
#define SELECTABLE2D_H

#include "DxLib.h"
#include "DXInput.h"
#include "Config.h"

#define SELECTABLE2D_MAX 128

#define SELECT2D_CHOOSE 1
#define SELECT2D_CANCEL 2
#define SELECT2D_NONE 0

class Selectable2D{
public:
	// ���݂̃C���f�b�N�X�B
	int index;
	// �ړ��O�̃C���f�b�N�X�B
	int lastIndex;
	int column;		// ��
	int row;		// �s��

	// ���ꂼ��̑I�������I���\��
	bool isActive[SELECTABLE2D_MAX];

	// �I�����̈ړ�
	// ����L�[�������ꂽ�ꍇ��1,
	// �L�����Z���L�[�������ꂽ�ꍇ��2,
	// ����ȊO��0��Ԃ��B
	// hSnd : �ړ����ɖ炷���̃n���h���B
	int Move(int hSnd = 0);
	int CheckKey(int hSnd = 0);
		
	// ���E�̒[���Ȃ����Ă����true�B
	bool canHWrap;
	// �㉺�̒[���q�����Ă����true
	bool canVWrap; 

	// ���͂��玟�̓��͉\�܂ł̎��ԁB
	// �f�t�H���g�ł�0�B
	int choiceWait;
	int choiceDelay;	// ���݂̑҂����ԁB


	// ���݂̈ʒu�ɂƂǂ܂��Ă��鎞�ԁB
	int stayCount;

	// ���ڍׂȎw��B
	// �ő吔�A�����ʒu�A�����A���b�v�\�����w�肷��B
	Selectable2D(int _column, int _row, int _iniRow=0, int _iniCol=0, 
		bool hWrap=true, bool vWrap=true, int c=0);

	// ���݂̃C���f�b�N�X����s���E�񐔂��擾�B
	int GetRow(int _index) const{ return _index/column; };
	int GetColumn(int _index) const{ return _index%column; };
	
	// �c�̈ʒu�E���̈ʒu����C���f�b�N�X���擾�B
	int GetIndex(int _col, int _row){ return _row*column+_col; };
};


#endif // SELECTABLE_H