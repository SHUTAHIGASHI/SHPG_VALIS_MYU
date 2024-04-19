#include "UiManager.h"

namespace
{
	// UIテキスト描画間隔
	constexpr int kDrawInterval = 40;
	// UI描画位置
	constexpr int kUiDrawPosX = 0;
	constexpr int kUiDrawPosY = 0;
}

UiManager::UiManager():
	m_charaState(),
	m_statusDrawPos(VGet(0.0f, 0.0f, 0.0f))
{
}

UiManager::~UiManager()
{
}

void UiManager::Init()
{
}

void UiManager::Update()
{
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

	int drawY = 0;
	for(auto& text : uiTexts)
	{
		DrawFormatString(kUiDrawPosX, kUiDrawPosY + drawY, 0xffffff, "%s", text.c_str());
		drawY += kDrawInterval;
	}
}