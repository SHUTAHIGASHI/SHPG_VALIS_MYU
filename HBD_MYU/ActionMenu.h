#pragma once
#include <memory>
#include "Myu.h"

class ActionMenu
{
public:
	// コンストラクタ
	ActionMenu();
	// デストラクタ
	~ActionMenu();

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

	// キャラクター状態取得
	actionState GetMyuState() const;

private:
	// 項目選択時の処理
	void OnSelectItem(int index);

private:
	// キャラクター
	std::shared_ptr<class Myu> m_pMyu;
	// 選択メニュー
	std::shared_ptr<class SelectMenu> m_pSelectMenu;
};

