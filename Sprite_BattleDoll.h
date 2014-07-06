#ifndef SPRITE_BATTLEDOLL_H
#define SPRITE_BATTLEDOLL_H

#include <Windows.h>

#include "Sprite_Base.h"
#include "Static_Game.h"
#include "Game_BattleDoll.h"

// �X�v���C�g�̊�ʒu�����߂�萔

// �X�v���C�g�̕��ƍ���
#define	SPRITE_BATTLEDOLL_WIDTH		150
#define SPRITE_BATTLEDOLL_HEIGHT	200
// 0�Ԗڂ̃X�v���C�g�̈ʒu
#define SPRITE_BATTLEDOLL_IX		300
#define SPRITE_BATTLEDOLL_IY		(WND_HEIGHT - SPRITE_BATTLEDOLL_HEIGHT - 20)
// 1�Ԗڈȍ~�̃X�v���C�g�̈ʒu�̂���
#define SPRITE_BATTLEDOLL_DX		160
#define SPRITE_BATTLEDOLL_DY		0

// �o�g���V�[���ɂ����Đl�`��̂�\������X�v���C�g�B
// �퓬�V�[���ɂ����Đl�`��̂��Q�Ƃ���B
// ����̐l�`����ɎQ�Ƃ���킯�ł͂Ȃ��A
// �퓬�ɂ��������Ɋ�Â��ē���ւ�������x�ɎQ�Ƃ�ς���B
class Sprite_BattleDoll : public Sprite_Base{
protected:
	// �ʒu�̃C���f�b�N�X�B
	WORD						position;
	// �l�`�ւ̎Q�ƁB
	Game_BattleDoll*			pDoll;
	// �l�`�ւ̎Q�Ƃ��s���Ă��邩�B
	// (�l�`��3�̈ȉ��̏ꍇ�͎Q�Ƃ��Ȃ����Ƃ����肤��)
	bool						enabled;
public:
	// �R���X�g���N�^
	Sprite_BattleDoll();
	// �ʒu�̃C���f�b�N�X��n��
	// ���̒l�͈�x�ݒ肵����ς��Ȃ��B
	void SetPosition(WORD i){
		position = i; 
		SetPos(
			SPRITE_BATTLEDOLL_IX + SPRITE_BATTLEDOLL_DX*i,
			SPRITE_BATTLEDOLL_IY + SPRITE_BATTLEDOLL_DY*i);
	};
	// �l�`�ւ̃|�C���^��n��
	void SetDollPtr(Game_BattleDoll* p){ pDoll = p; enabled = true; };
	// �|�C���^���O��
	void ResetDollPtr(){ pDoll = NULL; enabled = false; };

	// �X�V
	virtual void Update();

	// �`��
	virtual void Draw() const;

};


#endif // SPRITE_BATTLEDOLL_H

