// MyFiles.h

#ifndef MYFILES_H
#define MYFILES_H

#include <Windows.h>
#include <tchar.h>

// �A������ő�̃t�@�C����
#define MAX_FILES					32
#define MAX_FILEPATH				64 // �����t�@�C���̃t�@�C����

// �t�@�C���̃v���p�e�B�Ɋւ���t���O
#define MYFILE_FLAG_USED 0x01			// MyFileInfo���g�p����Ă��邩
#define MYFILE_FLAG_COPYED 0x02			// �Ǝ��Ń��������m�ۂ������̂ł͂Ȃ��A
										// ����I�u�W�F�N�g�̃|�C���^���R�s�[���Ă���
#define MYFILE_FLAG_PROTECTED 0x04		// �Q�Ƃł��Ȃ����e���|�C���^���w���Ă���
										// (�ʏ헧���Ă͂����Ȃ��t���O)

// ���̑�
#define INDEX_ERROR (0xff)			// �C���f�b�N�X���擾����֐����G���[�̏ꍇ�ɕԂ��l
#define INDEX_ANY (0xfe)			// �C���f�b�N�X����ɐ������Ȃ��ꍇ

// �t�@�C���w�b�_���L�q����\����
// ���[�h��̏��ێ����s���B
typedef struct MyFileInfo{
	TCHAR name[MAX_FILEPATH];			// �t�@�C����
	DWORD size; 						// �t�@�C���T�C�Y
	void* pointer;						// �|�C���^�ʒu
	WORD flags;						// �g�p����Ă��邩
	// �R���X�g���N�^
	MyFileInfo(){
		for(int i=0; i<MAX_FILEPATH; i++){
			name[i] = _T('\0');
		}
		size = 0;
		pointer = NULL;
		flags = 0x00;
	};
}MYFILEINFO, *LPMYFILEINFO;


// �Ǝ��`���Ńt�@�C����ǂݍ��񂾂舵�����肷��B
// �ł���{�I�ȃt�@�C���`���́A�ŏ��Ƀt�@�C���̐��A���Ƀt�@�C���̃T�C�Y�̗񋓁A
// �����ăt�@�C���̒��g���A������Ă��邾���Ƃ������́B
//
// DWORD 
class MyFiles{
private:
	// �����o�Q
	bool fNeedToRelease;	// �v���O�����I�����Ƀ��������������K�v������
	// �t�@�C���T�C�Y
	WORD fileNum;						// �L���ȕ����t�@�C���̐�
	MyFileInfo fileInfo[MAX_FILES];		// �����t�@�C�����ꂼ��̏��
										// (�f�[�^���w���|�C���^�������Ɋ܂܂��)
public:
	// �R���X�g���N�^
	MyFiles();
	// �f�X�g���N�^
	~MyFiles();

	// �P���֐��n

	// �C���f�b�N�X���Q�Ɖ\�Ȃ��̂��ǂ�����Ԃ�
	bool IndexEnabled(WORD index){ return(index>=0 && index<MAX_FILES); };

	// �g�p����Ă��Ȃ����ōł��Ⴂ�t�@�C���̃C���f�b�N�X��Ԃ�
	// INDEX_ERROR�Ȃ�C���f�b�N�X�����݂��Ȃ�
	WORD GetEmptyIndex();

	// �w�肵���t�@�C���̃C���f�b�N�X���g�p�\����Ԃ�
	bool CheckIndexIsEmpty(WORD index);
	bool CheckIndexIsUsed(WORD index){ return !CheckIndexIsEmpty(index); };

	// �w�肵�����O�̃t�@�C�������C���f�b�N�X��Ԃ��B
	WORD GetNamedIndex(LPTSTR fileName, WORD fileNameLength=0);

	// �����ȃf�[�^�ւ̃A�N�Z�T
	LPVOID GetFilePointerByIndex(WORD index);
	LPVOID GetFilePointerByName(LPTSTR fileName, WORD fileNameLength=0){
		return GetFilePointerByIndex(GetNamedIndex(fileName, fileNameLength));
	};

	// �t�@�C�������Z�b�g����
	// �ςȕ����Ŗ��߂��Ȃ��悤�ɏ��������s��
	void SetFileName(int index, LPTSTR fileName);

	// �t���O���Z�b�g����
	void ResetFileFlags(int index){ fileInfo[index].flags = 0x00; };
	void SetFileFlags(int index, WORD flag);

	// �������̈���m�ۂ��Apointer�Ɋ��蓖�Ă�
	bool InitializePointer(int index, DWORD size);

	// ���G�֐��n
	// �e�L�X�g�t�@�C���ɋL�q���ꂽ�t�@�C���Q��MyFiles�ɓǂݍ���
	// �ǉ��ǂݍ��݂͕s�\�i�ǉ��œǂݍ������Ƃ����ꍇ�͑O�̃t�@�C���Q���������j
	// fileName : �t�@�C����
	bool LoadFilesFromTxt(LPTSTR fileName);

	// �Ǝ��`���ŕۑ����ꂽ�t�@�C���Q��MyFiles�ɓǂݍ���
	// �ǉ��ǂݍ��݂Ƃ��Ă��̊֐����g�p���邱�Ƃ͕s�\
	// fileName : �t�@�C����
	bool LoadFilesFromDat(LPTSTR fileName);

