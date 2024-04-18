#pragma once
#include <string>

// �A�C�e���̎��
enum class ItemType
{
	Food,
	Toys,
};

class ItemBase
{
public:
	ItemBase(std::string name, ItemType type, double exp, double hun, double hap):
		m_name(name),
		m_type(type),
		m_expNum(exp),
		m_hungerNum(hun),
		m_happyNum(hap)
	{}
	virtual ~ItemBase()
	{}

	// �A�C�e�������擾
	std::string GetName() const
	{
		return m_name;
	}
	// �A�C�e���^�C�v���擾
	ItemType GetType() const
	{
		return m_type;
	}

private:
	std::string m_name;
	ItemType m_type;
	int m_expNum;
	int m_hungerNum;
	int m_happyNum;
};

