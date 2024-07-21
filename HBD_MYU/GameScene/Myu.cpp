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

	// ���o�������ԏ������
	constexpr int kOutingTimeMax = 60 * 10;
	constexpr int kOutingTimeMin = 60 * 5;
	//constexpr int kOutingTimeMax = 3600 * 5;
	//constexpr int kOutingTimeMin = 3600 * 1;

	// �e��ړ�����W
	static VECTOR kBedPos = VGet(1500.0f, 300.0f, 0.0f);	// �x�b�h�̍��W
	static VECTOR kTablePos = VGet(1000.0f, 500.0f, 0.0f);	// �e�[�u���̍��W
	static VECTOR kDoorPos = VGet(700.0f, 730.0f, 0.0f);	// �O�o���̍��W
}

Myu::Myu() :
	m_updateFuncMap(),
	m_updateFunc(&Myu::UpdateIdleNormal),
	m_updateIdleFuncMap(),
	m_cursorPos(Game::kVecZero),
	m_nextPos(Game::kVecZero),
	m_state(),
	m_countFrame(0),
	m_actionEndFrameCount(0),
	m_roomMoveFrameCount(kRoomMoveFrame),
	m_mousePlayingFrameCount(0),
	m_outingTimeCount(0),
	m_roomMoveSpeed(kBaseMoveSpeed),
	m_pCharaDraw(std::make_shared<CharaDraw>())
{
	// ��Ԃ��Ƃ̎��s�����֐��}�b�v
	m_onActionFuncMap[actionState::Idle] = &Myu::OnIdle;
	m_onActionFuncMap[actionState::Eat] = &Myu::OnEat;
	m_onActionFuncMap[actionState::Sleep] = &Myu::OnSleep;
	m_onActionFuncMap[actionState::Lesson] = &Myu::OnLesson;
	m_onActionFuncMap[actionState::Outing] = &Myu::OnOuting;

	// �X�V�֐��}�b�v
	m_updateFuncMap[actionState::Idle] = &Myu::UpdateIdle;
	m_updateFuncMap[actionState::RoomMove] = &Myu::UpdateMoveBeforeChange;
	m_updateFuncMap[actionState::Eat] = &Myu::UpdateEat;
	m_updateFuncMap[actionState::Sleep] = &Myu::UpdateSleep;
	m_updateFuncMap[actionState::Lesson] = &Myu::UpdatePlay;
	m_updateFuncMap[actionState::Outing] = &Myu::UpdateOuting;
	// �ҋ@��Ԃ̊���Ƃ̍X�V�֐��}�b�v
	m_updateIdleFuncMap[emotionState::Normal] = &Myu::UpdateNormalEmo;
}

Myu::~Myu()
{
}

void Myu::Init()
{
	// �X�e�[�^�X������
	m_state.name = Game::kCharaName;
	m_state.pos = VGet(Game::kGameWidth, Game::kGameHeight, 0.0f);
	m_state.emotion = emotionState::Normal;
	m_state.action = actionState::Idle;
	m_state.nextAction = actionState::Idle;
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
	if (state == actionState::Idle)
	{
		m_state.action = state;
	}
	else
	{
		m_state.nextAction = state;
	}

	// ��ԕύX���̏���
	(this->*m_onActionFuncMap[state])();
}

void Myu::OnMousePlaying(float x, float y)
{
	// �}�E�X���W
	m_cursorPos = VGet(x, y, 0.0f);

	if (m_mousePlayingFrameCount > 0)
	{
		if (VSize(VSub(m_state.pos, m_cursorPos)) < Game::kChipSize / 2)
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

void Myu::OnRoomMove()
{
	// �������ړ����x
	m_roomMoveSpeed = kBaseMoveSpeed * 3;
	// �X�e�[�^�X�ω�
	m_state.action = actionState::RoomMove;
}

void Myu::OnIdle()
{
	m_roomMoveSpeed = kBaseMoveSpeed;
}

void Myu::OnEat()
{
	// �ړ���̍��W��ݒ�
	m_nextPos = kTablePos;
	// �����ړ��X�e�[�^�X�ω�
	OnRoomMove();
}

void Myu::OnSleep()
{
	// �ړ���̍��W��ݒ�
	m_nextPos = kBedPos;
	// �����ړ��X�e�[�^�X�ω�
	OnRoomMove();
}

void Myu::OnLesson()
{
	// �ړ���̍��W��ݒ�
	m_nextPos = kDoorPos;
	// �����ړ��X�e�[�^�X�ω�
	OnRoomMove();
}

void Myu::OnOuting()
{
	// �ړ���̍��W��ݒ�
	m_nextPos = kDoorPos;
	// �����ړ��X�e�[�^�X�ω�
	OnRoomMove();
	// �O�o���Ԑݒ�
	m_outingTimeCount = GetRand(kOutingTimeMax - kOutingTimeMin) + kOutingTimeMin;
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

void Myu::UpdateMoveBeforeChange()
{
	// �������̈ړ�����
	UpdateRoomMove();

	// �ړ�����
	auto moveDir = VSub(m_nextPos, m_state.pos);
	if (VSize(moveDir) < Game::kChipSize / 2)
	{
		m_state.action = m_state.nextAction;
	}
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
	m_state.sleep -= kSleepDecrease * 10;
	m_state.hunger += kHungerIncrease;
	m_state.happy += kHappyIncrease;
	if (m_state.sleep < kInitSleep)
	{
		m_state.sleep = kInitSleep;
		ChangeState(actionState::Idle);
		printfDx("sleepend");
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
	// �O�o���ԃJ�E���g
	m_outingTimeCount--;
	if (m_outingTimeCount < 0)
	{
		// ���o�����I��
		m_outingTimeCount = 0;
		ChangeState(actionState::Idle);
		// UI�`��
		//m_pUi->OnReturning(m_outingCharaName);
	}
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
	//m_mousePlayingFrameCount--;
	if (VSize(VSub(m_nextPos, m_state.pos)) < 1.0f)
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
	m_updateFunc = &Myu::UpdateIdleNormal;
	m_mousePlayingFrameCount = 0;
	m_roomMoveSpeed = kBaseMoveSpeed;

	// �J�[�\���Ɉ�����
	m_state.pos = m_cursorPos;
}

void Myu::UpdateNormalEmo()
{
	
}

