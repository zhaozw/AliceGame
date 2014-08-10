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
// �t�@�C������#newpage�Ə����ƁA������y�[�W����̍��}�Ƃ݂Ȃ��B
// ����ȊO�ɂ��A#���擪�ɂ���s�̏ꍇ�A
// �ŏ��̒P��𖽗߂̎�ށA����ȍ~���X�y�[�X��؂�̃p�����[�^�Ƃ���
// ����ȍs�Ɣ��f���ď������s���B
// �m�x���Q�[���̃X�N���v�^�̂������ȒP�ȃo�[�W�����B
// 
// �C�t�@�C���̏I�[�ɒB������A���̎��_�ł̓��e��stockMessage�ɑ���A
// ���̃��b�Z�[�W�̏������I��������_�Ńt�@�C�������B
// �t�@�C���̏I�[��#exit�ŕ\������B
// �܂��Aifstream�̃t�@�C�����[�̌��m�ɂ���Ă����l�̏������s���B


// typeID�̒l
#define WND_HINT_TYPE_UNDIFINED			0		// SetupByTypeID�����s�����O
#define WND_HINT_SHANGHAI				1		// �V�����n�C�l�`�̃q���g
#define WND_HINT_ALICE					2		// �A���X�̃q���g

// NewPage�̖߂�l
#define WND_HINT_NEWPAGE_OK				0		// ���ɓǂݍ��ޕ��͂�������A
												// �ǂݍ��݂ɐ��������B
#define WND_HINT_NEWPAGE_OVERFLOW		1		// ���͓͂ǂݍ��񂾂��A
												// �y�[�W��؂肪�����炸
												// �K���Ȉʒu�ŋ�؂����B
#define WND_HINT_NEWPAGE_END			2		// ���̖͂��[�ɒB�����B
#define WND_HINT_NEWPAGE_ERROR			3		// �ǂݍ��ݎ��ɃG���[�����������B

// CheckCommand�̖߂�l
#define WND_HINT_CHKCMD_NONE			0		// �R�}���h�ł͂Ȃ�
												// (���ʂɓ��e���R�s�[����)
#define WND_HINT_CHKCMD_ERROR			1		// �Ȃ񂩂�������
#define	WND_HINT_CHKCMD_NEWPAGE			10		// �y�[�W�̖��[
#define WND_HINT_CHKCMD_END				11		// ���e�̖��[

class Window_HintMessage : public Window_Message{
protected:
	WORD		typeID;			// �E�B���h�E�̑傫���A�w�i�A�t�H���g�Ȃ�
								// ��ʂ�̏���^���邽�߂�ID�ԍ��B
								// SetupByTypeID�Ŏw�肵���l����������B
	TCHAR fileName[MAX_PATH];	// �t�@�C���̖��O
	std::streamoff filePos;		// ���x���J����������肷��֌W��
								// �t�@�C���̈ʒu��ێ����Ă���
								// ���̃N���X���g��ifstream��ێ������A
								// �s��ǂݍ��ނ��тɊ֐����Ő錾���Ďg�p����
	int			lineCount;		// ���ݓǂݍ��񂾍s��
	TCHAR		buffer[WND_MSG_DRAWLINE][WND_MSG_STOCKLENGTH];	
								// ���ݓǂݍ���ł���f�[�^�B
								// Window_Message�Ŏg�p����T�C�Y�����m�ۂ��Ă���B
								// (�o�b�t�@�̒��g����x�ɃE�B���h�E�ɑ������肷�鎞�p)
								// �`��ɂ�����1�y�[�W�����ő�ŃX�g�b�N���邽�߁A
								// �o�b�t�@�̑傫���͕`��s���~�X�g�b�N�����ƂȂ�B
	bool		isError;		// �����̓ǂݍ��݂ŃG���[���������Ă����ԁB
	bool		isTerminated;	// �����̍Ō�܂œǂݍ��ݏI���A
								// ���݂̕���\�����I�����������ԁB

public:
	// �R���X�g���N�^
	Window_HintMessage();
	// ���e�̃��Z�b�g
	void Clear();

	// �o�b�t�@�̃��Z�b�g
	void ClearBuffer();


	// �t�@�C����ǂݍ��݁A���̒��g��
	// ���b�Z�[�W�Ƃ��ĕ\�����A�I���ƕ���֐��B
	// �S�����̊֐������ł����񂶂�Ȃ����ȁB
	bool OpenAndPlay(LPTSTR fileName, WORD _typeID);

	// �E�B���h�E�̎�ނɊւ���p�����[�^���w�肵�A
	// �E�B���h�E�̈ʒu��w�i�A�����F�Ȃǂ�ݒ肷��B
	// �����̃E�B���h�E�̓V�[���̍ŏ���Setup���s�����A
	// Window_HintMessage�͎g�p���钼�O��Setup���s���B
	// ����́A��x�Ɉ�����E�B���h�E���o�Ȃ����A
	// �����V�[���ł������^�C�v�̃E�B���h�E���g���ꍇ�����邱�ƂɊ֌W����B
	// OpenAndPlay��wndType�l��0�ȊO������Ƃ��̒l�������Ƃ���
	// ���̊֐������s���邽�߁A��{�I�ɒP�ƂŎ��s����K�v�͂Ȃ��B
	bool SetupByTypeID(WORD _typeID, bool check);

	// �t�@�C�������w�肷��
	// �����Ƀt�@�C�����J���Ă݂āA�J���Ȃ�������false��Ԃ�
	bool SetFileName(LPTSTR name);

	// �E�B���h�E���J��������y�[�W������ꂽ���ȂǁA
	// �E�B���h�E�̕\�����e���Ȃ��Ȃ������Ɏ��s�����B
	// �t�@�C���̒��g����y�[�W���i���ɕ\�����镪�j�����ǂݍ��݁A
	// stockLine�Ƀf�[�^��~�ς���B
	BYTE NewPage();

	// ���݂�buffer�̓��e��stockLine�ɓ]������B
	bool FlushBuffer();

	// �R�}���h���m�F����
	WORD CheckCommand(LPTSTR buf);

	// �A�N�Z�T
	int GetLineCount(){ return lineCount; };

	// ���e���X�V����
	virtual void ExUpdate();

	// IDLE��ԂɂȂ����
	virtual bool CheckIsIdle();

	// �`��
	virtual void DrawFrameBack() const;		// �w�i�̐l�`�Ȃǂ̕`��
	virtual void DrawContent() const;

};


#endif // WINDOW_HINTMESSAGE_H
