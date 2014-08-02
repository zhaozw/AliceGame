#ifndef SPRITE_BATTLEDOLL_H
#define SPRITE_BATTLEDOLL_H

#include <Windows.h>

#include "Sprite_Base.h"
#include "Static_Game.h"
#include "Game_BattleDoll.h"
#include "Func_MyGraphic.h"

// �X�v���C�g�̊�ʒu�����߂�萔

// �X�v���C�g�̕��ƍ���
#define	SPRITE_BATTLEDOLL_WIDTH		150
#define SPRITE_BATTLEDOLL_HEIGHT	200
// �`��X�N���[���̗]���̑傫��
#define SPRITE_BATTLEDOLL_MARGIN	50
// �`��X�N���[���̕��ƍ���
#define	SPRITE_BATTLEDOLL_SCREENWIDTH	(WIDTH_DOLLILLUST+SPRITE_BATTLEDOLL_MARGIN*2)
#define SPRITE_BATTLEDOLL_SCREENHEIGHT	(HEIGHT_DOLLILLUST+SPRITE_BATTLEDOLL_MARGIN*2)
// �`�掞�̊g��{��
#define SPRITE_BATTLEDOLL_DRAWWIDTH		240
// ����
#define SP_B_DW	SPRITE_BATTLEDOLL_DRAWWIDTH
#define SP_B_SW	SPRITE_BATTLEDOLL_SCREENWIDTH
#define SP_B_SH	SPRITE_BATTLEDOLL_SCREENHEIGHT
// �`�掞�̊g��{��
#define SPRITE_BATTLEDOLL_DRAWHEIGHT	(SP_B_DW*SP_B_SH/SP_B_SW)
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
	// �`��p�̃X�N���[���̃n���h���B
	int							drawScreen;
public:
	// �R���X�g���N�^
	Sprite_BattleDoll();
	// 
	// �ʒu�̃C���f�b�N�X��n��
	// ���̒l�͈�x�ݒ肵����ς��Ȃ��B
	void SetPosition(WORD i){
		position = i; 
		SetPos(
			SPRITE_BATTLEDOLL_IX + SPRITE_BATTLEDOLL_DX*i,
			SPRITE_BATTLEDOLL_IY + SPRITE_BATTLEDOLL_DY*i);
	};
	// �l�`�ւ̃|�C���^��n��
	void SetDollPtr(Game_BattleDoll* p){ pDoll = p; enabled = (p!=NULL); };
	// �l�`�ւ̃|�C���^��Ԃ�
	Game_BattleDoll*  GetDollPtr(){ return (enabled ? pDoll : NULL); };
	// �|�C���^���O��
	void ResetDollPtr(){ pDoll = NULL; enabled = false; };
	// �`��p�X�N���[�����쐬����B
	bool SetupDrawScreen();
	// �X�V
	virtual void Update();

	// �`��
	virtual void Draw() const;
	void DrawFrame() const;
	void DrawDoll() const;
	void DrawInfo() const;

	// �A�N�Z�T
	int	GetDollX() const{ return (GetX()+SPRITE_BATTLEDOLL_WIDTH/2); };
	int	GetDollY() const{ return (GetY()+SPRITE_BATTLEDOLL_HEIGHT/2+20); };
	
	// ���̃N���X����X�v���C�g�̈ʒu��m�肽���ꍇ
	static int GetSpriteX(int n){ return SPRITE_BATTLEDOLL_IX+n*SPRITE_BATTLEDOLL_DX; };

};


#endif // SPRITE_BATTLEDOLL_H

