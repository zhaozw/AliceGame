// Image.cpp

#include <Windows.h>
#include "Image.h"
#include "DxLib.h"
#include "WindowSkin.h"
#include "Func_MyGraphic.h"

Image::Image(){
}

bool Image::Load(){
	if(!Load_WndSkin()){	// �E�B���h�E�X�L��
		return false;
	}
	if(!Load_Chars()){		// �����n
		return false;
	}
	if(!Load_Illust()){		// �C���X�g
		return false;
	}
	if(!Load_Enemy()){		// �G�L����
		return false;
	}
	if(!Load_BG()){			// �w�i
		return false;
	}
	if(!Load_Icon()){		// �A�C�R���E�h�b�g�G
		return false;
	}
	if(!Load_Effect()){		// �G�t�F�N�g
		return false;
	}
	return true;
}


bool Image::Load_WndSkin(){
	// �E�B���h�E�摜�̓ǂݍ���
	window.image = LoadGraph(_T("sysimg\\Window.png"), 1);
	// �E�B���h�E�X�L���摜�ւ̊��蓖��

	// �E�B���h�E�g�̃T�C�Y�A���S���̕��ƍ���
	int frameSize=0, faceWidth=0, faceHeight=0;
	int cntX=0, cntY=0;
	int* pWndImg=NULL; // �E�B���h�E�摜�̔z��ւ̃|�C���^
	int parentImg = 0;

	// �ʏ�^�C�v�̃E�B���h�E�̓ǂݍ���
	// �����̃E�B���h�E�ɂ��ċ��ʂœǂݍ��߂�\�L�@�ł̕\�L
	for(int n=0; n<1; n++){
		// �ʏ�^�C�v�̃E�B���h�E�̐������J��Ԃ�
		switch(n){
		case WNDSKIN_SIMPLE:
			// �V���v���E�B���h�E
			pWndImg = window.simple;
			parentImg = window.image;
			cntX = 0; cntY = 0;
			frameSize = 16;
			faceWidth = 32;
			faceHeight = 32;
			break;
		default:
			break;
		}

		// �������狤�ʕ���
		// ����
		pWndImg[WNDIMGINDEX_TOPLEFT] = DerivationGraph(
			cntX, cntY, frameSize, frameSize, parentImg);
		// ��
		pWndImg[WNDIMGINDEX_TOP] = DerivationGraph(
			cntX+frameSize, cntY, faceWidth, frameSize, parentImg);
		// �E��
		pWndImg[WNDIMGINDEX_TOPRIGHT] = DerivationGraph(
			cntX+frameSize+faceWidth, cntY, frameSize, frameSize, parentImg);
		// ��
		pWndImg[WNDIMGINDEX_LEFT] = DerivationGraph(
			cntX, cntY+frameSize, frameSize, faceHeight, parentImg);
		// ����
		pWndImg[WNDIMGINDEX_CENTER] = DerivationGraph(
			cntX+frameSize, cntY+frameSize, faceWidth, faceHeight, parentImg);
		// �E
		pWndImg[WNDIMGINDEX_RIGHT] = DerivationGraph(
			cntX+frameSize+faceWidth, cntY+frameSize, frameSize, faceHeight, parentImg);
		// ����
		pWndImg[WNDIMGINDEX_BOTTOMLEFT] = DerivationGraph(
			cntX, cntY+frameSize+faceHeight, frameSize, frameSize, parentImg);
		// ��
		pWndImg[WNDIMGINDEX_BOTTOM] = DerivationGraph(
			cntX+frameSize, cntY+frameSize+faceHeight,
			faceWidth, frameSize, parentImg);
		// �E��
		pWndImg[WNDIMGINDEX_BOTTOMRIGHT] = DerivationGraph(
			cntX+frameSize+faceWidth, cntY+frameSize+faceHeight,
			frameSize, frameSize, parentImg);
	}

	return true;
}

bool Image::Load_Chars(){
	int srcX = 0, srcY = 0;		// DerivationGraph���̊�ʒu
	int width=0, height=0;		// DerivationGraph���̕��ƍ���
	int hImage;					// DerivationGraph���̃n���h��

	chars.dummy_number_i = LoadGraph(_T("sysimg\\number_i.png"));

	// �����摜�𓯂��t�H�[�}�b�g�œǂݍ���
	for(int n=0; n<1; n++){
		switch(n){
		case 0:
			// number_i
			srcX = 0;
			srcY = 0;
			width = NUMBER_I_WIDTH;
			height = NUMBER_I_HEIGHT;
			hImage = chars.dummy_number_i;
			break;
		}

		// ���[�v�ǂݍ��ݕ���
		for(int w=0; w<IMAGE_SIZE_COLUMN_NUMBER; w++){
			for(int h=0; h<IMAGE_SIZE_ROW_NUMBER; h++){
				if(w!=(IMAGE_SIZE_COLUMN_NUMBER-1) || h!=(IMAGE_SIZE_ROW_NUMBER-1)){
					chars.number_i[w+h*IMAGE_SIZE_COLUMN_NUMBER]
						= DerivationGraph(
							srcX+w*width,
							srcY+h*height,
							width, height, hImage);
				}else{
					for(int i=0; i<2; i++){
						chars.number_i[w+h*IMAGE_SIZE_COLUMN_NUMBER+i]
							= DerivationGraph(
								srcX+w*width+i*width/2,
								srcY+h*height,
								width/2, height, hImage);
					}
				}
			}
		}
	}
	return true;
}


