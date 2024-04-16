#include "SceneMain.h"
#include "SceneManager.h"
#include "SoundManager.h"
#include "GameDataManager.h"
#include "Player.h"
#include "ScenePause.h"
#include "SceneAction.h"

namespace
{

}

SceneMain::SceneMain(SceneManager& manager):
	Scene(manager),
	m_updateFunc(&SceneMain::NormalUpdate),
	m_drawFunc(&SceneMain::NormalDraw),
	m_isEnd(false)
{
}
 
SceneMain::~SceneMain()
{
	// �Q�[���|�C���g�ۑ�
	//GameDataManager::GetInstance().SetGameScore(m_correct, m_questionNum);
}

void SceneMain::Update(const InputState& input)
{
	if (input.IsTriggered(InputType::pause))
	{
		m_Manager.PushScene(new ScenePause(m_Manager));
	}

	// �X�V�����̃����o�֐��|�C���^
	(this->*m_updateFunc)(input);
}

void SceneMain::Draw()
{
	(this->*m_drawFunc)();
}

void SceneMain::NormalUpdate(const InputState& input)
{
}

void SceneMain::NormalDraw()
{
}
