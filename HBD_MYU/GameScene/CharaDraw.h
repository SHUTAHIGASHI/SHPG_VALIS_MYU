#pragma once
#include "Game.h"
#include "Myu.h"

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
	void SetImage(int handle);
	// �L�����N�^�[�̈ʒu���Z�b�g
	void SetPos(float x, float y);
	// �L�����N�^�[�̃T�C�Y���Z�b�g
	void SetSize(float size);
	// �L�����N�^�[�̊p�x���Z�b�g
	void SetAngle(float angle);
	// �L�����N�^�[�̊�����Z�b�g
	void SetEmotion(emotionState emotion);

private:
	// �`��摜
	int m_hImage;
	// �摜�T�C�Y
	int m_imageSizeX;
	int m_imageSizeY;
	// �`��ʒu
	VECTOR m_pos;
	// �`��T�C�Y
	float m_size;
	// �`��p�x
	float m_angle;
	// �L�����N�^�[�̊���
	emotionState m_emotion;
};

