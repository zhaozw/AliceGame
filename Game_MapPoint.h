#ifndef GAME_MAPPOINT_H
#define GAME_MAPPOINT_H

#include <Windows.h>
#include "Static_Map.h"

// �}�b�v��̃|�C���g���\���N���X�B
// �퓬�|�C���g��A�C�e���|�C���g�Ȃǂ̑��������B
// Scene_Map���ɂ����ă��X�g�����B
// �Ȃ��A�}�b�v��ɂ͓����\������邪�A
// ���̓|�C���g���玩���v�Z�����B
// �ǂ̕����L�[����������ǂ̃|�C���g�Ԃ��ړ�����̂���
// ���߂邽�߁A�}�b�v�|�C���g���m�͑��݂ɎQ�Ƃ���B

class Game_MapPoint{
	// �|�C���g��ID�B
	// ���X�g�̒����猟������̂ɕK�v�B
	// 0�͎g�p����Ă��Ȃ����Ƃ������A1����n�܂�B
	WORD			id;
	// �}�b�v��̃|�C���g�̑����B
	// �萔MAPPOINT_XXX�̒l�����B
	WORD			type;
	// �|�C���g�̎��p�����[�^�B
	// �ėp�I�ɗp����B
	int				param;
	// �e�����ɂȂ����Ă���|�C���g��ID�B
	// ��(�k)�E�E(��)�E��(��)�E��(��)�̏��B
	WORD			pointID[4];	
	// �e�����ɂȂ����Ă��铹��ID�B
	// ��(�k)�E�E(��)�E��(��)�E��(��)�̏��B
	WORD			pathID[4];
	// �}�b�v��̍��W�̈ʒu�B
	// ���̂܂܉�ʏ�̃|�C���g��\���B
	// ��ʂ̃X�N���[���͑z�肵�Ȃ��B
	int				posX;
	int				posY;
	// �|�C���g�̊J����ԁB
	// �萔 MAPSTATE_XXX�̒l�����B
	WORD			state;

public:
	// �R���X�g���N�^
	Game_MapPoint();
	
	// �A�N�Z�T
	int				GetPosX(){ return posX; };
	int				GetPosY(){ return posY;	};
	void			SetPosX(int x){ posX = x; };
	void			SetPosY(int y){ posY = y; };
	void			SetPos(int x, int y){ SetPosX(x); SetPosY(y); };
	// ���ڈʒu�ł͂Ȃ��O���b�h�Ŏw��
	// �|�C���g�����ꂢ�ɕ��ׂ�������
	void			SetGridX(int gridX){ posX = MAPGRID_INI_X + MAPGRID_DLT_X*gridX; };
	void			SetGridY(int gridY){ posY = MAPGRID_INI_Y + MAPGRID_DLT_Y*gridY; };
	void			SetGrid(int gridX, int gridY){ SetGridX(gridX); SetGridY(gridY); };


	// �e�����̃|�C���g��ID��Ԃ��B
	// 0�͂Ȃ����Ă��Ȃ����Ƃ������B
	WORD			GetNorthPoint(){ return pointID[0]; };
	WORD			GetEastPoint(){ return pointID[1]; };
	WORD			GetSouthPoint(){ return pointID[2]; };
	WORD			GetWestPoint(){ return pointID[3]; };

	// �e�����̓���ID��Ԃ��B
	// 0�͂Ȃ����Ă��Ȃ����Ƃ������B
	WORD			GetNorthPath(){ return pathID[0]; };
	WORD			GetEastPath(){ return pathID[1]; };
	WORD			GetSouthPath(){ return pathID[2]; };
	WORD			GetWestPath(){ return pathID[3]; };

	// ���W�𒼐ڎw��ł͂Ȃ��O���b�h�Ŏw�肷��B
	// 

	// �}�b�v���N���A�������Ɏ��s�����֐��B
	void			Clear();

	// �}�b�v�̃|�C���g�̕`����s���B
	void			Draw() const;

};

// �}�b�v��̓����\���N���X�B
// �f�[�^�Ƃ��Ă͕ۑ�����Ȃ����A
// �֗��̂���Scene_Map���Ń��X�g�Ƃ��č쐬�����B

class Game_MapPath{
protected:
	// ����ID
	int				id;

public:
	// �R���X�g���N�^
	Game_MapPath();

	// �}�b�v�̃|�C���g�̕`����s���B
	void			Draw() const;
};

#endif // GAME_MAPPOINT_H