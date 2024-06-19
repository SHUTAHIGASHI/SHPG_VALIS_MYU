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
	constexpr int kColorGreen = 0x4e7b62;
	constexpr int kColorRed = 0xeb4545;
	constexpr int kColorGray = 0xbbbbbb;
	constexpr int kColorBlack = 0x0a192c;
	constexpr int kColorWhite = 0xffffff;
	// ０のベクトル
	static VECTOR kVecZero = VGet(0.0f, 0.0f, 0.0f);

	// ゲームデータの保存ファイル名
	const char* const kGameDataFileName = "Data/charaData.csv";

	// フォントファイル
	const char* const kFontFileName = "Data/fontData/Mamelon-4-Hi-Regular.otf";
	// フォント名
	const char* const kFontName = "マメロン 4 Hi Regular";
	// フォントサイズ
	constexpr int kFontSize = 40;
	// カラーモード
	constexpr int kColorDepth = 32;
	// プレイヤーの基本設定
	constexpr float kChipSize = 64.0f;

	// キャラクターの初期名
	const char* const kCharaName = "みゅーちゃん";
	// キャラクター画像ファイル
	const char* const kCharaFileName = "Data/ImageData/myuTest.png";

	// ゲームのステージサイズ
	constexpr float kGameWidthLeft = Game::kChipSize * 8;
	constexpr float kGameWidthRight = kScreenWidth - Game::kChipSize;
	constexpr float kGameHeightTop = Game::kChipSize * 4;
	constexpr float kGameHeightBottom = Game::kChipSize * 13 - (Game::kChipSize / 2);
	constexpr float kGameWidth = kGameWidthRight - kGameWidthLeft;
	constexpr float kGameHeight = kGameHeightBottom - kGameHeightTop;
}