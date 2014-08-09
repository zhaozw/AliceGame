// Image.cpp

#include <Windows.h>
#include "Image.h"
#include "DxLib.h"
#include "WindowSkin.h"
#include "Func_MyGraphic.h"

Image::Image(){
}

bool Image::Load(){
	if(!Load_WndSkin()){	// ウィンドウスキン
		return false;
	}
	if(!Load_Chars()){		// 文字系
		return false;
	}
	if(!Load_Illust()){		// イラスト
		return false;
	}
	if(!Load_Enemy()){		// 敵キャラ
		return false;
	}
	if(!Load_BG()){			// 背景
		return false;
	}
	if(!Load_Icon()){		// アイコン・ドット絵
		return false;
	}
	if(!Load_Effect()){		// エフェクト
		return false;
	}
	return true;
}


bool Image::Load_WndSkin(){
	// ウィンドウ画像の読み込み
	window.image = LoadGraph(_T("sysimg\\Window.png"), 1);
	// ウィンドウスキン画像への割り当て

	// ウィンドウ枠のサイズ、中心部の幅と高さ
	int frameSize=0, faceWidth=0, faceHeight=0;
	int cntX=0, cntY=0;
	int* pWndImg=NULL; // ウィンドウ画像の配列へのポインタ
	int parentImg = 0;

	// 通常タイプのウィンドウの読み込み
	// 複数のウィンドウについて共通で読み込める表記法での表記
	for(int n=0; n<1; n++){
		// 通常タイプのウィンドウの数だけ繰り返し
		switch(n){
		case WNDSKIN_SIMPLE:
			// シンプルウィンドウ
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

		// ここから共通部分
		// 左上
		pWndImg[WNDIMGINDEX_TOPLEFT] = DerivationGraph(
			cntX, cntY, frameSize, frameSize, parentImg);
		// 上
		pWndImg[WNDIMGINDEX_TOP] = DerivationGraph(
			cntX+frameSize, cntY, faceWidth, frameSize, parentImg);
		// 右上
		pWndImg[WNDIMGINDEX_TOPRIGHT] = DerivationGraph(
			cntX+frameSize+faceWidth, cntY, frameSize, frameSize, parentImg);
		// 左
		pWndImg[WNDIMGINDEX_LEFT] = DerivationGraph(
			cntX, cntY+frameSize, frameSize, faceHeight, parentImg);
		// 中央
		pWndImg[WNDIMGINDEX_CENTER] = DerivationGraph(
			cntX+frameSize, cntY+frameSize, faceWidth, faceHeight, parentImg);
		// 右
		pWndImg[WNDIMGINDEX_RIGHT] = DerivationGraph(
			cntX+frameSize+faceWidth, cntY+frameSize, frameSize, faceHeight, parentImg);
		// 左下
		pWndImg[WNDIMGINDEX_BOTTOMLEFT] = DerivationGraph(
			cntX, cntY+frameSize+faceHeight, frameSize, frameSize, parentImg);
		// 下
		pWndImg[WNDIMGINDEX_BOTTOM] = DerivationGraph(
			cntX+frameSize, cntY+frameSize+faceHeight,
			faceWidth, frameSize, parentImg);
		// 右下
		pWndImg[WNDIMGINDEX_BOTTOMRIGHT] = DerivationGraph(
			cntX+frameSize+faceWidth, cntY+frameSize+faceHeight,
			frameSize, frameSize, parentImg);
	}

	return true;
}

bool Image::Load_Chars(){
	int srcX = 0, srcY = 0;		// DerivationGraph時の基準位置
	int width=0, height=0;		// DerivationGraph時の幅と高さ
	int hImage;					// DerivationGraph時のハンドル

	chars.dummy_number_i = LoadGraph(_T("sysimg\\number_i.png"));

	// 数字画像を同じフォーマットで読み込む
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

		// ループ読み込み部分
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

	// 人形イラストの読み込み
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

	// ダミー人形イラストの読み込み
	LoadDivGraph(_T("img\\doll_dummy.png"), 2, 2, 1, 512, 512, illust.doll_dummy);

	return true;
}

bool Image::Load_Enemy(){
	enemy.elf = LoadGraph(_T("img_enemy\\Elf.png"));
	if(enemy.elf == -1) return false;
	// 妖精
	if(LoadDivGraph(_T("img_enemy\\Fairy.png"),
		4, 4, 1, 120, 120, enemy.fairy) != 0) return false;
	// カタツムリ
	if(LoadDivGraph(_T("img_enemy\\Snail.png"),
		4, 2, 2, 120, 80, enemy.snail) != 0) return false;
	// 蝶
	if(LoadDivGraph(_T("img_enemy\\Butterfly.png"),
		4, 1, 4, 240, 80, enemy.butterfly) != 0) return false;
	// ネズミ
	if(LoadDivGraph(_T("img_enemy\\Rat.png"),
		4, 2, 2, 150, 100, enemy.rat) != 0) return false;
	// カラス
	if(LoadDivGraph(_T("img_enemy\\Crow.png"),
		4, 2, 2, 150, 100, enemy.crow) != 0) return false;
	// スライム
	if(LoadDivGraph(_T("img_enemy\\Slime.png"),
		4, 2, 2, 100, 50, enemy.slime) != 0) return false;
	// 花
	if(LoadDivGraph(_T("img_enemy\\Flower.png"),
		4, 2, 2, 130, 130, enemy.flower) != 0) return false;
	// スケルトン
	if(LoadDivGraph(_T("img_enemy\\Skeleton.png"),
		4, 2, 2, 160, 240, enemy.skeleton) != 0) return false;
	// ハーピー
	if(LoadDivGraph(_T("img_enemy\\Harpy.png"),
		4, 2, 2, 220, 280, enemy.harpy) != 0) return false;
	// 鳥
	if(LoadDivGraph(_T("img_enemy\\Bird.png"),
		4, 2, 2, 100, 100, enemy.bird) != 0) return false;
	// オウム
	if(LoadDivGraph(_T("img_enemy\\Parrot.png"),
		4, 2, 2, 240, 240, enemy.parrot) != 0) return false;
	// ネクロマンサー
	enemy.cardinal = LoadGraph(_T("img_enemy\\Cardinal.png"));
	if(enemy.cardinal == -1) return false;
	return true;
}

bool Image::Load_BG(){
	return true;
}

bool Image::Load_Icon(){
	TCHAR fileName[MAX_PATH];

	// 人形アイコンの読み込み
	for(int t=0; t<DOLL_TYPE_MAX; t++){
		sprintf_s(fileName, MAX_PATH-1, _T("img_illust\\doll%02d_icon.png"), t+1);
		if((icon.doll_group[t] = LoadGraph(fileName, 1)) == -1){
			return false;
		}
		for(int h=0; h<DOLL_ATTR_NUM; h++){
			for(int w=0; w<DOLL_FACE_NUM; w++){
				// 今のところ、属性の差分はない
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

	// 属性アイコンの読み込み
	icon.attrstone_group = LoadGraph(_T("img\\attr_stone.png"));
	for(int h=0; h<DOLL_GROUP_NUM; h++){
		for(int w=0; w<DOLL_ATTR_NUM; w++){
			icon.attrstone[w][h] = DerivationGraph(
				SIZE_ATTRSTONE*w, SIZE_ATTRSTONE*h,
				SIZE_ATTRSTONE, SIZE_ATTRSTONE, icon.attrstone_group);
		}
	}

	// ステートアイコンの読み込み
	icon.state_group = LoadGraph(_T("img\\state_icon.png"));
	for(int h=0; h<4; h++){
		for(int w=0; w<8; w++){
			icon.state[w+h*8] = DerivationGraph(
				IMAGE_SIZE_STATEICON*w, IMAGE_SIZE_STATEICON*h,
				IMAGE_SIZE_STATEICON, IMAGE_SIZE_STATEICON, icon.state_group);
		}
	}

	// 属性関係画像の読み込み
	icon.attr_graph = LoadGraph(_T("img\\attr_graph.png"));

	return true;
}

bool Image::Load_Effect(){
	return true;
}