bool Image::Load_Illust(){
	TCHAR fileName[MAX_PATH];

	// �l�`�C���X�g�̓ǂݍ���
	for(int t=0; t<DOLL_TYPE_MAX; t++){
		sprintf_s(fileName, MAX_PATH-1, _T("img\\illust_doll%02d.png"), t+1);
		if((illust.doll_group[t] = LoadGraph(fileName, 1)) == -1){
			return false;
		}
		for(int h=0; h<2; h++){
			for(int w=0; w<2; w++){
				illust.doll[t][w+h*2] = DerivationGraph(
					WIDTH_DOLLILLUST*w, HEIGHT_DOLLILLUST*h,
					WIDTH_DOLLILLUST, HEIGHT_DOLLILLUST, illust.doll_group[t]);
			}
		}
	}

	// �_�~�[�l�`�C���X�g�̓ǂݍ���
	LoadDivGraph(_T("img\\doll_dummy.png"), 2, 2, 1, 512, 512, illust.doll_dummy);

	return true;
}

bool Image::Load_Enemy(){
	enemy.elf = LoadGraph(_T("img_enemy\\Elf.png"));
	if(enemy.elf == -1) return false;
	// �d��
	if(LoadDivGraph(_T("img_enemy\\Fairy.png"),
		4, 4, 1, 120, 120, enemy.fairy) != 0) return false;
	// �J�^�c����
	if(LoadDivGraph(_T("img_enemy\\Snail.png"),
		4, 2, 2, 120, 80, enemy.snail) != 0) return false;
	// ��
	if(LoadDivGraph(_T("img_enemy\\Butterfly.png"),
		4, 1, 4, 240, 80, enemy.butterfly) != 0) return false;
	// �l�Y�~
	if(LoadDivGraph(_T("img_enemy\\Rat.png"),
		4, 2, 2, 150, 100, enemy.rat) != 0) return false;
	// �J���X
	if(LoadDivGraph(_T("img_enemy\\Crow.png"),
		4, 2, 2, 150, 100, enemy.crow) != 0) return false;
	// �X���C��
	if(LoadDivGraph(_T("img_enemy\\Slime.png"),
		4, 2, 2, 100, 50, enemy.slime) != 0) return false;
	// ��
	if(LoadDivGraph(_T("img_enemy\\Flower.png"),
		4, 2, 2, 130, 130, enemy.flower) != 0) return false;
	// �X�P���g��
	if(LoadDivGraph(_T("img_enemy\\Skeleton.png"),
		4, 2, 2, 160, 240, enemy.skeleton) != 0) return false;
	// �n�[�s�[
	if(LoadDivGraph(_T("img_enemy\\Harpy.png"),
		4, 2, 2, 220, 280, enemy.harpy) != 0) return false;
	// ��
	if(LoadDivGraph(_T("img_enemy\\Bird.png"),
		4, 2, 2, 100, 100, enemy.bird) != 0) return false;
	// �I�E��
	if(LoadDivGraph(_T("img_enemy\\Parrot.png"),
		4, 2, 2, 240, 240, enemy.parrot) != 0) return false;
	// �l�N���}���T�[
	enemy.cardinal = LoadGraph(_T("img_enemy\\Cardinal.png"));
	if(enemy.cardinal == -1) return false;
	return true;
}

bool Image::Load_BG(){
	return true;
}

bool Image::Load_Icon(){
	TCHAR fileName[MAX_PATH];

	// �l�`�A�C�R���̓ǂݍ���
	for(int t=0; t<DOLL_TYPE_MAX; t++){
		sprintf_s(fileName, MAX_PATH-1, _T("img_illust\\doll%02d_icon.png"), t+1);
		if((icon.doll_group[t] = LoadGraph(fileName, 1)) == -1){
			return false;
		}
		for(int h=0; h<DOLL_ATTR_NUM; h++){
			for(int w=0; w<DOLL_FACE_NUM; w++){
				// ���̂Ƃ���A�����̍����͂Ȃ�
				icon.doll[t][w][h] = DerivationGraph(
					WIDTH_DOLLICON*w, 0,
					WIDTH_DOLLICON, HEIGHT_DOLLICON, icon.doll_group[t]);
				/*
				icon.doll[t][w][h] = DerivationGraph(
					WIDTH_DOLLICON*w, HEIGHT_DOLLICON*h,
					WIDTH_DOLLICON, HEIGHT_DOLLICON, icon.doll_group[t]);
					*/
			}
		}
	}

	// �����A�C�R���̓ǂݍ���
	icon.attrstone_group = LoadGraph(_T("img\\attr_stone.png"));
	for(int h=0; h<DOLL_GROUP_NUM; h++){
		for(int w=0; w<DOLL_ATTR_NUM; w++){
			icon.attrstone[w][h] = DerivationGraph(
				SIZE_ATTRSTONE*w, SIZE_ATTRSTONE*h,
				SIZE_ATTRSTONE, SIZE_ATTRSTONE, icon.attrstone_group);
		}
	}

	// �X�e�[�g�A�C�R���̓ǂݍ���
	icon.state_group = LoadGraph(_T("img\\state_icon.png"));
	for(int h=0; h<4; h++){
		for(int w=0; w<8; w++){
			icon.state[w+h*8] = DerivationGraph(
				IMAGE_SIZE_STATEICON*w, IMAGE_SIZE_STATEICON*h,
				IMAGE_SIZE_STATEICON, IMAGE_SIZE_STATEICON, icon.state_group);
		}
	}

	// �����֌W�摜�̓ǂݍ���
	icon.attr_graph = LoadGraph(_T("img\\attr_graph.png"));

	return true;
}

bool Image::Load_Effect(){
	return true;
}
