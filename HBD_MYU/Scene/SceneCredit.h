#pragma once
#include "Scene.h"
#include "Game.h"
#include <memory>
#include <string>

class SceneCredit :
    public Scene
{
public:
    SceneCredit(SceneManager& manager);
    virtual ~SceneCredit();

    // �X�V
    void Update(const InputState& input);
    // �`��
    void Draw();

private: // �v���C�x�[�g�֐�
    // �e�L�X�g�`��
    void DrawMenuText();
private: // �ϐ�
    // �w�i�`����W
    VECTOR m_bgPos;
    // ���t���[���J�E���g
    int m_countFrame;
    // �X�N���[���̃t���[���ҋ@
    int m_scrollWaitFrame;
    // �w�i�摜
    int m_hCreditImg;
    // �摜�T�C�Y
    int m_ClearGraphX;
    int m_ClearGraphY;
    // �X�N���[�����邩�ǂ���
    bool m_isCanScroll;
    // �e�L�X�g�`�攻��
    bool m_isScrollEnd;
};
