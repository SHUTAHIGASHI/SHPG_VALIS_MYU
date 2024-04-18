#pragma once
#include "Game.h"

// �L�����N�^�[�̊���̎��
enum class CharaEmotion
{
	Normal,
	Happy,
	Sad,
	Angry,
	Max
};

class CharaDraw
{
public:
	// �R���X�g���N�^
	CharaDraw();
	// �f�X�g���N�^
	~CharaDraw();
	// �`��
	void Draw();

	// �L�����N�^�[�̉摜���Z�b�g
	void SetImage(const char* fileName);
	// �L�����N�^�[�̈ʒu���Z�b�g
	void SetPos(float x, float y);
	// �L�����N�^�[�̃T�C�Y���Z�b�g
	void SetSize(float size);
	// �L�����N�^�[�̊p�x���Z�b�g
	void SetAngle(float angle);
	// �L�����N�^�[�̊�����Z�b�g
	void SetEmotion(CharaEmotion emotion);

private:
	// �`��摜
	int m_hImage;
	// �`��ʒu
	VECTOR m_pos;
	// �`��T�C�Y
	float m_size;
	// �`��p�x
	float m_angle;
	// �L�����N�^�[�̊���
	CharaEmotion m_emotion;
};

