#pragma once
#include "Scene.h"

class SceneAction:
	public Scene
{
public:
	// �R���X�g���N�^
	SceneAction(SceneManager& manager);
	// �f�X�g���N�^
	virtual ~SceneAction();
	// �X�V
	void Update(const InputState& input);
	// �`��
	void Draw();

private:
};

