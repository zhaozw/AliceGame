#ifndef SPRITE_BASE_H
#define SPRITE_BASE_H

#include <Windows.h>

// ��ɐ퓬��ʂ̃X�v���C�g��\������N���X�B
 
// morphID�Ɏw�肳���萔�Q
// ����Ȃ��B�����I�������͎����I�ɂ���ɂȂ�B
#define		SPMORPH_NONE			0
// ���ł���B
// ���̃A�N�V�����̏I����Avisible�l��false�ɂȂ�B
#define		SPMORPH_DISAPPEAR		1
// �I�����ꂽ��ԂɂȂ�B
// SPMORPH_DISACTIVATE�ƃZ�b�g�Ŏg���B
#define		SPMORPH_ACTIVATE		2
// �I����Ԃ���������B
// SPMORPH_ACTIVATE�̌�Ŏ��s����B
#define		SPMORPH_DISACTIVATE		3
// ��x�����_�ł���B
// ���m�ɂ́A���̏�ԂɂȂ����u�Ԉ������A���̌�܂��o�Ă���B
// param�l = ������t���[����
#define		SPMORPH_BLINK			4
// ��x�����_�ł���B
// ���m�ɂ́A���̏�ԂɂȂ����u�Ԉ������A���̌�܂��o�Ă���B
// param�l = ������t���[����
#define		SPMORPH_DAMAGE_DOLL		5


// param.effect�Ɏw�肳���萔�Q
#define		SPEFFECT_NONE			0

// �X�v���C�g�̍l����
// �X�v���C�g�����������]�����肷��摜�̔B
// �X�v���C�g��SpriteParam�Ƃ����\���̂������Ă��āA
// �����Ɋg��{�����]�p�̏�񂪕ێ�����Ă���B
// ����u�Ԃ��ƂɁASpriteParam�������Ă���p�����[�^�ɏ]����
// �`����s���B���ۂ̕`��͔h���N���X�ɂ���ĈقȂ�B
// 
// �X�v���C�g�́A����^�C�~���O�Łu������������������v�Ƃ���
// ���߂�^����ƁA���Ԍo�߂ɉ����ď���ɂ�����������������B
// ���Ȃ킿�ASpriteParam���X�V����A����ɂ���ĕ`�悪�ω�����B

// �X�v���C�g�̕ό`�Ȃǂ̏���\���p�����[�^�B
// 

typedef struct SpriteParam{
	// �{���̕`��ʒu����̕ψ�
	float	dx, dy;
	// ��]�p
	float	angle;
	// �B�����ۂ�(true���ƕ\�����Ȃ��B)
	// visible��true����hide��false�̏ꍇ�̂ݕ`����s���B
	// ���҂̈Ⴂ�́Ahide��morphID�ɂ���Đݒ肳��A
	// visible�͂���ȊO�̃v���O��������ݒ肳���B
	bool	hide;
	// �s�����x(0�`255, 255�ŕs����)
	int		opacity;
	// �g��{��(x�����Ay�������ꂼ��)
	float	xScale, yScale;
	// �A�j���[�V��������ꍇ�̃Z���B�g�p���Ȃ��ꍇ��0�B
	int		cell;
	// ������ʁB��������A�����ȂǁB
	// �g�p������̂����Ή�������Ηǂ��B
	BYTE	effect;
	// �ėp�p�����[�^�B
	// ���̒l�����́AmorphID�ɂ���ĕω������A
	// SetMorphID���œK�X�n�����B
	// �`��̍ۂ͂��̒l���g���Ă��悢�B
	int		param;

	// �f�t�H���g�l
	SpriteParam(){
		dx = dy = 0;
		angle = 0;
		hide = false;
		opacity = 255;
		xScale = yScale = 1.0f;
		cell = 0;
		effect = SPEFFECT_NONE;
		param = 0;
	}
}SPRITEPARAM;

