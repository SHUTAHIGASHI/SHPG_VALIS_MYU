#include "Myu.h"

namespace
{
	// �X�e�[�^�X�ő�l
	constexpr double kMaxStatus = 1000.0;
	// �X�e�[�^�X������
	constexpr double kExpIncrease = 1.0;
	constexpr double kHungerIncrease = 0.5;
	constexpr double kSleepIncrease = 0.5;
	constexpr double kHappyIncrease = 0.5;
	// �X�e�[�^�X������
	constexpr double kHungerDecrease = 0.2;
	constexpr double kSleepDecrease = 0.2;
	constexpr double kHappyDecrease = 0.2;
	// �X�e�[�^�X�����l
	constexpr int kInitLevel = 1;
	constexpr double kInitExp = 0.0;
	constexpr double kInitHunger = 0.0;
	constexpr double kInitSleep = 0.0;
	constexpr double kInitHappy = kMaxStatus / 2;

	// �s����̑ҋ@�t���[��
	constexpr int kActionEndFrame = 60;
	// �����ړ��t���[��
	constexpr int kRoomMoveFrame = 120;
	// �������̈ړ����x
	constexpr float kRoomMoveSpeed = 1.0f;

	// �o���l�ő�l
	constexpr double kMaxExp = 5000.0;
}

Myu::Myu():
	m_updateFuncMap(),
	m_updateIdleFuncMap(),
	m_nextPos(Game::kVecZero),
	m_state(),
	m_countFrame(0),
	m_actionEndFrameCount(0),
	m_roomMoveFrameCount(kRoomMoveFrame)
{
	// �X�V�֐��}�b�v
	m_updateFuncMap[actionState::Idle] = &Myu::UpdateIdle;
	m_updateFuncMap[actionState::Eat] = &Myu::UpdateEat;
	m_updateFuncMap[actionState::Sleep] = &Myu::UpdateSleep;
	m_updateFuncMap[actionState::Play] = &Myu::UpdatePlay;
	m_updateFuncMap[actionState::Outing] = &Myu::UpdateOuting;
	// �ҋ@��Ԃ̊���Ƃ̍X�V�֐��}�b�v
	m_updateIdleFuncMap[emotionState::Normal] = &Myu::UpdateIdleNormal;
}

Myu::~Myu()
{
	// �f�[�^�ꎞ�ۑ�
	GameDataManager::GetInstance().SaveTempData(m_state);
}

void Myu::Init()
{
	// �X�e�[�^�X������
	m_state.name = Game::kCharaName;
	m_state.drawPos = VGet(Game::kGameWidth, Game::kGameHeight, 0.0f);
	m_state.emotion = emotionState::Normal;
	m_state.action = actionState::Idle;
	GameDataManager::GetInstance().SetData(m_state);
	// �ړ��揉����
	m_nextPos = m_state.drawPos;
}

void Myu::Update()
{
	// �t���[���J�E���g
	m_countFrame++;

	// �X�e�[�^�X���Ƃ̍X�V���������o�֐��|�C���^
	(this->*m_updateFuncMap[m_state.action])();
	// �X�e�[�^�X�ő�l�Ǘ�
	StatusMaxCheck();

	// �X�e�[�^�X�ω�
	m_state.exp += kExpIncrease;
	// ���x���A�b�v����
	LevelUp();
}

