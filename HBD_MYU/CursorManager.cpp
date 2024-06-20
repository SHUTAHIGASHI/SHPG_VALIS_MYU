#include "CursorManager.h"
#include "Load.h"

CursorManager::~CursorManager()
{
	// カーソル画像削除
	m_cursorHandle = -1;
}

void CursorManager::UpdateCursor(const InputState& input)
{
	// マウスカーソル位置設定
	m_posX = input.GetMousePosX();
	m_posY = input.GetMousePosY();

	if (input.IsPressed(InputType::select))
	{
		ChangeCursor("cursorGet");
	}
	else
	{
		ChangeCursor("cursor");
	}
}

void CursorManager::DrawCursor()
{
	// マウスカーソル描画
	DrawRotaGraph(m_posX + 8.0f, m_posY + 24.0f, 0.8, 0.0, m_cursorHandle, true);
}

void CursorManager::ChangeCursor(std::string key)
{
	m_cursorHandle = Load::GetInstance().GetHandle(key);
}

CursorManager::CursorManager()
{
	m_cursorHandle = Load::GetInstance().GetHandle("cursor");
}