class Sprite_Base{
public:
protected:
	// �`��̊�{�ʒu
	float	ix, iy;
	// ���݂̃X�v���C�g�̑傫���B
	int		width, height;
	// ���݂̃X�v���C�g�̉�]���S�B
	float	cx, cy;
	// �`��ɗv����p�����[�^
	SPRITEPARAM		param;	
	// �X�v���C�g���\����Ԃł��邩�ۂ�
	bool			visible;
	// ���ݐݒ肳��Ă���ό`���@��ID
	// SPMORPH_xx�̒萔�Q�Ŏw�肳���B
	// SPMORPH_NONE�̏ꍇ�͎��Ԃ̍X�V���s��Ȃ��B
	// ����morph�̍X�V���I���������SPMORPH_NONE�Ɏ����I�ɖ߂�B
	BYTE			morphID;
	// ���݂�morphID�̌o�ߎ��ԁB
	int				morphCount;
	// ���݂�morphID�́A�ό`���I�����鎞��
	// SetMorphID���Ɏ����œ��͂����B
	int				morphTime;
	// ���݂�morphID�́A�X�L�b�v����鎞�ԁB
	// SetMorphID���Ɏ����œ��͂����B
	int				morphSkipTime;

public:
	// �R���X�g���N�^
	Sprite_Base();
	Sprite_Base(float x, float y);
	Sprite_Base(float x, float y, int w, int h);

	// �ʒu�̎w��
	void SetPos(float x, float y){ ix = x; iy = y; };

	// �傫���̎w��
	void SetSize(int w, int h){ width = w; height = h; };

	// �X�V
	virtual void Update();
	// morphID�̒l�ɉ�����param�̒l���X�V����B
	// Update�֐��𕪊��������́B
	// Sprite_Base_Morph.cpp�ɓ��e���L�q����B
	void UpdateMorph();

	// �`��
	// �e�h���N���X�ɂ���ĈقȂ�
	virtual void Draw() const{};

	// morphID�l�̃Z�b�g
	// �K�v�Ȃ�p�����[�^���n���B
	// Sprite_Base_Morph.cpp�ɓ��e���L�q����B
	// force��true�̏ꍇ�A���݂�morph�ɑ΂��ď㏑������B
	bool SetMorphID(BYTE morph, bool force=true, int param=0);

	// morph�̉����B
	void ResetMorph();

	// ���݉摜�̕ό`�����ǂ�����Ԃ��B
	bool GetMorphing(){ return morphID != SPMORPH_NONE; };

	// �X�L�b�v�\�ȏ�Ԃ���Ԃ�
	bool GetCanSkip(){ return ((!GetMorphing()) || morphCount >= morphSkipTime); };

	// �A�N�Z�T
	void SetIX(float x){ ix = x; }; 
	void SetIY(float y){ ix = y; }; 
	void SetCX(float x){ cx = x; }; 
	void SetCY(float y){ cx = y; }; 
	void SetWidth(int w){ width = w; };
	void SetHeight(int h){ height = h; };
	void SetVisible(bool b){ visible = b; };
	float GetIX() const{ return ix; };
	float GetIY() const{ return iy; };
	float GetCX() const{ return cx; };
	float GetCY() const{ return cy; };
	int	GetWidth() const{ return width; };
	int	GetHeight() const{ return height; };
	bool GetVisible() const{ return visible; };

protected:
	// �p�����[�^�͊�{�I�ɊO������A�N�Z�X�o���Ȃ�
	float GetX() const{ return ix+param.dx; };
	float GetY() const{ return iy+param.dy; };
	float GetDX() const{ return param.dx; };
	float GetDY() const{ return param.dy; };
	float GetAngle() const{ return param.angle; };
	bool GetHide() const{ return param.hide; };
	int	GetMorphCount() const{ return morphCount; };
	int GetMorphTime() const{ return morphTime; };
	float GetMorphRate() const{ return (float)morphCount/morphTime; };
	float GetMorphRestRate() const{ return (1.0f - GetMorphRate()); };



};


#endif // SPRITE_BASE_H