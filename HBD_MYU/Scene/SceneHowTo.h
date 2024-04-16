#pragma once
#include "Scene.h"
#include "Game.h"

class SceneHowTo :
    public Scene
{
public:
    SceneHowTo(SceneManager& manager);
    virtual ~SceneHowTo();

    void Update(const InputState& input);
    void Draw();

private:
    // ���t���[���J�E���g
    int m_countFrame;
    // �摜�n���h��
    int m_hImg;
    // �`����W
    VECTOR m_pos;
};

