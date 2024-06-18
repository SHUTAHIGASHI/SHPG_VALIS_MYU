#pragma once
#include "Scene.h"
#include "Game.h"

class SceneHowTo :
    public Scene
{
public:
    SceneHowTo(SceneManager& manager);
    virtual ~SceneHowTo();

	void Init() {}
    void Update(const InputState& input);
    void Draw();
	void End() {}

private:
    // 毎フレームカウント
    int m_countFrame;
    // 画像ハンドル
    int m_hImg;
    // 描画座標
    VECTOR m_pos;
};

