#pragma once
#include "Scene.h"
#include "GameDataManager.h"
#include <memory>
#include <string>

class SceneMain :
    public Scene
{
public:
    // �R���X�g���N�^
    SceneMain(SceneManager& manager);
    // �f�X�g���N�^
    virtual ~SceneMain();

    // �X�V����
    void Update(const InputState& input);
    // �`�揈��
    void Draw();

private:
    // �����o�֐��|�C���^(�X�V)
    using m_tUpdateFunc = void (SceneMain::*) (const InputState& input);
    m_tUpdateFunc m_updateFunc = nullptr;
    void NormalUpdate(const InputState& input);

    // �����o�֐��|�C���^(�`��)
    using m_tDrawFunc = void (SceneMain::*) ();
    m_tDrawFunc m_drawFunc = nullptr;
    void NormalDraw();

private:
    // �I�������ς݂��ǂ���
    bool m_isEnd;

private:
    // �A�N�V�������j���[
    std::shared_ptr<class Action> m_actionMenu;
    // �L�����N�^�[�`��
    std::shared_ptr<class CharaDraw> m_charaDraw;
};

