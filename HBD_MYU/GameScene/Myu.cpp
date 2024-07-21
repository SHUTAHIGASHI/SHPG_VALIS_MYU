#include "Myu.h"
#include "CharaDraw.h"
#include "Load.h"

namespace
{
	// ステータス最大値
	constexpr double kMaxStatus = 1000.0;
	// ステータス増加量
	constexpr double kExpIncrease = 1.0;
	constexpr double kHungerIncrease = 0.5;
	constexpr double kSleepIncrease = 0.5;
	constexpr double kHappyIncrease = 0.5;
	// ステータス減少量
	constexpr double kHungerDecrease = 0.2;
	constexpr double kSleepDecrease = 0.2;
	constexpr double kHappyDecrease = 0.2;
	// ステータス初期値
	constexpr int kInitLevel = 1;
	constexpr double kInitExp = 0.0;
	constexpr double kInitHunger = 0.0;
	constexpr double kInitSleep = 0.0;
	constexpr double kInitHappy = kMaxStatus / 2;

	// 行動後の待機フレーム
	constexpr int kActionEndFrame = 60;
	// 部屋移動フレーム
	constexpr int kRoomMoveFrame = 120;
	// マウス戯れ時のフレーム
	constexpr int kMousePlayingFrame = 60 * 6;

	// 部屋内の移動速度
	constexpr float kBaseMoveSpeed = 1.0f;
	// 経験値最大値
	constexpr double kMaxExp = 5000.0;

	// お出かけ時間上限下限
	constexpr int kOutingTimeMax = 60 * 10;
	constexpr int kOutingTimeMin = 60 * 5;
	//constexpr int kOutingTimeMax = 3600 * 5;
	//constexpr int kOutingTimeMin = 3600 * 1;

	// 各種移動先座標
	static VECTOR kBedPos = VGet(1500.0f, 300.0f, 0.0f);	// ベッドの座標
	static VECTOR kTablePos = VGet(1000.0f, 500.0f, 0.0f);	// テーブルの座標
	static VECTOR kDoorPos = VGet(700.0f, 730.0f, 0.0f);	// 外出時の座標
}

Myu::Myu() :
	m_updateFuncMap(),
	m_updateFunc(&Myu::UpdateIdleNormal),
	m_updateIdleFuncMap(),
	m_cursorPos(Game::kVecZero),
	m_nextPos(Game::kVecZero),
	m_state(),
	m_countFrame(0),
	m_actionEndFrameCount(0),
	m_roomMoveFrameCount(kRoomMoveFrame),
	m_mousePlayingFrameCount(0),
	m_outingTimeCount(0),
	m_roomMoveSpeed(kBaseMoveSpeed),
	m_pCharaDraw(std::make_shared<CharaDraw>())
{
	// 状態ごとの実行処理関数マップ
	m_onActionFuncMap[actionState::Idle] = &Myu::OnIdle;
	m_onActionFuncMap[actionState::Eat] = &Myu::OnEat;
	m_onActionFuncMap[actionState::Sleep] = &Myu::OnSleep;
	m_onActionFuncMap[actionState::Lesson] = &Myu::OnLesson;
	m_onActionFuncMap[actionState::Outing] = &Myu::OnOuting;

	// 更新関数マップ
	m_updateFuncMap[actionState::Idle] = &Myu::UpdateIdle;
	m_updateFuncMap[actionState::RoomMove] = &Myu::UpdateMoveBeforeChange;
	m_updateFuncMap[actionState::Eat] = &Myu::UpdateEat;
	m_updateFuncMap[actionState::Sleep] = &Myu::UpdateSleep;
	m_updateFuncMap[actionState::Lesson] = &Myu::UpdatePlay;
	m_updateFuncMap[actionState::Outing] = &Myu::UpdateOuting;
	// 待機状態の感情ごとの更新関数マップ
	m_updateIdleFuncMap[emotionState::Normal] = &Myu::UpdateNormalEmo;
}

Myu::~Myu()
{
}

void Myu::Init()
{
	// ステータス初期化
	m_state.name = Game::kCharaName;
	m_state.pos = VGet(Game::kGameWidth, Game::kGameHeight, 0.0f);
	m_state.emotion = emotionState::Normal;
	m_state.action = actionState::Idle;
	m_state.nextAction = actionState::Idle;
	GameDataManager::GetInstance().SetData(m_state);
	// 移動先初期化
	m_nextPos = m_state.pos;
	// キャラ描画設定
	m_pCharaDraw->SetImage(Load::GetInstance().GetHandle("chara"));
	m_pCharaDraw->SetPos(Game::kScreenWidthHalf, Game::kScreenHeightHalf);
}

