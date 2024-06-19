#pragma once
#include <DxLib.h>
#include "Myu.h"
#include <string>
#include <list>
#include <map>

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
	void OnReturning(std::list<std::string> charaName);

	// �L�����N�^�[���ݒ�
	void SetCharacterInfo(charaState charaState) { m_charaState = charaState; }
	// �X�e�[�^�X�`��ʒu
	void SetStatusDrawPos(float x, float y) { m_statusDrawPos = VGet(x, y, 0.0f); }

private:
	// �L�����N�^�[���
	charaState m_charaState;
	// �`��ʒu
	VECTOR m_statusDrawPos;
	// ���o�������̃L������
	std::list<std::string> m_outingCharaName;
	// ���o������̃e�L�X�g�`��J�E���g
	int m_returningTextCount;
private:
	// UI�o�[�̃}�b�v
	std::map<std::string, class UiBar*> m_uiBars;

};

