#include "Action.h"
#include "Game.h"
#include "SelectMenuBase.h"
#include "ItemManager.h"
#include "UiManager.h"

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

	// お出かけ時間上限下限
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

	// キャラクター初期化
	m_pMyu->Init();
	// アイテム初期化
	m_pItem->Init();
}

void Action::Update(const InputState& input)
{
	// 更新処理のメンバ関数ポインタ
	(this->*m_updateFunc)();
	// キャラクターの更新
	m_pMyu->Update();
	// 選択メニューの更新
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
	// メニューを描画
	m_pSelectMenu->Draw();
}

void Action::OnIdle()
{
	m_pMyu->ChangeState(actionState::Idle);
	m_updateFunc = &Action::UpdateIdle;
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
	m_updateFunc = &Action::UpdateOuting;
	// 外出時間設定
	m_outingTimeCount = GetRand(kOutingTimeMax - kOutingTimeMin) + kOutingTimeMin;
	// 外出時のキャラ名設定
	SetRandomCharaName();
}

const state Action::GetCharaStatus() const
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
	printfDx("お出かけ中: %d\n", m_outingTimeCount);
	if (m_outingTimeCount < 0)
	{
		// お出かけ終了
		m_outingTimeCount = 0;
		OnIdle();
		m_pUi->OnReturning(m_outingCharaName);
	}
}
