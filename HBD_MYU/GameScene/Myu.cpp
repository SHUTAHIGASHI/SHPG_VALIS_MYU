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
	else
	{
		m_updateFunc = &Myu::UpdateActioning;
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

void Myu::AddStatus()
{
	// �s���p�^�[�����Ƃ̃X�e�[�^�X�ω�
	switch (static_cast<int>(m_state.action))
	{
	case 0:
		break;
	case 1:
		m_state.hunger -= kHungerChange;
		break;
	case 2:
		m_state.sleep -= kSleepChange;
		break;
	case 3:
		m_state.happy += kHappyChange;
		break;
	case 4:
		m_state.happy += kHappyChange;
		break;
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
}

void Myu::UpdateActioning()
{
	// �X�e�[�^�X�ω�
	m_state.exp += kExpChange;
	AddStatus();
}

