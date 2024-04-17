#pragma once

#include <DxLib.h>
#include "InputState.h"
#include "SoundManager.h"
#include "GameDataManager.h"

namespace Game
{
	// システム基本設定 //
#ifdef _DEBUG
	// ウィンドウモード設定
	constexpr bool kWindowMode = true;
#else
	constexpr bool kWindowMode = false;
#endif

	// ウィンドウ名
	const char* const kTitleText = "ミューママ誕生日おめっとう！！";
	// ウィンドウサイズ
	constexpr int kScreenWidth = 1600;
	constexpr int kScreenHeight = 900;
	constexpr int kScreenWidthHalf = kScreenWidth / 2;
	constexpr int kScreenHeightHalf = kScreenHeight / 2;
	constexpr int kScreenWidthTriple = kScreenWidth * 3;
	constexpr int kScreenHeightTriple = kScreenHeight * 3;
	// ゲームで使う色コード
	constexpr int kColorPink = 0xf69896;
	constexpr int kColorCyan = 0x7db3f3;
	constexpr int kColorGray = 0xbbbbbb;
	constexpr int kColorBlack = 0x0a192c;
	constexpr int kColorWhite = 0xffffff;
	// フォントファイル
	const char* const kFontFileName = "Data/fontData/JKG-L_3.ttf";
	// フォントサイズ
	constexpr int kFontSize = 40;
	// カラーモード
	constexpr int kColorDepth = 32;
	// プレイヤーの基本設定
	constexpr float kChipSize = 640.0f;

	// キャラクターの初期名
	const char* const kCharaName = "みゅーちゃん";

	// ゲームのステージサイズ
	constexpr float kGameWidthLeft = kScreenWidthHalf - 300.0f;
	constexpr float kGameWidthRight = kScreenWidthHalf + 300.0f;
	constexpr float kGameHeightTop = kScreenHeightHalf - 400.0f;
	constexpr float kGameHeightBottom = kScreenHeightHalf + 400.0f;
}