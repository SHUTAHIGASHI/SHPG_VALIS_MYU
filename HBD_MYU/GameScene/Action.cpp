#include "Action.h"
#include "Game.h"
#include "SelectMenuBase.h"
#include "UiManager.h"

namespace
{
	// �I�����ږ�
	const char* const kMenuItems[] = {
		"���͂�",
		"�˂ނ�",
		"���b�X��",
		"���������",
	};

	// ���o�������̃L������
	const char* const kOutingCharaName[] = {
		"�`�m",
		"�l�t�B",
		"�j�i",
		"����",
		"���B�b�e",
	};

	// ���o�������ԏ������
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
	// �e�s�����̏����Ǘ��}�b�v
	m_selectFuncMap["���͂�"] = &Action::OnGiveFood;
	m_selectFuncMap["�˂ނ�"] = &Action::OnSleep;
	m_selectFuncMap["���b�X��"] = &Action::OnLesson;
	m_selectFuncMap["���������"] = &Action::OnOuting;
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

	// �L�����N�^�[������
	m_pMyu->Init();
}

void Action::Update(const InputState& input)
{
	// �X�V�����̃����o�֐��|�C���^
	(this->*m_updateFunc)(input);
	// �L�����N�^�[�̍X�V
	m_pMyu->Update();
	// �I�����j���[�̍X�V
	m_pSelectMenu->Update(input);
	// �I�����̏���
	if (input.IsTriggered(InputType::select))
	{
		OnSelectItem(m_pSelectMenu->GetSelectedNum());
	}
}

void Action::Draw()
{
	// ���j���[��`��
	m_pSelectMenu->Draw();
	// �L�����N�^�[��`��
	m_pMyu->Draw();
}

void Action::OnIdle()
{
	// �ҋ@
	m_pMyu->ChangeState(actionState::Idle);
	m_updateFunc = &Action::UpdateIdle;
}

void Action::OnGiveFood()
{
	// ���͂��������
	m_pMyu->ChangeState(actionState::Eat);
}

void Action::OnSleep()
{
	// �Q��
	m_pMyu->ChangeState(actionState::Sleep);
}

void Action::OnLesson()
{
	// ���b�X��
	m_pMyu->ChangeState(actionState::Lesson);
}

void Action::OnOuting()
{
	// �O�o
	m_pMyu->ChangeState(actionState::Outing);
	m_updateFunc = &Action::UpdateOuting;
	// �O�o���Ԑݒ�
	m_outingTimeCount = GetRand(kOutingTimeMax - kOutingTimeMin) + kOutingTimeMin;
	// �O�o���̃L�������ݒ�
	SetRandomCharaName();
}

const charaState Action::GetCharaStatus() const
{
	return m_pMyu->GetStatus();
}

void Action::OnSelectItem(int index)
{
	// �J�[�\�����͈͓��łȂ��ꍇ�͏������Ȃ�
	if (!m_pSelectMenu->IsCursorRanged())
	{
		return;
	}

	// �I�����̏���
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
	// �J�[�\�����͈͓����ǂ���
	if (m_cursorPosX > Game::kGameWidthLeft &&
		m_cursorPosX < Game::kGameWidthRight &&
		m_cursorPosY > Game::kGameHeightTop &&
		m_cursorPosY < Game::kGameHeightBottom)
	{
		// �͈͓�
		return true;
	}
	// �͈͊O
	return false;
}

void Action::UpdateIdle(const InputState& input)
{
	// �J�[�\�����W�X�V
	m_cursorPosX = input.GetMousePosX();
	m_cursorPosY = input.GetMousePosY();

	// �I�����̏���
	if (input.IsTriggered(InputType::select))
	{
		// �J�[�\�����͈͓��łȂ��ꍇ�͏������Ȃ�
		if (CheckCursorRange())
		{
			// �}�E�X�ŗV��
			m_pMyu->OnMousePlaying(m_cursorPosX, m_cursorPosY);
		}
	}
}

void Action::UpdateOuting(const InputState& input)
{
	// �O�o���ԃJ�E���g
	m_outingTimeCount--;
	if (m_outingTimeCount < 0)
	{
		// ���o�����I��
		m_outingTimeCount = 0;
		OnIdle();
		m_pUi->OnReturning(m_outingCharaName);
	}
}
