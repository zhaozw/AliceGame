#ifndef WINDOW_BATTLEMESSAGE_H
#define WINDOW_BATTLEMESSAGE_H

#include "Window_Message.h"

// �E�B���h�E�\���֘A�̒萔
#define WND_BATTLEMSG_X				0
#define WND_BATTLEMSG_Y				0
#define WND_BATTLEMSG_WIDTH			(WND_WIDTH)
#define WND_BATTLEMSG_HEIGHT		128
#define WND_BATTLEMSG_PX			16
#define WND_BATTLEMSG_PY			16

// �e�L�X�g�ړ��̃A�j���[�V�����ɗv���鎞��
#define WND_BATTLEMSG_MOVETIME		8

class Scene_Battle;

class Window_BattleMessage : public Window_Message{
private:
	// �e�ƂȂ�V�[��
	Scene_Battle*	pParent;
public:
	// �R���X�g���N�^
	Window_BattleMessage();
	// ������
	void Setup(Scene_Battle* _pParent);
	// ���e�̕`����s���B
	// Window_Message�N���X���炳��ɔh���A�Ǝ��̕`����s���B
	virtual void DrawContent() const;
	// SceneBattle�N���X�̎w��
	void SetParent(Scene_Battle* p){ pParent = p; };
	// �N���X���Ǝ��̃A�b�v�f�[�g�֐�
	virtual void ExUpdate();
	// �N���X���Ǝ���IDLE��Ԕ���֐�
	virtual bool CheckIsIdle();
	// ���̃��b�Z�[�W���󂯓���鏀�����o���Ă��邩
	bool IsReady();
};

#endif // WINDOW_BATTLEMESSAGE