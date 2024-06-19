#pragma once

class UiBar
{
public:
	// コンストラクタ
    UiBar(int maxNum);
	// デストラクタ
    virtual ~UiBar();
	// 更新
    void Update();
	// 数値更新
    void UpdateUIData(int hp);
	// 描画
    void Draw();
	// 最大値変更
	void ChangeMaxNum(int maxNum) { m_maxNum = maxNum; }
	// 描画座標設定
    void SetDrawPos(int x, int y);
	// バーの色設定
	void SetColor(int color) { m_color = color; }

private:
    // 描画座標
    int m_drawX, m_drawY;

private:
    // 現在の数値
    int m_num;
    // 最大値
    int m_maxNum;
    // 現在の率
    float m_currentNumRate;
    float m_maxNumRate;
	// バーの色
	int m_color;
};

