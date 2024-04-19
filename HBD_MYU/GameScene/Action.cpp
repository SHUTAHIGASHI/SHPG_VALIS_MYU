#include "Action.h"
#include "Game.h"
#include "SelectMenuBase.h"
#include "ItemManager.h"

namespace
{
	// 選択項目名
	const char* const kMenuItems[] = {
		"ごはん",
		"あそぶ",
		"ねむる",
		"がいしゅつ",
	};

	// お出かけ時のキャラ名
	const char* const kOutingCharaName[] = {
		"チノ",
		"ネフィ",
		"ニナ",
		"ララ",
		"ヴィッテ",
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

	// キャラクター初期化
	m_pMyu->Init();
	// アイテム初期化
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
	// メニューを描画
	m_pSelectMenu->Draw();
}

void Action::OnGiveFood()
{
	// ごはんをあげる
	m_pMyu->ChangeState(actionState::Eat);
}

void Action::OnPlay()
{
	// 遊ぶ
	m_pMyu->ChangeState(actionState::Play);
}

void Action::OnSleep()
{
	// 寝る
	m_pMyu->ChangeState(actionState::Sleep);
}

void Action::OnOuting()
{
	// 外出
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
	// 選択した項目によって処理を分岐
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
