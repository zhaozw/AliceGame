#ifndef IMAGE_H
#define IMAGE_H

// �����摜�̑傫��
#define IMAGE_SIZE_NUMBER			13	// �����摜�̔z��̑傫��
#define IMAGE_SIZE_COLUMN_NUMBER	4	// �����摜�̔z��̉�
#define IMAGE_SIZE_ROW_NUMBER		3	// �����摜�̔z��̏c
#define NUMBER_I_WIDTH				16
#define NUMBER_I_HEIGHT				24
#define IMAGE_SIZE_STATEICON		24

#include "WindowSkin.h"
#include "Static_AliceDoll.h"

//==================================================
// Image�N���X
// 
// �摜�̃n���h�����܂Ƃ߂ĕێ�����O���[�o���ϐ��B
// �O���[�o���ϐ�g_image����Q�Ƃ����B
// 

// �E�B���h�E�Ɋւ���摜��ێ�����B
typedef struct Image_Window{
	int image; // �E�B���h�E�̃_�~�[�摜
	int simple[MAX_WNDIMGINDEX];
}IMAGE_WINDOW;

// �����Ɋւ���摜��ێ�����B
typedef struct Image_Chars{
	int dummy_number_i;
	int number_i[IMAGE_SIZE_NUMBER];
}IMAGE_CHARS;

// �C���X�g�Ɋւ���摜��ێ�����B
typedef struct Image_Illust{
	int doll_group[DOLL_TYPE_MAX];
	int doll[DOLL_TYPE_MAX][DOLL_ATTR_NUM];
	int doll_dummy[2];
}IMAGE_ILLUST;

// �G�L�����̉摜��ێ�����B
typedef struct Image_Enemy{
	int	elf;
	int fairy[DOLL_ATTR_NUM];
	int snail[DOLL_ATTR_NUM];
	int butterfly[DOLL_ATTR_NUM];
	int rat[DOLL_ATTR_NUM];
	int crow[DOLL_ATTR_NUM];
	int slime[DOLL_ATTR_NUM];
	int flower[DOLL_ATTR_NUM];
	int skeleton[DOLL_ATTR_NUM];
	int harpy[DOLL_ATTR_NUM];
	int bird[DOLL_ATTR_NUM];
	int parrot[DOLL_ATTR_NUM];
	int cardinal;
	Image_Enemy(){
		elf = -1;
		for(int n=0; n<DOLL_ATTR_NUM; n++){
			fairy[n] = -1;
			snail[n] = -1;
			butterfly[n] = -1;
			rat[n] = -1;
			crow[n] = -1;
			slime[n] = -1;
			flower[n] = -1;
			skeleton[n] = -1;
			harpy[n] = -1;
			bird[n] = -1;
			parrot[n] = -1;
		}
		cardinal = -1;
	}
}IMAGE_ENEMY;


// �e��A�C�R���n�̉摜��ێ�����B
typedef struct Image_Icon{
	int doll_group[DOLL_TYPE_MAX];
	int doll[DOLL_TYPE_MAX][DOLL_FACE_NUM][DOLL_ATTR_NUM];
	int attrstone_group;
	int attrstone[DOLL_GROUP_NUM][DOLL_ATTR_NUM];
	int state_group;
	int	state[64];
	int attr_graph;
}IMAGE_ICON_; // IMAGE_ICON���Ƒg�ݍ��݂̒萔�Ƃ��Ԃ�̂�

// �e��w�i�n�i��ʑS�́j�̉摜��ێ�����B
typedef struct Image_BG{
}IMAGE_BG;

// �G�t�F�N�g�i�p�[�e�B�N���j�̉摜��ێ�����B
typedef struct Image_Effect{
}IMAGE_EFFECT;

class Image{
public: 
	IMAGE_WINDOW	window;
	IMAGE_CHARS		chars;
	IMAGE_ILLUST	illust;
	IMAGE_ENEMY		enemy;
	IMAGE_ICON_		icon;
	IMAGE_BG		bg;
	IMAGE_EFFECT	effect;
public:
	// �R���X�g���N�^�B
	// �S�Ẵn���h����-1��������B
	Image();

	// ���[�h�B
	// ���s������false��Ԃ��B
	bool Load();

	// �E�B���h�E�X�L���̃��[�h�B
	bool Load_WndSkin();

	// �����̃��[�h�B
	bool Load_Chars();

	// �C���X�g�̃��[�h�B
	bool Load_Illust();

	// �G�L�����̃��[�h�B
	bool Load_Enemy();

	// �w�i�摜�̃��[�h�B
	bool Load_BG();

	// �A�C�R���̃��[�h�B
	bool Load_Icon();

	// �G�t�F�N�g�摜�̃��[�h�B
	bool Load_Effect();

	

};


#endif // IMAGE_H