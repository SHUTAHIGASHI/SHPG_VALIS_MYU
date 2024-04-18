#pragma once
#include <string>
#include <memory>
#include "Game.h"

enum class actionState
{
	Idle,
	Eat,
	Sleep,
	Play,
	Outing,
	Max
};

class Myu
{
private:
	struct state
	{
		std::string name = "�݂�[�����";
		actionState action = actionState::Idle;
		int level = 1;
		double exp = 0.0;
		double hunger = 0.0;
		double happy = 0.0;
		double sleep = 0.0;
	};

public:
	// �R���X�g���N�^
	Myu();
	// �f�X�g���N�^
	~Myu();

	// ������
	void Init();
	// �X�V
	void Update();
	// ��ԑJ��
	void ChangeState(actionState state);

	// ���݂̃X�e�[�^�X�擾
	state GetState() const { return m_state; }

private:
	// ���x���A�b�v����
	void LevelUp();

	// �����o�֐��|�C���^(�X�V)
	using m_tUpdateFunc = void (Myu::*) ();
	m_tUpdateFunc m_updateFunc = nullptr;
	// ��Ԃ��Ƃ̍X�V
	void UpdateIdle();
	void UpdateEat();
	void UpdateSleep();
	void UpdatePlay();
	void UpdateOuting();

private:
	// �X�e�[�^�X�Ǘ�
	state m_state;
};

