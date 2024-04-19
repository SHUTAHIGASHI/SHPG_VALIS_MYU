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
	// �L�����`��ݒ�
	m_pCharaDraw->SetImage(Game::kCharaFileName);
	m_pCharaDraw->SetPos(Game::kScreenWidthHalf, Game::kScreenHeightHalf);
	// UI�ݒ�
	m_pUiManager->Init();
}

SceneMain::~SceneMain()
{
	// �Q�[���|�C���g�ۑ�
	//GameDataManager::GetInstance().SetGameScore(m_correct, m_questionNum);
}

void SceneMain::Update(const InputState& input)
{
	if (input.IsTriggered(InputType::pause))
	{
		m_Manager.PushScene(new ScenePause(m_Manager));
	}

	// �X�V�����̃����o�֐��|�C���^
	(this->*m_updateFunc)(input);

	// UI�X�V
	m_pUiManager->SetCharacterInfo(m_pAction->GetMyuStatus());
	m_pUiManager->Update();
}

void SceneMain::Draw()
{
	(this->*m_drawFunc)();

	// UI�`��
	m_pUiManager->Draw();
}

void SceneMain::NormalUpdate(const InputState& input)
{
	m_pAction->Update(input);
}

void SceneMain::NormalDraw()
{
	DrawBox(Game::kGameWidthLeft, Game::kGameHeightTop, Game::kGameWidthRight, Game::kGameHeightBottom, Game::kColorWhite, false);

	DrawFormatString(Game::kGameWidthLeft + 10, Game::kGameHeightTop + 10, Game::kColorWhite, "%d", static_cast<int>(m_pAction->GetActionState()));

	m_pAction->Draw();
	m_pCharaDraw->Draw();
}
