#include "Action.h"
#include "Game.h"
#include "SelectMenuBase.h"
#include "UiManager.h"

namespace
{
	// 選択項目名
	const char* const kMenuItems[] = {
		"ごはん",
		"ねむる",
		"レッスン",
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
	m_cursorPosX(0.0f),
	m_cursorPosY(0.0f),
	m_pMyu(std::make_shared<Myu>()),
	m_pSelectMenu(std::make_shared<SelectMenuBase>()),
	m_pUi(nullptr)
{
	// 各行動時の処理管理マップ
	m_selectFuncMap["ごはん"] = &Action::OnGiveFood;
	m_selectFuncMap["ねむる"] = &Action::OnSleep;
	m_selectFuncMap["レッスン"] = &Action::OnLesson;
	m_selectFuncMap["がいしゅつ"] = &Action::OnOuting;
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
	m_pSelectMenu->SetDrawPos(Game::kUiWidthRight / 2, Game::kScreenHeightHalf);

	// キャラクター初期化
	m_pMyu->Init();
}

void Action::Update(const InputState& input)
{
	// 更新処理のメンバ関数ポインタ
	(this->*m_updateFunc)(input);
	// キャラクターの更新
	m_pMyu->Update();
	// 選択メニューの更新
	m_pSelectMenu->Update(input);
	// 選択時の処理
	if (input.IsTriggered(InputType::select))
	{
		OnSelectItem(m_pSelectMenu->GetSelectedNum());
	}
}

void Action::Draw()
{
	// メニューを描画
	m_pSelectMenu->Draw();
	// キャラクターを描画
	m_pMyu->Draw();
}

void Action::OnIdle()
{
	// 待機
	m_pMyu->ChangeState(actionState::Idle);
	m_updateFunc = &Action::UpdateIdle;
}

void Action::OnGiveFood()
{
	// ごはんをあげる
	m_pMyu->ChangeState(actionState::Eat);
}

void Action::OnSleep()
{
	// 寝る
	m_pMyu->ChangeState(actionState::Sleep);
}

void Action::OnLesson()
{
	// レッスン
	m_pMyu->ChangeState(actionState::Lesson);
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

const charaState Action::GetCharaStatus() const
{
	return m_pMyu->GetStatus();
}

void Action::OnSelectItem(int index)
{
	// カーソルが範囲内でない場合は処理しない
	if (!m_pSelectMenu->IsCursorRanged())
	{
		return;
	}

	// 選択時の処理
	(this->*m_selectFuncMap[kMenuItems[index]])();
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

bool Action::CheckCursorRange()
{
	// カーソルが範囲内かどうか
	if (m_cursorPosX > Game::kGameWidthLeft &&
		m_cursorPosX < Game::kGameWidthRight &&
		m_cursorPosY > Game::kGameHeightTop &&
		m_cursorPosY < Game::kGameHeightBottom)
	{
		// 範囲内
		return true;
	}
	// 範囲外
	return false;
}

void Action::UpdateIdle(const InputState& input)
{
	// カーソル座標更新
	m_cursorPosX = input.GetMousePosX();
	m_cursorPosY = input.GetMousePosY();

	// 選択時の処理
	if (input.IsTriggered(InputType::select))
	{
		// カーソルが範囲内でない場合は処理しない
		if (CheckCursorRange())
		{
			// マウスで遊ぶ
			m_pMyu->OnMousePlaying(m_cursorPosX, m_cursorPosY);
		}
	}
}

void Action::UpdateOuting(const InputState& input)
{
	// 外出時間カウント
	m_outingTimeCount--;
	if (m_outingTimeCount < 0)
	{
		// お出かけ終了
		m_outingTimeCount = 0;
		OnIdle();
		m_pUi->OnReturning(m_outingCharaName);
	}
}
