#pragma once
#include <string>
#include <memory>
#include "Game.h"

enum class actionState
{
	Idle,
	Eat,
	Sleep,
	Play,
	Outing,
	Max
};

struct state
{
	std::string name = "ミュー";
	actionState action = actionState::Idle;
	int level = 1;
	double exp = 0.0;
	double hunger = 0.0;
	double happy = 0.0;
	double sleep = 0.0;
};

class Myu
{
public:
	// コンストラクタ
	Myu();
	// デストラクタ
	~Myu();

	// 初期化
	void Init();
	// 更新
	void Update();
	// 状態遷移
	void ChangeState(actionState state);

	// 現在のステータス取得
	const state GetStatus() const { return m_state; }

private:
	// レベルアップ処理
	void LevelUp();
	// ステータス加算
	void AddStatus();

	// メンバ関数ポインタ(更新)
	using m_tUpdateFunc = void (Myu::*) ();
	m_tUpdateFunc m_updateFunc = nullptr;
	// 状態ごとの更新
	void UpdateIdle();
	// 行動中の更新処理
	void UpdateActioning();

private:
	// ステータス管理
	state m_state;
	// 毎フレームカウント
	int m_countFrame;
};

