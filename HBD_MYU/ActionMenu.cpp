#include "ActionMenu.h"
#include "Game.h"
#include "SelectMenuBase.h"

namespace
{
	// ‘I‘ğ€–Ú–¼
	const char* const kMenuItems[] = {
		"‚²‚Í‚ñ",
		"‚ ‚»‚Ô",
		"‚Ë‚Ş‚é",
	};
}

ActionMenu::ActionMenu():
	m_pMyu(std::make_shared<Myu>()),
	m_pSelectMenu(std::make_shared<SelectMenu>())
{
	Init();
}

ActionMenu::~ActionMenu()
{
}

void ActionMenu::Init()
{
	m_pSelectMenu->Init(true);
	for(auto& item : kMenuItems)
	{
		m_pSelectMenu->AddSelectItem(item);
	}
	m_pSelectMenu->SetItemDrawPos(Game::kScreenWidthHalf / 3, 100.0f);
}

void ActionMenu::Update(const InputState& input)
{
	m_pMyu->Update();
	m_pSelectMenu->Update(input);
	if (input.IsTriggered(InputType::select))
	{
		OnSelectItem(m_pSelectMenu->GetSelectedIndex());
	}
}

void ActionMenu::Draw()
{
	// ƒƒjƒ…[‚ğ•`‰æ
	m_pSelectMenu->Draw();
}

void ActionMenu::OnGiveFood()
{
	// ‚²‚Í‚ñ‚ğ‚ ‚°‚é
	m_pMyu->ChangeState(actionState::Eat);
}

void ActionMenu::OnPlay()
{
	// —V‚Ô
	m_pMyu->ChangeState(actionState::Play);
}

void ActionMenu::OnSleep()
{
	// Q‚é
	m_pMyu->ChangeState(actionState::Sleep);
}

actionState ActionMenu::GetMyuState() const
{
	return m_pMyu->GetState().action;
}

void ActionMenu::OnSelectItem(int index)
{
	// ‘I‘ğ‚µ‚½€–Ú‚É‚æ‚Á‚Äˆ—‚ğ•ªŠò
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
