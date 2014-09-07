#ifndef FUNC_ALICEFILE_H
#define FUNC_ALICEFILE_H

#include <Windows.h>

// �Z�[�u�\�ȍő吔
#define MAX_SAVEFILE		32
// �Z�[�u�t�@�C������ێ����镶����̒���
#define SIZE_SAVEFILENAME	64

// �e�Z�[�u�R���e���c�����[���邽�߂̃C���f�b�N�X�l
#define SAVEFILE_INDEX_FILEHEADER		0
#define SAVEFILE_INDEX_ALICEINFO		1
#define SAVEFILE_INDEX_CHOOSEMAP		2
#define SAVEFILE_INDEX_DOLLLIST			3


// �e�Z�[�u�R���e���c���Í������邽�߂̕�����
#define SAVEFILE_CODE_FILEHEADER		"7zgC6Hd"
#define SAVEFILE_CODE_ALICEINFO			"7zgD63a"
#define SAVEFILE_CODE_CHOOSEMAP			"bvgD53d"
#define SAVEFILE_CODE_DOLLLIST			"9zgD6Hd"


// �|�C���^���������߂̃N���X�錾
class Game_FileHeader;

// �C���f�b�N�X���w�肷��ƃt�@�C������Ԃ��B
// str : �t�@�C�������i�[����TCHAR�̔z��
// strLength : �m�ۂ���������̃T�C�Y
// index : �C���f�b�N�X
// �߂�l : �C���f�b�N�X���s���̏ꍇ��false��Ԃ�
bool GetSaveGameFileName(LPTSTR str, int strLength, BYTE index);

// �t�@�C�������݂��邩�ۂ���Ԃ��B
// �߂�l : ���݂���ꍇ��true
bool GetGameFileIsExist(BYTE index);

// �t�@�C���̃w�b�_�����i�[����B
// pHeader : �����i�[����Game_FileHeader�N���X�ւ̃|�C���^
// index : �t�@�C���̃C���f�b�N�X
bool GetGameFileHeader(Game_FileHeader* pHeader, BYTE index);

// ���݂̓��e���C���f�b�N�X���w�肵�ĕۑ�����B
// �㏑���Ȃǂ̊m�F�͍s��Ȃ��B
// �߂�l�F���������ꍇ��true
bool SaveGame(BYTE index);

// ���݂̓��e���C���f�b�N�X���w�肵�Ċe�O���[�o���ϐ��ɓǂݍ��ށB
// �߂�l�F���������ꍇ��true
bool LoadGame(BYTE index);

// �e�O���[�o���ϐ���S�ă��Z�b�g����B
bool NewGame();

// ������Ԃ̐l�`�����X�g�ɉ�����B
void GenerateInitialDoll();

// 2014�N�x�ăR�~�̃o�[�W�����ɂ�����f�[�^��ێ�����N���X�B
// �O���[�o���ϐ�g_aliceFile140816����Q�Ƃ����B

#define ALICEFILE_140816_TUTORIAL			10
#define ALICEFILE_140816_FILENAME			"savedata\\Trial_ver140806.dat"
#define ALICEFILE_140816_XORCODE			"aZkw7QQn"
#define ALICEFILE_140816_XORCODE_LENGTH		8
#define ALICEFILE_140816_XORCODE2			"3kkNniHnkkN"
#define ALICEFILE_140816_XORCODE2_LENGTH	11

typedef struct AliceFile_140816_Data{
	bool	firstHint;				// �ŏ��̃q���g���b�Z�[�W�B
								// ���Ă����true�ŁA����ȍ~�͎����ł̕\�����s��Ȃ��B
	BYTE	tutorialBattle[ALICEFILE_140816_TUTORIAL];	
								// �`���[�g���A���o�g�����N���A�������ۂ��B
								// ������Ȃ�0(�����\��)�A
								// ���N���A�Ȃ�1(�����͕\�����Ȃ�)�A
								// �N���A���Ă����2�B
								// �N���A���Ă����true�B
	bool	tutorialHint;		// �`���[�g���A���̃q���g�̕\���B
								// true�Ȃ疈�񌩂�Bfalse�Ȃ珉��̂݌���B
	int		forFuture[10];		// �����I�Ɏg�p�ł���f�[�^�̈�B
								// �g�p����Ă��Ȃ����͂��ׂ�0�ł���B
}ALICEFILE_140816_DATA;

class AliceFile_140816{
public:
	// �f�[�^
	ALICEFILE_140816_DATA	data;
public:
	// �R���X�g���N�^
	AliceFile_140816();

	// ���e��ۑ�����B
	bool Save();

	// ���e��ǂݍ��ށB
	bool Load();

	// ���e�̃��Z�b�g
	void Reset();
};


#endif // FUNC_ALICEFILE_H