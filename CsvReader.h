// CsvReader.h

#ifndef CSVREADER_H
#define CSVREADER_H

#include <Windows.h>
#include <tchar.h>
#include <streambuf>

#define CSV_MAX_COLUMN		10			// 1�s������̗v�f��
#define CSV_MAX_TEXT		64			// �Z��������̕�����

// Read�֐��̖߂�l
#define CSV_READ_NOERROR	0
#define CSV_READ_GOOD		0
#define CSV_READ_END		1			// �t�@�C���̖���
#define CSV_READ_ERROR		2			// �G���[���o��
#define CSV_READ_NODATA		3			// ��s

#define CSV_ERROR_VALUE		-1
#define CSV_ERROR_VALUE_FLOAT 0

// CSV�t�@�C����ǂݍ���ŗ��p���₷���`�Œ񋟂���N���X�B
// ��̓I�ɂ́A�t�@�C����1�s���ǂ�ł����A�R���}��؂�̃e�L�X�g�ɕ�������B
// ������^����ʂ̌^�ɕύX����̂�GetValue��p����B
class CsvReader{
private:
	TCHAR fileName[MAX_PATH];		// �t�@�C���̖��O
	std::streamoff filePos;	// ���x���J����������肷��֌W��t�@�C���̈ʒu��ێ����Ă���
					// ���̃N���X���g��ifstream��ێ����Ȃ�
	TCHAR value[CSV_MAX_COLUMN][CSV_MAX_TEXT];
	DWORD lineNum;		// �s�ԍ�
	WORD valueNum;		// ��łȂ������񂪓������l�̐�

public:
	// �R���X�g���N�^
	CsvReader();
	CsvReader(LPTSTR fileName);

	// �f�X�g���N�^
	~CsvReader();

	// �t�@�C�����J��
	// (���ۂɂ͊J�����A�t�@�C�������Z�b�g���邾��	
	bool Open(LPTSTR fileName);

	// �t�@�C���̍s��(��s����)�𒲂ׂ�
	// �G���[�̏ꍇ��0��Ԃ�
	DWORD GetMaxLine();
	DWORD GetMaxLine(LPTSTR fileName){ if(!Open(fileName)) return 0; GetMaxLine(); };

	// �t�@�C������1�s�ǂݍ��݁A�l���Z�b�g����
	WORD Read();

	// �l���Z�b�g�����Ɏ��̍s�Ɉړ�����
	// v, strLen���w�肵���ꍇ�AstrLen�ȓ��̒����œǂݍ��񂾍s�̓��e���R�s�[����B
	// ���̍ہA�R���}�ŋ�؂����肹�����̂܂܎�荞�ށB
	WORD NextLine(LPTSTR v=NULL, WORD strLen=0);

	// �t�@�C�������
	// �����Ń��Z�b�g���s��
	bool Close(){ Reset(); return true; };

	// �ǂݍ��݂�S�ă��Z�b�g����
	void Reset();

	// �w�肵���C���f�b�N�X���g�p����Ă��邩�ǂ������`�F�b�N����
	bool Used(int i){ return (i<valueNum); };

	// �l���擾����
	void GetValue(WORD index, LPTSTR v, WORD strLen=CSV_MAX_TEXT);

	// �l�𐮐��l�Ƃ��Ď擾����
	int GetIntValue(WORD index, int errorValue=CSV_ERROR_VALUE);

	// �l�������l�Ƃ��Ď擾����
	float GetFloatValue(WORD index, float errorValue=CSV_ERROR_VALUE_FLOAT);

	// �l�𕶎��Ƃ��Ď擾����
	TCHAR GetCharacter(WORD index, TCHAR errorValue=_T(' '), WORD charPos=0);
	
	// �l��char�^�̕ϐ��Ƃ��Ď擾����
	char GetCharValue(WORD index, char errorValue=0);


	// �l���u�[���l�Ƃ��Ď擾����(1�ȏ�Ȃ�true�A����ȊO�Ȃ�false)
	bool GetBoolValue(WORD index){
		return (GetIntValue(index)>0); 
	};

	// �t�@�C���̌��݂̈ʒu����A
	// ����̕������擪�Ɏ��s�����������̍s�̎��̍s�Ɉړ�����B
	// goNextLine��false���ƕ������擪�Ɏ��s���̂܂܂Ɉړ�����B
	// fromHead���w�肷��ƃt�@�C���̐擪���猟������B
	// �w��̍s��������Ȃ������ꍇ��false��Ԃ��B
	// ������Ȃ������ꍇ�͌��̏ꏊ���ێ�����B
	bool Seek(LPTSTR word, WORD strlen, bool fromHead=false, bool goNextLine=true);

};

#endif // CSVREADER_H