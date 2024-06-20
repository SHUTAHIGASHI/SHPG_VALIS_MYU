#pragma once
#include "game.h"
#include <unordered_map>
#include <string>

class CursorManager
{
public:
	~CursorManager();
	/// <summary>
	/// Load�g�p�҂�GetInstance()��ʂ����Q�Ƃ��炵�����p�ł��Ȃ�
	/// </summary>
	/// <returns></returns>
	static CursorManager& GetInstance()
	{
		// �B��̎���
		static CursorManager instance;

		// ����̎Q�Ƃ�Ԃ�
		return instance;
	}

	// �J�[�\���X�V
	void UpdateCursor(const InputState& input);

	// �J�[�\���`��
	void DrawCursor();

	// �J�[�\���`�F���W
	void ChangeCursor(std::string key);

private:
	// �V���O���g���p�^�[���Ȃ̂ŃR���X�g���N�^��private�ɒu��
	CursorManager();
	// �R�s�[��������֎~����
	CursorManager(const CursorManager&) = delete;			// �R�s�[�R���X�g���N�^
	void operator = (const CursorManager&) = delete;		// ������֎~

	// �J�[�\�����W
	float m_posX;
	float m_posY;

	// �J�[�\���摜�n���h��
	int m_cursorHandle;
};

