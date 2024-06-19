#pragma once
#include <string>

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
	// �o�[�l�[���ݒ�
	void SetBarName(std::string barName) 
    { 
		// �o�[�l�[�����󕶎��̏ꍇ�͕`�悵�Ȃ�
        m_barName = barName; 
		m_isDrawBarName = true;
    }

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
    // �o�[�l�[��
	std::string m_barName;
    // �o�[�l�[���`�攻��
	bool m_isDrawBarName;
};

