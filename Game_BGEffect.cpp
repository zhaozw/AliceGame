// Game_BGEffect.cpp

#include "Game_BGEffect.h"
#include "Image.h"
#include <DxLib.h>
#include "Static_Game.h"

extern Image	g_image;

// 描画先をもとに戻すために
extern int hDrawWindow;

Game_BGEffect::Game_BGEffect(){
	typeID = GAME_BG_TYPE_NONE;
	param = 0;
	time = 0;
	posX = posY = 0;
	loopWidth = loopHeight = 1; // 不意のdiv0防止

    //obj = new BackGroundEffect::Object(g_image.enemy.bird[0],2);
    obj = new BackGroundEffect::Object();
    obj->SetDuplicateGraph(g_image.icon.tile);
    obj->SetPolySize(400, 400);
    obj->SetScale(2.5f);
    obj->SetPosition(400, 300);
    obj->SetDivision(1);
    obj->CreatePolygon();
    obj->SetPixelUV();
    obj->SetUVRate(-0.01f, -0.01f);
    obj->SetRotateRate(0.001f);
}

bool Game_BGEffect::Initialize(){
	// スクリーンの作成などを行う

	return true;
}

bool Game_BGEffect::Terminate(){
	// 画像ハンドルの解放などを行う
    delete obj;
	return true;
}

#define DUMMYTILE_SIZE		48

bool Game_BGEffect::SetTypeID(WORD id){
	// 値の代入
	typeID = id;
	time = 0;

	// 初期化処理(typeID値により分岐する)
	switch(typeID){
	case GAME_BG_TYPE_NONE:
		break;
	case GAME_BG_TYPE_DUMMY:
		loopWidth = DUMMYTILE_SIZE;
		loopHeight = DUMMYTILE_SIZE;
		break;
	default:
		return false;
		break;
	}
	return true;
}

void Game_BGEffect::Update(){
	switch(typeID){
	case GAME_BG_TYPE_NONE:
		break;
	case GAME_BG_TYPE_DUMMY:
		posX += 0.3f;
		posY += 0.2f;
		if(posX > loopWidth) posX -= loopWidth;
		if(posY > loopHeight) posY -= loopHeight;
		
        obj->Update();

        break;
	}

	// 時間値の増加
	time++;
}

void Game_BGEffect::Draw() const{
	int tmpX=0, tmpY=0;
	switch(typeID){
	case GAME_BG_TYPE_NONE:
		break;
	case GAME_BG_TYPE_DUMMY:
        
		tmpX = posX-loopWidth;
		tmpY = posY-loopHeight;
		while(tmpY < WND_HEIGHT){
			while(tmpX < WND_WIDTH){
				//DrawGraph(tmpX, tmpY, g_image.icon.tile, 0);
				tmpX += DUMMYTILE_SIZE;
			}
			tmpY += loopHeight;
			tmpX = posX - loopWidth;
		}

        obj->Draw();
        
		break;
	}
}

void Game_BGEffect::SetRandTime(){
	time = GetRand(32767);
}

/*
    BackGroundEffect::Object定義
*/
using namespace BackGroundEffect;

Object::Object(){
    // 姿勢情報の初期化
    centerPos = VGet(400, 300, 0); // とりあえず真ん中
    rot = 0.0f;
    scale = 1.0f;

    rotateRate = 0.0f;
    scaleRate = 0.0f;
    uRate = 0.0f;
    vRate = 0.0f;

    texW = texH = 0.0f;
    uMax = vMax = 0.0f;
    divNum = 1;
    polyW = polyH = 0.0f;

    addV = addU = 0.0f;

    // ポインタの初期化
    vertex = nullptr;
    index = nullptr;

    isDuplicateTexture = false;
}

Object::Object(int gh, int div) : Object(){
    
    // テクスチャ情報の取得
    texture = gh;

    // 画像のサイズを取得
    {
        int w, h;
        GetGraphSize(gh, &w, &h);
        texW = (float)w;
        texH = (float)h;

        // 画像の大きさはポリゴンの大きさ
        polyW = texW;
        polyH = texH;
    }

    // 画像に合うようにUV値を計算
    {
        int w, h;
        GetGraphTextureSize(gh, &w, &h);
        uMax = texW / (float)w;
        vMax = texH / (float)h;
    }

    // 頂点情報を取得
    CreateVertex(div);

    // 頂点インデックスの作成
    CreateIndex();

    // uvの設定
    SetTexelUV();
    

}

