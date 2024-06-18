#include "Load.h"
#include <DxLib.h>

Load::~Load()
{
}

void Load::AllLoadData()
{
	// データをロードする
	m_graphData["bg"] = LoadGraph("Data/ImageData/MainBg_MYU.png");
	m_graphData["title"] = LoadGraph("Data/ImageData/MYU_GAME_TITLE.png");
}

void Load::DeleteAllData()
{
	// データを削除する
	for (auto& data : m_graphData)
	{
		DeleteGraph(data.second);
	}
	m_graphData.clear();
}
