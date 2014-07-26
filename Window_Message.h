#ifndef WINDOW_MESSAGE_H
#define WINDOW_MESSAGE_H

#include <Windows.h>
#include "Window_Text.h"

class Window_Message_DrawLine;
class Window_Message_DrawMsg;
class Window_Message_StockLine;
class Window_Message_StockMsg;
class Scene_Base;

// �e��萔�̒�`
#define WND_MSG_DRAWLINE		4		// �\������s��
#define WND_MSG_DRAWLENGTH		48		// �\�����E��s������̕�����	
#define WND_MSG_STOCKLINE		8		// ���e���X�g�b�N����s��
#define WND_MSG_STOCKLENGTH		128		// �X�g�b�N���E��s������́u�o�C�g���v

// ���b�Z�[�W���̕����̃t���O
#define F_MSGCHAR_ENDMSG		0x0001	// ���͂̏I�[��\��
#define F_MSGCHAR_ONE_BYTE		0x0002	// 1�o�C�g�����ł���

// ��������Ȃǂ̃t���O
#define F_READTYPE_QUICK		0x0001	// ���͂̓r���ł�����L�[�ŏu�ԕ\��
#define F_READTYPE_AUTOQUICK	0x0002	// �L�����Z���L�[�Ō���L�[�������ςȂ�����
#define F_READTYPE_DIRECTQUICK	0x0004	// �u�ԕ\���̍ۂɎ��̍s�ɐi��
#define F_READTYPE_NOWAIT		0x0008	// ���͂��u�ԓI�ɕ\������(messageSpeed�l�𖳎�)
#define F_READTYPE_PUSH			0x0010	// ���ɕ\�����镶�͂�����ꍇ�A�����Ői�߂�
#define F_READTYPE_FLOOD		0x0020	// ���ɕ\�����镶�͂������Ă��Ȃ��Ă��i�߂�
#define F_READTYPE_AUTOPLAY		0x0040	// ����L�[��L�����Z���L�[�ɂ��i�s���o���Ȃ��B
										// �i��Ɏ��Ԍo�߂݂̂ɂ���Đi�s����j
#define F_READTYPE_BLANKLINE	0x0080	// �X�g�b�N����̎��Ɍ���L�[��������
										// ��s��}�����Ď��̍s�ɐi�ށB
										// �t���O���w�肵�Ȃ��ꍇ�A
										// �X�g�b�N���Ȃ��ꍇ�y�[�W��������Ȃ��B
										// 


// ���b�Z�[�W�X�s�[�h
#define WND_MSG_DEFSPD			1.0


// �o�g�����b�Z�[�W�E�B���h�E�ŕ\������ꕶ���̏���ێ�����\���́B
typedef struct Window_Message_DrawChar{
	TCHAR		character[3];	// �ꕶ��
	WORD		flags;			// ����������^�C�~���O�����ɗp����t���O
	bool		used;
	Window_Message_DrawChar(){
		for(int n=0; n<3; n++){
			character[n] = '\0';
		}
		flags = 0x0000;
		used = false;
	}
} WINDOW_MESSAGE_DRAWCHAR;

// �o�g�����b�Z�[�W�E�B���h�E�ŕ\�������s�̏���ێ�����\���́B
// �`��ʒu��Window_Message�N���X���ŕێ�����B
class Window_Message_DrawLine{
public:
	WINDOW_MESSAGE_DRAWCHAR	chars[WND_MSG_DRAWLENGTH]; // �s���̊e����
	WORD					flags;	// ����������^�C�~���O�����ɗp����t���O
public:
	// �R���X�g���N�^
	Window_Message_DrawLine();
	// ���e���N���A����
	void Clear();
	// �X�^�b�N������e���C���|�[�g����B
	bool Import(LPTSTR buf, int strLen);
	// ���݂̓��e�̕��������擾����B
	int GetStrLength() const;
	// ���g�̓��e��`�悷��B
	// hFont	: �`��ɗp����t�H���g
	// fontWidth: �t�H���g�̕�
	// x, y		: �`��ʒu(��΍��W)
	// count	: �`�悷�镶�����B-1���w�肷��ƑS�Ă̕�����`��B
	void DrawContent(int hFont, int fontWidth, int x, int y, int count=-1) const;
};

// �o�g�����b�Z�[�W�E�B���h�E�ŕ\�����郁�b�Z�[�W�S�̂̏���ێ�����N���X�B
class Window_Message_DrawMsg{
private:
	Window_Message_DrawLine	lines[WND_MSG_DRAWLINE];	// �e�s
	int						index; // ���ݕ`�撆�̍s�̃C���f�b�N�X
public:
	// �R���X�g���N�^
	Window_Message_DrawMsg();
	// �w�肵���s�̃N���A
	void ClearLine(int n);
	// ���͓��e��S�ăN���A
	void ClearAll();
	// �A�N�Z�T
	int GetIndex() const{ return index; };
	// ���݂̍s�̕����������߂�
	int GetLineLength(int historyCount=0) const;
	// �w�肵���s��`�悷��B
	void DrawLine(int hFont, int hFontWidth,
		int x, int y, int count=-1, int historyCount=0) const;
	// ��̍s�ɕ`�悷����e��ǉ�����B
	// �s�̒����ɂ��Ă̊m�F�͍s��Ȃ��B
	bool ImportLine(LPTSTR buf);
	// ��̍s��}������B
	void BlankLine();
};

