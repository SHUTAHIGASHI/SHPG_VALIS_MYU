#pragma once
#include "Scene.h"
#include "Game.h"
#include <string>
#include <vector>

class SelectMenu
{
public:
    // �R���X�g���N�^
    SelectMenu();
    // �f�X�g���N�^
    virtual ~SelectMenu();
    // ������
    void Init(bool isMouse);
    // �X�V����
    void Update(const InputState& input);
    // �`��
    void Draw();
    // �I�����ڒǉ�
    void AddSelectItem(std::string itemName);

    // �I�𒆂̍��ڒl�擾
    int GetSelectedIndex() { return m_selectedPos; }

    // ���j���[���ڕ`��ʒu�ݒ�
    void SetItemDrawPos(float x, float y) { m_drawPos.x = x; m_drawPos.y = y; }
    // �����J���[�̐ݒ�
    void SetItemColor(int color) { m_itemColor = color; }
    void SetSelectedItemColor(int color) { m_selectedItemColor = color; }

private: // �v���C�x�[�g�֐�
    // ������̍X�V
    void DrawMenuText();

    // �����o�֐��|�C���^(�X�V)
    using m_tUpdateFunc = void (SelectMenu::*) (const InputState& input);
    m_tUpdateFunc m_updateFunc = nullptr;
    // �J�[�\���X�V����
    void CursorUpdate(const InputState& input);
    // �ʏ�I���X�V����
    void NormalUpdate(const InputState& input);

private:
    struct SelectItemState
    {
        std::string itemName = "EMPTY";
    };

private: // �V�[�������̊Ǘ��ϐ�
    // �I�𒆂̍���
    int m_selectedPos;
    // ���ڐ�
    std::vector<SelectItemState> m_selectItems;

    // �J�[�\���ʒu
    MouseInputState m_mouseState;
    // �J�[�\�����g���ɂ��邩�ǂ���
    bool m_isCursorRanged;

    // ���ڕ`��ʒu
    VECTOR m_drawPos;
    // �I�����ڂ̃J���[
    int m_itemColor;
    int m_selectedItemColor;
};
