#include "SceneOption.h"
#include "SceneManager.h"
#include "SoundManager.h"
#include "Load.h"

namespace
{
	// タイトルテキスト描画位置
	constexpr float kTitleDrawPosX = Game::kScreenWidthHalf;
	constexpr float kTitleDrawPosY = Game::kScreenHeightHalf - 200.0f;
	// テキスト描画位置
	constexpr float kTextDrawPosY = Game::kScreenHeightHalf - 120.0f;
	// テキスト描画間隔
	constexpr float kTextDistance = 70.0f;
	// サウンドテキストの間隔
	constexpr float kSoundTextDistance = 230.0f;

	// テキスト描画色
	constexpr int kTextColor = Game::kColorGreen;

	// 音量変化量
	constexpr int kVolumeChangeNum = 10;

	// シーン名
	const char* const kSceneText = "〜設定〜";

	// テキスト
	const char* const kMenuTexts[] = {
		"閉じる",
		"音楽",
		"効果音",
		"ウィンドウモード",
		"保存して閉じる"
	};
	// 選択可能項目の数
	constexpr int kMenuTextSize = sizeof(kMenuTexts) / sizeof(char*);
}

SceneOption::SceneOption(SceneManager& manager) :
	Scene(manager),
	m_countFrame(0),
	m_exVolumeBGM(0),
	m_exVolumeSE(0),
	m_volumeBGM(0),
	m_volumeSE(0),
	m_selectedPos(0),
	m_selectedItemName(),
	m_hBgImg(-1),
	m_hMusicVolImg(-1),
	m_isCursorRanged(false),
	m_isVolumeChangeMode(false),
	m_isSavedWindowMode(false)
{
	// 画像読み込み
	m_hBgImg = LoadGraph("Data/ImageData/OptionBg.png");
	m_hMusicVolImg = Load::GetInstance().GetHandle("volume");
}

SceneOption::~SceneOption()
{
	// 画像ハンドル解放
	DeleteGraph(m_hBgImg);
	m_hMusicVolImg = -1;
}

void SceneOption::Init()
{
	// 音量情報を取得
	m_volumeSE = SoundManager::GetInstance().GetSEVolume();
	m_volumeBGM = SoundManager::GetInstance().GetBGMVolume();
	// 音量情報をセット
	m_exVolumeBGM = m_volumeBGM;
	m_exVolumeSE = m_volumeSE;
	// 現在のウィンドウモードを保存
	m_isSavedWindowMode = static_cast<bool>(GetWindowModeFlag());
}

void SceneOption::Update(const InputState& input)
{
	// フレームカウント
	m_countFrame++;
	if (m_countFrame > 600)
	{
		m_countFrame = 0;
	}

	// 音量変更モード解除
	if (input.IsTriggered(InputType::pause))
	{
		// 音量情報をリセットして閉じる
		ResetVolumeInfo();
		// ウィンドウモードリセット
		if (m_isSavedWindowMode != static_cast<bool>(GetWindowModeFlag())) ChangeWindowMode(m_isSavedWindowMode);
		// シーンを閉じる
		m_Manager.PopScene();
	}

	// 音量変更モード
	if (m_isVolumeChangeMode)
	{
		// 音量変更
		ChangeVolume(input);
	}
	else
	{
		// カーソル更新
		CursorUpdate(input);
	}

	// 選択
	if (input.IsTriggered(InputType::select) && m_isCursorRanged)
	{
		// 選択時の処理
		OnSelect();
	}
}

void SceneOption::Draw()
{
	// 背景描画
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 150);
	DrawBox(0, 0, Game::kScreenWidth, Game::kScreenHeight, 0x000000, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	// 背景描画
	DrawRotaGraphF(Game::kScreenWidthHalf, Game::kScreenHeightHalf, 1.2, 0.0, m_hBgImg, true);
	// タイトル描画
	auto titleLength = GetDrawFormatStringWidth(kSceneText);
	DrawFormatStringF(kTitleDrawPosX - (titleLength / 2), kTitleDrawPosY, kTextColor, "%s", kSceneText);
	// 項目描画
	DrawMenuText();
}

void SceneOption::ChangeVolume(const InputState& input)
{
	if (m_selectedPos == 1)
	{
		// BGM
		ControllVolume(input, m_volumeBGM);
	}
	else if (m_selectedPos == 2)
	{
		// SE
		ControllVolume(input, m_volumeSE);
	}
}

void SceneOption::ControllVolume(const InputState& input, int& volume)
{
	// 音量変更
	if (input.IsTriggered(InputType::right))
	{
		// 音量上
		volume += kVolumeChangeNum;
		if (volume > 100) volume = 100;
		SetVolumeInfo();
	}
	if (input.IsTriggered(InputType::left))
	{
		// 音量下
		volume -= kVolumeChangeNum;
		if (volume < 0) volume = 0;
		SetVolumeInfo();
	}
}

void SceneOption::SetVolumeInfo()
{
	// 音量情報をセット
	SoundManager::GetInstance().SetSEVolume(m_volumeSE);
	SoundManager::GetInstance().SetBGMVolume(m_volumeBGM);
}

