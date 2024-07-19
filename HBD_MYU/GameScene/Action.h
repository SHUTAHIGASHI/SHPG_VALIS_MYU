#pragma once
#include <list>
#include <memory>
#include <map>
#include "Myu.h"

class Action
{
public:
	// コンストラクタ
	Action();
	// デストラクタ
	~Action();

	// UI制御のポインタをセット
	void SetUiManager(class UiManager* ui) { m_pUi = ui; }

	// 初期化
	void Init();
	// 更新
	void Update(const InputState& input);
	// 描画
	void Draw();

	// キャラクターステータス取得
	const charaState GetCharaStatus() const;

private:
	// 待機状態に戻る
	void OnIdle();
	// 餌をあげる
	void OnGiveFood();
	// 寝る
	void OnSleep();
	// レッスンに行く
	void OnLesson();
	// 外出
	void OnOuting();
	// セーブ
	void OnSave();

	// 項目選択時の処理
	void OnSelectItem(int index);
	// ランダムでキャラ名を選択
	void SetRandomCharaName();
	// カーソルの範囲内チェック
	bool CheckCursorRange();

	// メンバ関数ポインタ(更新)
	using m_tUpdateFunc = void (Action::*) (const InputState& input);
	m_tUpdateFunc m_updateFunc = nullptr;
	// 状態ごとの更新
	void UpdateIdle(const InputState& input);
	void UpdateActioning(const InputState& input);

	// 各行動時の処理管理マップ
	using m_tSelectFunc = void (Action::*) ();
	std::map<std::string, m_tSelectFunc> m_selectFuncMap;

private:
	// お出かけ時のキャラ名
	std::list<std::string> m_outingCharaName;
	// カーソル座標
	float m_cursorPosX;
	float m_cursorPosY;

private:
	// キャラクター
	std::shared_ptr<class Myu> m_pMyu;
	// 選択メニュー
	std::shared_ptr<class SelectMenuBase> m_pSelectMenu;
	// UI制御
	class UiManager* m_pUi;
};
