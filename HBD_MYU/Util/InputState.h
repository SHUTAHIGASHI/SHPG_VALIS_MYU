#pragma once
#include <EffekseerForDXLib.h>

enum class InputType
{
	// システム系ボタン
	all,	// 全入力
	pause,	// ポーズ
	select,	// 決定
	up,		// 上
	down,	// 下
	right,	// 右
	left,	// 左
};

struct MouseInputState
{
	// マウスカーソル座標
	int x = 0;
	int y = 0;
	// マウス入力状態
	int keyMouseState = 0;
	int lastKeyMouseState = 0;
	// マウスホイール入力状態
	int mouseWheelState = 0;
};

class InputState
{
public:
	// トリガー判定
	bool IsTriggered(InputType type)const;
	// 押し込み判定
	bool IsPressed(InputType type)const;
	// 入力状態更新
	void Update();
	// マウスホイールの入力状態取得
	bool IsMouseWheel(bool isPlus)const;
	// パッドスティックの入力状態取得
	bool IsStickInput(int stickType, bool isPlus)const;
	// マウスカーソルの座標取得
	int GetMousePosX()const { return mouseState.x; }
	int GetMousePosY()const { return mouseState.y; }

private:
	int lastPadState = 0;
	int padState = 0;
	char keyState[256];
	char lastKeyState[256];
	// マウスの入力状態
	MouseInputState mouseState;
	// パッドの入力状態
	DINPUT_JOYSTATE dinputPadState;
};