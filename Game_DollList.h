#ifndef GAME_DOLLLIST_H
#define GAME_DOLLLIST_H

#include "FlexList.h"
#include "Game_AliceDoll.h"

// �������Ă���l�`�̃��X�g�������N���X�B
// �O���[�o���ϐ�g_dollList����Q�Ƃ����B

class Game_DollList{
private:
	FlexList<Game_AliceDoll_Essence>	list;
	
public:
	// �R���X�g���N�^
	Game_DollList();
	// �h�[�����X�g�Ȃǃ|�C���^�̉�����s��
	bool Release();
};

#endif // GAME_DOLLLIST_H