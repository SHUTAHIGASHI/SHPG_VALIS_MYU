#pragma once
#include <DxLib.h>
#include "Myu.h"
#include <string>
#include <list>
#include <map>

struct UiLog
{
	UiLog(std::string log) : log(log)
	{
		textLength = GetDrawFormatStringWidth(log.c_str());
	}
	std::string log;
	int textLength;
	VECTOR pos = VGet(Game::kScreenWidth, Game::kUiHeightBottom - Game::kChipSizeHalf, 0.0f);;
};

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

	// ���O�ǉ�
	void AddLog(std::string log);

	// �A���UI����
	void OnReturning(std::list<std::string> charaName);

	// �L�����N�^�[���ݒ�
	void SetCharacterInfo(charaState charaState) { m_charaState = charaState; }
	// �X�e�[�^�X�`��ʒu
	void SetStatusDrawPos(float x, float y) { m_statusDrawPos = VGet(x, y, 0.0f); }
private:
	// �s����ԕ`��
	void DrawActionState();

	// ���O�e�L�X�g�X�V
	void UpdateLogText();
	// ���O�e�L�X�g�`��
	void DrawLogText();

private:
	// �L�����N�^�[���
	charaState m_charaState;
	// �`��ʒu
	VECTOR m_statusDrawPos;
	// �`�悷�郍�O
	std::list<UiLog> m_logs;
private:
	// UI�o�[�̃}�b�v
	std::map<std::string, class UiBar*> m_uiBars;
};