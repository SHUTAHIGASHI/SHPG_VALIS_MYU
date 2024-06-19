#pragma once
#include <string>
#include <memory>
#include <map>
#include "Game.h"

// �L�����N�^�[�̊���̎��
enum class emotionState
{
	// �ʏ�
	Normal,
	// �K��
	Happy,
	// �߂���
	Sad,
	// �{��
	Angry,
	// ����
	Surprise,
	// ���
	Tired,
	// ����
	Sleepy,
	// ��
	Hungry,
	// �̂�����
	Sing,
	// �x�肽��
	Dance,
	// �V�т���
	Play,
	// ���U��
	Outing,
	// ����������
	Cook,
	// �y����
	Fun,
	// �ő�
	Max
};

// �X�e�[�g�̎��
enum class actionState
{
	Idle,
	Eat,
	Sleep,
	Play,
	Outing,
	Max
};

struct charaState
{
	std::string name = "�݂�[�����";
	VECTOR drawPos = VGet(0.0f, 0.0f, 0.0f);
	emotionState emotion = emotionState::Normal;
	actionState action = actionState::Idle;
	int level = 1;
	double exp = 0.0;
	double hunger = 0.0;
	double happy = 0.0;
	double sleep = 0.0;
};

class Myu
{
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
	const charaState GetStatus() const { return m_state; }

private:
	// ���x���A�b�v����
	void LevelUp();
	// �X�e�[�^�X�ő�l�Ǘ�
	void StatusMaxCheck();
	// �������̈ړ�����
	void UpdateRoomMove();

	// �����o�֐��|�C���^(�X�e�[�g���Ƃ̍X�V)
	using m_tUpdateFunc = void (Myu::*) ();
	// �X�e�[�g���Ƃ̊֐��|�C���^��MAP�ŊǗ�
	std::map<actionState, m_tUpdateFunc> m_updateFuncMap;
	// ��Ԃ��Ƃ̍X�V
	void UpdateIdle();
	// �H����
	void UpdateEat();
	// ������
	void UpdateSleep();
	// �V�ђ�
	void UpdatePlay();
	// �O�o��
	void UpdateOuting();

	// �����o�֐��|�C���^(�X�V)
	using m_tUpdateIdleFunc = void (Myu::*) ();
	// ����Ƃ̊֐��|�C���^��MAP�ŊǗ�
	std::map<emotionState, m_tUpdateIdleFunc> m_updateIdleFuncMap;
	// ��Ԃ��Ƃ̍X�V
	void UpdateIdleNormal();
	//// �K��
	//void UpdateIdleHappy();
	//// �߂���
	//void UpdateIdleSad();
	//// �{��
	//void UpdateIdleAngry();
	//// ����
	//void UpdateIdleSurprise();
	//// ���
	//void UpdateIdleTired();
	//// ����
	//void UpdateIdleSleepy();
	//// ��
	//void UpdateIdleHungry();
	//// �̂�����
	//void UpdateIdleSing();
	//// �x�肽��
	//void UpdateIdleDance();
	//// �V�т���
	//void UpdateIdlePlay();
	//// ���U��
	//void UpdateIdleOuting();
	//// ����������
	//void UpdateIdleCook();
	//// �y����
	//void UpdateIdleFun();

private:
	// ���̈ړ����W
	VECTOR m_nextPos;
	// �X�e�[�^�X�Ǘ�
	charaState m_state;
	// ���t���[���J�E���g
	int m_countFrame;
	// �s������̃t���[���J�E���g
	int m_actionEndFrameCount;
	// �����ړ��̃t���[���J�E���g
	int m_roomMoveFrameCount;
};

