#ifndef SPRITE_BATTLEENEMY_H
#define SPRITE_BATTLEENEMY_H

#include "Sprite_Base.h"
#include "Game_BattleEnemy.h"

class Sprite_BattleEnemy : public Sprite_Base{
private:
	// �G�L�����ւ̎Q��
	Game_BattleEnemy*		pEnemy;
	WORD	refID;		// �G��ID�B
	// �摜���ł̒��S�̈ʒu
	// �G�L�����͍����ł͂Ȃ��A�摜�̂����_���w�肵�Ċ�Ƃ���
	// width, height�̒l�͎��ۂɂ͎g�p���Ȃ��B
	float	cx, cy;	
	float	baseExRate;	// ��{�I�ȕ\���{��
	int		hImg;		// �摜�̃n���h��
public:
	// �R���X�g���N�^
	Sprite_BattleEnemy();

	// �G�̏������Ɋ��蓖��
	bool	AttachBattleEnemy(Game_BattleEnemy* _pEnemy);

	// �G��refID���ς�������ɕ`���ύX����B
	// Update�����玩���ŌĂяo�����B
	void	UpdateRefID();
	// 
	// �X�V
	virtual void Update();

	// �`��
	virtual void Draw() const;

	// HP�Q�[�W�̕`��
	// x, y�͒��S�ʒu
	virtual void DrawHPGauge(int x, int y) const;
};


#endif // SPRITE_BATTLEENEMY_H