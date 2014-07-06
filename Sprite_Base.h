#ifndef SPRITE_BASE_H
#define SPRITE_BASE_H

// ��ɐ퓬��ʂ̃X�v���C�g��\������N���X�B
 
#define		ANIME_NONE				0
#define		ANIME_TIME_NONE			9999
#define		ANIME_SKIPTIME_NONE		9999

class Sprite_Base{
public:
	enum SPRITESTATE{
		IDLE,				// �X�V����Ă��Ȃ����
		ANIME_NOT_SKIP,		// �A�j���[�V�������A�X�L�b�v�s��
		ANIME_SKIP,			// �A�j���[�V�������A�X�L�b�v�\
		UNDIFINED,			// �G���[��
	};
protected:
	// �`��̊�{�ʒu
	float	ix, iy;
	// �ꎞ�I�ȕ`��ʒu�̂���
	float	dx, dy;
	// �X�v���C�g�̑傫��
	int		width, height;
	// �`��p�x
	float	angle; 
	// �`��{��
	float	exRate;
	// �\��/��\��
	bool	visible;
	// �A�j���[�V������ID�B
	int		animeID;
	// �A�j���[�V�����̌��݂̃t���[����
	int		animeCount;
	// �A�j���[�V�������I������t���[����
	int		animeTime;
	// �A�j���[�V�������X�L�b�v�\�ɂȂ�t���[����
	int		animeSkipTime;
	// ���݂̏��
	SPRITESTATE state;
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

	// �`��
	virtual void Draw() const{};

	// �A�N�Z�T
	float GetX() const{ return ix+dx; };
	float GetY() const{ return iy+dy; };
	float GetIX() const{ return ix; };
	float GetIY() const{ return iy; };
	float GetDX() const{ return dx; };
	float GetDY() const{ return dy; };
	int	GetWidth() const{ return width; };
	int	GetHeight() const{ return height; };
	void SetIX(float x){ ix = x; }; 
	void SetIY(float y){ ix = y; }; 
	void SetDX(float x){ dx = x; }; 
	void SetDY(float y){ dy = y; }; 
	bool GetVisible(){ return visible; };
	void SetVisible(bool v){ visible = v; };


};


#endif // SPRITE_BASE_H