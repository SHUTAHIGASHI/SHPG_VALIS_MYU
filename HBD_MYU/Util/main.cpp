#include "Game.h"
#include "SoundManager.h"
#include "CursorManager.h"
#include "SceneManager.h"
#include "SceneTitle.h"
#include "SceneDebug.h"
#include "Load.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// ログ無効化
	SetOutApplicationLogValidFlag(false);
	// 他ウィンドウを選択していても動作
	SetAlwaysRunFlag(true);
	// ウィンドウモード設定
	ChangeWindowMode(Game::kWindowMode);
	// ウィンドウモードのサイズ変更
	SetWindowSizeChangeEnableFlag(true);
	// ウィンドウ名設定
	SetMainWindowText(Game::kTitleText);
	// 画面サイズの設定
	SetGraphMode(Game::kScreenWidth, Game::kScreenHeight, Game::kColorDepth);
	// ダブルバッファモード
	SetDrawScreen(DX_SCREEN_BACK);
	// フルスクリーンウインドウの切り替えでリソースが消えるのを防ぐ
	SetChangeScreenModeGraphicsSystemResetFlag(false);

	// ＤＸライブラリ初期化処理
	if (DxLib_Init() == -1)
	{
		return -1;			// エラーが起きたら直ちに終了
	}

	// ゲーム中のマウスポインタ描画設定
	SetMouseDispFlag(false);
	// マウスカーソル位置設定
	SetMousePoint(Game::kScreenWidthHalf, Game::kScreenHeightHalf);

	// リソースの読み込み
	LPCSTR font = Game::kFontFileName;	// 読み込むフォントファイルのパス
	if (AddFontResourceEx(font, FR_PRIVATE, NULL) > 0) {
	}
	else {
		// フォント読み込みエラー処理
		MessageBox(NULL, "フォント読み込み失敗", "", MB_OK);
	}
	// 標準フォント設定
	ChangeFont(Game::kFontName);
	SetFontSize(Game::kFontSize);

	// サウンドマネージャー宣言
	auto& soundManager = SoundManager::GetInstance();
	// カーソルマネージャー宣言
	auto& cursorManager = CursorManager::GetInstance();
	// キー入力状態クラス宣言
	InputState input;
	// シーンマネージャー宣言
	SceneManager scene;

	//ロード
	Load::GetInstance().AllLoadData();
	// カーソル画像読み込み
	int hCursorImg = Load::GetInstance().GetHandle("cursor");

#ifdef _DEBUG
	scene.ChangeScene(new SceneDebug(scene));
#else
	scene.ChangeScene(new SceneTitleMenu(scene));
#endif

	while (ProcessMessage() == 0)
	{
		LONGLONG time = GetNowHiPerformanceCount();
		//SetMousePoint(static_cast<int>(Game::kScreenWidthHalf), static_cast<int>(Game::kScreenHeightHalf));

		// 画面のクリア
		ClearDrawScreen();

		// 入力状態の更新
		input.Update();

		// 現在のシーンの更新
		scene.Update(input);

		// カーソルの更新
		cursorManager.UpdateCursor(input);

		// 背景描画
		DrawExtendGraph(0, 0, Game::kScreenWidth, Game::kScreenHeight, Load::GetInstance().GetHandle("gameBg"), true);

		// 現在のシーンの描画
		scene.Draw();

		// マウスカーソル描画
		cursorManager.DrawCursor();

		// 裏画面を表画面と入れ替える
		ScreenFlip();

		if (scene.IsGameEnd()) break;

#ifdef _DEBUG
		// escキーを押したら終了する
		if (CheckHitKey(KEY_INPUT_L)) scene.ChangeScene(new SceneDebug(scene));
#endif
		while (GetNowHiPerformanceCount() - time < 16667)
		{

		}
	}
	// マウスカーソル描画
	SetMouseDispFlag(true);

	// カーソル画像削除
	hCursorImg = -1;
	//データ削除
	Load::GetInstance().DeleteAllData();
	// DXライブラリ使用の終了処理
	DxLib_End();

	// 処理の終了
	return 0;
}