void Myu::Update()
{
	// フレームカウント
	m_countFrame++;

	// ステータスごとの更新処理メンバ関数ポインタ
	(this->*m_updateFuncMap[m_state.action])();
	// ステータス最大値管理
	StatusLimitCheck();

	// ステータス変化
	m_state.exp += kExpIncrease;
	// レベルアップ処理
	LevelUp();

	// キャラクターの位置を設定
	m_pCharaDraw->SetPos(m_state.pos.x, m_state.pos.y);
}

void Myu::Draw()
{
	// キャラクター描画
	m_pCharaDraw->Draw();
}

void Myu::ChangeState(actionState state)
{
	if (state == actionState::Idle)
	{
		m_state.action = state;
	}
	else
	{
		m_state.nextAction = state;
	}

	// 状態変更時の処理
	(this->*m_onActionFuncMap[state])();
}

void Myu::OnMousePlaying(float x, float y)
{
	// マウス座標
	m_cursorPos = VGet(x, y, 0.0f);

	if (m_mousePlayingFrameCount > 0)
	{
		if (VSize(VSub(m_state.pos, m_cursorPos)) < Game::kChipSize / 2)
		{
			m_updateFunc = &Myu::UpdateMouseTake;
		}
		return;
	}

	// マウス戯れ時の処理
	m_updateFunc = &Myu::UpdateMousePlaying;
	m_mousePlayingFrameCount = kMousePlayingFrame;

	// マウス座標を設定
	m_nextPos = m_cursorPos;

	// 移動速度を上げる
	m_roomMoveSpeed = kBaseMoveSpeed * 2;
}

void Myu::LevelUp()
{
	// レベルアップ
	m_state.expMax = kMaxExp * (m_state.level * 0.5);
	if (m_state.exp > m_state.expMax)
	{
		m_state.level++;
		m_state.exp = 0;
		return;
	}
}

void Myu::StatusLimitCheck()
{
	// ステータス最大値管理
	if (m_state.hunger > kMaxStatus)
	{
		m_state.hunger = kMaxStatus;
	}
	if (m_state.sleep > kMaxStatus)
	{
		m_state.sleep = kMaxStatus;
	}
	if (m_state.happy > kMaxStatus)
	{
		m_state.happy = kMaxStatus;
	}

	// ステータス最低値管理
	if (m_state.hunger < 0)
	{
		m_state.hunger = 0;
	}
	if (m_state.sleep < 0)
	{
		m_state.sleep = 0;
	}
	if (m_state.happy < 0)
	{
		m_state.happy = 0;
	}
}

void Myu::UpdateRoomMove()
{
	if (m_roomMoveFrameCount < 0)
	{
		return;
	}

	// 移動方向
	auto moveDir = VSub(m_nextPos, m_state.pos);
	if(VSize(moveDir) < 1.0f)
	{
		return;
	}
	// 移動方向が0でない場合は正規化
	if (VSize(moveDir) > 0) moveDir = VNorm(moveDir);
	// 移動方向に速度を掛ける
	moveDir = VScale(moveDir, m_roomMoveSpeed);
	// 移動
	m_state.pos = VAdd(m_state.pos, moveDir);
}

void Myu::OnRoomMove()
{
	// 部屋内移動速度
	m_roomMoveSpeed = kBaseMoveSpeed * 3;
	// ステータス変化
	m_state.action = actionState::RoomMove;
}

void Myu::OnIdle()
{
	m_roomMoveSpeed = kBaseMoveSpeed;
}

void Myu::OnEat()
{
	// 移動先の座標を設定
	m_nextPos = kTablePos;
	// 部屋移動ステータス変化
	OnRoomMove();
}

void Myu::OnSleep()
{
	// 移動先の座標を設定
	m_nextPos = kBedPos;
	// 部屋移動ステータス変化
	OnRoomMove();
}

void Myu::OnLesson()
{
	// 移動先の座標を設定
	m_nextPos = kDoorPos;
	// 部屋移動ステータス変化
	OnRoomMove();
}

void Myu::OnOuting()
{
	// 移動先の座標を設定
	m_nextPos = kDoorPos;
	// 部屋移動ステータス変化
	OnRoomMove();
	// 外出時間設定
	m_outingTimeCount = GetRand(kOutingTimeMax - kOutingTimeMin) + kOutingTimeMin;
}

