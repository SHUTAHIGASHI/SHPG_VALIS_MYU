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
	// �s����ԕ`��
	void DrawActionState();
	// �A��̃e�L�X�g�`��
	void DrawReturningText();

	// �A���UI����
	void OnReturning(std::vector<std::string> charaName);

	// �L�����N�^�[���ݒ�
	void SetCharacterInfo(state charaState) { m_charaState = charaState; }
	// �X�e�[�^�X�`��ʒu
	void SetStatusDrawPos(float x, float y) { m_statusDrawPos = VGet(x, y, 0.0f); }

private:
	// �L�����N�^�[���
	state m_charaState;
	// �`��ʒu
	VECTOR m_statusDrawPos;
	// ���o�������̃L������
	std::vector<std::string> m_outingCharaName;
	// ���o������̃e�L�X�g�`��J�E���g
	int m_returningTextCount;
};

