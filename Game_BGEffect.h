#ifndef GAME_BGEFFECT_H
#define GAME_BGEFFECT_H

#include <Windows.h>
#include <DxLib.h>
#include <vector>
#include <array>

// typeIDの列挙。
#define GAME_BG_TYPE_NONE				0	// 背景なし。何も描画しない。
#define GAME_BG_TYPE_DUMMY				1	// ダミー背景。チェック画像を並べて表示。
#define GAME_BG_TYPE_LOOP_WAVE          2   // 波＋平行移動
#define GAME_BG_TYPE_HUE                3   // 色相変化
#define GAME_BG_TYPE_PC                 4   // 極座標変換

//================================================
// Game_BGEffectクラス
// 
// エフェクトのかかった背景のクラス。
// 戦闘画面の背景、マップ画面の背景などで利用する。
// 
namespace BackGroundEffect{
    class Object{
        // テクスチャ関係
        int texture;
        float texW, texH;
        float uMax, vMax;
        float addU; // UVアニメーション用
        float addV; // UVアニメーション用
        float alpha;
        // 極座標変換用
        float pcFacter;
        int pcX, pcY;
        bool isPolarConversion;

        // 
        float pcU, pcV;

        // 頂点関係
        //DrawPrimitive2D();
        VERTEX2D* vertex;
        int vertexNum;
        int divNum;
        float polyW, polyH;

        // 頂点インデックス
        USHORT* index;
        int indexNum;

        // 姿勢情報
        VECTOR centerPos;
        float rot;
        float scale;

        // Update時の動作フラグとパラメータ
        float rotateRate; // 1フレームでrotateRate分増加する
        float scaleRate; // 1フレームでscaleRate分増加する
        float uRate; // 1フレームでuRate分Uを動かす
        float vRate; // 1フレームでvRate分Vを動かす
        float sinThetaRate;
        float cosThetaRate;
        float sinWaveTheta;
        float sinWaveFacter;
        float cosWaveTheta;
        float cosWaveFacter;

        void SetVertexPosition();
        void SetUV();
        
        void SetRotate();
        void SetScale();

        void CreateVertex(int div);
        void CreateIndex();

        bool isDuplicateTexture;
        

    public:
        Object();
        Object(int graphHandle, int div = 1);
        ~Object();

        void SetGraph(int handle); // 使用する画像ハンドルをセットする
        void SetDuplicateGraph(int handle); // ハンドルのコピーをtextureとして使用する

        void SetAlpha(float a){ alpha = a; } // アルファ値を設定

        void SetScale(float scale){ this->scale = scale; } // スケールをセット

        void SetDivision(int div){ divNum = div; } // ポリゴン分割数をセットする
        void CreatePolygon(){  // ポリゴンを作成する
            CreateVertex(divNum);
            CreateIndex();
            SetVertexPosition();
            SetTexelUV();
        }
        void SetPolySize(int w,int h); // ポリゴンのサイズを決める
        void SetTexelUV(); // テクスチャに合わせたUV
        void SetPixelUV(); // ポリゴンに合わせたUV
        void SetPolarConversionFacter(float facter); // 極座標変換の減衰率を計算する。　=r^2*facter
        void SetPolarConversionXY(int x, int y); // 極座標変換の場所を設定する

        void SetPosition(int x, int y){ // 中心座標の設定
            centerPos.x = (float)x;
            centerPos.y = (float)y;
        };

        // 各種動作のパラメータセッター
        void SetRotateRate(float rate){ rotateRate = rate; }
        void SetScaleRate(float rate){ scaleRate = rate; }
        void SetUVRate(float u, float v){ uRate = u; vRate = v; }
        void SetSinThetaRate(float rad){
            sinThetaRate = rad;
        }
        void SetCosThetaRate(float rad){
            cosThetaRate = rad;
        }
        void SetSinWaveFacter(float fact){
            sinWaveFacter = fact;
        }
        void SetCosWaveFacter(float fact){
            cosWaveFacter = fact;
        }

        float GetPolyWidth(){ return polyW; }
        float GetPolyHeight(){ return polyH; }
        float GetTextureWidth(){ return texW; }
        float GetTextureHeight(){ return texH; }
        