// �o�g�����b�Z�[�W�E�B���h�E�ŏ����X�g�b�N�����s�̏���ێ�����\���́B
class Window_Message_StockLine{
public:
	TCHAR		chars[WND_MSG_STOCKLENGTH];
public:
	// �R���X�g���N�^
	Window_Message_StockLine();
	// ���e�̃N���A
	void Clear();
	// ���g���󂩂ǂ�����Ԃ�
	bool IsEmpty();
	// ������̃|�C���^��n��
	TCHAR*		GetCharsPtr(){ return chars; };
};

// �o�g�����b�Z�[�W�E�B���h�E�ŏ����X�g�b�N����S�̂̏���ێ�����N���X�B
class Window_Message_StockMsg{
private:
	Window_Message_StockLine		lines[WND_MSG_STOCKLINE]; // �e�s
	int								index; // ���ɏ�������s�̃C���f�b�N�X
	int								emptyIndex;	// ���ɓ��e��ǉ�����s�̃C���f�b�N�X
												// �󂩂ǂ����̔����AddMsg���ɍs��
public:
	// �R���X�g���N�^
	Window_Message_StockMsg();

	// �w�肵���s�̓��e���N���A
	void ClearLine(int n);

	// ���e��S�ăN���A
	void ClearAll();

	// ��̍s�Ɏw�肵���e�L�X�g�̓��e���R�s�[����
	bool AddMsg(LPTSTR str, int strlen);

	// ���݂̍s�̓��e���w�肵���̈�ɓǂݏo���B
	// �o�b�t�@�T�C�Y�̓`�F�b�N���Ȃ��B
	// discard : �ǂݏo�����ہA�ǂݏo�������e���X�g�b�N���珜�O����B
	// �G���[���������ꍇ�A���e����̏ꍇ��false��Ԃ��B
	bool ReadLine(LPTSTR buf, bool discard);

	// ���݂̍s���󂩂ǂ������`�F�b�N����B
	bool IsEmpty(){ return lines[index].IsEmpty(); };

	// ���݂̓��e���X�g�b�N���珜�O����B
	void DiscardLine();

};

// Window_Message�N���X
// �퓬���ɗ���郁�b�Z�[�W��\������N���X�B

class Window_Message : public Window_Text{
public:
	enum SUBSTATE{
		WNDSUBSTATE_NOTEXT,		// �e�L�X�g���Ȃ����
		WNDSUBSTATE_READING,	// �s��ǂ�ł�����
		// WNDSUBSTATE_CLICKWAIT,	// �N���b�N�҂��̏��
		WNDSUBSTATE_UNDIFINED,
	};
protected:
	// �`�撆�̃��b�Z�[�W
	Window_Message_DrawMsg	drawMsg;
	// ���e��ێ����Ă��郁�b�Z�[�W
	Window_Message_StockMsg	stockMsg;
	// �T�u�X�e�[�g
	enum SUBSTATE			subState;
	// ��������p�^�[��
	WORD					readTypeFlag;
	// �`�撆�̍s�̌��݂̈ʒu
	int						linePos;
	// ���݂̍s�̕\�����n�܂��Ă���̎���
	int						lineCount;
	// ���Ȃ��Ƃ����̃t���[�����o�܂ł͎��̍s�ɐi�܂Ȃ�
	int						lineCountMin;
	// �N���b�N�҂����s���Ă���t���[����
	int						clickWaitCount;
	// �N���b�N�҂��������Ŕ�΂��t���[����
	int						clickWaitTime;
	// �t�H���g�̉���
	int						fontWidth;
	// 1�t���[��������Ɋ��߂镶����
	float					messageSpeed;

public:
	// �R���X�g���N�^
	Window_Message();

	// ���e�̃Z�b�g�A�b�v
	void Setup(WindowSkin* pSkin, WINDOWAREA _frameArea, WINDOWAREA _contentArea,
		bool _visible);
	void Setup_FixPadding(WindowSkin* pSkin, WINDOWAREA _frameArea,
		int _px, int _py, bool _visible);
	void Setup_FixContentWidth(WindowSkin* pSkin, WINDOWAREA _frameArea,
		int _content_width, int _py, bool _visible);
	
	// ���e��S�ăN���A(Setup���A�R���X�g���N�^���Ɏg�p)
	void ResetAll();

