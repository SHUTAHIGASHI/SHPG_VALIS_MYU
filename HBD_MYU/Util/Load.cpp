#include "Load.h"
#include <DxLib.h>

Load::~Load()
{
}

void Load::AllLoadData()
{
	// データをロードする
	// チノ
	m_subjects.push_back(SubjectData(SubjectType::CHINO, LoadGraph("Data/ImageData/Subject/chinoUtamita1.png")));
}

void Load::AllDeleteData()
{
	// データを削除する
	for (auto& data : m_subjects)
	{
		DeleteGraph(data.subHandle);
	}
	m_subjects.clear();
}
