#include "CharaDraw.h"

CharaDraw::CharaDraw():
	m_isDraw(false),
	m_hImage(-1),
	m_imageSizeX(0),
	m_imageSizeY(0),
	m_pos(VGet(0.0f, 0.0f, 0.0f)),
	m_size(1.0f),
	m_angle(0.0f),
	m_emotion(emotionState::Normal)
{
}

CharaDraw::~CharaDraw()
{
	m_hImage = -1;
}

void CharaDraw::Draw()
{
	if (!m_isDraw)
	{
		return;
	}

	// ‰æ‘œ‚Ì•`‰æ
	DrawBox(m_pos.x - m_imageSizeX / 2, m_pos.y - m_imageSizeY / 2,
		m_pos.x + m_imageSizeX / 2, m_pos.y + m_imageSizeY / 2, 
		0xffffff, false);
	DrawRotaGraphF(m_pos.x, m_pos.y, m_size, m_angle, m_hImage, true);
}

void CharaDraw::SetImage(int handle)
{
	m_hImage = handle;
	GetGraphSize(m_hImage, &m_imageSizeX, &m_imageSizeY);
}

void CharaDraw::SetPos(float x, float y)
{
	m_pos = VGet(x, y, 0.0f);
}

void CharaDraw::SetSize(float size)
{
	m_size = size;
}

void CharaDraw::SetAngle(float angle)
{
	m_angle = angle;
}

void CharaDraw::SetEmotion(emotionState emotion)
{
	m_emotion = emotion;
}
