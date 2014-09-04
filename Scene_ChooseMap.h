// Scene_ChooseMap.h

// �G���A���̃}�b�v��I������V�[���B

#pragma once

#include "Scene_Base.h"

class Scene_ChooseMap : public Scene_Base{
private:
	int			cntIndex;			// ���ݑI�𒆂̃|�C���g�ԍ��B
	int			lastIndex;		// �Ō�ɑI�����Ă����|�C���g�ԍ��B
	bool		moving;			// �ړ����t���O�B
public:
	// �R���X�g���N�^
	Scene_ChooseMap();


	// ����������
	virtual bool Initialize(bool fSkipFrame);
	// �I������
	virtual bool Terminate();

	// �X�V����
	virtual int Update();
	// �`�揈��
	virtual void Draw() const;


};

