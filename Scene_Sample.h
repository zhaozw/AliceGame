#ifndef SCENE_SAMPLE_H
#define SCENE_SAMPLE_H

#include "Scene_Base.h"

#include "Player_Sample.h"

#define PHAZE_UNKNOWN 0
#define PHAZE_WAITKEY 1
#define PHAZE_ENTERNAME 2

class Scene_Sample : public Scene_Base{
public:
	Player_Sample player;

private:

public:
	// コンストラクタ
	Scene_Sample();
	// 初期化処理
	virtual bool Initialize(bool fSkipFrame);
	// 終了処理
	virtual bool Terminate();
	
	// 更新処理
	virtual int Update();
	// 描画処理
	virtual void Draw();

};

#endif // SCENESAMPLE_H