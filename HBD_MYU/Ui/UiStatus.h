#pragma once
#include "Game.h"

class UiStatus
{
public:
	UiStatus();
	virtual ~UiStatus();

	void Init();
	void Draw();

	void DrawStatus();

	void UpdateUiData(int level, int point);
private:
	int SetDrawInfo(int i);
	std::string SetDrawText(int i);

private:
	// �X�R�A�{�[�h�摜
	int m_hScoreBoardImg;
	// �`����W
	float m_posX;
	float m_posY;
	// �`��F
	int m_textColor;

private:
	// ���݂̃��x��
	int	m_boostLevelNum;
	// ���݂̃|�C���g
	int m_pointNum;
};

