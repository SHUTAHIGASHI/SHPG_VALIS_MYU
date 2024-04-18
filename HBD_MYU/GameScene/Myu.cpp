#include "Myu.h"

namespace
{
	// ステータス最大値
	constexpr double kMaxStatus = 1000.0;
	// ステータス変化量
	constexpr double kExpChange = 10.0;
	constexpr double kHungerChange = 1.0;
	constexpr double kSleepChange = 1.0;
	constexpr double kHappyChange = 1.0;
	// 経験値最大値
	constexpr double kMaxExp = 1000.0;
}

Myu::Myu():
	m_updateFunc(&Myu::UpdateIdle),
	m_state()
{
}

Myu::~Myu()
{
}

void Myu::Init()
{
}

void Myu::Update()
{
	// 更新処理のメンバ関数ポインタ
	(this->*m_updateFunc)();
	// レベルアップ処理
	LevelUp();

	printfDx("hunger:%f sleep:%f happy:%f\n", m_state.hunger, m_state.sleep, m_state.happy);
	printfDx("level:%d exp:%f\n", m_state.level, m_state.exp);
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
	m_state.exp++;
	m_state.hunger += kHungerChange;
	m_state.sleep += kSleepChange;
	m_state.happy -= kHappyChange;
	if (m_state.hunger >= kMaxStatus)
	{
		ChangeState(actionState::Eat);
	}
	else if (m_state.sleep >= kMaxStatus)
	{
		ChangeState(actionState::Sleep);
	}
	else if (m_state.happy <= 0)
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
