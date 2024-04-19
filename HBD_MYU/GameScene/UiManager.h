#pragma once
#include "Myu.h"
#include <string>
#include <vector>
#include <DxLib.h>

class UiManager
{
public:
	// �R���X�g���N�^
	UiManager();
	// �f�X�g���N�^
	~UiManager();

	// ������
	void Init();
	// �X�V
	void Update();
	// �`��
	void Draw();

	// �L�����N�^�[���ݒ�
	void SetCharacterInfo(state charaState) { m_charaState = charaState; }
	// �X�e�[�^�X�`��ʒu
	void SetStatusDrawPos(float x, float y) { m_statusDrawPos = VGet(x, y, 0.0f); }
private:
	// �L�����N�^�[���
	state m_charaState;
	// �`��ʒu
	VECTOR m_statusDrawPos;
};

