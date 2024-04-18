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

	// 初期化
	void Init();
	// 更新
	void Update(const InputState& input);
	// 描画
	void Draw();

	// 餌をあげる
	void OnGiveFood();
	// 遊んであげる
	void OnPlay();
	// 寝る
	void OnSleep();
	// 外出
	void OnOuting();

	// キャラクター状態取得
	actionState GetMyuState() const;

private:
	// 項目選択時の処理
	void OnSelectItem(int index);

private:
	// お出かけ時のキャラ名
	std::vector<std::string> m_outingCharaName;

private:
	// キャラクター
	std::shared_ptr<class Myu> m_pMyu;
	// アイテム
	std::shared_ptr<class ItemManager> m_pItem;
	// 選択メニュー
	std::shared_ptr<class SelectMenu> m_pSelectMenu;
};

