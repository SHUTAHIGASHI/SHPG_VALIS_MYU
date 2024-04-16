#pragma once

class UiHpBar
{
public:
    UiHpBar();
    virtual ~UiHpBar();
    
    void Init();
    void Update();
    void UpdateUIData(int hp);
    void Draw();

private:
    // �w�i�摜
    int m_hBarImg;
    // �`����W
    int m_drawX, m_drawY;
    int m_drawW, m_drawH;

private:
    // ���݂�HP��
    float m_currentHpRate;
};

