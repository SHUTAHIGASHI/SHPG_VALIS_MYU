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
	// �^�C�g�����S�`��ʒu
	constexpr float kLogoDrawPosX = 225.0f;
	constexpr float kLogoDrawPosY = Game::kScreenHeight - 120.0f;
}

SceneMain::SceneMain(SceneManager& manager):
	Scene(manager),
	m_updateFunc(&SceneMain::NormalUpdate),
	m_drawFunc(&SceneMain::NormalDraw),
	m_isEnd(false),
	m_pAction(std::make_shared<Action>()),
	m_pCharaDraw(std::make_shared<CharaDraw>()),
	m_pUiManager(std::make_shared<UiManager>()),
	m_pMapDraw(std::make_shared<MapDraw>())
{
	// �A�N�V�����}�l�[�W���[�ݒ�
	m_pAction->SetUiManager(m_pUiManager.get());
	// �L�����`��ݒ�
	m_pCharaDraw->SetImage(Game::kCharaFileName);
	m_pCharaDraw->SetPos(Game::kScreenWidthHalf, Game::kScreenHeightHalf);
	// UI�ݒ�
	m_pUiManager->Init();
	// �}�b�v�`��ݒ�
	m_pMapDraw->Init();
}

SceneMain::~SceneMain()
{
	// �Q�[���|�C���g�ۑ�
	//GameDataManager::GetInstance().SetGameScore(m_correct, m_questionNum);

	// �摜�J��
	m_hTitleLogoImg = -1;
}

void SceneMain::Init()
{
	m_hTitleLogoImg = Load::GetInstance().GetHandle("title");
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
	m_pUiManager->Update();
	m_pUiManager->SetCharacterInfo(m_pAction->GetCharaStatus());
}

void SceneMain::Draw()
{
	// �}�b�v�`��
	m_pMapDraw->Draw();

	(this->*m_drawFunc)();

	// UI�`��
	m_pUiManager->Draw();

	// �^�C�g�����S�`��
	DrawRotaGraphF(kLogoDrawPosX, kLogoDrawPosY, 0.3, 0.0, m_hTitleLogoImg, true);
}

void SceneMain::End()
{
}

void SceneMain::NormalUpdate(const InputState& input)
{
	m_pAction->Update(input);
	m_pCharaDraw->SetPos(m_pAction->GetCharaStatus().drawPos.x, m_pAction->GetCharaStatus().drawPos.y);
}

void SceneMain::NormalDraw()
{
	m_pAction->Draw();
	m_pCharaDraw->Draw();
}
