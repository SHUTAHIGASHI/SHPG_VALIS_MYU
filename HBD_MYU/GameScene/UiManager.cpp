#include "UiManager.h"
#include "UiBar.h"

namespace
{
	// UI�e�L�X�g�`��Ԋu
	constexpr int kDrawInterval = 40;
	// UI�`��ʒu
	constexpr float kUiDrawPosX = 120.0f;
	constexpr float kUiDrawPosY = 100.0f;
	constexpr float kUiDrawPosInterval = 40.0f;

	// ���o������̃e�L�X�g�`�掞��
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
	
	// ���l�X�V
	m_uiBars["exp"]->UpdateUIData(m_charaState.exp);
	m_uiBars["hunger"]->UpdateUIData(m_charaState.hunger);
	m_uiBars["happy"]->UpdateUIData(m_charaState.happy);
	m_uiBars["sleep"]->UpdateUIData(m_charaState.sleep);

	// �o�[�̍X�V
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
		"���O�F" + m_charaState.name,
		"���x���F" + std::to_string(m_charaState.level),
		"�o���l�F" + std::to_string(m_charaState.exp),
		"�󕠁F" + std::to_string(m_charaState.hunger),
		"�K���F" + std::to_string(m_charaState.happy),
		"���C�F" + std::to_string(m_charaState.sleep)
	};

	// �o�[�`��
	for (auto uiBar : m_uiBars)
	{
		uiBar.second->Draw();
	}

	// ���݂̍s����ԕ`��
	DrawActionState();

	// �A��̃e�L�X�g�`��
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
	std::string drawText2 = m_charaState.name + "��";
	for (auto& name : m_outingCharaName)
	{
		drawText2 += name + "��";
	}
	drawText2 += "�V��ŋA���Ă����I";
	DrawFormatString(0, 840, 0xffffff, "%s", drawText2.c_str());
}

void UiManager::OnReturning(std::list<std::string> charaName)
{
	m_outingCharaName = charaName;
	m_returningTextCount = kReturningTextDrawTime;
}
