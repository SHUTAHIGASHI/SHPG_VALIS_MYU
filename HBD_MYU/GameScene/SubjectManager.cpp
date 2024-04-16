#include "SubjectManager.h"
#include "Game.h"
#include "Load.h"
#include "Subject.h"
#include "SceneMain.h"

namespace
{
	// ����`��ʒu
	constexpr float kSubjectDrawPosX = Game::kScreenWidthHalf;
	constexpr float kSubjectDrawPosY = Game::kScreenHeightHalf - 100.0f;
	// ����g�嗦
	constexpr double kSubjectScale = 0.65;
}

SubjectManager::SubjectManager()
{
	// �S�Ă̗v�f�ǂݍ���
	LoadAllSubject();
	// �S�Ă̗v�f���Z�b�g
	AllSubjectReset();
	// �v�f�f�[�^����ǂݍ���
	m_currentSubjectData = NULL;
}

SubjectManager::~SubjectManager()
{	
	m_subjects.clear();
}

void SubjectManager::Draw()
{
	if (m_currentSubjectData != NULL)
	{
		DrawRotaGraphF(kSubjectDrawPosX, kSubjectDrawPosY,
			kSubjectScale, 0.0, m_currentSubjectData->subHandle, true);
	}
}

void SubjectManager::OnSubChange()
{
	m_currentSubjectData = GetRandSubject();
}

void SubjectManager::OnChino()
{
	if (m_currentSubjectData->subType == SubjectType::CHINO)
	{
		m_pMain->OnCorrect();
	}
	else
	{
		m_pMain->OnIncorrect();
	}
}

void SubjectManager::OnNotChino()
{
	if (m_currentSubjectData->subType != SubjectType::CHINO 
		&& m_currentSubjectData->subType != SubjectType::SOUGHT)
	{
		m_pMain->OnCorrect();
	}
	else
	{
		m_pMain->OnIncorrect();
	}
}

void SubjectManager::OnSought()
{
	if (m_currentSubjectData->subType == SubjectType::SOUGHT)
	{
		m_pMain->OnCorrect();
	}
	else
	{
		m_pMain->OnIncorrect();
	}
}

int SubjectManager::GetSubjectNum()
{
	return static_cast<int>(m_subjects.size());
}

SubjectData* SubjectManager::GetRandSubject()
{
	int randNum = 0, countSub = 0;
	do {
		randNum = GetRand(static_cast<int>(m_subjects.size()) - 1);
		countSub++;
		if (m_subjects.size() <= countSub)
		{
			AllSubjectReset();
		}
	} while (m_subjects[randNum].isDisable);
	m_subjects[randNum].isDisable = true;

	return new SubjectData(m_subjects[randNum]);
}

void SubjectManager::AllSubjectReset()
{
	for (auto& sub : m_subjects)
	{
		sub.isDisable = false;
	}
}

void SubjectManager::LoadAllSubject()
{ 
	m_subjects = Load::GetInstance().GetAllData();
}
