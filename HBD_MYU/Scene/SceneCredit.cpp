#include "SceneCredit.h"
#include "SceneManager.h"
#include "SceneTitle.h"
#include "SceneMain.h"

namespace
{
	// �I���\���ڂ̐�
	constexpr int kSelectItemNum = 1;
	// �e�L�X�g
	const char* const kTextTitle = "�N���b�N�Ń^�C�g���֖߂�";
	// �X�N���[�����x
	constexpr float kScrollSpeed = 4.0f;
	// �X�N���[���ҋ@����
	constexpr int kScrollDelay = 60 * 3;
}

SceneCredit::SceneCredit(SceneManager& manager) :
	Scene(manager),
	m_bgPos(),
	m_countFrame(0),
	m_scrollWaitFrame(0),
	m_hCreditImg(-1),
	m_ClearGraphX(0),
	m_ClearGraphY(0),
	m_isCanScroll(false),
	m_isScrollEnd(false)
{
	m_hCreditImg = LoadGraph("Data/ImageData/Credit.png");
	// �O���t�T�C�Y�擾
	GetGraphSize(m_hCreditImg, &m_ClearGraphX, &m_ClearGraphY);
	m_bgPos = VGet(Game::kScreenWidthHalf, 0.0f, 0.0f);
}

SceneCredit::~SceneCredit()
{
	DeleteGraph(m_hCreditImg);
}

void SceneCredit::Update(const InputState& input)
{
	m_countFrame++;
	if (m_countFrame > 10000)
	{
		m_countFrame = 0;
	}

	m_scrollWaitFrame++;
	if (m_scrollWaitFrame > kScrollDelay)
	{
		m_scrollWaitFrame = kScrollDelay;
		m_isCanScroll = true;
	}

	// �X�N���[���͈̔̓`�F�b�N
	if (m_bgPos.y <= -Game::kScreenHeight * 2)
	{
		m_isScrollEnd = true;
	}
	else
	{
		m_isScrollEnd = false;
	}

	// �X�N���[����
	if (!m_isScrollEnd)
	{
		if (m_isCanScroll)
		{
			m_bgPos.y += -kScrollSpeed;
			if (m_bgPos.y < -Game::kScreenHeight * 3)
			{
				m_bgPos.y = -Game::kScreenHeight * 3;
			}
		}

		/*if (input.IsPressed(InputType::up))
		{
			m_bgPos.y += kScrollSpeed;
			if (m_bgPos.y > 0.0f)
			{
				m_bgPos.y = 0.0f;
			}
		}
		else if (input.IsPressed(InputType::down))
		{
			m_bgPos.y += -kScrollSpeed;
			if (m_bgPos.y < -Game::kScreenHeight * 3)
			{
				m_bgPos.y = -Game::kScreenHeight * 3;
			}
		}*/
	}
	// �X�N���[����
	else
	{
		if (input.IsTriggered(InputType::select))
		{
			SoundManager::GetInstance().PlaySE(SoundType::select);

			m_Manager.PopScene();
			return;
		}
	}
}

void SceneCredit::Draw()
{
	DrawRotaGraphF(m_bgPos.x, m_bgPos.y + m_ClearGraphY / 2, 1.0, 0.0, m_hCreditImg, true);
	if (m_isScrollEnd)
	{
		DrawMenuText();
	}
	else
	{
		if ((m_countFrame / 10) % 6 != 0)
		{
			DrawFormatStringF(Game::kScreenWidth - 300.0f, 
				Game::kScreenHeight - 100, Game::kColorGray, "���ւÂ���");
			DrawFormatStringF(Game::kScreenWidth - 300.0f,
				Game::kScreenHeight - 100 - 2, Game::kColorWhite, "���ւÂ���");
		}
	}
}

void SceneCredit::DrawMenuText()
{
	float stringLength = static_cast<float>(GetDrawFormatStringWidth(kTextTitle));
	if ((m_countFrame / 10) % 6 != 0)
	{
		DrawFormatStringF(Game::kScreenWidthHalf - (stringLength / 2), Game::kScreenHeight - 100, Game::kColorGray, "%s", kTextTitle);
		DrawFormatStringF(Game::kScreenWidthHalf - (stringLength / 2), Game::kScreenHeight - 100 - 2, Game::kColorWhite, "%s", kTextTitle);
	}
}