Object::~Object(){
    delete[] vertex;
    delete[] index;
    if (isDuplicateTexture) DeleteGraph(texture);
}

void Object::CreateVertex(int div)
{
    if (vertex) delete[] vertex;

    this->divNum = div;
    vertexNum = divNum * 2 * divNum * 2;
    vertex = new VERTEX2D[vertexNum];
    SetVertexPosition();

    return;
}

void Object::CreateIndex()
{
    // インデックスの量を計算　式がわからなかったのでゴリ押し
    indexNum = 0;
    for (int y = 0; y + 1 < divNum * 2; ++y){
        for (int x = 0; x + 1 < divNum * 2; ++x){
            indexNum += 2;
        }
    }
    indexNum *= 3;

    // インデックス作成
    if (index) delete[] index;
    index = new USHORT[indexNum];

    int seek = 0;
    for (int y = 0; y + 1 < divNum * 2; ++y){
        int up = y*divNum * 2;
        int down = (y + 1)*divNum * 2;

        for (int x = 0; x + 1 < divNum * 2; ++x){
            int v0 = up + x; // 左上
            int v1 = up + x + 1; // 右上
            int v2 = down + x; // 左下
            int v3 = down + x + 1; // 右下

            // インデックスの割り当て
            index[seek++] = v0;
            index[seek++] = v1;
            index[seek++] = v2;

            index[seek++] = v1;
            index[seek++] = v2;
            index[seek++] = v3;
        }
    }

    return;
}

void Object::SetVertexPosition()
{
    float gridW = polyW / (float)(divNum * 2);
    float gridH = polyH / (float)(divNum * 2);

    for (int y = 0; y < divNum * 2; ++y){
        for (int x = 0; x < divNum * 2; ++x){
            VERTEX2D* cur = &vertex[x + y*divNum * 2];
            float xr, yr;
            xr = (float)x / (float)(divNum * 2-1);
            yr = (float)y / (float)(divNum * 2-1);
            cur->pos.x = xr * polyW;
            cur->pos.y = yr * polyH;
            cur->pos.x -= polyW / 2.0f;
            cur->pos.y -= polyH / 2.0f;
            cur->pos.x += centerPos.x;
            cur->pos.y += centerPos.y;
        }
    }

    return;
}

void Object::SetUV()
{
    for (int y = 0; y < divNum * 2; ++y){
        for (int x = 0; x < divNum * 2; ++x){
            VERTEX2D* cur = &vertex[x + y*divNum * 2];
            cur->u = uMax * (float)x / (float)(divNum * 2 - 1) + addU;
            cur->v = vMax * (float)y / (float)(divNum * 2 - 1) + addV;

            cur->dif.a = 255;
            cur->dif.r = 255;
            cur->dif.g = 255;
            cur->dif.b = 255;
            cur->rhw = 1.0f;
        }
    }

    return;
}

void Object::SetTexelUV()
{
    int w, h;
    GetGraphTextureSize(texture, &w, &h);
    uMax = texW / (float)w;
    vMax = texH / (float)h;

    SetUV();

    return;
}

void Object::SetPixelUV()
{
    // 1texelを計算
    float uTexel = 1.0f / texW;
    float vTexel = 1.0f / texH;

    // uvをピクセルに合わせる
    uMax = uTexel * polyW * 2;
    vMax = vTexel * polyH * 2;

    SetUV();

    return;
}

void Object::SetRotate()
{
    MATRIX m = MGetRotZ(rot);

    for (int y = 0; y < divNum * 2; ++y){
        for (int x = 0; x < divNum * 2; ++x){
            VERTEX2D* cur = &vertex[x + y*divNum * 2];
            cur->pos = VSub(cur->pos, centerPos);
            cur->pos = VTransform(cur->pos, m);
            cur->pos = VAdd(cur->pos, centerPos);
        }
    }

    return;
}

