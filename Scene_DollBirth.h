#ifndef SCENE_DOLLBIRTH_H
#define SCENE_DOLLBIRTH_H

#include "Scene_Base.h"
#include "Window_DollStatus.h"
#include "Window_EnterName.h"

// �X�e�[�g�̗�
#define SCNSTATE_DOLLBIRTH_DOLLAPPEAR		0
#define SCNSTATE_DOLLBIRTH_SHOWSTATUS		1
#define SCNSTATE_DOLLBIRTH_ENTERNAME		2

// �A�j���[�V�����̗�
#define SCNANIME_DOLLBIRTH_DOLLAPPEAR					1
#define SCNANIME_DOLLBIRTH_DOLLAPPEAR_TIME			120


class Scene_DollBirth : public Scene_Base{
public:
	Window_DollStatus		w_status;
	Window_EnterName		w_name;
private:
public:
	// �R���X�g���N�^
	Scene_DollBirth();
	// ����������
	virtual bool Initialize(bool fSkipFrame);
	bool InitWindow();
	// �I������
	virtual bool Terminate();
	
	// �X�V����
	virtual int Update();
	// �`�揈��
	virtual void Draw() const;
};

#endif // SCENE_DOLLBIRTH_H