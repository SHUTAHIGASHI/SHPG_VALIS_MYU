#pragma once
#include <vector>
#include <memory>
#include "ItemBase.h"

class ItemManager
{
public:
	ItemManager();
	~ItemManager();

	// 初期化
	void Init();

	// アイテム情報取得
	std::shared_ptr<class ItemBase> GetItem(int index);
	// ランダムでアイテム取得
	std::shared_ptr<class ItemBase> GetRandomItem();
	// 指定したアイテムタイプからランダムで取得
	std::shared_ptr<class ItemBase> GetRandomItem(ItemType type);

private:
	std::vector<std::shared_ptr<class ItemBase>> m_Items;
};

