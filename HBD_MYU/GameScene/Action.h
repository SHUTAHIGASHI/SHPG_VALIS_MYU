#pragma once
#include <memory>
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

	// 待機状態に戻る
	void OnIdle();
	// 餌をあげる
	void OnGiveFood();
	// 遊んであげる
	void OnPlay();
	// 寝る
	void OnSleep();
	// 外出
	void OnOuting();
	// キャラクターステータス取得
	const state GetCharaStatus() const;

private:
	// 項目選択時の処理
	void OnSelectItem(int index);
	// ランダムでキャラ名を選択
	void SetRandomCharaName();

	// メンバ関数ポインタ(更新)
	using m_tUpdateFunc = void (Action::*) ();
	m_tUpdateFunc m_updateFunc = nullptr;
	// 状態ごとの更新
	void UpdateIdle();
	void UpdateEat();
	void UpdateSleep();
	void UpdatePlay();
	void UpdateOuting();

private:
	// お出かけ時のキャラ名
	std::vector<std::string> m_outingCharaName;
	// お出かけ時間カウント
	int m_outingTimeCount;

private:
	// キャラクター
	std::shared_ptr<class Myu> m_pMyu;
	// アイテム
	std::shared_ptr<class ItemManager> m_pItem;
	// 選択メニュー
	std::shared_ptr<class SelectMenu> m_pSelectMenu;
	// UI制御
	class UiManager* m_pUi;
};

