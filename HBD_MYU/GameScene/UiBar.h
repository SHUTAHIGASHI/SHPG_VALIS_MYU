#pragma once

class UiBar
{
public:
	// �R���X�g���N�^
    UiBar(int maxNum);
	// �f�X�g���N�^
    virtual ~UiBar();
	// �X�V
    void Update();
	// ���l�X�V
    void UpdateUIData(int hp);
	// �`��
    void Draw();
	// �ő�l�ύX
	void ChangeMaxNum(int maxNum) { m_maxNum = maxNum; }
	// �`����W�ݒ�
    void SetDrawPos(int x, int y);
	// �o�[�̐F�ݒ�
	void SetColor(int color) { m_color = color; }

private:
    // �`����W
    int m_drawX, m_drawY;

private:
    // ���݂̐��l
    int m_num;
    // �ő�l
    int m_maxNum;
    // ���݂̗�
    float m_currentNumRate;
    float m_maxNumRate;
	// �o�[�̐F
	int m_color;
};