        int GetTextureHandle(){ return texture; }

        void Draw();
        void Update();
    };
}


class Game_BGEffect{
private:
	// 背景のタイプID。
	WORD		typeID;

	// 同じタイプIDを使用しながら背景を微妙に変化させたい時の汎用パラメータ。
	// 使い方はtypeIDによって異なる。
	int			param;

	// 時間のパラメータ。
	// SetTypeIDを行う際に0になり、Updateが呼び出される度に増える。
	// 使うかどうか・使い方はtypeIDによって異なる。
	// 毎回エフェクトの基準時間を変えたい場合は、
	// SetRandTime関数を実行すると適当な値がtimeに代入される。
	int			time;

	// 変形の基準に使う座標。
	// これも汎用的なものであり、使い方はtypeIDによって異なる。
	// SetPosition関数で指定する。
	float		posX;
	float		posY;

    // 変形の基準に使う汎用変数。
    // SetFacter関数で指定する。
    float       facterX;
    float       facterY;

    // 角度変形の基準に使う汎用変数
    float       radX, radY;

    // 縮小拡大の基準に使う汎用変数
    float       scaleX, scaleY;

    // エフェクトのアルファ値 0~1.0f
    float       alpha;

    // エフェクトの出力先。　-1であればhDrawWindowが出力先
    int outScreen;
    bool isCreatedOutScreen;

    // エフェクトで使用する画像ハンドル　BGEffectの画像をさらに使いまわしたいときに使用する。
    int inScreen;

    // エフェクトで使用するテンポラリスクリーン 一部で使用する。
    int tempScreen;

    // エフェクトで使用するobjの配列
    std::vector< BackGroundEffect::Object* > obj;

public:

	// コンストラクタ
	Game_BGEffect();

	// タイプIDを変更する。
	// タイプIDごとの初期化処理も含む。
    bool SetTypeID(WORD id);

	// タイプIDを取得する。
	WORD GetTypeID(){ return typeID; }

	// パラメータを変更する。
	void SetParam(int p){ param = p; }

	// パラメータを取得する。
	int GetParam(){ return param; }

	// タイプIDとパラメータをまとめてセットする。
	bool SetTypeID(WORD id, int param){ SetParam(param); return SetTypeID(id); }

	// 初期化を行う。
	// タイプIDごとの初期化はこの関数ではなくSetTypeID内で行う。
	bool Initialize();

	// 終了処理を行う。
	bool Terminate();

	// タイプIDごとの演算処理を行う。
	// このオブジェクトが属するクラスから毎フレーム実行される。
	void Update();

	// タイプIDごとの描画処理を行う。
	// このオブジェクトが属するクラスから毎フレーム実行される。
	void Draw() const;

	// 適当な時間を代入する。
    void SetRandTime(){ time = GetRand(32767); }

	// 基準位置を代入する。
	void SetPosition(float _x, float _y){ posX = _x; posY = _y; }
    // 変形基準の要素を代入する。
    void SetFacter(float _x, float _y){ facterX = _x; facterY = _y; }
    // 変形角度の要素を代入する。
    void SetRadian(float x, float y){ radX = x; radY = y; }
    // 縮小拡大の要素を代入する。
    void SetScale(float x, float y){ scaleX = x; scaleY = y; }
    // アルファ値を代入する
    void SetAlpha(float a){ alpha = a; }

    // 出力先スクリーンを設定する
    void SetOutputScreen(int handle){ outScreen = handle; }
    // 出力先スクリーンを作成する。
    int CreateOutputScreen(int w,int h){
        if (isCreatedOutScreen) DeleteGraph(outScreen);
        outScreen = MakeScreen(w, h, true);
        isCreatedOutScreen = true;
        return outScreen;
    }
    // 出力先スクリーンの取得
    int GetOutputScreen(){ return outScreen; }

    // 使用する画像を設定する typeによっては使用しない。
    // 使用する場合はSetTypeIDを呼び出す前に呼ぶこと。
    void SetInputScreen(int handle){ inScreen = handle; }
    
    


};



#endif // GAME_BGEFFECT_H