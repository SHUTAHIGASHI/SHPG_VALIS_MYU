#pragma once
#include "Scene.h"

class SceneLesson :
    public Scene
{
    public:
	SceneLesson(SceneManager& manager);
	~SceneLesson();

    // ����������
    void Init()override;
    // �X�V����
    void Update(const InputState& input)override;
    // �`�揈��
    void Draw()override;
    // �I������
    void End()override;

private:
};

