#pragma once

// 背景の描画クラス
class MapDraw
{
public:
	// コンストラクタ
	MapDraw();
	// デストラクタ
	~MapDraw();

	// 初期化
	void Init();
	// 更新
	void Update();
	// 描画
	void Draw();

private:
	// 背景画像
	int m_bgImage;
};

