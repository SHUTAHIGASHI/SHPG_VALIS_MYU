#include "Load.h"
#include <DxLib.h>

Load::~Load()
{
}

void Load::AllLoadData()
{
	// �f�[�^�����[�h����
	// �`�m
	m_subjects.push_back(SubjectData(SubjectType::CHINO, LoadGraph("Data/ImageData/Subject/chinoUtamita1.png")));
}

void Load::AllDeleteData()
{
	// �f�[�^���폜����
	for (auto& data : m_subjects)
	{
		DeleteGraph(data.subHandle);
	}
	m_subjects.clear();
}
