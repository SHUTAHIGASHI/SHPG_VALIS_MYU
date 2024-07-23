#pragma once
#include "Scene.h"

class SceneLesson :
    public Scene
{
    public:
	SceneLesson(SceneManager& manager);
	~SceneLesson();

    // ‰Šú‰»ˆ—
    void Init()override;
    // XVˆ—
    void Update(const InputState& input)override;
    // •`‰æˆ—
    void Draw()override;
    // I—¹ˆ—
    void End()override;

private:
};

