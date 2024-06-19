#pragma once
#include <string>
#include <memory>
#include <map>
#include "Game.h"

// キャラクターの感情の種類
enum class emotionState
{
	// 通常
	Normal,
	// 幸せ
	Happy,
	// 悲しい
	Sad,
	// 怒り
	Angry,
	// 驚き
	Surprise,
	// 疲れ
	Tired,
	// 眠い
	Sleepy,
	// 空腹
	Hungry,
	// 歌いたい
	Sing,
	// 踊りたい
	Dance,
	// 遊びたい
	Play,
	// お散歩
	Outing,
	// 料理したい
	Cook,
	// 楽しい
	Fun,
	// 最大
	Max
};

// ステートの種類
enum class actionState
{
	Idle,
	Eat,
	Sleep,
	Play,
	Outing,
	Max
};

struct charaState
{
	std::string name = "みゅーちゃん";
	VECTOR drawPos = VGet(0.0f, 0.0f, 0.0f);
	emotionState emotion = emotionState::Normal;
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
	const charaState GetStatus() const { return m_state; }

private:
	// レベルアップ処理
	void LevelUp();
	// ステータス最大値管理
	void StatusMaxCheck();
	// 部屋内の移動処理
	void UpdateRoomMove();

	// メンバ関数ポインタ(ステートごとの更新)
	using m_tUpdateFunc = void (Myu::*) ();
	// ステートごとの関数ポインタをMAPで管理
	std::map<actionState, m_tUpdateFunc> m_updateFuncMap;
	// 状態ごとの更新
	void UpdateIdle();
	// 食事中
	void UpdateEat();
	// 睡眠中
	void UpdateSleep();
	// 遊び中
	void UpdatePlay();
	// 外出中
	void UpdateOuting();

	// メンバ関数ポインタ(更新)
	using m_tUpdateIdleFunc = void (Myu::*) ();
	// 感情ごとの関数ポインタをMAPで管理
	std::map<emotionState, m_tUpdateIdleFunc> m_updateIdleFuncMap;
	// 状態ごとの更新
	void UpdateIdleNormal();
	//// 幸せ
	//void UpdateIdleHappy();
	//// 悲しい
	//void UpdateIdleSad();
	//// 怒り
	//void UpdateIdleAngry();
	//// 驚き
	//void UpdateIdleSurprise();
	//// 疲れ
	//void UpdateIdleTired();
	//// 眠い
	//void UpdateIdleSleepy();
	//// 空腹
	//void UpdateIdleHungry();
	//// 歌いたい
	//void UpdateIdleSing();
	//// 踊りたい
	//void UpdateIdleDance();
	//// 遊びたい
	//void UpdateIdlePlay();
	//// お散歩
	//void UpdateIdleOuting();
	//// 料理したい
	//void UpdateIdleCook();
	//// 楽しい
	//void UpdateIdleFun();

private:
	// 次の移動座標
	VECTOR m_nextPos;
	// ステータス管理
	charaState m_state;
	// 毎フレームカウント
	int m_countFrame;
	// 行動直後のフレームカウント
	int m_actionEndFrameCount;
	// 部屋移動のフレームカウント
	int m_roomMoveFrameCount;
};

