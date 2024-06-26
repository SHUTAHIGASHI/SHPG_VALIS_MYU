#include "Load.h"
#include <DxLib.h>

Load::~Load()
{
}

void Load::AllLoadData()
{
	// データをロードする
	m_graphData["chara"] = LoadGraph("Data/ImageData/Myu.png");
	m_graphData["gameBg"] = LoadGraph("Data/ImageData/Bg_MYU.png");
	m_graphData["bg"] = LoadGraph("Data/ImageData/MainBg_MYU.png");
	m_graphData["title"] = LoadGraph("Data/ImageData/MYU_GAME_TITLE.png");
	m_graphData["cursor"] = LoadGraph("Data/ImageData/Cursor.png");
	m_graphData["cursorGet"] = LoadGraph("Data/ImageData/CursorGet.png");
	m_graphData["volume"] = LoadGraph("Data/ImageData/Volume.png");
	m_graphData["button"] = LoadGraph("Data/ImageData/Button.png");
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
