#include "Myu.h"

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
	// 部屋内の移動速度
	constexpr float kRoomMoveSpeed = 1.0f;

	// 経験値最大値
	constexpr double kMaxExp = 5000.0;
}

Myu::Myu():
	m_updateFuncMap(),
	m_updateIdleFuncMap(),
	m_nextPos(Game::kVecZero),
	m_state(),
	m_countFrame(0),
	m_actionEndFrameCount(0),
	m_roomMoveFrameCount(kRoomMoveFrame)
{
	// 更新関数マップ
	m_updateFuncMap[actionState::Idle] = &Myu::UpdateIdle;
	m_updateFuncMap[actionState::Eat] = &Myu::UpdateEat;
	m_updateFuncMap[actionState::Sleep] = &Myu::UpdateSleep;
	m_updateFuncMap[actionState::Play] = &Myu::UpdatePlay;
	m_updateFuncMap[actionState::Outing] = &Myu::UpdateOuting;
	// 待機状態の感情ごとの更新関数マップ
	m_updateIdleFuncMap[emotionState::Normal] = &Myu::UpdateIdleNormal;
}

Myu::~Myu()
{
	// データ一時保存
	GameDataManager::GetInstance().SaveTempData(m_state);
}

void Myu::Init()
{
	// ステータス初期化
	m_state.name = Game::kCharaName;
	m_state.drawPos = VGet(Game::kGameWidth, Game::kGameHeight, 0.0f);
	m_state.emotion = emotionState::Normal;
	m_state.action = actionState::Idle;
	GameDataManager::GetInstance().SetData(m_state);
	// 移動先初期化
	m_nextPos = m_state.drawPos;
}

void Myu::Update()
{
	// フレームカウント
	m_countFrame++;

	// ステータスごとの更新処理メンバ関数ポインタ
	(this->*m_updateFuncMap[m_state.action])();
	// ステータス最大値管理
	StatusMaxCheck();

	// ステータス変化
	m_state.exp += kExpIncrease;
	// レベルアップ処理
	LevelUp();
}

void Myu::ChangeState(actionState state)
{
	m_state.action = state;
}

void Myu::LevelUp()
{
	if (m_state.exp > kMaxExp * (m_state.level * 0.5))
	{
		m_state.level++;
		m_state.exp = 0;
		return;
	}
}

void Myu::StatusMaxCheck()
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
}

void Myu::UpdateRoomMove()
{
	if (m_roomMoveFrameCount < 0)
	{
		return;
	}

	// 移動方向
	auto moveDir = VSub(m_nextPos, m_state.drawPos);
	if(VSize(moveDir) < 1.0f)
	{
		return;
	}
	// 移動方向が0でない場合は正規化
	if (VSize(moveDir) > 0) moveDir = VNorm(moveDir);
	// 移動方向に速度を掛ける
	moveDir = VScale(moveDir, kRoomMoveSpeed);
	// 移動
	m_state.drawPos = VAdd(m_state.drawPos, moveDir);
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

	// 感情ごとの処理
	(this->*m_updateIdleFuncMap[emotionState::Normal])();

	// 部屋内の移動処理
	UpdateRoomMove();
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
	m_state.sleep -= kSleepDecrease;
	m_state.hunger += kHungerIncrease;
	m_state.happy += kHappyIncrease;
	if (m_state.sleep < kInitSleep)
	{
		m_state.sleep = kInitSleep;
		ChangeState(actionState::Idle);
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

