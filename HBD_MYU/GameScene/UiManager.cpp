#include "UiManager.h"
#include "UiBar.h"

namespace
{
	// UIテキスト描画間隔
	constexpr int kDrawInterval = 40;
	// UI描画位置
	constexpr float kUiDrawPosX = 120.0f;
	constexpr float kUiDrawPosY = 100.0f;
	constexpr float kUiDrawPosInterval = 40.0f;

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
	m_uiBars["hunger"] = new UiBar(1000);
	m_uiBars["hunger"]->SetColor(0xffff00);
	m_uiBars["happy"] = new UiBar(1000);
	m_uiBars["happy"]->SetColor(0x00ffff);
	m_uiBars["sleep"] = new UiBar(1000);
	m_uiBars["sleep"]->SetColor(0xff0000);
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
	m_uiBars["exp"]->UpdateUIData(m_charaState.exp);
	m_uiBars["hunger"]->UpdateUIData(m_charaState.hunger);
	m_uiBars["happy"]->UpdateUIData(m_charaState.happy);
	m_uiBars["sleep"]->UpdateUIData(m_charaState.sleep);

	// バーの更新
	int i = 0;
	for (auto uiBar : m_uiBars)
	{
		uiBar.second->SetDrawPos(kUiDrawPosX, kUiDrawPosY + (kUiDrawPosInterval * i));
		uiBar.second->Update();
		i++;
	}
}

void UiManager::Draw()
{
	std::vector<std::string> uiTexts = {
		"名前：" + m_charaState.name,
		"レベル：" + std::to_string(m_charaState.level),
		"経験値：" + std::to_string(m_charaState.exp),
		"空腹：" + std::to_string(m_charaState.hunger),
		"幸福：" + std::to_string(m_charaState.happy),
		"眠気：" + std::to_string(m_charaState.sleep)
	};

	// バー描画
	for (auto uiBar : m_uiBars)
	{
		uiBar.second->Draw();
	}

	// 現在の行動状態描画
	DrawActionState();

	// 帰宅時のテキスト描画
	if (m_returningTextCount > 0)
	{
		DrawReturningText();
	}

	/*int drawY = 0;
	for(auto& text : uiTexts)
	{
		DrawFormatString(kUiDrawPosX, kUiDrawPosY + drawY, 0xffffff, "%s", text.c_str());
		drawY += kDrawInterval;
	}*/
}

void UiManager::DrawActionState()
{
	// 描画する状態切り替え
	std::string actionText;
	switch (static_cast<int>(m_charaState.action))
	{
	case 0:
		actionText = "待機中";
		break;
	case 1:
		actionText = "食事中";
		break;
	case 2:
		actionText = "睡眠中";
		break;
	case 3:
		actionText = "遊び中";
		break;
	case 4:
		actionText = "外出中";
		break;
	}
	// 行動状態描画
	DrawFormatString(400, 800, 0xffffff, "行動：%s", actionText.c_str());
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
