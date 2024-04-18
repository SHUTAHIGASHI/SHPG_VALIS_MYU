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

class Myu
{
private:
	struct state
	{
		std::string name = "みゅーちゃん";
		actionState action = actionState::Idle;
		int level = 1;
		double exp = 0.0;
		double hunger = 0.0;
		double happy = 0.0;
		double sleep = 0.0;
	};

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
	state GetState() const { return m_state; }

private:
	// レベルアップ処理
	void LevelUp();

	// メンバ関数ポインタ(更新)
	using m_tUpdateFunc = void (Myu::*) ();
	m_tUpdateFunc m_updateFunc = nullptr;
	// 状態ごとの更新
	void UpdateIdle();
	void UpdateEat();
	void UpdateSleep();
	void UpdatePlay();
	void UpdateOuting();

private:
	// ステータス管理
	state m_state;
};

