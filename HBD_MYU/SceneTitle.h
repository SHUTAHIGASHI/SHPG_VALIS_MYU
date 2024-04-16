#pragma once
#include "Scene.h"

class SceneTitle:
    public Scene
{
public:
    // コンストラクタ
    SceneTitle(SceneManager& manager);
    // デストラクタ
    virtual ~SceneTitle();
    // 更新
    void Update(const InputState& input);
    // 描画
    void Draw();

private:
};