void Myu::ChangeState(actionState state)
{
	m_state.action = state;
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

void Myu::StatusMaxCheck()
{
	// �X�e�[�^�X�ő�l�Ǘ�
	if (m_state.hunger > kMaxStatus)
	{
		m_state.hunger = kMaxStatus;
	}
	if (m_state.sleep > kMaxStatus)
	{
		m_state.sleep = kMaxStatus;
	}
	if (m_state.happy > kMaxStatus)
	{
		m_state.happy = kMaxStatus;
	}
}

void Myu::UpdateRoomMove()
{
	if (m_roomMoveFrameCount < 0)
	{
		return;
	}

	// �ړ�����
	auto moveDir = VSub(m_nextPos, m_state.drawPos);
	if(VSize(moveDir) < 1.0f)
	{
		return;
	}
	// �ړ�������0�łȂ��ꍇ�͐��K��
	if (VSize(moveDir) > 0) moveDir = VNorm(moveDir);
	// �ړ������ɑ��x���|����
	moveDir = VScale(moveDir, kRoomMoveSpeed);
	// �ړ�
	m_state.drawPos = VAdd(m_state.drawPos, moveDir);
}

void Myu::UpdateIdle()
{
	// �X�e�[�^�X�ω�
	if(m_countFrame % 30 == 0)
	{
		m_state.hunger += kHungerIncrease;
		m_state.sleep += kSleepIncrease;
		m_state.happy -= kHappyIncrease;
		m_countFrame = 0;
	}

	// ����Ƃ̏���
	(this->*m_updateIdleFuncMap[emotionState::Normal])();

	// �������̈ړ�����
	UpdateRoomMove();
}

void Myu::UpdateEat()
{
	// �X�e�[�^�X�ω�
	m_state.hunger -= kHungerDecrease;
	m_state.sleep += kSleepIncrease;
	if (m_state.hunger < kInitHunger)
	{
		m_state.hunger = kInitHunger;
		ChangeState(actionState::Idle);
	}
}

void Myu::UpdateSleep()
{
	// �X�e�[�^�X�ω�
	m_state.sleep -= kSleepDecrease;
	m_state.hunger += kHungerIncrease;
	m_state.happy += kHappyIncrease;
	if (m_state.sleep < kInitSleep)
	{
		m_state.sleep = kInitSleep;
		ChangeState(actionState::Idle);
	}
}

void Myu::UpdatePlay()
{
	// �X�e�[�^�X�ω�
	m_state.happy += kHappyDecrease;
	if (m_state.happy > kInitHappy)
	{
		m_state.happy = kInitHappy;
		ChangeState(actionState::Idle);
	}
}

void Myu::UpdateOuting()
{
	// �X�e�[�^�X�ω�
	m_state.happy += kHappyIncrease * 2;
}

void Myu::UpdateIdleNormal()
{
	m_roomMoveFrameCount--;
	// �X�e�[�^�X�ω�
	if (m_roomMoveFrameCount > 0)
	{
		return;
	}

	m_roomMoveFrameCount = GetRand(kRoomMoveFrame);
	// �����_���ŏ㉺�̈ړ������擾
	// 0:�����Ȃ� 1:�� 2:��
	auto verticalMove = GetRand(2);
	// �����̒��������_���ňړ�
	switch (verticalMove)
	{
	case 0:
		break;
	case 1:
		m_nextPos.x += Game::kChipSize;
		break;
	case 2:
		m_nextPos.x -= Game::kChipSize;
		break;
	}
	// �����_���ō��E�̈ړ������擾
	// 0:�����Ȃ� 1:�� 2:�E
	auto sideMove = GetRand(2);
	// �����̒��������_���ňړ�
	switch (sideMove)
	{
	case 0:
		break;
	case 1:
		m_nextPos.y += Game::kChipSize;
		break;
	case 2:
		m_nextPos.y -= Game::kChipSize;
		break;
	}

	// �X�e�[�W�O�ɏo�Ȃ��悤�ɂ���
	if (m_nextPos.x < Game::kGameWidthLeft)
	{
		m_nextPos.x = Game::kGameWidthLeft;
	}
	if (m_nextPos.x > Game::kGameWidthRight)
	{
		m_nextPos.x = Game::kGameWidthRight;
	}
	if (m_nextPos.y < Game::kGameHeightTop)
	{
		m_nextPos.y = Game::kGameHeightTop;
	}
	if (m_nextPos.y > Game::kGameHeightBottom)
	{
		m_nextPos.y = Game::kGameHeightBottom;
	}
}