void Myu::UpdateIdle()
{
	// ステータス変化
	if(m_countFrame % 30 == 0)
	{
		m_state.hunger += kHungerIncrease;
		m_state.sleep += kSleepIncrease;
		m_state.happy -= kHappyIncrease;
		m_countFrame = 0;
	}

	// 待機時の処理
	(this->*m_updateFunc)();

	// 部屋内の移動処理
	UpdateRoomMove();
}

void Myu::UpdateMoveBeforeChange()
{
	// 部屋内の移動処理
	UpdateRoomMove();

	// 移動方向
	auto moveDir = VSub(m_nextPos, m_state.pos);
	if (VSize(moveDir) < Game::kChipSize / 2)
	{
		m_state.action = m_state.nextAction;
	}
}

void Myu::UpdateEat()
{
	// ステータス変化
	m_state.hunger -= kHungerDecrease;
	m_state.sleep += kSleepIncrease;
	if (m_state.hunger < kInitHunger)
	{
		m_state.hunger = kInitHunger;
		ChangeState(actionState::Idle);
	}
}

void Myu::UpdateSleep()
{
	// ステータス変化
	m_state.sleep -= kSleepDecrease * 10;
	m_state.hunger += kHungerIncrease;
	m_state.happy += kHappyIncrease;
	if (m_state.sleep < kInitSleep)
	{
		m_state.sleep = kInitSleep;
		ChangeState(actionState::Idle);
		printfDx("sleepend");
	}
}

void Myu::UpdatePlay()
{
	// ステータス変化
	m_state.happy += kHappyDecrease;
	if (m_state.happy > kInitHappy)
	{
		m_state.happy = kInitHappy;
		ChangeState(actionState::Idle);
	}
}

void Myu::UpdateOuting()
{
	// ステータス変化
	m_state.happy += kHappyIncrease * 2;
	// 外出時間カウント
	m_outingTimeCount--;
	if (m_outingTimeCount < 0)
	{
		// お出かけ終了
		m_outingTimeCount = 0;
		ChangeState(actionState::Idle);
		// UI描画
		//m_pUi->OnReturning(m_outingCharaName);
	}
}

void Myu::UpdateIdleNormal()
{
	m_roomMoveFrameCount--;
	// ステータス変化
	if (m_roomMoveFrameCount > 0)
	{
		return;
	}

	m_roomMoveFrameCount = GetRand(kRoomMoveFrame);
	// ランダムで上下の移動方向取得
	// 0:動かない 1:上 2:下
	auto verticalMove = GetRand(2);
	// 部屋の中をランダムで移動
	switch (verticalMove)
	{
	case 0:
		break;
	case 1:
		m_nextPos.x += Game::kChipSize;
		break;
	case 2:
		m_nextPos.x -= Game::kChipSize;
		break;
	}
	// ランダムで左右の移動方向取得
	// 0:動かない 1:左 2:右
	auto sideMove = GetRand(2);
	// 部屋の中をランダムで移動
	switch (sideMove)
	{
	case 0:
		break;
	case 1:
		m_nextPos.y += Game::kChipSize;
		break;
	case 2:
		m_nextPos.y -= Game::kChipSize;
		break;
	}

	// ステージ外に出ないようにする
	if (m_nextPos.x < Game::kGameWidthLeft)
	{
		m_nextPos.x = Game::kGameWidthLeft;
	}
	if (m_nextPos.x > Game::kGameWidthRight)
	{
		m_nextPos.x = Game::kGameWidthRight;
	}
	if (m_nextPos.y < Game::kGameHeightTop)
	{
		m_nextPos.y = Game::kGameHeightTop;
	}
	if (m_nextPos.y > Game::kGameHeightBottom)
	{
		m_nextPos.y = Game::kGameHeightBottom;
	}
}

void Myu::UpdateMousePlaying()
{
	//m_mousePlayingFrameCount--;
	if (VSize(VSub(m_nextPos, m_state.pos)) < 1.0f)
	{
		m_updateFunc = &Myu::UpdateIdleNormal;
		m_mousePlayingFrameCount = 0;
		m_roomMoveSpeed = kBaseMoveSpeed;
	}

	// 感情ごとの更新
	(this->*m_updateIdleFuncMap[m_state.emotion])();
}

void Myu::UpdateMouseTake()
{
	m_updateFunc = &Myu::UpdateIdleNormal;
	m_mousePlayingFrameCount = 0;
	m_roomMoveSpeed = kBaseMoveSpeed;

	// カーソルに握られる
	m_state.pos = m_cursorPos;
}

void Myu::UpdateNormalEmo()
{
	
}

