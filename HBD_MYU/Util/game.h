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
	constexpr int kScreenWidth = 1920;
	constexpr int kScreenHeight = 1080;
	constexpr int kScreenWidthHalf = kScreenWidth / 2;
	constexpr int kScreenHeightHalf = kScreenHeight / 2;
	constexpr int kScreenWidthTriple = kScreenWidth * 3;
	constexpr int kScreenHeightTriple = kScreenHeight * 3;
	// �Q�[���Ŏg���F�R�[�h
	constexpr int kColorPink = 0xf69896;
	constexpr int kColorCyan = 0x7db3f3;
	constexpr int kColorGray = 0xbbbbbb;
	constexpr int kColorBlack = 0x0a192c;
	constexpr int kColorWhite = 0xffffff;
	// �t�H���g�t�@�C��
	const char* const kFontFileName = "Data/fontData/JKG-L_3.ttf";
	// �t�H���g�T�C�Y
	constexpr int kFontSize = 40;
	// �J���[���[�h
	constexpr int kColorDepth = 32;
	// �v���C���[�̊�{�ݒ�
	constexpr float kChipSize = 640.0f;
	// �Q�[���̃X�e�[�W�T�C�Y
	constexpr float kGameHeightHalf = Game::kScreenHeightHalf - 100.0f;
}