	// �`�掞�̃t�H���g�̕����w��
	// (���p�����̏ꍇ�͎����Ŕ����̒l���w�肳���)
	void SetFontWidth(int width){ fontWidth = width; };

	// stockMsg�ɓ��e��ǉ�����B
	bool AddStockMsg(LPTSTR str, int strlen);

	// ���ݕ`�撆�̍s����ł��邩�ǂ�����Ԃ��B
	bool DrawMsgIsEmpty(int historyCount=0){
		return drawMsg.GetLineLength(historyCount) == 0; };

	// stockMsg���󂩂ǂ�����Ԃ��B
	bool StockIsEmpty(){ return stockMsg.IsEmpty(); };

	// ���e�̃A�b�v�f�[�g���s���B
	virtual void Update();			// �N���X���Ƃɔh������A�b�v�f�[�g�֐��B

	// Window_Message�N���X����h������N���X�̃A�b�v�f�[�g�B
	// ����ɃN���X���Ƃɔh������BUpdate�֐���������s�����B
	virtual void ExUpdate();

	// Window_Message�N���X�̃E�B���h�E��IDLE�ɂȂ�����������B
	virtual bool CheckIsIdle();

	// ���e�̕`����s���B
	virtual void DrawContent() const;

	// ���b�Z�[�W�����s����B
	// ��̓I�ɂ́AstockMsg�̓��e��1�s���ǂݏo���A
	// drawMsg�̐V�����s�ɑ΂��ēǂݏo����stockMsg�̓��e��n���ĕ�����ɕϊ�����B
	// 
	// force : true�̏ꍇ�A�\������ׂ����b�Z�[�W���Ȃ��Ă����s����B
	// ���̏ꍇ�AstockMsg�̓��e��ǂݏo���͂����A
	// drawMsg�ɂ͕������܂܂Ȃ���s��n���B
	void NewLine(bool force);

	// ���b�Z�[�W�̍X�V�̔�����s���B
	void UpdateLine();

	// ���b�Z�[�W�̉��s�̔�����s���B
	// ���ۂ̉��s�܂ł��̊֐����ōs���B
	// chooseKey	: ����L�[���u���̏u�ԂɁv�����ꂽ���ǂ���
	// skipKey		: �X�L�b�v�L�[���u��������ςȂ��v���ǂ���
	// �߂�l		: ���s���s�������ǂ���
	bool CheckNewLine(bool chooseKey, bool skipKey);

	// ���ɕ\������ׂ����͂����݂��邩�ǂ����̔�����s���B
	bool CheckStockMsg();

	// ���݂̍s�̕��������擾����B
	int GetLineLength();
	int GetClickWaitCount(){ return clickWaitCount; };
	void SetClickWaitTime(int t){ clickWaitTime = t; };
	int GetClickWaitTime(){ return clickWaitTime; };

	// �A�N�Z�T
	void SetReadType(WORD flag){ readTypeFlag = flag; };
	WORD GetReadType(){ return readTypeFlag; };
	
	// ���e1�s�̕`����s���B
	// dx, dy : �E�B���h�E�̍���ɑ΂���ʒu
	// historyCount :	0�̏ꍇ�A�ŐV�̍s��`��B
	//					1�ȏ�̏ꍇ�A������w�肵���������Â��s��`�悷��B
	//					�����Ȑ��l�̏ꍇ�͕`�悵�Ȃ��B
	void DrawLine(int dx, int dy, int historyCount=0) const;
	void DrawCurrentLine(int dx, int dy) const;
	void DrawHistoryLine(int dx, int dy, int historyCount=1) const;

};

// StockMessage��DrawMessage�̕���킵���Ƃ���̕⑫
// StockMessage�Ɋւ��ẮA���ɓǂݍ��ނ͈̂�ԍŏ��ɒǉ����ꂽ�X�g�b�N�ł���B
// �����āA���ɒǉ������͈̂�ԍŌ�ɒǉ����ꂽ�X�g�b�N�̎��̃C���f�b�N�X�ł���
// index��emptyIndex��ʂ̃����o�Ƃ��Ď����Ă��Ȃ��Ɓi�������͖���v�Z���Ȃ��Ɓj
// ���ɒǉ����ׂ��C���f�b�N�X��������Ȃ��B
// ����ADrawMessage�̓X�g�b�N����ǂݍ��܂��s�����ɕ\������s�ł���A
// ���ɓ��e�������Ă���s�͑S�ė����ł���B
// ���̂��߁A�V�����s��ǂݍ��ނƂ��́A�����قǂ܂ŕ\�����Ă����s�̎��̍s��
// ��ɓ��e��ǂݍ��߂Ηǂ��B���̂��߁AemptyIndex�����o�͕s�v�ƂȂ�B

#endif // WINDOW_MESSAGE_H