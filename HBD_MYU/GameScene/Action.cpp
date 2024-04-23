#include "Action.h"
#include "Game.h"
#include "SelectMenuBase.h"
#include "ItemManager.h"
#include "UiManager.h"

namespace
{
	// �I�����ږ�
	const char* const kMenuItems[] = {
		"���͂�",
		"������",
		"�˂ނ�",
		"���������",
	};

	// ���o�������̃L������
	const char* const kOutingCharaName[] = {
		"�`�m",
		"�l�t�B",
		"�j�i",
		"����",
		"���B�b�e",
	};

	// ���o�������ԏ������
	constexpr int kOutingTimeMax = 60 * 2;
	constexpr int kOutingTimeMin = 60 * 1;
	//constexpr int kOutingTimeMax = 3600 * 5;
	//constexpr int kOutingTimeMin = 3600 * 1;
}

Action::Action():
	m_updateFunc(&Action::UpdateIdle),
	m_outingTimeCount(0),
	m_pMyu(std::make_shared<Myu>()),
	m_pItem(std::make_shared<ItemManager>()),
	m_pSelectMenu(std::make_shared<SelectMenu>())
{
	Init();
}

Action::~Action()
{
}

void Action::Init()
{
	m_pSelectMenu->Init(true);
	for(auto& item : kMenuItems)
	{
		m_pSelectMenu->AddSelectItem(item);
	}
	m_pSelectMenu->SetItemDrawPos(Game::kScreenWidthHalf / 3, Game::kScreenHeightHalf);

	// �L�����N�^�[������
	m_pMyu->Init();
	// �A�C�e��������
	m_pItem->Init();
}

void Action::Update(const InputState& input)
{
	// �X�V�����̃����o�֐��|�C���^
	(this->*m_updateFunc)();
	// �L�����N�^�[�̍X�V
	m_pMyu->Update();
	// �I�����j���[�̍X�V
	m_pSelectMenu->Update(input);
	if (input.IsTriggered(InputType::select))
	{
		OnSelectItem(m_pSelectMenu->GetSelectedIndex());
	}

	std::shared_ptr<ItemBase> testItem;
	if (input.IsTriggered(InputType::attack))
	{
		testItem = m_pItem->GetRandomItem(ItemType::Toys);
	}

	if(testItem != nullptr)
	{
		printfDx("Item: %s\n", testItem->GetName().c_str());
	}
}

void Action::Draw()
{
	// ���j���[��`��
	m_pSelectMenu->Draw();
}

void Action::OnIdle()
{
	m_pMyu->ChangeState(actionState::Idle);
	m_updateFunc = &Action::UpdateIdle;
}

void Action::OnGiveFood()
{
	// ���͂��������
	m_pMyu->ChangeState(actionState::Eat);
}

void Action::OnPlay()
{
	// �V��
	m_pMyu->ChangeState(actionState::Play);
}

void Action::OnSleep()
{
	// �Q��
	m_pMyu->ChangeState(actionState::Sleep);
}

void Action::OnOuting()
{
	// �O�o
	m_pMyu->ChangeState(actionState::Outing);
	m_updateFunc = &Action::UpdateOuting;
	// �O�o���Ԑݒ�
	m_outingTimeCount = GetRand(kOutingTimeMax - kOutingTimeMin) + kOutingTimeMin;
	// �O�o���̃L�������ݒ�
	SetRandomCharaName();
}

const state Action::GetCharaStatus() const
{
	return m_pMyu->GetStatus();
}

void Action::OnSelectItem(int index)
{
	// �I���������ڂɂ���ď����𕪊�
	switch (index)
	{
	case 0:
		OnGiveFood();
		break;
	case 1:
		OnPlay();
		break;
	case 2:
		OnSleep();
		break;
	case 3:
		OnOuting();
		break;
	default:
		break;
	}
}

void Action::SetRandomCharaName()
{
	m_outingCharaName.clear();
	unsigned int nameSize = GetRand((sizeof(kOutingCharaName) / sizeof(char*)) - 1);
	if(nameSize <= 0)
	{
		nameSize = 1;
	}
	for (int i = 0; i < nameSize; i++)
	{
		unsigned int index = GetRand((sizeof(kOutingCharaName) / sizeof(char*)) - 1);
		for (auto& name : m_outingCharaName)
		{
			if (name == kOutingCharaName[index])
			{
				index = GetRand((sizeof(kOutingCharaName) / sizeof(char*)) - 1);
				continue;
			}
		}
		m_outingCharaName.push_back(kOutingCharaName[index]);
	}
}

void Action::UpdateIdle()
{
}

void Action::UpdateOuting()
{
	m_outingTimeCount--;
	printfDx("���o������: %d\n", m_outingTimeCount);
	if (m_outingTimeCount < 0)
	{
		// ���o�����I��
		m_outingTimeCount = 0;
		OnIdle();
		m_pUi->OnReturning(m_outingCharaName);
	}
}
