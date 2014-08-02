#ifndef SELECTABLE2D_H
#define SELECTABLE2D_H

#include "DxLib.h"
#include "DXInput.h"
#include "Config.h"

#define SELECTABLE2D_MAX 128

#define SELECT2D_CHOOSE 1
#define SELECT2D_CANCEL 2
#define SELECT2D_NONE 0

#ifndef SELECTRESULT_CANCELED
#define SELECTRESULT_CANCELED	-1
#endif // SELECTRESULT_CANCELED

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
	
	// ���e�̃N���A�B
	// isActive�l�����ׂ�true�ɂ���B
	void Reset(){
		for(int n=0; n<SELECTABLE2D_MAX; n++){
			isActive[n] = true;
		}
		index = lastIndex = 0;
	}
		
	// ���E�̒[���Ȃ����Ă����true�B
	bool canHWrap;
	// �㉺�̒[���q�����Ă����true
	bool canVWrap; 
	// �I��s�\�̍��ڂɃJ�[�\�������킹�邱�Ƃ��o���邩
	// (�I���o���邩�ǂ����͕ʁB���̂�����̋@�\�͌��X���̃N���X�Ɋ܂܂�Ȃ�)�B
	bool canChooseInactive;

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

	// ���݂̑I�������L���ł��邩�ǂ�����Ԃ��B
	bool IsInactive() const{ return !isActive[index]; };
};


#endif // SELECTABLE_H