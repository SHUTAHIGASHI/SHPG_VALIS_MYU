#pragma once
#include "Scene.h"

class SceneAction:
	public Scene
{
public:
	// コンストラクタ
	SceneAction(SceneManager& manager);
	// デストラクタ
	virtual ~SceneAction();
	// 更新
	void Update(const InputState& input);
	// 描画
	void Draw();

private:
};

