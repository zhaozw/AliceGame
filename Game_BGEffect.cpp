// Game_BGEffect.cpp

#include "Game_BGEffect.h"
#include "Image.h"
#include <DxLib.h>
#include "Static_Game.h"

extern Image	g_image;

// radianの正規化
static auto radNormalize = [](float angle)->float{
    angle = fmod(angle, DX_TWO_PI_F);
    if (angle < 0.0f){
        angle = (DX_TWO_PI_F)+angle;
    }
    return angle;
};


// 描画先をもとに戻すために
extern int hDrawWindow;

Game_BGEffect::Game_BGEffect(){
    typeID = GAME_BG_TYPE_NONE;
    param = 0;
    time = 0;
    posX = posY = 0;
    facterX = facterY = radX = radY = 0;
    scaleX = scaleY = 0;
    outScreen = -1;
    inScreen = -1;
    isCreatedOutScreen = false;
    tempScreen = -1;
    alpha = 1.0f;
}

bool Game_BGEffect::Initialize(){
    // スクリーンの作成などを行う
    
    return true;
}

bool Game_BGEffect::Terminate(){
    // 画像ハンドルの解放などを行う
    if (isCreatedOutScreen){
        DeleteGraph(outScreen);
    }
    if (tempScreen != -1){
        DeleteGraph(tempScreen);
    }


    // objectの解放
    for (auto& ptr : obj){
        delete ptr;
    }

    return true;
}

bool Game_BGEffect::SetTypeID(WORD id){
    // 値の代入
    typeID = id;
    time = 0;

    // 初期化処理(typeID値により分岐する)
    switch (typeID){
    case GAME_BG_TYPE_NONE:
        break;
    case GAME_BG_TYPE_DUMMY:
        [&](){
            BackGroundEffect::Object* o = new BackGroundEffect::Object();
            o->SetDuplicateGraph(g_image.icon.tile);
            o->SetDivision(1);
            o->SetPolySize(800, 600);
            o->SetPosition(400, 300);
            o->CreatePolygon();
            o->SetPixelUV();
            o->SetUVRate(-0.05f, -0.05f);

            obj.push_back(o);
        }();
        break;

    case GAME_BG_TYPE_LOOP_WAVE:
        [&](){
            BackGroundEffect::Object* o = new BackGroundEffect::Object();
            o->SetDuplicateGraph(inScreen);
            o->SetDivision(10);
            o->SetPolySize(800, 600);
            o->SetPosition(posX, posY);
            o->CreatePolygon();
            o->SetPixelUV();
            o->SetUVRate(facterX / o->GetPolyWidth(), facterY / o->GetPolyHeight());
            o->SetCosWaveFacter((float)param);
            o->SetSinWaveFacter((float)param);
            o->SetCosThetaRate(radX);
            o->SetSinThetaRate(radY);
            obj.push_back(o);
        }();
        break;
        
    case GAME_BG_TYPE_HUE :
        [&](){
            BackGroundEffect::Object* o = new BackGroundEffect::Object();
            o->SetDuplicateGraph(inScreen);
            o->SetDivision(1);
            o->SetPosition(posX, posY);
            o->CreatePolygon();
            o->SetTexelUV();
            
            tempScreen = MakeScreen((int)o->GetPolyWidth(), (int)o->GetPolyHeight(), true);

            obj.push_back(o);
        }();
        break;

    case GAME_BG_TYPE_PC:
        [&](){
            BackGroundEffect::Object* o = new BackGroundEffect::Object();
            o->SetDuplicateGraph(inScreen);
            o->SetDivision(30);
            o->SetPosition(posX, posY);
            o->CreatePolygon();
            o->SetTexelUV();
            o->SetPolarConversionFacter((float)param / 100.0f);
            o->SetPolarConversionXY(facterX, facterY);

            obj.push_back(o);
        }();
        break;

    default:
        return false;
        break;
    }
    return true;
}

