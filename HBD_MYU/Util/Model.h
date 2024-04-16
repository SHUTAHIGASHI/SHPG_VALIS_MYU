#pragma once
#include "Game.h"

class Model
{
public:
	// �R���X�g���N�^
	Model();
	// �f�X�g���N�^
	virtual ~Model();

	// ������
	void Init(int hModel);
	// �X�V(�A�j���[�V�����g�p���̂�)
	void Update();
	// �`��
	void Draw();

	/* setter */
	void SetPosition(VECTOR pos);		// ���W
	void SetScale(float size);			// �g��
	void SetMotionType(int);			// ���[�V�����^�C�v
	void SetDirection(VECTOR lookPos, float rota);	// ����
	void SetRotation(VECTOR);			// ��]

private:
	// ���f���n���h��
	int m_hModel;

	// �A�j���[�V����
	int m_AnimNo;
	int m_AnimIndex;
	float m_AnimTotalTime;
	float m_AnimPlayTime;

	// �\���ʒu���W
	VECTOR m_pos;
	// ��]
	VECTOR m_rotation;
};

