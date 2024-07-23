#include "SceneLesson.h"
#include "SceneManager.h"
#include "SoundManager.h"

SceneLesson::SceneLesson(SceneManager& manager):
	Scene(manager)
{
}

SceneLesson::~SceneLesson()
{
}

void SceneLesson::Init()
{
	// BGM�ύX
	SoundManager::GetInstance().SetBGM("henitai");
}

void SceneLesson::Update(const InputState& input)
{
}

void SceneLesson::Draw()
{
}

void SceneLesson::End()
{
	// BGM�ύX
	SoundManager::GetInstance().SetBGM("katsuairon");
}
