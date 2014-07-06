#ifndef SCENE_SAMPLE_H
#define SCENE_SAMPLE_H

#include "Scene_Base.h"

#include "Player_Sample.h"

#define PHAZE_UNKNOWN 0
#define PHAZE_WAITKEY 1
#define PHAZE_ENTERNAME 2

class Scene_Sample : public Scene_Base{
public:
	Player_Sample player;

private:

public:
	// �R���X�g���N�^
	Scene_Sample();
	// ����������
	virtual bool Initialize(bool fSkipFrame);
	// �I������
	virtual bool Terminate();
	
	// �X�V����
	virtual int Update();
	// �`�揈��
	virtual void Draw();

};

#endif // SCENESAMPLE_H