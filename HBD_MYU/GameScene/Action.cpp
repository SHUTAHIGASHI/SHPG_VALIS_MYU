#include "Action.h"
#include "Game.h"
#include "SelectMenuBase.h"
#include "ItemManager.h"

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
}

Action::Action():
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
	m_pMyu->Update();
	m_pSelectMenu->Update(input);
	if (input.IsTriggered(InputType::select))
	{
		OnSelectItem(m_pSelectMenu->GetSelectedIndex());
	}

	std::shared_ptr<ItemBase> testItem;
	if (input.IsTriggered(InputType::attack))
	{
		testItem = m_pItem->GetRandomItem(ItemType::Food);
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
}

actionState Action::GetActionState() const
{
	return m_pMyu->GetStatus().action;
}

const state& Action::GetMyuStatus() const
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
	default:
		break;
	}
}
