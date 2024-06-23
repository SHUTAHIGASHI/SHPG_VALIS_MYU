#pragma once
#include "Scene.h"
#include <string>
#include <memory>
#include "Game.h"

class SceneTitle :
    public Scene
{
public:
    // �R���X�g���N�^
    SceneTitle(SceneManager& manager);
    // �f�X�g���N�^
    virtual ~SceneTitle();
    // ������
    void Init();
    // �X�V
    void Update(const InputState& input);
    // �`��
    void Draw();
    // �I��
    void End();

private: // �v���C�x�[�g�֐�
    // �f�[�^�ǂݍ���
    void LoadData();
    // �^�C�g���I��������
    void OnSceneEnd();
    // �L�����N�^�[�X�V
	void UpdateChara();

    using m_tUpdateFunc = void (SceneTitle::*) (const InputState& input);
    m_tUpdateFunc m_updateFunc = nullptr;
    // �^�C�g����ʍX�V����
    void NormalUpdate(const InputState& input);

private: // �V�[���̕ϐ�
    // ���t���[���J�E���g�p
    int m_countFrame;
    // �摜�n���h��
    int m_hTitleLogoImg;
    // �L�����n���h��
	int m_hCharaImg;
	// �L�����N�^�[���W
	VECTOR m_charaPos;
    VECTOR m_charaDir;

private:
    // �Z���N�g���j���[�̊Ǘ��ϐ�
    std::shared_ptr<class SelectMenuBase> m_pSelectMenu;
};

