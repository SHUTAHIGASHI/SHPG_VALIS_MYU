#pragma once
#include "Game.h"
#include <string>

namespace
{
	// �����ړ����x
	constexpr float kTextMoveSpeed = 2.0f;

	// �����`�掞��
	constexpr int kDrawDelay = 30;
}

class UiPointBase
{
public:
	// �R���X�g���N�^
	UiPointBase();
	// �f�X�g���N�^
	virtual ~UiPointBase();

	// �X�V
	virtual void Update() = 0;
	// �`��
	virtual void Draw();

	// UI�ɕ\��������̐ݒ�
	void SetUIInfo(int tData);

	// UI�\�����I�����邩�ǂ���
	bool IsDelete() { return m_isDelete; }

protected:
	// �摜�`��ʒu
	float m_posX;
	float m_posY;
protected:
	// �L�����ǂ���
	bool m_isDelete;
	// ������~�J�E���g
	int m_countDelay;
	// �`�悷�鐔�l�f�[�^
	int m_numData;
	// �`�悷�镶���f�[�^
	std::string m_textData;
	// �`�悷�镶���̐F
	int m_textColor;
};

