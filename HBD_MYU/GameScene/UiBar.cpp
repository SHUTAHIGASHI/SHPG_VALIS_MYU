#include "UiBar.h"
#include "Game.h"
#include "Player.h"

namespace
{
	// ゲージの座標
	constexpr int kGaugeW = 150;
	constexpr int kGaugeH = 30;
	// バーネームの描画位置補正値
	constexpr int kBarNameOffset = 6;
}

UiBar::UiBar(int maxNum) :
	m_drawX(0),
	m_drawY(0),
	m_num(0),
	m_maxNum(0),
	m_currentNumRate(0.0f),
	m_maxNumRate(0.0f),
	m_color(0),
	m_barName(),
	m_isDrawBarName(false)
{
	// 最大HP
	m_maxNum = maxNum;
	// 描画座標
	m_drawX = 0;
	m_drawY = 0;
	// HP率の計算
	m_maxNumRate = (static_cast<float>(m_maxNum) / m_maxNum) * kGaugeW;
}

UiBar::~UiBar()
{
}

void UiBar::Update()
{
	// HP率の計算
	m_currentNumRate = (static_cast<float>(m_num) / m_maxNum) * kGaugeW;
}

void UiBar::UpdateUIData(int hp)
{
	// HPの更新
	m_num = hp;
}

void UiBar::Draw()
{
	// HPバーの描画
	int drawX = m_drawX - static_cast<int>(m_maxNumRate / 2);
	int drawY = m_drawY;
	int drawW = drawX + static_cast<int>(m_currentNumRate);
	int drawH = drawY + kGaugeH;
	DrawBox(drawX, drawY, drawW, drawH, m_color, true);
	// 枠の描画
	drawW = drawX + static_cast<int>(m_maxNumRate);
	DrawBox(drawX, drawY, drawW, drawH, 0xffffff, false);
	// バーネームの描画
	auto textLength = GetDrawFormatStringWidth(m_barName.c_str());
	drawX = (m_drawX - kGaugeW / 2) - kBarNameOffset - textLength;
	drawY = (m_drawY - 20) + kGaugeH / 2;
	if (m_isDrawBarName)
	{
		DrawString(drawX, drawY, m_barName.c_str(), 0xffffff);
	}
}

void UiBar::SetDrawPos(int x, int y)
{
	m_drawX = x;
	m_drawY = y;
}
