#pragma once
#include "Scene.h"
#include "Game.h"
#include <memory>
#include <string>

class SceneDebug :
    public Scene
{
public:
    SceneDebug(SceneManager& manager);
    virtual ~SceneDebug();

	void Init() {}
    void Update(const InputState& input);
    void Draw();
	void End() {}

private:
    void UpdateText();

private:
    // �I�𒆂̍���
    int m_selectedPos;
    // �I�𒆂̍��ږ�
    std::string m_selectedItemName;
};