	// �t�@�C�������w�肵��MyFiles�ɒǉ�����
	// fileName : �t�@�C����
	// �߂�l : �ǉ����ꂽ�t�@�C���ʒu�BINDEX_ERROR�̓G���[
	// 
	WORD AddFileToFiles(LPTSTR fileName, LPTSTR newName,
		WORD index=INDEX_ANY, bool useNewName=true);

	// �t�@�C�������w�肵�A�ꕔ�𔲂�������MyFiles�ɒǉ�����
	// fileName : �t�@�C����
	// offset : �I�t�Z�b�g
	// length : ������������
	// �߂�l : �ǉ����ꂽ�t�@�C���ʒu�BINDEX_ERROR�̓G���[
	// 
	WORD AddFilePartToFiles(LPTSTR fileName, LPTSTR newName,
		DWORD offset, DWORD length, WORD index=INDEX_ANY, bool useNewName=true);

	// �I�u�W�F�N�g���w���A�h���X�����Ƀf�[�^��MyFiles�ɒǉ�����B
	// �I�u�W�F�N�g�̃T�C�Y�������Ǝw�肵�Ȃ���΂Ȃ�Ȃ��B
	// �|�C���^�̎w���I�u�W�F�N�g���A�N�Z�X�ł��Ȃ����̂̏ꍇ�̓G���[�B
	// �߂�l : �ǉ����ꂽ�t�@�C���ʒu�BINDEX_ERROR�̓G���[
	// �f�[�^���R�s�[����̂ł͂Ȃ��I�u�W�F�N�g�̈ʒu���w�������Ȃ̂ŁA
	// �I�u�W�F�N�g�̊J���͕ʓr�s���K�v������B
	WORD AddObjectToFiles(LPVOID pointer, DWORD size, 
		LPTSTR objName, int index=INDEX_ANY);

	// ���炩�̕��@�ō쐬�����o�C�g���MyFiles�ɒǉ�����B
	// �o�C�g��̃T�C�Y���w�肵�Ȃ���΂Ȃ�Ȃ��B
	// needToRelease��true�̎��AMyFiles�N���X�ɂ���ĉ�������B
	// ���ɓ�d�J�����N�����₷�������ł���̂ŁA���ӁB
	// �߂�l : �ǉ����ꂽ�t�@�C���ʒu�BINDEX_ERROR�̓G���[
	WORD AddBytesToFiles(void* pointer, DWORD size, 
		LPTSTR objName, bool needToRelease, int index=INDEX_ANY);

	// MyFiles�̒��g���Í�������Ă��Ȃ��`���Ńo�C�i���t�@�C���ɏ����o��
	// fileName :		�t�@�C����
	// hideName :		�����o�����Ƀt�@�C�������B�����ǂ���
	//					(�P���ɁA�t�@�C�����ɑ�������Ƃ���Ƀ_�~�[�̕����������)
	// sizeInBytes :	�����o�����t�@�C���̃T�C�Y���i�[����|�C���^�B
	bool SaveFilesToRawFile(LPTSTR fileName, bool hideName, DWORD* sizeInBytes);

	// MyFiles�̒��g�̂����w�肳�ꂽ�C���f�b�N�X�̃t�@�C�����o�C�i���t�@�C���Ƃ��ď����o��
	// index : �C���f�b�N�X
	// outName : �����o�����̖��O
	// useRawName : true�Ȃ�outName�𖳎�����MyFiles�̖��O�Ńt�@�C���������o��
	bool SaveFileToRawFileByIndex(int index, LPTSTR outName, bool useRawName=true);

	// MyFiles�̒��g�̂����w�肳�ꂽ���O�̃t�@�C�����o�C�i���t�@�C���Ƃ��ď����o��
	// searchName : ���O
	// outName : �����o�����̖��O
	// useRawName : true�Ȃ�outName�𖳎�����MyFiles�̖��O�Ńt�@�C���������o��
	bool SaveFileToRawFileByName(LPTSTR searchName, LPTSTR outName, bool useRawName=true);

	// MyFiles�̒��g���i��������Łj�Í����E����������i�֐�����Encode�����������o����j
	// �t�@�C���f�[�^�����̂܂ܔr���I�_���a�ňÍ�������
	// index : �Í������钆�g
	// code : �Í����R�[�h
	// codeLength : �Í����R�[�h�̒���
	bool EncodeFileXOR(WORD index, LPTSTR code, WORD cordLength);

	// �t�@�C���̒��g����v���邩�ǂ�����r����B
	// �A�b�v�f�[�^�Ȃǂ��쐬����ۂɁB
	bool CompareFiles(WORD index, WORD index2);

	// �t�@�C���̃T�C�Y���擾����B
	DWORD GetFileSize(WORD index){
		if(!IndexEnabled(index)) return 0;
		return fileInfo[index].size;
	}

	// �����I�Ƀ��������������(���펞)
	bool Release(int index);
	bool ReleaseAll();

	// �����I�Ƀ��������������(����)
	// checkUsed : �g�p����Ă��邩�ǂ����̃t���O��M�p���邩
	bool ForceRelease(int index, bool checkUsed=false);
	bool ForceReleaseAll(bool checkUsed=false);

};


#endif