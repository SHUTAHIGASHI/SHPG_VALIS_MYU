#include "Myu.h"

namespace
{
	// ステータス最大値
	constexpr double kMaxStatus = 1000.0;
	// ステータス変化量
	constexpr double kExpChange = 10.0;
	constexpr double kHungerChange = 0.5;
	constexpr double kSleepChange = 0.5;
	constexpr double kHappyChange = 0.5;
	// ステータス初期値
	constexpr int kInitLevel = 1;
	constexpr double kInitExp = 0.0;
	constexpr double kInitHunger = 0.0;
	constexpr double kInitSleep = 0.0;
	constexpr double kInitHappy = kMaxStatus / 2;
	// 経験値最大値
	constexpr double kMaxExp = 1000.0;
}

Myu::Myu():
	m_updateFunc(&Myu::UpdateIdle),
	m_countFrame(0)
{
}

Myu::~Myu()
{
}

void Myu::Init()
{
	// ステータス初期化
	m_state.name = Game::kCharaName;
	m_state.action = actionState::Idle;
	m_state.level = kInitLevel;
	m_state.exp = kInitExp;
	m_state.hunger = kInitHunger;
	m_state.sleep = kInitSleep;
	m_state.happy = kInitHappy;
}

void Myu::Update()
{
	// フレームカウント
	m_countFrame++;

	// 更新処理のメンバ関数ポインタ
	(this->*m_updateFunc)();
	// レベルアップ処理
	LevelUp();
}

void Myu::ChangeState(actionState state)
{
	m_state.action = state;
	if (state == actionState::Idle)
	{
		m_updateFunc = &Myu::UpdateIdle;
	}
	else if (state == actionState::Eat)
	{
		m_updateFunc = &Myu::UpdateEat;
	}
	else if (state == actionState::Sleep)
	{
		m_updateFunc = &Myu::UpdateSleep;
	}
	else if (state == actionState::Play)
	{
		m_updateFunc = &Myu::UpdatePlay;
	}
}

void Myu::LevelUp()
{
	if (m_state.exp > kMaxExp * (m_state.level * 0.5))
	{
		m_state.level++;
		m_state.exp = 0;
		return;
	}
}

void Myu::UpdateIdle()
{
	// ステータス変化
	m_state.exp++;
	if(m_countFrame % 30 == 0)
	{
		m_state.hunger += kHungerChange;
		m_state.sleep += kSleepChange;
		m_state.happy -= kHappyChange;
		m_countFrame = 0;
	}

	if (m_state.hunger > kMaxStatus)
	{
		ChangeState(actionState::Eat);
	}
	else if (m_state.sleep > kMaxStatus)
	{
		ChangeState(actionState::Sleep);
	}
	else if (m_state.happy < 0.0)
	{
		ChangeState(actionState::Play);
	}
}

void Myu::UpdateEat()
{
	m_state.exp++;
	m_state.hunger--;
	if (m_state.hunger <= 0)
	{
		m_state.hunger = 0;
		ChangeState(actionState::Idle);
	}
}

void Myu::UpdateSleep()
{
	m_state.exp++;
	m_state.sleep--;
	if (m_state.sleep <= 0)
	{
		m_state.sleep = 0;
		ChangeState(actionState::Idle);
	}
}

void Myu::UpdatePlay()
{
	m_state.exp++;
	m_state.happy++;
	if (m_state.happy > kMaxStatus)
	{
		m_state.happy = kMaxStatus;
		ChangeState(actionState::Idle);
	}
}

void Myu::UpdateOuting()
{
}
