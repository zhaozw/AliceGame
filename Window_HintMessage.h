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

class Window_HintMessage : public Window_Message{
protected:
	TCHAR fileName[MAX_PATH];		// �t�@�C���̖��O
	std::streamoff filePos;	// ���x���J����������肷��֌W��t�@�C���̈ʒu��ێ����Ă���
					// ���̃N���X���g��ifstream��ێ����Ȃ�

public:
	// �R���X�g���N�^
	Window_HintMessage();
	// ���e�̃��Z�b�g
	void Clear();


};


#endif // WINDOW_HINTMESSAGE_H
