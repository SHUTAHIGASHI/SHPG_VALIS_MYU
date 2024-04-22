#include "SceneMain.h"
#include "SceneManager.h"
#include "SoundManager.h"
#include "GameDataManager.h"
#include "Player.h"
#include "ScenePause.h"
#include "Action.h"
#include "CharaDraw.h"
#include "UiManager.h"

namespace
{

}

SceneMain::SceneMain(SceneManager& manager):
	Scene(manager),
	m_updateFunc(&SceneMain::NormalUpdate),
	m_drawFunc(&SceneMain::NormalDraw),
	m_isEnd(false),
	m_pAction(std::make_shared<Action>()),
	m_pCharaDraw(std::make_shared<CharaDraw>()),
	m_pUiManager(std::make_shared<UiManager>())
{
	// アクションマネージャー設定
	m_pAction->SetUiManager(m_pUiManager.get());
	// キャラ描画設定
	m_pCharaDraw->SetImage(Game::kCharaFileName);
	m_pCharaDraw->SetPos(Game::kScreenWidthHalf, Game::kScreenHeightHalf);
	// UI設定
	m_pUiManager->Init();
}

SceneMain::~SceneMain()
{
	// ゲームポイント保存
	//GameDataManager::GetInstance().SetGameScore(m_correct, m_questionNum);
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
	(this->*m_drawFunc)();

	// UI描画
	m_pUiManager->Draw();
}

void SceneMain::NormalUpdate(const InputState& input)
{
	m_pAction->Update(input);
}

void SceneMain::NormalDraw()
{
	DrawBox(Game::kGameWidthLeft, Game::kGameHeightTop, Game::kGameWidthRight, Game::kGameHeightBottom, Game::kColorWhite, false);

	m_pAction->Draw();
	m_pCharaDraw->Draw();
}
