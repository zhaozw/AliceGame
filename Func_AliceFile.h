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
#define SAVEFILE_INDEX_DOLLLIST			2


// �e�Z�[�u�R���e���c���Í������邽�߂̕�����
#define SAVEFILE_CODE_FILEHEADER		"7zgC6Hd"
#define SAVEFILE_CODE_ALICEINFO			"7zgD63a"
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



#endif // FUNC_ALICEFILE_H