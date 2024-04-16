#pragma once
#include "Game.h"

class SceneMain;
class SubjectManager;

class Player
{
public:
	// �R���X�g���N�^
	Player();
	// �f�X�g���N�^
	virtual ~Player();
	// �V�[�����C���̃Z�b�g
	void SetMain(SceneMain* main) { m_pMain = main; }
	// �v�f�}�l�[�W���[�̃Z�b�g
	void SetSubjectManager(SubjectManager* subManager) { m_pSubjectManager = subManager; }

	// �X�V
	void Update(const InputState& input);
	// �`��
	void Draw();

private:
	// �{�^���ʒu�ݒ�
	void SetButtonPos();
	// �{�^���͈̔̓`�F�b�N
	bool ButtonRangeCheck(float posX, float posY);
	// �{�^���T�C�Y���Z�b�g
	void AllButtonSizeReset();
	// �I�����̏���
	void CorsorUpdate(const InputState& input);

private:
	// �{�^���T�C�Y
	double m_chinoButtonSize;
	double m_notChinoButtonSize;
	double m_soughtButtonSize;

	// �e�{�^���̉摜�n���h��
	int m_hChinoButton;
	int m_hNotChinoButton;
	int m_hSoughtButton;

	// �{�^���ʒu
	VECTOR m_ChinoButtonPos;
	VECTOR m_NotChinoButtonPos;
	VECTOR m_SoughtButtonPos;

	// �J�[�\���ʒu
	MouseInputState m_mouseState;

private:
	SceneMain* m_pMain;
	SubjectManager* m_pSubjectManager;
};