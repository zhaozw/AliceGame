#ifndef GAME_BGEFFECT_H
#define GAME_BGEFFECT_H

#include <Windows.h>
#include <DxLib.h>
#include <vector>
#include <array>

// typeIDの列挙。
#define GAME_BG_TYPE_NONE				0	// 背景なし。何も描画しない。
#define GAME_BG_TYPE_DUMMY				1	// ダミー背景。チェック画像を並べて表示。

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
        void SetPolarConversionUV(int x, int y); // 極座標変換

        void SetPosition(int x, int y){ // 中心座標の設定
            centerPos.x = (float)x;
            centerPos.y = (float)y;
        };

        // 各種動作のパラメータセッター
        void SetRotateRate(float rate){ rotateRate = rate; }
        void SetScaleRate(float rate){ scaleRate = rate; }
        void SetUVRate(float u, float v){ uRate = u; vRate = v; }
        
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

	// 繰り返しに使用する値で、
	// 画像の幅と高さなどに使用する。
	// 使い方はtypeIDによって異なってもよい。
	float		loopWidth;
	float		loopHeight;

    
    BackGroundEffect::Object* obj;

public:

	// コンストラクタ
	Game_BGEffect();

	// タイプIDを変更する。
	// タイプIDごとの初期化処理も含む。
	bool SetTypeID(WORD id);

	// タイプIDを取得する。
	WORD GetTypeID(){ return typeID; };

	// パラメータを変更する。
	void SetParam(int p){ param = p; };

	// パラメータを取得する。
	int GetParam(){ return param; };

	// タイプIDとパラメータをまとめてセットする。
	bool SetTypeID(WORD id, int param){ SetParam(param); return SetTypeID(id); };

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
	void SetRandTime();

	// 基準位置を代入する。
	void SetPosition(float _x, float _y){ posX = _x; posY = _y; };


};



#endif // GAME_BGEFFECT_H