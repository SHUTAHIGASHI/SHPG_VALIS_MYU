#include "ItemManager.h"
#include "Game.h"

ItemManager::ItemManager()
{
}

ItemManager::~ItemManager()
{
}

void ItemManager::Init()
{
	m_Items.push_back(std::make_shared<ItemBase>("�K�N", ItemType::Toys, 0.0, 0.0, 10.0));
	m_Items.push_back(std::make_shared<ItemBase>("�ٓ�", ItemType::Food, 0.0, 0.0, 10.0));
	m_Items.push_back(std::make_shared<ItemBase>("�~��", ItemType::Toys, 0.0, 0.0, 10.0));
	m_Items.push_back(std::make_shared<ItemBase>("�N�b�L�[", ItemType::Food, 0.0, 0.0, 10.0));
}

std::shared_ptr<class ItemBase> ItemManager::GetItem(int index)
{
	return std::shared_ptr<class ItemBase>();
}

std::shared_ptr<class ItemBase> ItemManager::GetRandomItem()
{
	int index = GetRand(m_Items.size() - 1);

	return m_Items[index];
}

std::shared_ptr<class ItemBase> ItemManager::GetRandomItem(ItemType type)
{
	int index = 0;
	do
	{
		index = GetRand(m_Items.size() - 1);
	} while (m_Items[index]->GetType() != type);

	return m_Items[index];
}
