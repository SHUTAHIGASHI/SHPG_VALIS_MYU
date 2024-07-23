#include "Action.h"
#include "Game.h"
#include "SelectMenuBase.h"
#include "UiManager.h"
#include "GameDataManager.h"

namespace
{
	// 選択項目名
	const char* const kMenuItems[] = {
		"ごはん",
		"ねむる",
		"レッスン",
		"がいしゅつ",
		"セーブ"
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
	m_updateFunc(&Action::UpdateIdle),
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
	m_selectFuncMap["セーブ"] = &Action::OnSave;

	// 自身のポインタをキャラに渡す
	m_pMyu->SetAction(this);
}

Action::~Action()
{
}

void Action::Init()
{
	// 選択メニュー初期化
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

void Action::OnReturnHome()
{
	// UI描画
	m_pUi->OnReturning(m_outingCharaName);
}

void Action::OnIdle()
{
	// 待機
	m_pMyu->ChangeState(actionState::Idle);
	m_updateFunc = &Action::UpdateIdle;
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
	unsigned int nameSize = GetRand((sizeof(kOutingCharaName) / sizeof(char*)));
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
	if (input.IsPressed(InputType::select))
	{
		// カーソルが範囲内でない場合は処理しない
		if (CheckCursorRange())
		{
			// マウスで遊ぶ
			m_pMyu->OnMousePlaying(m_cursorPosX, m_cursorPosY);
		}
	}
}

void Action::UpdateActioning(const InputState& input)
{
	if (m_pMyu->GetStatus().action == actionState::Idle)
	{
		// 待機状態になったら待機処理へ
		OnIdle();
	}
}

void Action::OnGiveFood()
{
	// ごはんをあげる
	m_pMyu->ChangeState(actionState::Eat);
	// 行動時の更新処理
	m_updateFunc = &Action::UpdateActioning;
}

void Action::OnSleep()
{
	// 寝る
	m_pMyu->ChangeState(actionState::Sleep);
	// 行動時の更新処理
	m_updateFunc = &Action::UpdateActioning;
}

void Action::OnLesson()
{
	// レッスン
	m_pMyu->ChangeState(actionState::Lesson);
	// 行動時の更新処理
	m_updateFunc = &Action::UpdateActioning;
}

void Action::OnOuting()
{
	// 外出
	m_pMyu->ChangeState(actionState::Outing);
	// 行動時の更新処理
	m_updateFunc = &Action::UpdateActioning;
	// 外出時のキャラ名設定
	SetRandomCharaName();
}

void Action::OnSave()
{
	// セーブ
	GameDataManager::GetInstance().SaveTempData(m_pMyu->GetStatus());
	// UI
	m_pUi->AddLog("セーブしました！");
}