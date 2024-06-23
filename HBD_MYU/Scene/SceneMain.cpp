#include "SceneMain.h"
#include "SceneManager.h"
#include "SoundManager.h"
#include "GameDataManager.h"
#include "Player.h"
#include "ScenePause.h"
#include "Action.h"
#include "CharaDraw.h"
#include "UiManager.h"
#include "MapDraw.h"
#include "Load.h"

namespace
{
	// タイトルロゴ描画位置
	constexpr float kLogoDrawPosX = Game::kUiWidthRight / 2;
	constexpr float kLogoDrawPosY = Game::kScreenHeight - 120.0f;
}

SceneMain::SceneMain(SceneManager& manager):
	Scene(manager),
	m_updateFunc(&SceneMain::NormalUpdate),
	m_drawFunc(&SceneMain::NormalDraw),
	m_isEnd(false),
	m_pAction(std::make_shared<Action>()),
	m_pUiManager(std::make_shared<UiManager>()),
	m_pMapDraw(std::make_shared<MapDraw>())
{
	// アクションマネージャー設定
	m_pAction->SetUiManager(m_pUiManager.get());
}

SceneMain::~SceneMain()
{
	// ゲームポイント保存
	//GameDataManager::GetInstance().SetGameScore(m_correct, m_questionNum);
}

void SceneMain::Init()
{
	// ゲームデータ初期化
	m_pAction->Init();
	// UI設定
	m_pUiManager->Init();
	// マップ描画設定
	m_pMapDraw->Init();
}

void SceneMain::Update(const InputState& input)
{
	if (input.IsTriggered(InputType::pause))
	{
		m_Manager.PushScene(new ScenePause(m_Manager));
	}

	// 更新処理のメンバ関数ポインタ
	(this->*m_updateFunc)(input);

	// UI更新
	m_pUiManager->Update();
	m_pUiManager->SetCharacterInfo(m_pAction->GetCharaStatus());
}

void SceneMain::Draw()
{
	// マップ描画
	m_pMapDraw->Draw();

	(this->*m_drawFunc)();

	// UI描画
	m_pUiManager->Draw();

	// ステージ範囲描画
	DrawBox(Game::kGameWidthLeft, Game::kGameHeightTop, Game::kGameWidthRight, Game::kGameHeightBottom, GetColor(255, 255, 255), FALSE);
}

void SceneMain::End()
{
}

void SceneMain::NormalUpdate(const InputState& input)
{
	m_pAction->Update(input);
}

void SceneMain::NormalDraw()
{
	m_pAction->Draw();
}
