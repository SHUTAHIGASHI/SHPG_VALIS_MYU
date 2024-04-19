#include "UiManager.h"

namespace
{
	// UI�e�L�X�g�`��Ԋu
	constexpr int kDrawInterval = 40;
	// UI�`��ʒu
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
		"���O�F" + m_charaState.name,
		"���x���F" + std::to_string(m_charaState.level),
		"�o���l�F" + std::to_string(m_charaState.exp),
		"�󕠁F" + std::to_string(m_charaState.hunger),
		"�K���F" + std::to_string(m_charaState.happy),
		"���C�F" + std::to_string(m_charaState.sleep)
	};

	int drawY = 0;
	for(auto& text : uiTexts)
	{
		DrawFormatString(kUiDrawPosX, kUiDrawPosY + drawY, 0xffffff, "%s", text.c_str());
		drawY += kDrawInterval;
	}
}