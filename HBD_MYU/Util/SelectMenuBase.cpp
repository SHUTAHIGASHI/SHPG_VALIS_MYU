#include "SelectMenuBase.h"
#include "SceneManager.h"

namespace
{
	// 文字間隔
	constexpr int kTextDistance = Game::kFontSize * 1.5;
}

SelectMenu::SelectMenu():
m_updateFunc(&SelectMenu::NormalUpdate),
m_selectedPos(0),
m_selectItems(),
m_mouseState(),
m_isCursorRanged(false),
m_drawPos(VGet(0.0f, 0.0f, 0.0f)),
m_itemColor(Game::kColorWhite),
m_selectedItemColor(Game::kColorCyan)
{
}

SelectMenu::~SelectMenu()
{
}

void SelectMenu::Init(bool isMouse)
{
	if (isMouse) m_updateFunc = &SelectMenu::CursorUpdate;
}

void SelectMenu::Update(const InputState& input)
{
	// マウスカーソル座標取得
	m_mouseState.x = input.GetMousePosX();
	m_mouseState.y = input.GetMousePosY();
	// 更新
	(this->*m_updateFunc)(input);
}

void SelectMenu::Draw()
{
	DrawMenuText();
}

void SelectMenu::AddSelectItem(std::string itemName)
{
	m_selectItems.push_back(SelectItemState());
	m_selectItems.back().itemName = itemName;
}

void SelectMenu::DrawMenuText()
{
	int drawX = 0, drawY = 0;

	int itemCount = 0;
	for (auto& items : m_selectItems)
	{
		int textLength = GetDrawFormatStringWidth(items.itemName.c_str());
		drawX = static_cast<int>(m_drawPos.x - (textLength / 2));
		drawY = static_cast<int>(m_drawPos.y + (kTextDistance * itemCount));
		DrawFormatString(drawX, drawY, m_itemColor, "%s", items.itemName.c_str());

		itemCount++;
	}

	std::string drawText = "> " + m_selectItems[m_selectedPos].itemName + " <";
	int textLength = GetDrawFormatStringWidth(drawText.c_str());
	drawX = static_cast<int>(m_drawPos.x - (textLength / 2));
	drawY = static_cast<int>(m_drawPos.y + (kTextDistance * m_selectedPos));
	DrawFormatString(drawX, drawY - 2, m_selectedItemColor, "%s", drawText.c_str());
}

void SelectMenu::CursorUpdate(const InputState& input)
{
	m_isCursorRanged = false;

	int buttonPosX = 0, buttonPosY = 0;
	int itemCount = 0;
	for (auto& items : m_selectItems)
	{
		int textLength = GetDrawFormatStringWidth(items.itemName.c_str());
		buttonPosX = static_cast<int>(m_drawPos.x - (textLength / 2));
		buttonPosY = static_cast<int>(m_drawPos.y + (kTextDistance * itemCount));

		if (m_mouseState.x > buttonPosX && m_mouseState.x < buttonPosX + textLength
			&& m_mouseState.y > buttonPosY && m_mouseState.y < buttonPosY + Game::kFontSize)
		{
			m_isCursorRanged = true;
			m_selectedPos = itemCount;
		}
		itemCount++;
	}
}

void SelectMenu::NormalUpdate(const InputState& input)
{
	int selectItemMax = static_cast<int>(m_selectItems.size() - 1);
	if (input.IsTriggered(InputType::up))
	{
		m_selectedPos--;
		if (m_selectedPos < 0) m_selectedPos = selectItemMax;
	}
	else if (input.IsTriggered(InputType::down))
	{
		m_selectedPos++;
		if (m_selectedPos > selectItemMax) m_selectedPos = 0;
	}
}
