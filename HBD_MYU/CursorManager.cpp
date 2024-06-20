#include "CursorManager.h"
#include "Load.h"

CursorManager::~CursorManager()
{
	// �J�[�\���摜�폜
	m_cursorHandle = -1;
}

void CursorManager::UpdateCursor(const InputState& input)
{
	// �}�E�X�J�[�\���ʒu�ݒ�
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
	// �}�E�X�J�[�\���`��
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
