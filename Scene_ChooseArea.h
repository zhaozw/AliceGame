// Scene_ChooseArea.h

// �G���A��I������V�[���B
// �G���A�̑I����Selectable�N���X�ł͂Ȃ��A
// ��蕡�G�Ȉړ��𔺂��čs���B

#pragma once

#include "Scene_Base.h"

class Scene_ChooseArea : public Scene_Base{
private:
	int			cntIndex;		// ���ݑI�𒆂̃G���A�B
	int			lastIndex;		// �I�����Ă����G���A�B
	bool		moving;			// �G���A�Ԃ��ړ����ł���Ƃ����t���O�B
public:
	// �R���X�g���N�^
	Scene_ChooseArea();

	// ����������
	virtual bool Initialize(bool fSkipFrame);
	// �I������
	virtual bool Terminate();

	// �X�V����
	virtual int Update();
	// �`�揈��
	virtual void Draw() const;


};

