#include "UiManager.h"

namespace
{
	// UI�e�L�X�g�`��Ԋu
	constexpr int kDrawInterval = 40;
	// UI�`��ʒu
	constexpr int kUiDrawPosX = 0;
	constexpr int kUiDrawPosY = 0;
	// ���o������̃e�L�X�g�`�掞��
	constexpr int kReturningTextDrawTime = 60;
}

UiManager::UiManager():
	m_charaState(),
	m_statusDrawPos(VGet(0.0f, 0.0f, 0.0f)),
	m_outingCharaName(),
	m_returningTextCount(0)
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
	if (m_returningTextCount > 0)
	{
		m_returningTextCount--;
	}
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

	// ���݂̍s����ԕ`��
	DrawActionState();

	// �A��̃e�L�X�g�`��
	if (m_returningTextCount > 0)
	{
		DrawReturningText();
	}

	int drawY = 0;
	for(auto& text : uiTexts)
	{
		DrawFormatString(kUiDrawPosX, kUiDrawPosY + drawY, 0xffffff, "%s", text.c_str());
		drawY += kDrawInterval;
	}
}

void UiManager::DrawActionState()
{
	// �`�悷���Ԑ؂�ւ�
	std::string actionText;
	switch (static_cast<int>(m_charaState.action))
	{
	case 0:
		actionText = "�ҋ@��";
		break;
	case 1:
		actionText = "�H����";
		break;
	case 2:
		actionText = "������";
		break;
	case 3:
		actionText = "�V�ђ�";
		break;
	case 4:
		actionText = "�O�o��";
		break;
	}
	// �s����ԕ`��
	DrawFormatString(400, 800, 0xffffff, "�s���F%s", actionText.c_str());
}

void UiManager::DrawReturningText()
{
	std::string drawText1 = m_charaState.name + "���A���Ă����I";
	DrawFormatString(400, 800, 0xffffff, "%s", drawText1.c_str());
	std::string drawText2 = m_charaState.name + "��";
	for (auto& name : m_outingCharaName)
	{
		drawText2 += name + ",";
	}
	drawText2 += "�ƗV��ŋA���Ă����I";
	DrawFormatString(400, 840, 0xffffff, "%s", drawText2.c_str());
}

void UiManager::OnReturning(std::vector<std::string> charaName)
{
	m_outingCharaName = charaName;
	m_returningTextCount = kReturningTextDrawTime;
}
