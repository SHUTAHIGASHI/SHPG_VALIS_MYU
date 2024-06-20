#include "UiManager.h"
#include "UiBar.h"

namespace
{
	// UIテキスト描画間隔
	constexpr int kDrawInterval = 40;
	// UI描画位置
	constexpr float kUiDrawPosX = Game::kUiWidthRight / 2;
	constexpr float kUiDrawPosY = 100.0f;
	// ステータスバー描画位置
	constexpr float kStatusPosInterval = 50.0f;
	constexpr float kStatusDrawPosX = Game::kUiWidthRight / 2 + 50.0f ;
	constexpr float kStatusDrawPosY = 220.0f;

	// お出かけ後のテキスト描画時間
	constexpr int kReturningTextDrawTime = 120;
}

UiManager::UiManager():
	m_charaState(),
	m_statusDrawPos(VGet(0.0f, 0.0f, 0.0f)),
	m_outingCharaName(),
	m_returningTextCount(0),
	m_uiBars()
{
	m_uiBars["exp"] = new UiBar(1000);
	m_uiBars["exp"]->SetColor(0x00ff00);
	m_uiBars["exp"]->SetBarName("経験値");
	m_uiBars["hunger"] = new UiBar(1000);
	m_uiBars["hunger"]->SetColor(0xffff00);
	m_uiBars["hunger"]->SetBarName("空腹");
	m_uiBars["happy"] = new UiBar(1000);
	m_uiBars["happy"]->SetColor(0x00ffff);
	m_uiBars["happy"]->SetBarName("幸福");
	m_uiBars["sleep"] = new UiBar(1000);
	m_uiBars["sleep"]->SetColor(0xff0000);
	m_uiBars["sleep"]->SetBarName("眠気");
}

UiManager::~UiManager()
{
}

void UiManager::Init()
{
}

void UiManager::Update()
{
	if (m_returningTextCount > 0)
	{
		m_returningTextCount--;
	}
	
	// 数値更新
	m_uiBars["exp"]->ChangeMaxNum(m_charaState.expMax);
	m_uiBars["exp"]->UpdateUIData(m_charaState.exp);
	m_uiBars["hunger"]->UpdateUIData(m_charaState.hunger);
	m_uiBars["happy"]->UpdateUIData(m_charaState.happy);
	m_uiBars["sleep"]->UpdateUIData(m_charaState.sleep);

	// バーの更新
	int i = 0;
	for (auto uiBar : m_uiBars)
	{
		uiBar.second->SetDrawPos(kStatusDrawPosX, kStatusDrawPosY + (kStatusPosInterval * i));
		uiBar.second->Update();
		i++;
	}
}

void UiManager::Draw()
{
	// UIテキスト描画
	std::vector<std::string> uiTexts = {
		"名前：" + m_charaState.name,
		"レベル：" + std::to_string(m_charaState.level)
	};
	int drawY = 0;
	// テキスト描画
	for (auto& text : uiTexts)
	{
		auto textLength = GetDrawFormatStringWidth("%s", text.c_str());
		DrawFormatString(kUiDrawPosX - (textLength / 2), kUiDrawPosY + drawY, 0xffffff, "%s", text.c_str());
		drawY += kDrawInterval;
	}

	// バー描画
	for (auto uiBar : m_uiBars)
	{
		uiBar.second->Draw();
	}

	// 背景描画
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 150);
	DrawBox(Game::kUiWidthLeft, Game::kUiHeightBottom - 200.0f, Game::kUiWidthRight, Game::kUiHeightBottom, 0x000000, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	// 現在の行動状態描画
	DrawActionState();

	// 帰宅時のテキスト描画
	if (m_returningTextCount > 0)
	{
		DrawReturningText();
	}	
}

void UiManager::DrawActionState()
{
	// 描画する状態切り替え
	std::string actionText = "行動：";;
	switch (static_cast<int>(m_charaState.action))
	{
	case 0:
		actionText += "待機中";
		break;
	case 1:
		actionText += "食事中";
		break;
	case 2:
		actionText += "睡眠中";
		break;
	case 3:
		actionText += "遊び中";
		break;
	case 4:
		actionText += "外出中";
		break;
	}
	// 行動状態描画
	auto textLength = GetDrawFormatStringWidth(actionText.c_str());
	DrawFormatString((Game::kUiWidthRight / 2) - textLength / 2, 800, 0xffffff, "%s", actionText.c_str());
}

void UiManager::DrawReturningText()
{
	std::string drawText2 = m_charaState.name + "は";
	for (auto& name : m_outingCharaName)
	{
		drawText2 += name + "と";
	}
	drawText2 += "遊んで帰ってきた！";
	DrawFormatString(0, 840, 0xffffff, "%s", drawText2.c_str());
}

void UiManager::OnReturning(std::list<std::string> charaName)
{
	m_outingCharaName = charaName;
	m_returningTextCount = kReturningTextDrawTime;
}
