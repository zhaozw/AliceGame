#ifndef SCENE_MAP_H
#define SCENE_MAP_H

#include "Scene_Base.h"
#include "Game_MapPoint.h"
#include "VectorList.h"

class Scene_Map : public Scene_Base{
protected:
	// �}�b�vID�B
	// Game_Temp���ɕێ����ꂽ�l��
	// ���������ɓǂݍ��݁A
	// ��������Ƀ}�b�v�̃��[�h�Ȃǂ��s���B
	int								id;

	// �|�C���g�̃��X�g�B
	// �t�@�C������ǂݍ��܂��B
	VectorList<Game_MapPoint>		pointList;

	// ���̃��X�g�B
	// �|�C���g�̃��X�g�����ɍ쐬�����B
	VectorList<Game_MapPath>		pathList;
public:
	// �R���X�g���N�^
	Scene_Map();
	// ����������
	virtual bool Initialize(bool fSkipFrame);
	bool InitWindow();
	// �I������
	virtual bool Terminate();
	
	// �X�V����
	virtual int Update();
	// �`�揈��
	virtual void Draw() const;

	// �t�@�C������}�b�v��ǂݍ��ށB
	// �t�@�C������id�l���玩���I�Ɍv�Z�����B
	bool Load();
};


#endif // SCENE_MAP_H


