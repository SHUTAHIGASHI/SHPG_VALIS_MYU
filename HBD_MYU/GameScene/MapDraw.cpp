#include "MapDraw.h"
#include "Game.h"
#include "Load.h"

MapDraw::MapDraw():
	m_bgImage(0)
{
}

MapDraw::~MapDraw()
{
	m_bgImage = -1;
}

void MapDraw::Init()
{
	m_bgImage = Load::GetInstance().GetHandle("bg");
}

void MapDraw::Update()
{
}

void MapDraw::Draw()
{
	DrawExtendGraphF(0, 0, Game::kScreenWidth, Game::kScreenHeight, m_bgImage, true);
}
