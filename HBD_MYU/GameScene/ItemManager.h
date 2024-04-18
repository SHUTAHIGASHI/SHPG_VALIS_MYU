#pragma once
#include <vector>
#include <memory>
#include "ItemBase.h"

class ItemManager
{
public:
	ItemManager();
	~ItemManager();

	// ������
	void Init();

	// �A�C�e�����擾
	std::shared_ptr<class ItemBase> GetItem(int index);
	// �����_���ŃA�C�e���擾
	std::shared_ptr<class ItemBase> GetRandomItem();
	// �w�肵���A�C�e���^�C�v���烉���_���Ŏ擾
	std::shared_ptr<class ItemBase> GetRandomItem(ItemType type);

private:
	std::vector<std::shared_ptr<class ItemBase>> m_Items;
};