void Object::SetScale()
{
    for (int y = 0; y < divNum * 2; ++y){
        for (int x = 0; x < divNum * 2; ++x){
            VERTEX2D* cur = &vertex[x + y*divNum * 2];
            float sx, sy;
            cur->pos.x -= centerPos.x;
            cur->pos.y -= centerPos.y;
            sx = cur->pos.x;
            sy = cur->pos.y;
            cur->pos.x = sx * scale;
            cur->pos.y = sy * scale;
            cur->pos.x += centerPos.x;
            cur->pos.y += centerPos.y;
        }
    }

    return;
}

void Object::SetPolySize(int w,int h)
{
    polyW = (float)w;
    polyH = (float)h;

    return;
}

void Object::SetGraph(int gh)
{
    texture = gh;
    int w, h;
    GetGraphSize(gh, &w, &h);

    // 初期状態またはテクスチャ＝ポリゴンの状態の時は大きさを同期する
    if ( (texW == polyW && texH == polyH) ||
        (polyW == 0 && polyH == 0)){
        texW = (float)w;
        texH = (float)h;
        polyW = texW;
        polyH = texH;
    }
    else{
        texW = (float)w;
        texH = (float)h;
    }

    return;
}

void Object::SetDuplicateGraph(int handle)
{
    SetGraph(handle);

    if (isDuplicateTexture) DeleteGraph(texture);
    int temp = MakeScreen((int)texW, (int)texH, true);
    SetDrawScreen(temp);
    ClearDrawScreen();
    DrawGraph(0, 0, handle, true);
    SetDrawScreen(hDrawWindow);

    SetGraph(temp);

    isDuplicateTexture = true;

    return;
}

void Object::Update()
{
    // 座標を設定
    SetVertexPosition();

    // UV設定
    addU += uRate;
    addV += vRate;
    {
        float temp;
        addU = modff(addU, &temp);
        addV = modff(addV, &temp);
    }
    SetUV();

    // 拡大縮小
    if (scaleRate != 0.0f){
        scale += scaleRate;
    }
    SetScale();

    // 回転
    if (rotateRate != 0.0f){
        rot += rotateRate;

        // rotの正規化
        rot = fmod(rot, DX_TWO_PI_F);
        if (rot < 0.0f){
            rot = (DX_TWO_PI_F)+rot;
        }
    }
    SetRotate();

    return;
}

void Object::Draw()
{
    // 描画の前にテクスチャアドレッシングモードを変更
    SetTextureAddressModeUV(DX_TEXADDRESS_WRAP, DX_TEXADDRESS_WRAP, 0);

    // ポリゴンを描画
    DrawPrimitiveIndexed2D(
        vertex, vertexNum, index, indexNum,
        DX_PRIMTYPE_TRIANGLESTRIP, texture, true);

    /*
    // 頂点位置とトライアングルを描画 *debugDraw
#ifdef _DEBUG

    SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);
    {
        // index
        USHORT* end = index + indexNum;
        USHORT* cur = index;

        while (cur < end){
            int x1, x2, x3;
            int y1, y2, y3;
            x1 = (int)vertex[cur[0]].pos.x;
            y1 = (int)vertex[cur[0]].pos.y;

            x2 = (int)vertex[cur[1]].pos.x;
            y2 = (int)vertex[cur[1]].pos.y;

            x3 = (int)vertex[cur[2]].pos.x;
            y3 = (int)vertex[cur[2]].pos.y;

            DrawLine(x1, y1, x2, y2, GetColor(0, 255, 0), 1);
            DrawLine(x2, y2, x3, y3, GetColor(0, 255, 0), 1);
            DrawLine(x3, y3, x1, y1, GetColor(0, 255, 0), 1);
            
            cur += 3;
        }

    }

    SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
    {
        VERTEX2D* end = vertex + vertexNum;
        VERTEX2D* cur = vertex;

        // vert
        while (cur < end){
            int x = (int)cur->pos.x;
            int y = (int)cur->pos.y;

            DrawCircle(x, y, 1, GetColor(0, 255, 0), true);
            char buf[32];
            sprintf_s(buf, "%.2f:%.2f", cur->u, cur->v);
            DrawString(x-50,y-20,buf,GetColor(255,0,0));
            ++cur;
        }
    }

    SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
#endif
    */
    return;
}