void SceneOption::ResetVolumeInfo()
{
	// 音量情報をリセット
	SoundManager::GetInstance().SetSEVolume(m_exVolumeSE);
	SoundManager::GetInstance().SetBGMVolume(m_exVolumeBGM);
}

void SceneOption::DrawSoundBar(float drawX, float drawY, int volume)
{
	// 音量バー描画色設定
	int barColorBGM = 0xffffff, barColorSE = 0xffffff;
	if (m_selectedPos == 1) barColorBGM = kTextColor;
	if (m_selectedPos == 2) barColorSE = kTextColor;

	// 音量バー描画
	for (int i = 0; i < 10; i++)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 75);
		DrawRotaGraphF(drawX + (i * 40), drawY + 25.0f, 0.2, 0.0, m_hMusicVolImg, true);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}

	int n = 0;
	n = volume / kVolumeChangeNum;
	for (int i = 0; i < n; i++)
	{
		// 音量バー描画
		DrawRotaGraphF(drawX + (i * 40), drawY + 25.0f, 0.2, 0.0, m_hMusicVolImg, true);
	}
}

void SceneOption::DrawMenuText()
{
	float drawX = 0.0f, drawY = 0.0f;
	// メニューテキスト描画
	for (int i = 0; i < kMenuTextSize; i++)
	{
		if (m_isVolumeChangeMode)
		{
			if (i == m_selectedPos) continue;
		}

		std::string tSelectedItemName;
		tSelectedItemName = GetCurrentText(i);
		int textLength = GetDrawFormatStringWidth(tSelectedItemName.c_str());
		drawX = static_cast<float>(Game::kScreenWidthHalf - (textLength / 2));
		drawY = static_cast<float>(kTextDrawPosY) + (i * kTextDistance);

		DrawFormatStringF(drawX, drawY, Game::kColorGray, "%s", tSelectedItemName.c_str());
	}
	// 選択中の項目描画
	m_selectedItemName = "> " + GetCurrentText(m_selectedPos) + " <";
	drawX = static_cast<float>(Game::kScreenWidthHalf - (GetDrawFormatStringWidth(m_selectedItemName.c_str()) / 2));
	drawY = static_cast<float>(kTextDrawPosY) + (m_selectedPos * kTextDistance);
	// 音量変更モード
	if (m_isVolumeChangeMode)
	{
		int* volume = 0;
		if (m_selectedPos == 1) volume = &m_volumeBGM;
		else if (m_selectedPos == 2)volume = &m_volumeSE;
		else return;
		// 音量バー描画
		DrawSoundBar(Game::kScreenWidthHalf - 180.0f, drawY, *volume);
	}
	else
	{
		// 選択中の項目描画
		if ((m_countFrame / 10) % 6 != 0)
		{
			DrawFormatStringF(drawX, drawY - 2, kTextColor, "%s", m_selectedItemName.c_str());
		}
	}
}

void SceneOption::CursorUpdate(const InputState& input)
{
	m_isCursorRanged = false;
	int buttonPosX = 0, buttonPosY = Game::kScreenHeightHalf;
	std::string tText;
	for (int i = 0; i < kMenuTextSize; i++)
	{
		tText = GetCurrentText(i);
		int textLength = GetDrawFormatStringWidth(tText.c_str());
		buttonPosX = static_cast<int>(Game::kScreenWidthHalf - (textLength / 2));
		buttonPosY = static_cast<int>(kTextDrawPosY + (kTextDistance * i));

		if (input.GetMousePosX() > buttonPosX && input.GetMousePosX() < buttonPosX + textLength
			&& input.GetMousePosY() > buttonPosY && input.GetMousePosY() < buttonPosY + Game::kFontSize)
		{
			m_isCursorRanged = true;
			m_selectedPos = i;
		}
	}
}

void SceneOption::OnSelect()
{
	// 選択音再生
	SoundManager::GetInstance().PlaySE(SoundType::select);
	// 選択項目による処理
	if (m_selectedPos == 0)
	{
		// 音量情報をリセットして閉じる
		ResetVolumeInfo();
		// ウィンドウモードリセット
		if (m_isSavedWindowMode != static_cast<bool>(GetWindowModeFlag())) ChangeWindowMode(m_isSavedWindowMode);
		// シーンを閉じる
		m_Manager.PopScene();
	}
	else if (m_selectedPos == 1 || m_selectedPos == 2)
	{
		// 音量変更モード
		m_isVolumeChangeMode = !m_isVolumeChangeMode;
	}
	else if (m_selectedPos == 3)
	{
		// ウィンドウモード変更
		auto result = ChangeWindowMode(!static_cast<bool>(GetWindowModeFlag()));
		assert(result == DX_CHANGESCREEN_OK);
	}
	else if (m_selectedPos == 4)
	{
		// 音量情報を保存して閉じる
		m_Manager.PopScene();
	}
}

std::string SceneOption::GetCurrentText(int textNum)
{
	// 選択中の文字列を返す
	return kMenuTexts[textNum];
}