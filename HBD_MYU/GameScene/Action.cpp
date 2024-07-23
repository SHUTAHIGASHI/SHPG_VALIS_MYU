#include "Action.h"
#include "Game.h"
#include "SelectMenuBase.h"
#include "UiManager.h"
#include "GameDataManager.h"

namespace
{
	// �I�����ږ�
	const char* const kMenuItems[] = {
		"���͂�",
		"�˂ނ�",
		"���b�X��",
		"���������",
		"�Z�[�u"
	};

	// ���o�������̃L������
	const char* const kOutingCharaName[] = {
		"�`�m",
		"�l�t�B",
		"�j�i",
		"����",
		"���B�b�e",
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
	// �e�s�����̏����Ǘ��}�b�v
	m_selectFuncMap["���͂�"] = &Action::OnGiveFood;
	m_selectFuncMap["�˂ނ�"] = &Action::OnSleep;
	m_selectFuncMap["���b�X��"] = &Action::OnLesson;
	m_selectFuncMap["���������"] = &Action::OnOuting;
	m_selectFuncMap["�Z�[�u"] = &Action::OnSave;

	// ���g�̃|�C���^���L�����ɓn��
	m_pMyu->SetAction(this);
}

Action::~Action()
{
}

void Action::Init()
{
	// �I�����j���[������
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

void Action::OnReturnHome()
{
	// UI�`��
	m_pUi->OnReturning(m_outingCharaName);
}

void Action::OnIdle()
{
	// �ҋ@
	m_pMyu->ChangeState(actionState::Idle);
	m_updateFunc = &Action::UpdateIdle;
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
	if (input.IsPressed(InputType::select))
	{
		// �J�[�\�����͈͓��łȂ��ꍇ�͏������Ȃ�
		if (CheckCursorRange())
		{
			// �}�E�X�ŗV��
			m_pMyu->OnMousePlaying(m_cursorPosX, m_cursorPosY);
		}
	}
}

void Action::UpdateActioning(const InputState& input)
{
	if (m_pMyu->GetStatus().action == actionState::Idle)
	{
		// �ҋ@��ԂɂȂ�����ҋ@������
		OnIdle();
	}
}

void Action::OnGiveFood()
{
	// ���͂��������
	m_pMyu->ChangeState(actionState::Eat);
	// �s�����̍X�V����
	m_updateFunc = &Action::UpdateActioning;
}

void Action::OnSleep()
{
	// �Q��
	m_pMyu->ChangeState(actionState::Sleep);
	// �s�����̍X�V����
	m_updateFunc = &Action::UpdateActioning;
}

void Action::OnLesson()
{
	// ���b�X��
	m_pMyu->ChangeState(actionState::Lesson);
	// �s�����̍X�V����
	m_updateFunc = &Action::UpdateActioning;
}

void Action::OnOuting()
{
	// �O�o
	m_pMyu->ChangeState(actionState::Outing);
	// �s�����̍X�V����
	m_updateFunc = &Action::UpdateActioning;
	// �O�o���̃L�������ݒ�
	SetRandomCharaName();
}

void Action::OnSave()
{
	// �Z�[�u
	GameDataManager::GetInstance().SaveTempData(m_pMyu->GetStatus());
	// UI
	m_pUi->AddLog("�Z�[�u���܂����I");
}