#pragma once
#include <string>
#include "Game.h"

enum class actionState
{
	Idle,
	Eat,
	Sleep,
	Play
};

class Myu
{
private:
	struct state
	{
		std::string name = "�݂�[�����";
		actionState action = actionState::Idle;
		int exp = 0;
		int level = 1;
		int hunger = 0;
		int happy = 0;
		int sleep = 0;
	};

public:
	// �R���X�g���N�^
	Myu():
		m_updateFunc(&Myu::UpdateIdle),
		m_state()
	{
		state myu;
	}
	// �f�X�g���N�^
	~Myu()
	{

	}

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

private:
	// �X�e�[�^�X
	state m_state;
};

