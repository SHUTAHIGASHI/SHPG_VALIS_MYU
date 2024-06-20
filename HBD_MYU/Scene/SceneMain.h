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

	// ����������
    void Init();
    // �X�V����
    void Update(const InputState& input);
    // �`�揈��
    void Draw();
	// �I������
    void End();

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
    // �A�N�V�����}�l�[�W���[
    std::shared_ptr<class Action> m_pAction;
    // UI
    std::shared_ptr<class UiManager> m_pUiManager;
    // �}�b�v�`��
	std::shared_ptr<class MapDraw> m_pMapDraw;
};

