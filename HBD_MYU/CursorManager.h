#pragma once
#include "game.h"
#include <unordered_map>
#include <string>

class CursorManager
{
public:
	~CursorManager();
	/// <summary>
	/// Load使用者はGetInstance()を通した参照からしか利用できない
	/// </summary>
	/// <returns></returns>
	static CursorManager& GetInstance()
	{
		// 唯一の実態
		static CursorManager instance;

		// それの参照を返す
		return instance;
	}

	// カーソル更新
	void UpdateCursor(const InputState& input);

	// カーソル描画
	void DrawCursor();

	// カーソルチェンジ
	void ChangeCursor(std::string key);

private:
	// シングルトンパターンなのでコンストラクタはprivateに置く
	CursorManager();
	// コピーも代入も禁止する
	CursorManager(const CursorManager&) = delete;			// コピーコンストラクタ
	void operator = (const CursorManager&) = delete;		// 代入も禁止

	// カーソル座標
	float m_posX;
	float m_posY;

	// カーソル画像ハンドル
	int m_cursorHandle;
};

