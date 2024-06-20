#include "InputState.h"

void InputState::Update()
{
	// 前のフレームのキー状況をコピー
	for (int i = 0; i < _countof(lastKeyState); ++i)
	{
		lastKeyState[i] = keyState[i];
	}
	// キーボードキー入力状態取得
	GetHitKeyStateAll(keyState);

	// マウスのキー状態取得
	mouseState.lastKeyMouseState = mouseState.keyMouseState;
	mouseState.keyMouseState = GetMouseInput();
	// マウスホイールの状態管理
	mouseState.mouseWheelState = GetMouseWheelRotVol(true);
	// マウスカーソルの座標取得
	GetMousePoint(&mouseState.x, &mouseState.y);

	// パッドキー状態取得
	lastPadState = padState;
	padState = GetJoypadInputState(DX_INPUT_PAD1);
	// パッドキー状態取得(スティック状態管理用)
	GetJoypadDirectInputState(DX_INPUT_PAD1, &dinputPadState);
}

bool InputState::IsMouseWheel(bool isPlus) const
{
	if (isPlus)
	{
		if (mouseState.mouseWheelState > 0)
		{
			return true;
		}
	}
	else
	{
		if (mouseState.mouseWheelState < 0)
		{
			return true;
		}
	}

	return false;
}

bool InputState::IsStickInput(int stickType, bool isPlus)const
{
	if (isPlus)
	{
		if (stickType > 0)
		{
			return true;
		}
	}
	else
	{
		if (stickType < 0)
		{
			return true;
		}
	}

	return false;
}

bool InputState::IsTriggered(InputType type)const
{
	if (type == InputType::all)
	{
		return !(lastPadState) &&
			(padState)||
			!lastKeyState&&
			keyState || 
			!(mouseState.lastKeyMouseState) &&
			(mouseState.keyMouseState);
	}
	else if (type == InputType::pause)
	{
		return !lastKeyState[KEY_INPUT_ESCAPE] &&
			keyState[KEY_INPUT_ESCAPE] ||
			!(lastPadState & PAD_INPUT_8) &&
			(padState & PAD_INPUT_8);
	}
	else if (type == InputType::select)
	{
		return !lastKeyState[KEY_INPUT_RETURN] &&
			keyState[KEY_INPUT_RETURN] ||
			!(lastPadState & PAD_INPUT_2) &&
			(padState & PAD_INPUT_2) ||
			!(mouseState.lastKeyMouseState & MOUSE_INPUT_LEFT) &&
			(mouseState.keyMouseState & MOUSE_INPUT_LEFT);
	}
	else if (type == InputType::up)
	{
		return !lastKeyState[KEY_INPUT_UP] &&
			keyState[KEY_INPUT_UP] ||
			!(lastPadState & PAD_INPUT_UP) &&
			(padState & PAD_INPUT_UP) ||
			(IsMouseWheel(true));
	}
	else if (type == InputType::down)
	{
		return !lastKeyState[KEY_INPUT_DOWN] &&
			keyState[KEY_INPUT_DOWN] ||
			!(lastPadState & PAD_INPUT_DOWN) &&
			(padState & PAD_INPUT_DOWN) ||
			(IsMouseWheel(false));
	}
	else if (type == InputType::right)
	{
		return !lastKeyState[KEY_INPUT_RIGHT] &&
			keyState[KEY_INPUT_RIGHT] ||
			!(lastPadState & PAD_INPUT_RIGHT) &&
			(padState & PAD_INPUT_RIGHT) ||
			(IsMouseWheel(false));
	}
	else if (type == InputType::left)
	{
		return !lastKeyState[KEY_INPUT_LEFT] &&
			keyState[KEY_INPUT_LEFT] ||
			!(lastPadState & PAD_INPUT_LEFT) &&
			(padState & PAD_INPUT_LEFT) ||
			(IsMouseWheel(true));
	}

	return false;
}

bool InputState::IsPressed(InputType type)const
{
	if (type == InputType::pause)
	{
		return keyState[KEY_INPUT_ESCAPE] ||
			(padState & PAD_INPUT_8);
	}
	else if (type == InputType::select)
	{
		return keyState[KEY_INPUT_RETURN] ||
			(padState & PAD_INPUT_2) ||
			(mouseState.keyMouseState & MOUSE_INPUT_LEFT);
	}
	else if (type == InputType::up)
	{
		return keyState[KEY_INPUT_UP] ||
			keyState[KEY_INPUT_W] ||
			(padState & PAD_INPUT_UP);
	}
	else if (type == InputType::down)
	{
		return keyState[KEY_INPUT_DOWN] ||
			keyState[KEY_INPUT_S] ||
			(padState & PAD_INPUT_DOWN);
	}
	else if (type == InputType::right)
	{
		return keyState[KEY_INPUT_RIGHT] ||
			keyState[KEY_INPUT_D] ||
			(padState & PAD_INPUT_RIGHT);;
	}
	else if (type == InputType::left)
	{
		return keyState[KEY_INPUT_LEFT] ||
			keyState[KEY_INPUT_A] ||
			(padState & PAD_INPUT_LEFT);
	}

	return false;
}