void Game_BGEffect::Update(){


    // ここで各パラメータを再設定しているのは外部から値が変更された場合を考えている。
    switch (typeID){
    case GAME_BG_TYPE_NONE:
        break;
    case GAME_BG_TYPE_DUMMY:
        break;
    case GAME_BG_TYPE_LOOP_WAVE:
        obj.at(0)->SetPosition(posX, posY);
        obj.at(0)->SetUVRate(facterX / obj.at(0)->GetPolyWidth(), facterY / obj.at(0)->GetPolyHeight());
        obj.at(0)->SetCosWaveFacter((float)param);
        obj.at(0)->SetSinWaveFacter((float)param);
        obj.at(0)->SetCosThetaRate(radX);
        obj.at(0)->SetSinThetaRate(radY);
        obj.at(0)->SetAlpha(alpha);
        break;
    case GAME_BG_TYPE_HUE:
        obj.at(0)->SetPosition(posX, posY);
        obj.at(0)->SetAlpha(alpha);
        break;

    case GAME_BG_TYPE_PC:
        obj.at(0)->SetPosition(posX, posY);
        obj.at(0)->SetPolarConversionFacter((float)param / 100.0f);
        obj.at(0)->SetPolarConversionXY(facterX, facterY);
        obj.at(0)->SetAlpha(alpha);
        break;
    }

    // typeに関係なくobjのアップデートは行う
    for (auto& it : obj){
        it->Update();
    }

    // 時間値の増加
    time++;
}

void Game_BGEffect::Draw() const{

    if (outScreen != -1){
        SetDrawScreen(outScreen);
        ClearDrawScreen();
    }

    int tmpX = 0, tmpY = 0;
    switch (typeID){
    case GAME_BG_TYPE_NONE:
        break;
    case GAME_BG_TYPE_DUMMY:
        for (auto& it : obj){
            it->Draw();
        }
        break;
    case GAME_BG_TYPE_LOOP_WAVE:
        for (auto& it : obj){
            it->Draw();
        }
        break;

    case GAME_BG_TYPE_HUE:
        [&](){
            int tex = obj.at(0)->GetTextureHandle();
            float rate = (float)time / (float)param;
            int hue = 360.0f * rate;
            hue = hue % 360;
            if (hue > 180){
                hue -= 360;
            }
            GraphFilterBlt(tex, tempScreen, DX_GRAPH_FILTER_HSB, 0, hue, 0, 0);

            SetDrawBlendMode(DX_BLENDMODE_ALPHA, (int)(255.0f*alpha));
            int x, y;
            x = posX - obj.at(0)->GetPolyWidth() / 2.0f;
            y = posY - obj.at(0)->GetPolyHeight() / 2.0f;
            DrawGraph(x, y, tempScreen, true);
            SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
        }();
        break;

    case GAME_BG_TYPE_PC:
        for (auto& it : obj){
            it->Draw();
        }
        break;

    }


    if (outScreen != -1){
        SetDrawScreen(hDrawWindow);
    }
}

/*
    BackGroundEffect::Object定義
    ここより以下は直接的にはGame_BGEffectに関係ない。
*/
namespace BackGroundEffect{

