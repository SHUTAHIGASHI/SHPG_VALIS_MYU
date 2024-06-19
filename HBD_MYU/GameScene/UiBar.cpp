#include "UiBar.h"
#include "Game.h"
#include "Player.h"

namespace
{
	// �Q�[�W�̍��W
	constexpr int kGaugeW = 100;
	constexpr int kGaugeH = 15;
	constexpr int kDrawPosDiff = 100;
}

UiBar::UiBar(int maxNum) :
	m_drawX(0),
	m_drawY(0),
	m_num(0),
	m_maxNum(0),
	m_currentNumRate(0.0f),
	m_maxNumRate(0.0f),
	m_color(0)
{
	// �ő�HP
	m_maxNum = maxNum;
	// �`����W
	m_drawX = 0;
	m_drawY = 0;
	// HP���̌v�Z
	m_maxNumRate = (static_cast<float>(m_maxNum) / m_maxNum) * kGaugeW;
}

UiBar::~UiBar()
{
}

void UiBar::Update()
{
	// HP���̌v�Z
	m_currentNumRate = (static_cast<float>(m_num) / m_maxNum) * kGaugeW;
}

void UiBar::UpdateUIData(int hp)
{
	// HP�̍X�V
	m_num = hp;
}

void UiBar::Draw()
{
	// HP�o�[�̕`��
	int drawX = m_drawX - static_cast<int>(m_maxNumRate / 2);
	int drawY = m_drawY - kDrawPosDiff;
	int drawW = drawX + static_cast<int>(m_currentNumRate);
	int drawH = drawY + kGaugeH;
	DrawBox(drawX, drawY, drawW, drawH, m_color, true);
	// �g�̕`��
	drawW = drawX + static_cast<int>(m_maxNumRate);
	DrawBox(drawX, drawY, drawW, drawH, 0xffffff, false);
}

void UiBar::SetDrawPos(int x, int y)
{
	m_drawX = x;
	m_drawY = y;
}
