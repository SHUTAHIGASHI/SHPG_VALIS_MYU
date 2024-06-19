#include "Load.h"
#include <DxLib.h>

Load::~Load()
{
}

void Load::AllLoadData()
{
	// �f�[�^�����[�h����
	m_graphData["bg"] = LoadGraph("Data/ImageData/MainBg_MYU.png");
	m_graphData["title"] = LoadGraph("Data/ImageData/MYU_GAME_TITLE.png");
	m_graphData["cursor"] = LoadGraph("Data/ImageData/Cursor.png");
	m_graphData["volume"] = LoadGraph("Data/ImageData/Volume.png");
}

void Load::DeleteAllData()
{
	// �f�[�^���폜����
	for (auto& data : m_graphData)
	{
		DeleteGraph(data.second);
	}
	m_graphData.clear();
}
