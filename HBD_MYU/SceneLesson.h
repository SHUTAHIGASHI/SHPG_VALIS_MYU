#pragma once
#include "Scene.h"

class SceneLesson :
    public Scene
{
    public:
	SceneLesson(SceneManager& manager);
	~SceneLesson();

    // 初期化処理
    void Init()override;
    // 更新処理
    void Update(const InputState& input)override;
    // 描画処理
    void Draw()override;
    // 終了処理
    void End()override;

private:
};

