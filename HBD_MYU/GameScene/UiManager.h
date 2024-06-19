#pragma once
#include <DxLib.h>
#include "Myu.h"
#include <string>
#include <list>
#include <map>

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
	// 行動状態描画
	void DrawActionState();
	// 帰宅時のテキスト描画
	void DrawReturningText();

	// 帰宅時のUI処理
	void OnReturning(std::list<std::string> charaName);

	// キャラクター情報設定
	void SetCharacterInfo(charaState charaState) { m_charaState = charaState; }
	// ステータス描画位置
	void SetStatusDrawPos(float x, float y) { m_statusDrawPos = VGet(x, y, 0.0f); }

private:
	// キャラクター情報
	charaState m_charaState;
	// 描画位置
	VECTOR m_statusDrawPos;
	// お出かけ時のキャラ名
	std::list<std::string> m_outingCharaName;
	// お出かけ後のテキスト描画カウント
	int m_returningTextCount;
private:
	// UIバーのマップ
	std::map<std::string, class UiBar*> m_uiBars;

};

