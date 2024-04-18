#include "SceneMain.h"
#include "SceneManager.h"
#include "SoundManager.h"
#include "GameDataManager.h"
#include "Player.h"
#include "ScenePause.h"
#include "Action.h"
#include "CharaDraw.h"

namespace
{

}

SceneMain::SceneMain(SceneManager& manager):
	Scene(manager),
	m_updateFunc(&SceneMain::NormalUpdate),
	m_drawFunc(&SceneMain::NormalDraw),
	m_isEnd(false),
	m_actionMenu(std::make_shared<Action>()),
	m_charaDraw(std::make_shared<CharaDraw>())
{
	// キャラ描画設定
	m_charaDraw->SetImage(Game::kCharaFileName);
	m_charaDraw->SetPos(Game::kScreenWidthHalf, Game::kScreenHeightHalf);
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
}

void SceneMain::Draw()
{
	(this->*m_drawFunc)();
}

void SceneMain::NormalUpdate(const InputState& input)
{
	m_actionMenu->Update(input);
}

void SceneMain::NormalDraw()
{
	DrawBox(Game::kGameWidthLeft, Game::kGameHeightTop, Game::kGameWidthRight, Game::kGameHeightBottom, Game::kColorWhite, false);

	DrawFormatString(Game::kGameWidthLeft + 10, Game::kGameHeightTop + 10, Game::kColorWhite, "%d", static_cast<int>(m_actionMenu->GetMyuState()));

	m_actionMenu->Draw();
	m_charaDraw->Draw();
}
