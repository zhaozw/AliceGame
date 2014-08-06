#ifndef WINDOW_HINTMESSAGE_H
#define WINDOW_HINTMESSAGE_H

#include "Window_Message.h"
#include <tchar.h>
#include <streambuf>

// �q���g���b�Z�[�W��\������N���X�B
// ����̏����ŏ����ꂽ�t�@�C����ǂݍ��݁A�\������B
// ��{�I�Ȏg�����Ƃ��āA�Q�[����ʂ̍őO�ʂɕ\������A
// ���ꂪ�\������Ă���Ԃ͑��̃E�B���h�E��R�}���h�ւ̓��͎͂󂯕t�����A
// �S�Ẵ��b�Z�[�W��\�������Ƃ���œ��e�����B
// CsvReader�N���X�̂悤�ɁA�t�@�C���|�C���^�ƃt�@�C���ʒu��ێ����Ă���B
// �P�Ƃ̋@�\�Ƃ��ĈÍ�������������i�\��j�B
//
// �֐�OpenAndPlay���s���ƁA�E�B���h�E���J���A�t�@�C���̒��g��ǂݍ����
// �E�B���h�E�ɕ\�����A����{�^���ɂ��y�[�W������s���Ȃ���
// �t�@�C���̒��g�����X�Ɠǂ�ł����A
// �I�[�܂ōs���ƕ���B
// ��{�I�ɂ��̃N���X�𗘗p���鎞�͂��̊֐��𗘗p����B
// 
// �@�t�@�C�����J��
// OpenAndPlay�֐����s���ƁA�܂��t�@�C�������邩�ǂ������m�F���A�E�B���h�E���J���B
// ���s�����炱�̎��_��false��Ԃ��B
// ����ȍ~�AWindow��state�l�͕����鎞�܂�WNDSTATE_UPDATE�̂܂܁B
// 
// �A�t�@�C���̒��g��ǂݍ���
// �t�@�C����擪�����s���ǂ�ł����B
// �ǂ񂾍s�̒��g��buffer�ɃZ�b�g����Ă����B
// �t�@�C���̒��g���Í������ꂽ���̂ł���΁A���̎��A�s�P�ʂŕ������s���B
//
// �B�y�[�W����܂ŒB������AWindow_Message��stockMessage�ɓ��e�𑗂�
// �t�@�C������#newline�Ə����ƁA������y�[�W����̍��}�Ƃ݂Ȃ��B
// ����ȊO�ɂ��A#���擪�ɂ���s�̏ꍇ�A
// �ŏ��̒P��𖽗߂̎�ށA����ȍ~���X�y�[�X��؂�̃p�����[�^�Ƃ���
// ����ȍs�Ɣ��f���ď������s���B
// �m�x���Q�[���̃X�N���v�^�̂������ȒP�ȃo�[�W�����B
// 
// �C�t�@�C���̏I�[�ɒB������A���̎��_�ł̓��e��stockMessage�ɑ���A
// ���̃��b�Z�[�W�̏������I��������_�Ńt�@�C�������B
// �t�@�C���̏I�[��#exit�ŕ\������B
// �܂��Aifstream�̃t�@�C�����[�̌��m�ɂ���Ă����l�̏������s���B

class Window_HintMessage : public Window_Message{
protected:
	TCHAR fileName[MAX_PATH];	// �t�@�C���̖��O
	std::streamoff filePos;		// ���x���J����������肷��֌W��
								// �t�@�C���̈ʒu��ێ����Ă���
								// ���̃N���X���g��ifstream��ێ������A
								// �s��ǂݍ��ނ��тɊ֐����Ő錾���Ďg�p����
	int			lineCount;		// ���ݓǂݍ��񂾍s��
	TCHAR		buffer[WND_MSG_STOCKLINE][WND_MSG_STOCKLENGTH];	
								// ���ݓǂݍ���ł���f�[�^�B
								// Window_Message�Ŏg�p����T�C�Y�����m�ۂ��Ă���B
								// (�o�b�t�@�̒��g����x�ɃE�B���h�E�ɑ������肷�鎞�p)
	int			linePos;		// ���݁Abuffer�̉��s�ڂ܂Ńf�[�^�������Ă��邩
								// (���ɓǂݍ��ވʒu�̃C���f�b�N�X)

public:
	// �R���X�g���N�^
	Window_HintMessage();
	// ���e�̃��Z�b�g
	void Clear();

	// �t�@�C����ǂݍ��݁A���̒��g��
	// ���b�Z�[�W�Ƃ��ĕ\�����A�I���ƕ���֐��B
	// �S�����̊֐������ł����񂶂�Ȃ����ȁB
	bool OpenAndPlay(LPTSTR fileName, WORD wndType);

	// �t�@�C�������w�肷��
	// �����Ƀt�@�C�����J���Ă݂āA�J���Ȃ�������false��Ԃ�
	bool SetFileName(LPTSTR name);

	// �t�@�C���̒��g����s�ǂݍ��ށB
	bool ReadLine();

	// ���݂�buffer�̓��e��stockLine�ɓ]������B
	bool FlushBuffer();

	// �A�N�Z�T
	int GetLineCount(){ return lineCount; };
};


#endif // WINDOW_HINTMESSAGE_H
