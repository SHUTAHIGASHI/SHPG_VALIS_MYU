#include "CharaDraw.h"

CharaDraw::CharaDraw():
	m_hImage(-1),
	m_pos(VGet(0.0f, 0.0f, 0.0f)),
	m_size(0.5f),
	m_angle(0.0f),
	m_emotion(CharaEmotion::Normal)
{
}

CharaDraw::~CharaDraw()
{
	DeleteGraph(m_hImage);
}

void CharaDraw::Draw()
{
	// ‰æ‘œ‚Ì•`‰æ
	DrawRotaGraphF(m_pos.x, m_pos.y, m_size, m_angle, m_hImage, true);
}

void CharaDraw::SetImage(const char* fileName)
{
	m_hImage = LoadGraph(fileName);
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

void CharaDraw::SetEmotion(CharaEmotion emotion)
{
	m_emotion = emotion;
}
