#include "Myu.h"

namespace
{
	// �X�e�[�^�X�ő�l
	constexpr double kMaxStatus = 1000.0;
	// �X�e�[�^�X�ω���
	constexpr double kExpChange = 10.0;
	constexpr double kHungerChange = 0.5;
	constexpr double kSleepChange = 0.5;
	constexpr double kHappyChange = 0.5;
	// �X�e�[�^�X�����l
	constexpr int kInitLevel = 1;
	constexpr double kInitExp = 0.0;
	constexpr double kInitHunger = 0.0;
	constexpr double kInitSleep = 0.0;
	constexpr double kInitHappy = kMaxStatus / 2;
	// �o���l�ő�l
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
	// �X�e�[�^�X������
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
	// �t���[���J�E���g
	m_countFrame++;

	// �X�V�����̃����o�֐��|�C���^
	(this->*m_updateFunc)();
	// ���x���A�b�v����
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
	// �X�e�[�^�X�ω�
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
