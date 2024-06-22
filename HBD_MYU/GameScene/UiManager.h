#pragma once
#include <DxLib.h>
#include "Myu.h"
#include <string>
#include <list>
#include <map>

struct UiLog
{
	UiLog(std::string log, VECTOR pos) : log(log), pos(pos) 
	{
		textLength = GetDrawFormatStringWidth(log.c_str());
	}
	std::string log;
	int textLength;
	VECTOR pos;
};

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

	// 帰宅時のUI処理
	void OnReturning(std::list<std::string> charaName);

	// キャラクター情報設定
	void SetCharacterInfo(charaState charaState) { m_charaState = charaState; }
	// ステータス描画位置
	void SetStatusDrawPos(float x, float y) { m_statusDrawPos = VGet(x, y, 0.0f); }
private:
	// 行動状態描画
	void DrawActionState();

	// ログテキスト更新
	void UpdateLogText();
	// ログテキスト描画
	void DrawLogText();

private:
	// キャラクター情報
	charaState m_charaState;
	// 描画位置
	VECTOR m_statusDrawPos;
	// 描画するログ
	std::list<UiLog> m_logs;
private:
	// UIバーのマップ
	std::map<std::string, class UiBar*> m_uiBars;
};