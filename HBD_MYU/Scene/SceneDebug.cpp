#include "SceneDebug.h"
#include "Game.h"
#include "SceneManager.h"
#include "SceneMain.h"
#include "SceneTitle.h"
#include "ScenePause.h"
#include "SceneCredit.h"
#include "SceneAction.h"

namespace
{
	// �I���\���ڂ̐�
	constexpr int kSelectItemNum = 5;
	// �e�L�X�g
	const char* const kTextGameMain = "���C��";
	const char* const kTextGameTitleMenu = "�^�C�g��";
	const char* const kTextGamePause = "�|�[�Y";
	const char* const kTextCredit = "�N���W�b�g";
	const char* const kTextAction = "�A�N�V����";
	const char* const kTextGameEnd = "�I��";
}

SceneDebug::SceneDebug(SceneManager& manager) :
	Scene(manager),
	m_selectedPos(0),
	m_selectedItemName()
{
}

SceneDebug::~SceneDebug()
{
}

void SceneDebug::Update(const InputState& input)
{
	if (input.IsTriggered(InputType::back))
	{
		m_Manager.GameEnd();
		return;
	}

	if (input.IsTriggered(InputType::select))
	{
		SoundManager::GetInstance().PlaySE(SoundType::select);

		if (m_selectedPos == 0)
		{
			m_Manager.ChangeScene(new SceneMain(m_Manager));
		}
		else if (m_selectedPos == 1)
		{
			m_Manager.ChangeScene(new SceneTitle(m_Manager));
		}
		else if (m_selectedPos == 2)
		{
			m_Manager.PushScene(new ScenePause(m_Manager));
		}
		else if (m_selectedPos == 3)
		{
			m_Manager.ChangeScene(new SceneCredit(m_Manager));
		}
		else if (m_selectedPos == 4)
		{
			m_Manager.PushScene(new SceneAction(m_Manager));
		}
		else
		{
			m_Manager.GameEnd();
		}
		return;
	}

	if (input.IsTriggered(InputType::up))
	{
		m_selectedPos--;
		if (m_selectedPos < 0) m_selectedPos = kSelectItemNum;
	}
	else if (input.IsTriggered(InputType::down))
	{
		m_selectedPos++;
		if (m_selectedPos > kSelectItemNum) m_selectedPos = 0;
	}

	UpdateText();
}

void SceneDebug::Draw()
{
	DrawFormatString(100, 100, 0xffffff, "�f�o�b�N�V�[��");
	DrawFormatString(Game::kScreenWidthHalf, Game::kScreenHeightHalf, 0xffff00, "%s", m_selectedItemName.c_str());
}

void SceneDebug::UpdateText()
{
	if (m_selectedPos == 0)
	{
		m_selectedItemName = kTextGameMain;
	}
	else if (m_selectedPos == 1)
	{
		m_selectedItemName = kTextGameTitleMenu;
	}
	else if (m_selectedPos == 2)
	{
		m_selectedItemName = kTextGamePause;
	}
	else if (m_selectedPos == 3)
	{
		m_selectedItemName = kTextCredit;
	}
	else if (m_selectedPos == 4)
	{
		m_selectedItemName = kTextAction;
	}
	else
	{
		m_selectedItemName = kTextGameEnd;
	}
}