    Object::Object(){
        // 姿勢情報の初期化
        centerPos = VGet(400, 300, 0); // とりあえず真ん中
        rot = 0.0f;
        scale = 1.0f;
        alpha = 1.0f;

        rotateRate = 0.0f;
        scaleRate = 0.0f;
        uRate = 0.0f;
        vRate = 0.0f;

        texW = texH = 0.0f;
        uMax = vMax = 0.0f;
        divNum = 1;
        polyW = polyH = 0.0f;

        addV = addU = 0.0f;

        sinWaveTheta = 0.0f;
        sinWaveFacter = 0.0f;
        cosWaveTheta = 0.0f;
        cosWaveFacter = 0.0f;
        sinThetaRate = 0.0f;
        cosThetaRate = 0.0f;

        pcX = pcY = 0;
        pcFacter = 1.0f;
        isPolarConversion = false;

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
        VERTEX2D* cur = &vertex[0];
        VERTEX2D* end = cur + vertexNum;
        while (cur < end){
            cur->dif.r = 255;
            cur->dif.g = 255;
            cur->dif.b = 255;
            cur->rhw = 1.0f;
            ++cur;
        }

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
        for (int y = 0; y < divNum * 2; ++y){
            for (int x = 0; x < divNum * 2; ++x){
                VERTEX2D* cur = &vertex[x + y*divNum * 2];
                float xr, yr;
                xr = (float)x / (float)(divNum * 2 - 1);
                yr = (float)y / (float)(divNum * 2 - 1);

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
        //float pcU=0, pcV=0;
        if (isPolarConversion){
            // 極座標変換用uv値を計算
            pcU = (float)pcX - (centerPos.x - polyW / 2.0f);
            pcU = (pcU / polyW);
            pcV = (float)pcY - (centerPos.y - polyH / 2.0f);
            pcV = (pcV / polyH);
        }

        for (int y = 0; y < divNum * 2; ++y){
            for (int x = 0; x < divNum * 2; ++x){
                VERTEX2D* cur = &vertex[x + y*divNum * 2];
                float xr = (float)x / (float)(divNum * 2 - 1);
                float yr = (float)y / (float)(divNum * 2 - 1);

                cur->u = uMax * xr;
                cur->v = vMax * yr;

                // 極座標変換
                if (isPolarConversion){
                    VECTOR v1 = VGet(xr, yr, 0);
                    VECTOR v2 = VGet(pcU, pcV, 0);

                    VECTOR c = VSub(v1, v2);
                    float r = VSize(c);

                    float ac = c.x / r;
                    float theta = acos(ac) * vMax / DX_PI_F;
                    // 本来なら0~2PIの値をとるべきだがUV座標の関係上うまくいかないのであきらめる
                    //if (c.y < 0) theta = -theta;
                	
                    float rate = r*r*pcFacter;
                    rate = max(0, min(1.0f, rate));

                	r *= uMax;
                	
                    cur->u = cur->u * rate + r * (1.0f - rate);
                    cur->v = cur->v * rate + theta * (1.0f - rate);
                }

                float sinWave = sin(sinWaveTheta + DX_PI_F*xr);
                sinWave = sinWave * sinWaveFacter / polyW;
                float cosWave = cos(cosWaveTheta + DX_PI_F*yr);
                cosWave = cosWave * cosWaveFacter / polyH;

                cur->u += cosWave + addU;
                cur->v += sinWave + addV;
            }
        }

        return;
    }

    void Object::SetTexelUV()
    {
        isPolarConversion = false;

        int w, h;
        GetGraphTextureSize(texture, &w, &h);
        uMax = texW / (float)w;
        vMax = texH / (float)h;

        SetUV();

        return;
    }

    void Object::SetPixelUV()
    {
        isPolarConversion = false;

        // 1texelを計算
        float uTexel = 1.0f / texW;
        float vTexel = 1.0f / texH;

        // uvをピクセルに合わせる
        uMax = uTexel * polyW;
        vMax = vTexel * polyH;

        SetUV();

        return;
    }

    void Object::SetPolarConversionXY(int x, int y)
    {
        isPolarConversion = true;
        pcX = x;
        pcY = y;
        return;
    }

    void Object::SetPolarConversionFacter(float facter){
        isPolarConversion = true;
        pcFacter = facter;
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

    void Object::SetPolySize(int w, int h)
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
        if ((texW == polyW && texH == polyH) ||
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
        polyW = polyH = 0.0f;

        SetGraph(temp);

        isDuplicateTexture = true;

        return;
    }

    void Object::Update()
    {


        // 座標をいじって波を起こす
        sinWaveTheta += sinThetaRate;
        cosWaveTheta += cosThetaRate;
        sinWaveTheta = radNormalize(sinWaveTheta);
        cosWaveTheta = radNormalize(cosWaveTheta);

        // 座標を設定
        SetVertexPosition();

        // UV設定
        addU += uRate;
        addV += vRate;
        addU = fmodf(addU, 1.0f);
        addV = fmodf(addV, 1.0f);


        SetUV();

        // 拡大縮小
        if (scaleRate != 0.0f){
            scale += scaleRate;
        }
        SetScale();

        // 回転
        if (rotateRate != 0.0f){
            rot += rotateRate;
            rot = radNormalize(rot);
        }
        SetRotate();

        return;
    }

    void Object::Draw()
    {
        // 描画の前にテクスチャアドレッシングモードを変更
        SetTextureAddressModeUV(DX_TEXADDRESS_WRAP, DX_TEXADDRESS_WRAP, 0);

        // ポリゴンを描画
        //SetDrawBlendMode(DX_BLENDMODE_ALPHA, (int)(255.0f*alpha));
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

        DrawFormatString(pcX, pcY, GetColor(100, 100, 255), "%f:%f", pcU, pcV);

        #endif
        */

        // 一応
        //SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);

        return;
    }
}