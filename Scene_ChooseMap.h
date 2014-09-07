// Scene_ChooseMap.h

// �}�b�v��I������V�[���B
// �G���A�I���ƃ}�b�v�I���̓�i�K�ɕ�������B
// �}�b�v��I�������Scene_Map�Ɉڍs����B

#pragma once

#include "Scene_Base.h"
#include "Static_Map.h"

class Scene_ChooseMap : public Scene_Base{
public:
	// phaze�l
	enum CHOOSEMAP_PHAZE{
		PHAZE_ERROR		= -1,
		PHAZE_STANDBY,			// �X�^���o�C��ԁB�ړ��o����B
		PHAZE_EVENT,			// �C�x���g�̏������B�ł��D��x�������B
		PHAZE_MENU,				// ���j���[�̏������B
		PHAZE_CHOOSEMAP,		// �G���A���̃}�b�v��I�𒆁B
		PHAZE_OPENPATH,			// �p�X���J���������B
		PHAZE_OPENPOINT,		// �|�C���g���J���������B
		PHAZE_CHECK,			// �C�x���g�E�p�X�E�|�C���g�̏������Ȃ�������������B

	};
private:
	int						cntIndex;		// ���ݑI�𒆂̃|�C���g�ԍ��B
	int						lastIndex;		// �Ō�ɑI�����Ă����|�C���g�ԍ��B
	bool					moving;			// �ړ����t���O�B
	enum CHOOSEMAP_PHAZE	phaze;			// �t�F�C�Y�B
	int						phazeTime;		// ���݂̃t�F�C�Y�̎��ԁB
	// �|�C���g���J����Ԃɂ��邩�ǂ����̔���B
	// �\������≉�o�݂̂Ɏg�p����A
	// ���ۂ̃v���C���[�̈ړ��̓p�X��ōs����B
	// �Ȃ��A�p�X�̏�Ԃ�Record_ChooseMap�N���X�Ɋ܂܂�Ă���B
	// �|�C���g�̏�Ԃ͂����Ɋ܂߂�K�v���Ȃ��̂ŃV�[���̃����o�Ƃ��Ă���B
	bool					pointIsOpened[CHOOSEMAP_POINT_MAX];	
	int						alicePosX, alicePosY; // �A���X�̈ʒu
	int						openingIndex;	// PHAZE_OPENPATH�܂���PHAZE_OPENPOINT�ɂ�����
											// �������Ă���Œ��̒n�_�̃C���f�b�N�X�B

public:
	// �R���X�g���N�^
	Scene_ChooseMap();


	// ����������
	virtual bool Initialize(bool fSkipFrame);
	// �I������
	virtual bool Terminate();

	// �X�V����
	virtual int Update();

	// phaze�l��ύX����Ƌ��ɁA���̏����������s���B
	bool SetPhaze(enum CHOOSEMAP_PHAZE phaze);

	// ��������C�x���g�����邩�ǂ����̔�����s���B
	// �C�x���g������ꍇ�̓C�x���gID���A
	// �C�x���g���Ȃ��ꍇ��0��Ԃ��B
	WORD CheckEventHappen();

	// �V���ɊJ�����p�X�����邩�ǂ����̔�����s���B
	// �C�x���g������ꍇ�̓p�XID���A
	// �C�x���g���Ȃ��ꍇ��0��Ԃ��B
	WORD CheckPathOpen();

	// �V���ɊJ�����|�C���g�����邩�ǂ����̔�����s���B
	// �C�x���g������ꍇ�̓|�C���gID���A
	// �C�x���g���Ȃ��ꍇ��0��Ԃ��B
	// �|�C���g�����邩�ǂ����̔���݂̂ł���ApathIsOpened�l�̍X�V�͍s��Ȃ��B
	WORD CheckPointOpen();
	
	// �w�肵���C���f�b�N�X�̃|�C���g�������ԂɂȂ邩�ǂ������擾����B
	// CheckPointOpen()����Q�Ƃ����B
	// �����Ԃ̔���́A�p�X��ōs����B
	// ���Ȃ킿�A���݊J����Ă���p�X�̂����A
	// ��ł��w�肵���|�C���g�Ɛڑ�����Ă���p�X������΁A
	// ���̃|�C���g�͊J����Ԃł���Ɣ��肷��B
	bool CheckOpenPoint(WORD index);

	// �S�Ẵ|�C���g�ɑ΂���CheckOpenPoint���s���A
	// �|�C���g�𑦍��ɊJ���B
	// �V�[���̍ŏ��ōs���B
	void RefreshPoints();

	// �A���X�̈ʒu(���W�A�����)���X�V����B
	// �ړ����̃J�E���^�̐�����s���B
	void UpdateAlicePos();

	// �A���X���ړ������邽�߂̓��͏������s���B
	bool CheckAliceMove();

	// �`�揈��
	virtual void Draw() const;

	// �w�i�̕`����s���B
	void DrawBG() const;

	// �}�b�v�̕`����s���B
	// �p�X�̕`��ƃ|�C���g�̕`����܂ށB
	void DrawMap() const;
	// �C���f�b�N�X�Ŏw�肵���p�X�̕`����s���B
	void DrawPath(int index) const;
	// �S�Ẵp�X�̕`����s���B
	void DrawPaths() const;
	// �C���f�b�N�X�Ŏw�肵���|�C���g�̕`����s���B
	void DrawPoint(int index) const;
	// �e�|�C���g�̕`����s���B
	void DrawPoints() const;

	// �L�����N�^�[�̕`����s���B
	void DrawCharacters() const;
	// �A���X�̕`����s���B
	void DrawAlice() const;

	// �A���X�̈ړ��o�����������������\������B
	void DrawAliceDirection(int aliceX, int aliceY) const;
	void DrawDirection(int aliceX, int aliceY, BYTE direction) const;

	// �R�}���h�\�����A�R�}���h�̕`����s���B
	void DrawCommand() const;

};

