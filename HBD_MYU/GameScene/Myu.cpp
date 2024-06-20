#include "Myu.h"
#include "CharaDraw.h"
#include "Load.h"

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
	// �}�E�X�Y�ꎞ�̃t���[��
	constexpr int kMousePlayingFrame = 60 * 6;

	// �������̈ړ����x
	constexpr float kBaseMoveSpeed = 1.0f;
	// �o���l�ő�l
	constexpr double kMaxExp = 5000.0;
}

Myu::Myu() :
	m_updateFuncMap(),
	m_updateFunc(&Myu::UpdateIdleNormal),
	m_updateIdleFuncMap(),
	m_nextPos(Game::kVecZero),
	m_state(),
	m_countFrame(0),
	m_actionEndFrameCount(0),
	m_roomMoveFrameCount(kRoomMoveFrame),
	m_mousePlayingFrameCount(0),
	m_roomMoveSpeed(kBaseMoveSpeed),
	m_pCharaDraw(std::make_shared<CharaDraw>())
{
	// �X�V�֐��}�b�v
	m_updateFuncMap[actionState::Idle] = &Myu::UpdateIdle;
	m_updateFuncMap[actionState::Eat] = &Myu::UpdateEat;
	m_updateFuncMap[actionState::Sleep] = &Myu::UpdateSleep;
	m_updateFuncMap[actionState::Lesson] = &Myu::UpdatePlay;
	m_updateFuncMap[actionState::Outing] = &Myu::UpdateOuting;
	// �ҋ@��Ԃ̊���Ƃ̍X�V�֐��}�b�v
	m_updateIdleFuncMap[emotionState::Normal] = &Myu::UpdateNormalEmo;
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
	m_state.pos = VGet(Game::kGameWidth, Game::kGameHeight, 0.0f);
	m_state.emotion = emotionState::Normal;
	m_state.action = actionState::Idle;
	GameDataManager::GetInstance().SetData(m_state);
	// �ړ��揉����
	m_nextPos = m_state.pos;
	// �L�����`��ݒ�
	m_pCharaDraw->SetImage(Load::GetInstance().GetHandle("chara"));
	m_pCharaDraw->SetPos(Game::kScreenWidthHalf, Game::kScreenHeightHalf);
}

void Myu::Update()
{
	// �t���[���J�E���g
	m_countFrame++;

	// �X�e�[�^�X���Ƃ̍X�V���������o�֐��|�C���^
	(this->*m_updateFuncMap[m_state.action])();
	// �X�e�[�^�X�ő�l�Ǘ�
	StatusLimitCheck();

	// �X�e�[�^�X�ω�
	m_state.exp += kExpIncrease;
	// ���x���A�b�v����
	LevelUp();

	// �L�����N�^�[�̈ʒu��ݒ�
	m_pCharaDraw->SetPos(m_state.pos.x, m_state.pos.y);
}

void Myu::Draw()
{
	// �L�����N�^�[�`��
	m_pCharaDraw->Draw();
}

void Myu::ChangeState(actionState state)
{
	m_state.action = state;
}

void Myu::OnMousePlaying(float x, float y)
{
	// �}�E�X���W
	m_cursorPos = VGet(x, y, 0.0f);

	if (m_mousePlayingFrameCount > 0)
	{
		if (VSize(VSub(m_state.pos, m_cursorPos)) < Game::kChipSize)
		{
			m_updateFunc = &Myu::UpdateMouseTake;
		}
		return;
	}

	// �}�E�X�Y�ꎞ�̏���
	m_updateFunc = &Myu::UpdateMousePlaying;
	m_mousePlayingFrameCount = kMousePlayingFrame;

	// �}�E�X���W��ݒ�
	m_nextPos = m_cursorPos;

	// �ړ����x���グ��
	m_roomMoveSpeed = kBaseMoveSpeed * 2;
}

void Myu::LevelUp()
{
	// ���x���A�b�v
	m_state.expMax = kMaxExp * (m_state.level * 0.5);
	if (m_state.exp > m_state.expMax)
	{
		m_state.level++;
		m_state.exp = 0;
		return;
	}
}

void Myu::StatusLimitCheck()
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

	// �X�e�[�^�X�Œ�l�Ǘ�
	if (m_state.hunger < 0)
	{
		m_state.hunger = 0;
	}
	if (m_state.sleep < 0)
	{
		m_state.sleep = 0;
	}
	if (m_state.happy < 0)
	{
		m_state.happy = 0;
	}
}

void Myu::UpdateRoomMove()
{
	if (m_roomMoveFrameCount < 0)
	{
		return;
	}

	// �ړ�����
	auto moveDir = VSub(m_nextPos, m_state.pos);
	if(VSize(moveDir) < 1.0f)
	{
		return;
	}
	// �ړ�������0�łȂ��ꍇ�͐��K��
	if (VSize(moveDir) > 0) moveDir = VNorm(moveDir);
	// �ړ������ɑ��x���|����
	moveDir = VScale(moveDir, m_roomMoveSpeed);
	// �ړ�
	m_state.pos = VAdd(m_state.pos, moveDir);
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

	// �ҋ@���̏���
	(this->*m_updateFunc)();

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

void Myu::UpdateMousePlaying()
{
	m_mousePlayingFrameCount--;
	if (m_mousePlayingFrameCount < 0)
	{
		m_updateFunc = &Myu::UpdateIdleNormal;
		m_mousePlayingFrameCount = 0;
		m_roomMoveSpeed = kBaseMoveSpeed;
	}

	// ����Ƃ̍X�V
	(this->*m_updateIdleFuncMap[m_state.emotion])();
}

void Myu::UpdateMouseTake()
{
	m_mousePlayingFrameCount--;
	if (m_mousePlayingFrameCount < 0)
	{
		m_updateFunc = &Myu::UpdateIdleNormal;
		m_mousePlayingFrameCount = 0;
		m_roomMoveSpeed = kBaseMoveSpeed;
	}

	// �J�[�\���Ɉ�����
	m_state.pos = m_cursorPos;
}

void Myu::UpdateNormalEmo()
{
	
}

