#pragma once
#include "Myu.h"
#include <string>
#include <vector>
#include <DxLib.h>

class UiManager
{
public:
	// コンストラクタ
	UiManager();
	// デストラクタ
	~UiManager();

	// 初期化
	void Init();
	// 更新
	void Update();
	// 描画
	void Draw();

	// キャラクター情報設定
	void SetCharacterInfo(state charaState) { m_charaState = charaState; }
	// ステータス描画位置
	void SetStatusDrawPos(float x, float y) { m_statusDrawPos = VGet(x, y, 0.0f); }
private:
	// キャラクター情報
	state m_charaState;
	// 描画位置
	VECTOR m_statusDrawPos;
};

