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
	Lesson,
	Outing,
	Max
};

struct charaState
{
	std::string name = "みゅーちゃん";
	VECTOR pos = VGet(0.0f, 0.0f, 0.0f);
	emotionState emotion = emotionState::Normal;
	actionState action = actionState::Idle;
	int level = 1;
	double exp = 0.0;
	double expMax = 0.0;
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
	// 描画
	void Draw();

	// 状態遷移
	void ChangeState(actionState state);

	// マウス戯れ時の処理
	void OnMousePlaying(float x, float y);

	// 現在のステータス取得
	const charaState GetStatus() const { return m_state; }

private:
	// レベルアップ処理
	void LevelUp();
	// ステータス限界値管理
	void StatusLimitCheck();
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

	// メンバ関数ポインタ(待機時の更新)
	m_tUpdateFunc m_updateFunc = nullptr;
	// 待機時の更新
	void UpdateIdleNormal();
	void UpdateMousePlaying();
	void UpdateMouseTake();

	// 感情ごとの関数ポインタをMAPで管理
	std::map<emotionState, m_tUpdateFunc> m_updateIdleFuncMap;
	// 状態ごとの更新
	void UpdateNormalEmo();
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
	// カーソル位置
	VECTOR m_cursorPos;
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
	// マウス戯れ時のフレームカウント
	int m_mousePlayingFrameCount;
	// 部屋の移動速度
	float m_roomMoveSpeed;

private:
	//キャラ描画
	std::shared_ptr<class CharaDraw> m_pCharaDraw;
};

