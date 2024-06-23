#include "UiManager.h"
#include "UiBar.h"

namespace
{
	// UI�e�L�X�g�`��Ԋu
	constexpr int kDrawInterval = 40;
	// UI�`��ʒu
	constexpr float kUiDrawPosX = Game::kUiWidthRight / 2;
	constexpr float kUiDrawPosY = 100.0f;
	// �X�e�[�^�X�o�[�`��ʒu
	constexpr float kStatusPosInterval = 50.0f;
	constexpr float kStatusDrawPosX = Game::kUiWidthRight / 2 + 50.0f ;
	constexpr float kStatusDrawPosY = 220.0f;

	// ���O�̗���鑬�x
	constexpr int kLogSpeed = 6.0f;
}

UiManager::UiManager():
	m_charaState(),
	m_statusDrawPos(VGet(0.0f, 0.0f, 0.0f)),
	m_uiBars()
{
	// UI�o�[������
	m_uiBars["exp"] = new UiBar(1000);
	m_uiBars["exp"]->SetColor(0x00ff00);
	m_uiBars["exp"]->SetBarName("�o���l");
	m_uiBars["hunger"] = new UiBar(1000);
	m_uiBars["hunger"]->SetColor(0xffff00);
	m_uiBars["hunger"]->SetBarName("��");
	m_uiBars["happy"] = new UiBar(1000);
	m_uiBars["happy"]->SetColor(0x00ffff);
	m_uiBars["happy"]->SetBarName("�K��");
	m_uiBars["sleep"] = new UiBar(1000);
	m_uiBars["sleep"]->SetColor(0xff0000);
	m_uiBars["sleep"]->SetBarName("���C");
}

UiManager::~UiManager()
{
}

void UiManager::Init()
{
}

void UiManager::Update()
{	
	// ���l�X�V
	m_uiBars["exp"]->ChangeMaxNum(m_charaState.expMax);
	m_uiBars["exp"]->UpdateUIData(m_charaState.exp);
	m_uiBars["hunger"]->UpdateUIData(m_charaState.hunger);
	m_uiBars["happy"]->UpdateUIData(m_charaState.happy);
	m_uiBars["sleep"]->UpdateUIData(m_charaState.sleep);

	// �o�[�̍X�V
	int i = 0;
	for (auto uiBar : m_uiBars)
	{
		uiBar.second->SetDrawPos(kStatusDrawPosX, kStatusDrawPosY + (kStatusPosInterval * i));
		uiBar.second->Update();
		i++;
	}

	// ���O�X�V
	UpdateLogText();
}

void UiManager::Draw()
{
	// UI�e�L�X�g�`��
	std::vector<std::string> uiTexts = {
		"���O�F" + m_charaState.name,
		"���x���F" + std::to_string(m_charaState.level)
	};
	int drawY = 0;
	// �e�L�X�g�`��
	for (auto& text : uiTexts)
	{
		auto textLength = GetDrawFormatStringWidth("%s", text.c_str());
		DrawFormatString(kUiDrawPosX - (textLength / 2), kUiDrawPosY + drawY, 0xffffff, "%s", text.c_str());
		drawY += kDrawInterval;
	}

	// �o�[�`��
	for (auto uiBar : m_uiBars)
	{
		uiBar.second->Draw();
	}

	// �w�i�`��
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 150);
	DrawBox(Game::kUiWidthLeft, Game::kUiHeightBottom - Game::kChipSize, Game::kScreenWidth, Game::kScreenHeight, 0x000000, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	// ���݂̍s����ԕ`��
	DrawActionState();

	// �A��̃e�L�X�g�`��
	DrawLogText();
}

void UiManager::AddLog(std::string log)
{
	m_logs.push_back(UiLog(log));
}

void UiManager::OnReturning(std::list<std::string> charaName)
{
	std::string drawText = m_charaState.name + "��";
	for (auto& name : charaName)
	{
		drawText += name + "��";
	}
	drawText += "�V��ŋA���Ă����I";
	m_logs.push_back(UiLog(drawText));
}

void UiManager::DrawActionState()
{
	// �`�悷���Ԑ؂�ւ�
	std::string actionText = "�s���F";;
	switch (static_cast<int>(m_charaState.action))
	{
	case 0:
		actionText += "�ҋ@��";
		break;
	case 1:
		actionText += "�H����";
		break;
	case 2:
		actionText += "������";
		break;
	case 3:
		actionText += "�V�ђ�";
		break;
	case 4:
		actionText += "�O�o��";
		break;
	}
	// �s����ԕ`��
	auto textLength = GetDrawFormatStringWidth(actionText.c_str());
	DrawFormatString((Game::kUiWidthRight / 2) - textLength / 2, 800, 0xffffff, "%s", actionText.c_str());
}

void UiManager::UpdateLogText()
{
	// ���O�X�V
	for (auto& log : m_logs)
	{
		log.pos.x -= kLogSpeed;
		if (log.pos.x + log.textLength < 0.0f)
		{
			// ���O�폜
			m_logs.pop_front();
			break;
		}
	}
}

void UiManager::DrawLogText()
{
	// ���O�`��
	for (auto& log : m_logs)
	{
		DrawFormatString(log.pos.x, log.pos.y, 0xffffff, "%s", log.log.c_str());
	}
}