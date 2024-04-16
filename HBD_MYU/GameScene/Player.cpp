#include "Player.h"
#include "SceneMain.h"
#include "SubjectManager.h"

namespace
{
	// �{�^���̑I��͈�
	constexpr float kButtonScaleX = 75.0f;
	constexpr float kButtonScaleY = 75.0f;
	// �{�^���̕`��Ԋu
	constexpr float kButtonDrawDistance = 300.0f;
	// �{�^���̕`��ʒu
	constexpr float kButtonPosY = Game::kScreenHeightHalf + 250.0f;
	constexpr float kSoughtButtonPosX = Game::kScreenWidthHalf;
	constexpr float kSoughtButtonPosY = Game::kScreenHeightHalf + 400.0f;
	// �{�^���̊g�嗦
	constexpr double kButtonScale = 0.25;
	constexpr double kButtonScaleMin = 0.2;
}

Player::Player():
	m_chinoButtonSize(kButtonScale),
	m_notChinoButtonSize(kButtonScale),
	m_soughtButtonSize(kButtonScale),
	m_hChinoButton(-1),
	m_hNotChinoButton(-1),
	m_hSoughtButton(-1),
	m_ChinoButtonPos(VGet(0.0f, 0.0f, 0.0f)),
	m_NotChinoButtonPos(VGet(0.0f, 0.0f, 0.0f)),
	m_SoughtButtonPos(VGet(0.0f, 0.0f, 0.0f)),
	m_mouseState()
{
	// �}�E�X�J�[�\���̉摜�ǂݍ���
	m_hChinoButton = LoadGraph("Data/ImageData/SeikaiButton.png");
	m_hNotChinoButton = LoadGraph("Data/ImageData/MatigaiButton.png");
	m_hSoughtButton = LoadGraph("Data/ImageData/SoughtButton.png");
	// �{�^���ʒu�ݒ�
	SetButtonPos();
}

Player::~Player()
{
	DeleteGraph(m_hChinoButton);
	DeleteGraph(m_hNotChinoButton);
	DeleteGraph(m_hSoughtButton);
}

void Player::Update(const InputState& input)
{
	// �{�^���T�C�Y���Z�b�g
	AllButtonSizeReset();
	// �}�E�X�J�[�\�����W�擾
	m_mouseState.x = input.GetMousePosX();
	m_mouseState.y = input.GetMousePosY();
	// �J�[�\���X�V����
	CorsorUpdate(input);
}

void Player::Draw()
{
	// �{�^���̕`��
	DrawRotaGraphF(m_ChinoButtonPos.x, m_ChinoButtonPos.y, m_chinoButtonSize, 0.0, m_hChinoButton, true);
	DrawRotaGraphF(m_NotChinoButtonPos.x, m_NotChinoButtonPos.y, m_notChinoButtonSize, 0.0, m_hNotChinoButton, true);
	DrawRotaGraphF(m_SoughtButtonPos.x, m_SoughtButtonPos.y, m_soughtButtonSize, 0.0, m_hSoughtButton, true);
}

void Player::SetButtonPos()
{
	m_ChinoButtonPos = VGet(Game::kScreenWidthHalf - kButtonDrawDistance, kButtonPosY, 0.0f);
	m_NotChinoButtonPos = VGet(Game::kScreenWidthHalf + kButtonDrawDistance, kButtonPosY, 0.0f);
	m_SoughtButtonPos = VGet(kSoughtButtonPosX, kSoughtButtonPosY, 0.0f);
}

bool Player::ButtonRangeCheck(float posX, float posY)
{
	if (m_mouseState.x > posX - kButtonScaleX && m_mouseState.x < posX + kButtonScaleX
		&& m_mouseState.y > posY - kButtonScaleY && m_mouseState.y < posY + kButtonScaleY)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Player::AllButtonSizeReset()
{
	m_chinoButtonSize = kButtonScale;
	m_notChinoButtonSize = kButtonScale;
	m_soughtButtonSize = kButtonScale;
}

void Player::CorsorUpdate(const InputState& input)
{
	int selectPos = 0;

	if(ButtonRangeCheck(m_ChinoButtonPos.x, m_ChinoButtonPos.y))
	{
		m_chinoButtonSize = kButtonScaleMin;
		selectPos = 0;
	}
	else if (ButtonRangeCheck(m_NotChinoButtonPos.x, m_NotChinoButtonPos.y))
	{
		m_notChinoButtonSize = kButtonScaleMin;
		selectPos = 1;
	}
	else if (ButtonRangeCheck(m_SoughtButtonPos.x, m_SoughtButtonPos.y))
	{
		m_soughtButtonSize = kButtonScaleMin;
		selectPos = 2;
	}
	else
	{
		return;
	}

	// �I�����̏���
	if (m_pMain->IsAnswering())
	{
		if (input.IsTriggered(InputType::select))
		{
			if (selectPos == 0)
			{
				m_pSubjectManager->OnChino();
			}
			else if (selectPos == 1)
			{
				m_pSubjectManager->OnNotChino();
			}
			else if (selectPos == 2)
			{
				m_pSubjectManager->OnSought();
			}
		}
	}
}
