#ifndef SELECTABLE_H
#define SELECTABLE_H

#include "DxLib.h"
#include "DXInput.h"
#include "Config.h"

#define SELECTABLE_MAX 64

#define SELECT_CHOOSE 1
#define SELECT_CANCEL 2
#define SELECT_NONE 0
#define SELECTRESULT_CANCELED	-1

class Selectable{
public:
	int index;
	int maxSize;

	// ���ꂼ��̑I�������I���\��
	bool isActive[SELECTABLE_MAX];

	// �I�����̈ړ�
	// ����L�[�������ꂽ�ꍇ��1,
	// �L�����Z���L�[�������ꂽ�ꍇ��2,
	// ����ȊO��0��Ԃ��B
	// hSnd : �ړ����ɖ炷���̃n���h���B
	int Move(int hSnd = 0);
	
	// �㉺�őI������^�C�v�Ȃ�true,
	// ���E�őI������^�C�v�Ȃ�false�B
	bool isVirtical;
	
	// ��Ɖ����Ȃ����Ă����true�B
	bool canWrap;

	// ���͂��玟�̓��͉\�܂ł̎��ԁB
	// �f�t�H���g�ł�0�B
	int choiceWait;
	int choiceDelay;	// ���݂̑҂����ԁB

	// �ړ��O�̃C���f�b�N�X�B
	int lastIndex;

	// ���݂̈ʒu�ɂƂǂ܂��Ă��鎞�ԁB
	int stayCount;

	// ���ڍׂȎw��B
	// �ő吔�A�����ʒu�A�����A���b�v�\�����w�肷��B
	Selectable(int m, int ini=0, bool v=true, bool w=true, int c=0);

	// �f�t�H���g�R���X�g���N�^
	Selectable();
};


#endif // SELECTABLE_H