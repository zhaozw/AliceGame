// Scene_StockDolls.h

// �A���X�̋L���̒��̐l�`���m�F������A
// ��������l�`�𐶂ݏo�����肷��N���X�B

#pragma once

#include "Scene_Base.h"

class Scene_StockDolls : public Scene_Base{
private:
public:
	// �R���X�g���N�^
	Scene_StockDolls();

	// ����������
	virtual bool Initialize(bool fSkipFrame);
	// �I������
	virtual bool Terminate();

	// �X�V����
	virtual int Update();
	// �`�揈��
	virtual void Draw() const;


};

