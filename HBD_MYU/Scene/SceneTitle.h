#pragma once
#include "Scene.h"

class SceneTitle:
    public Scene
{
public:
    // �R���X�g���N�^
    SceneTitle(SceneManager& manager);
    // �f�X�g���N�^
    virtual ~SceneTitle();
    // �X�V
    void Update(const InputState& input);
    // �`��
    void Draw();

private:
};

