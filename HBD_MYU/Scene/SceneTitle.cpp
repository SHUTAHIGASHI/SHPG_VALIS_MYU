#include "SceneTitle.h"
#include "SoundManager.h"
#include "SceneManager.h"
#include "SceneMain.h"
#include "SceneHowTo.h"
#include "SceneOption.h"
#include "SelectMenuBase.h"
#include "Load.h"

namespace
{
	// �^�C�g�����S�`��ʒu
	constexpr float kLogoDrawPosX = Game::kScreenWidthHalf;
	constexpr float kLogoDrawPosY = 300.0f;
	// �e�L�X�g�`��ʒu
	constexpr float kTextDrawPosY = Game::kScreenHeightHalf + 160.0f;
	constexpr float kTextDrawSpace = Game::kFontSize;
	// �e�L�X�g
	const char* const kMenuTexts[] = 
	{ 
		"�Q�[���X�^�[�g", 
		"�����т���", 
		"�ݒ�", 
		"�I��"
	};
}

SceneTitle::SceneTitle(SceneManager& manager) : Scene(manager),
m_updateFunc(&SceneTitle::NormalUpdate),
m_countFrame(0),
m_hTitleLogoImg(-1),
m_pSelectMenu(std::make_shared<SelectMenuBase>())
{
	// �f�[�^�ǂݍ���
	LoadData();
}

SceneTitle::~SceneTitle()
{
	// BGM��~
	SoundManager::GetInstance().StopBGM();
	// �摜�n���h�����
	m_hTitleLogoImg = -1;
}

void SceneTitle::Init()
{
	// �I�����j���[�̏�����
	m_pSelectMenu->Init(true);
	// �I�����ڒǉ�
	for (const auto& item : kMenuTexts)
	{
		m_pSelectMenu->AddSelectItem(item);
	}
	// �I�����ڕ`��ʒu�ݒ�
	m_pSelectMenu->SetDrawPos(Game::kScreenWidthHalf, kTextDrawPosY);
}

void SceneTitle::Update(const InputState& input)
{
	// ���y�Đ��J�n
	if (SoundManager::GetInstance().IsPlayingMusic() != 1)
	{
		SoundManager::GetInstance().PlayMusic();
	}

	// ���t���[���J�E���g
	m_countFrame++;
	// �X�V�����̃����o�֐��|�C���^
	(this->*m_updateFunc)(input);
}

void SceneTitle::Draw()
{
	// �^�C�g�����S�`��
	DrawRotaGraphF(kLogoDrawPosX, kLogoDrawPosY, 1.0, 0, m_hTitleLogoImg, true);
	// �I�����ڕ`��
	m_pSelectMenu->Draw();
}

void SceneTitle::End()
{
}

void SceneTitle::LoadData()
{
	// �摜�ǂݍ���
	m_hTitleLogoImg = Load::GetInstance().GetHandle("title");
}

void SceneTitle::OnSceneEnd()
{
	// �J�[�\�����͈͓��łȂ��ꍇ�͏������Ȃ�
	if (!m_pSelectMenu->IsCursorRanged())
	{
		return;
	}

	// �I�����ڂɂ���ăV�[���J��
	if (m_pSelectMenu->GetSelectedNum() == 0)
	{
		m_Manager.ChangeScene(new SceneMain(m_Manager));
	}
	else if (m_pSelectMenu->GetSelectedNum() == 1)
	{
		m_Manager.PushScene(new SceneHowTo(m_Manager));
	}
	else if (m_pSelectMenu->GetSelectedNum() == 2)
	{
		m_Manager.PushScene(new SceneOption(m_Manager));
	}
	else if (m_pSelectMenu->GetSelectedNum() == 3)
	{
		m_Manager.GameEnd();
	}
	return;
}

void SceneTitle::NormalUpdate(const InputState& input)
{
	// �I�����ڕ`��
	m_pSelectMenu->Update(input);

	if (input.IsTriggered(InputType::select))
	{
		SoundManager::GetInstance().PlaySE(SoundType::select);
		OnSceneEnd();
		return;
	}
}
