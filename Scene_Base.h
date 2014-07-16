#ifndef SCENE_BASE_H
#define SCENE_BASE_H

#include "Static_Game.h"
#include "Config.h"
#include "DxLib.h"
#include "DXTimeCtrl.h"
#include "DXInput.h"

#define SCNANIME_NONE	0

//////////////////////////////////////////////////
// Scene_Base�N���X
// �S�ẴQ�[���V�[���̌��ɂȂ�N���X�B
// ��{�I�ɏ�����(Initialize), ���s(Play), �I������(Terminate)��3�̊֐��������A
// �߂�l�Ŏ��̃V�[���𔻒肷��B
class Scene_Base{
protected:
	// ���̃V�[���̗\��B
	// ���̎��Ԍ�ɃV�[���̐؂�ւ����s���ꍇ�Ȃǂɗp����B
	int reservedScene;
	// ���̃V�[���̗\�񂪍s���Ă���̃J�E���g�B
	// �t�F�[�h�ȂǂɎg�p����B
	int reservedCount;
	int reservedCount_max;
	// �V�[���Ń��[�v���邲�Ƃɑ�����J�E���^�B
	int sceneTime;
	// ���Ԑ�����s�Ȃ�
	DXTimeCtrl timectrl;
	// ���̃t���[�����X�L�b�v����t���O
	bool fDrawSkip;
	// �V�[���̏�Ԃ�ێ����Ă���
	int state;
	int stateTime;
private:
	// �A�j���[�V�����̏�Ԃ�ێ����Ă���
	int	anime;
	int animeCount;
	int animeTime;
public:
	// �R���X�g���N�^
	Scene_Base();
	// �f�X�g���N�^
	virtual ~Scene_Base(){};
	// ����������
	// fSkipFrame : ���������ł͂Ȃ��R�}���������邩�ǂ���
	virtual bool Initialize(bool fSkipFrame);
	// ���s���� (Input, Update, Draw����Ȃ�A�e�V�[������)
	int Play();
	// �I������
	virtual bool Terminate();
	
	// ���͏��� (�e�V�[������)
	bool Input();
	// �v�Z����
	virtual int Update()=0;
	// �`�揈��
	virtual void Draw() const =0;
	
	// ���V�[���̗\��
	void ReserveScene(int sceneID, int count=1){
		if(reservedCount_max == 0){
			reservedScene = sceneID;
			reservedCount = 0;
			reservedCount_max = count;
		}
	}

	// ���̃V�[�����\�񂳂�Ă��邩
	bool SceneIsReserved(){
		return reservedScene != SCENE_NONE;
	}

	// �\�����
	void UnlockReservedScene(){
		reservedScene = SCENE_NONE;
		reservedCount = 0;
		reservedCount_max = 0;
	}
	
	// �t�F�[�h�ȂǂɎg�p
	float GetFadeRate() const{
		return (float)reservedCount/reservedCount_max;
	}

	// ReserveScene�ɕ����ăt�F�[�h�A�E�g����
	void DrawReserveFade(int color=0) const;

	// ���̃t���[�����X�L�b�v���邩�ۂ�
	void SetDrawSkip(bool f=true);

	// �V�[���̏�Ԃ�ύX����
	void SetState(int s){ state = s; stateTime = 0; };
	int GetState(){ return state; };

	// �A�j���̏�Ԃ�ύX����
	void SetAnime(int a, int time){ anime = a; animeTime = time; animeCount = 0; };
	void UpdateAnime(){
		if(animeTime < 0) animeTime = 0;
		if(anime != SCNANIME_NONE){
			animeCount++;
			if(animeCount>=animeTime){ 
				// �A�j���[�V�����̃u����h������
				// animeCount, animeTime�̃��Z�b�g�͍s��Ȃ�
				anime = SCNANIME_NONE;
			}
		}
	};
	// �A�N�Z�T
	int GetAnimeCount() const{ return animeCount; };
	int GetAnimeTime() const{ return animeTime; };
	int GetAnimeEnded(){ return anime == SCNANIME_NONE; };
};

#endif // SCENE_BASE_H