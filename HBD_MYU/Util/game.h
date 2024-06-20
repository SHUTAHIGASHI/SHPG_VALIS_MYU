#pragma once

#include <DxLib.h>
#include "InputState.h"
#include "SoundManager.h"
#include "GameDataManager.h"

namespace Game
{
	// �V�X�e����{�ݒ� //
#ifdef _DEBUG
	// �E�B���h�E���[�h�ݒ�
	constexpr bool kWindowMode = true;
#else
	constexpr bool kWindowMode = false;
#endif

	// �E�B���h�E��
	const char* const kTitleText = "�~���[�}�}�a�������߂��Ƃ��I�I";
	// �E�B���h�E�T�C�Y
	constexpr int kScreenWidth = 1600;
	constexpr int kScreenHeight = 900;
	constexpr int kScreenWidthHalf = kScreenWidth / 2;
	constexpr int kScreenHeightHalf = kScreenHeight / 2;
	constexpr int kScreenWidthTriple = kScreenWidth * 3;
	constexpr int kScreenHeightTriple = kScreenHeight * 3;
	// �Q�[���Ŏg���F�R�[�h
	constexpr int kColorGreen = 0x4e7b62;
	constexpr int kColorRed = 0xeb4545;
	constexpr int kColorGray = 0xbbbbbb;
	constexpr int kColorBlack = 0x231815;
	constexpr int kColorLightBlack = 0x493a34;
	constexpr int kColorWhite = 0xffffff;
	// �O�̃x�N�g��
	static VECTOR kVecZero = VGet(0.0f, 0.0f, 0.0f);

	// �Q�[���f�[�^�̕ۑ��t�@�C����
	const char* const kGameDataFileName = "Data/charaData.csv";

	// �t�H���g�t�@�C��
	const char* const kFontFileName = "Data/fontData/Mamelon-4-Hi-Regular.otf";
	// �t�H���g��
	const char* const kFontName = "�}������ 4 Hi Regular";
	// �t�H���g�T�C�Y
	constexpr int kFontSize = 40;
	// �J���[���[�h
	constexpr int kColorDepth = 32;
	// �v���C���[�̊�{�ݒ�
	constexpr float kChipSize = 64.0f;

	// �L�����N�^�[�̏�����
	const char* const kCharaName = "�݂�[�����";

	// �Q�[���̃X�e�[�W�T�C�Y
	constexpr float kGameWidthLeft = Game::kChipSize * 8;
	constexpr float kGameWidthRight = kScreenWidth - Game::kChipSize;
	constexpr float kGameHeightTop = Game::kChipSize * 4;
	constexpr float kGameHeightBottom = Game::kChipSize * 13 - (Game::kChipSize / 2);
	constexpr float kGameWidth = kGameWidthRight - kGameWidthLeft;
	constexpr float kGameHeight = kGameHeightBottom - kGameHeightTop;
	// UI�`�旓�̃T�C�Y
	constexpr float kUiWidthLeft = 0.0f;
	constexpr float kUiWidthRight = Game::kChipSize * 7;
	constexpr float kUiHeightTop = 0.0f;
	constexpr float kUiHeightBottom = Game::kChipSize * 14;
	constexpr float kUiWidth = kUiWidthRight - kUiWidthLeft;
	constexpr float kUiHeight = kUiHeightBottom - kUiHeightTop;
}