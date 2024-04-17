#pragma once
#include <string>
#include "Game.h"

enum class actionState
{
	Idle,
	Eat,
	Sleep,
	Play
};

class Myu
{
private:
	struct state
	{
		std::string name = "みゅーちゃん";
		actionState action = actionState::Idle;
		int exp = 0;
		int level = 1;
		int hunger = 0;
		int happy = 0;
		int sleep = 0;
	};

public:
	// コンストラクタ
	Myu():
		m_updateFunc(&Myu::UpdateIdle),
		m_state()
	{
		state myu;
	}
	// デストラクタ
	~Myu()
	{

	}

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

private:
	// ステータス
	state m_state;
};

