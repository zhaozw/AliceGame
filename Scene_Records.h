// Scene_Records.h

// �g���t�B�[���m�F����V�[���B

#pragma once

#include "Scene_Base.h"

class Scene_Records : public Scene_Base{
private:
public:
	// �R���X�g���N�^
	Scene_Records();

	// ����������
	virtual bool Initialize(bool fSkipFrame);
	// �I������
	virtual bool Terminate();

	// �X�V����
	virtual int Update();
	// �`�揈��
	virtual void Draw() const;


};

