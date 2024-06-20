#include "SceneTitle.h"
#include "SoundManager.h"
#include "SceneManager.h"
#include "SceneMain.h"
#include "SceneHowTo.h"
#include "SceneOption.h"
#include "SelectMenuBase.h"
#include "Load.h"

namespace
{
	// タイトルロゴ描画位置
	constexpr float kLogoDrawPosX = Game::kScreenWidthHalf;
	constexpr float kLogoDrawPosY = 300.0f;
	// テキスト描画位置
	constexpr float kTextDrawPosY = Game::kScreenHeightHalf + 160.0f;
	constexpr float kTextDrawSpace = Game::kFontSize;
	// テキスト
	const char* const kMenuTexts[] = 
	{ 
		"ゲームスタート", 
		"あそびかた", 
		"設定", 
		"終了"
	};
}

SceneTitle::SceneTitle(SceneManager& manager) : Scene(manager),
m_updateFunc(&SceneTitle::NormalUpdate),
m_countFrame(0),
m_hTitleLogoImg(-1),
m_pSelectMenu(std::make_shared<SelectMenuBase>())
{
	// データ読み込み
	LoadData();
}

SceneTitle::~SceneTitle()
{
	// BGM停止
	SoundManager::GetInstance().StopBGM();
	// 画像ハンドル解放
	m_hTitleLogoImg = -1;
}

void SceneTitle::Init()
{
	// 選択メニューの初期化
	m_pSelectMenu->Init(true);
	// 選択項目追加
	for (const auto& item : kMenuTexts)
	{
		m_pSelectMenu->AddSelectItem(item);
	}
	// 選択項目描画位置設定
	m_pSelectMenu->SetDrawPos(Game::kScreenWidthHalf, kTextDrawPosY);
}

void SceneTitle::Update(const InputState& input)
{
	// 音楽再生開始
	if (SoundManager::GetInstance().IsPlayingMusic() != 1)
	{
		SoundManager::GetInstance().PlayMusic();
	}

	// 毎フレームカウント
	m_countFrame++;
	// 更新処理のメンバ関数ポインタ
	(this->*m_updateFunc)(input);
}

void SceneTitle::Draw()
{
	// タイトルロゴ描画
	DrawRotaGraphF(kLogoDrawPosX, kLogoDrawPosY, 1.0, 0, m_hTitleLogoImg, true);
	// 選択項目描画
	m_pSelectMenu->Draw();
}

void SceneTitle::End()
{
}

void SceneTitle::LoadData()
{
	// 画像読み込み
	m_hTitleLogoImg = Load::GetInstance().GetHandle("title");
}

void SceneTitle::OnSceneEnd()
{
	// カーソルが範囲内でない場合は処理しない
	if (!m_pSelectMenu->IsCursorRanged())
	{
		return;
	}

	// 選択項目によってシーン遷移
	if (m_pSelectMenu->GetSelectedNum() == 0)
	{
		m_Manager.ChangeScene(new SceneMain(m_Manager));
	}
	else if (m_pSelectMenu->GetSelectedNum() == 1)
	{
		m_Manager.PushScene(new SceneHowTo(m_Manager));
	}
	else if (m_pSelectMenu->GetSelectedNum() == 2)
	{
		m_Manager.PushScene(new SceneOption(m_Manager));
	}
	else if (m_pSelectMenu->GetSelectedNum() == 3)
	{
		m_Manager.GameEnd();
	}
	return;
}

void SceneTitle::NormalUpdate(const InputState& input)
{
	// 選択項目描画
	m_pSelectMenu->Update(input);

	if (input.IsTriggered(InputType::select))
	{
		SoundManager::GetInstance().PlaySE(SoundType::select);
		OnSceneEnd();
		return;
	}
}
