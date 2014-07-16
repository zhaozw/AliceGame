#ifndef SCENE_DOLLBIRTH_H
#define SCENE_DOLLBIRTH_H

#include "Scene_Base.h"
#include "Window_DollStatus.h"
#include "Window_EnterName.h"

// ステートの列挙
#define SCNSTATE_DOLLBIRTH_DOLLAPPEAR		0
#define SCNSTATE_DOLLBIRTH_SHOWSTATUS		1
#define SCNSTATE_DOLLBIRTH_ENTERNAME		2

// アニメーションの列挙
#define SCNANIME_DOLLBIRTH_DOLLAPPEAR					1
#define SCNANIME_DOLLBIRTH_DOLLAPPEAR_TIME			120


class Scene_DollBirth : public Scene_Base{
public:
	Window_DollStatus		w_status;
	Window_EnterName		w_name;
private:
public:
	// コンストラクタ
	Scene_DollBirth();
	// 初期化処理
	virtual bool Initialize(bool fSkipFrame);
	bool InitWindow();
	// 終了処理
	virtual bool Terminate();
	
	// 更新処理
	virtual int Update();
	// 描画処理
	virtual void Draw() const;
};

#endif // SCENE_DOLLBIRTH_H