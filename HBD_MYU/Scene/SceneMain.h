#pragma once
#include "Scene.h"
#include "GameDataManager.h"
#include <memory>
#include <string>

class SceneMain :
    public Scene
{
public:
    // コンストラクタ
    SceneMain(SceneManager& manager);
    // デストラクタ
    virtual ~SceneMain();

	// 初期化処理
    void Init();
    // 更新処理
    void Update(const InputState& input);
    // 描画処理
    void Draw();
	// 終了処理
    void End();

private:
    // メンバ関数ポインタ(更新)
    using m_tUpdateFunc = void (SceneMain::*) (const InputState& input);
    m_tUpdateFunc m_updateFunc = nullptr;
    void NormalUpdate(const InputState& input);

    // メンバ関数ポインタ(描画)
    using m_tDrawFunc = void (SceneMain::*) ();
    m_tDrawFunc m_drawFunc = nullptr;
    void NormalDraw();

private:
    // 終了処理済みかどうか
    bool m_isEnd;

private:
    // アクションマネージャー
    std::shared_ptr<class Action> m_pAction;
    // UI
    std::shared_ptr<class UiManager> m_pUiManager;
    // マップ描画
	std::shared_ptr<class MapDraw> m_pMapDraw;
};

