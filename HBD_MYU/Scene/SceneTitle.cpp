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
	// キャラクター移動速度
	constexpr float kCharaSpeed = 2.0f;
	// キャラクター画像サイズ
	constexpr double kCharaSize = 0.1f;
}

SceneTitle::SceneTitle(SceneManager& manager) : Scene(manager),
m_updateFunc(&SceneTitle::NormalUpdate),
m_countFrame(0),
m_hTitleLogoImg(-1),
m_hCharaImg(-1),
m_charaPos(VGet(Game::kScreenWidthHalf, Game::kScreenHeightHalf, 0.0f)),
m_charaDir(VGet(kCharaSpeed, kCharaSpeed, 0.0f)),
m_pSelectMenu(std::make_shared<SelectMenuBase>())
{
	// データ読み込み
	LoadData();
}

SceneTitle::~SceneTitle()
{
	// 画像ハンドル解放
	m_hTitleLogoImg = -1;
	DeleteGraph(m_hCharaImg);
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
	// 毎フレームカウント
	m_countFrame++;
	// 更新処理のメンバ関数ポインタ
	(this->*m_updateFunc)(input);
	// キャラクター更新
	UpdateChara();
}

void SceneTitle::Draw()
{
	// キャラクター描画
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
	DrawRotaGraphF(m_charaPos.x, m_charaPos.y, kCharaSize, 0, m_hCharaImg, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
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
	m_hCharaImg = LoadGraph("Data/ImageData/Manju_MYU.png");
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

void SceneTitle::UpdateChara()
{
	// 画面端判定
	if (m_charaPos.x - Game::kChipSizeHalf < 0.0f || m_charaPos.x + Game::kChipSizeHalf > Game::kScreenWidth)
	{
		m_charaDir.x *= -1;
	}
	if (m_charaPos.y - Game::kChipSizeHalf < 0.0f || m_charaPos.y + Game::kChipSizeHalf > Game::kScreenHeight)
	{
		m_charaDir.y *= -1;
	}
	// キャラクター座標更新
	m_charaPos = VAdd(m_charaPos, m_charaDir);
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
