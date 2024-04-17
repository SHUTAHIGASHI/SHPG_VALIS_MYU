#pragma once
#include <unordered_map>
#include <string>
#include <DxLib.h>
#include "Myu.h"

/// <summary>
/// SE�̊Ǘ����s���V���O���g���N���X
/// </summary>
class GameDataManager
{
public:
	~GameDataManager();
	/// <summary>
	/// SoundManager�g�p�҂�GetInstance()��ʂ����Q�Ƃ��炵�����p�ł��Ȃ�
	/// </summary>
	/// <returns></returns>
	static GameDataManager& GetInstance()
	{
		// �B��̎���
		static GameDataManager instance;
		// ����̎Q�Ƃ�Ԃ�
		return instance;
	}

private:
	// �L�����N�^�[�f�[�^�̕ۑ�
	void SaveCharacterData(class Myu charaData);
	// �L�����N�^�[�f�[�^�̓ǂݍ���
	void LoadCharacterData();

	// ���ԃf�[�^�̕ۑ�
	void SaveDateData();
	// ���ԃf�[�^�̓ǂݍ���
	void LoadDateData();

	// �V���O���g���p�^�[���Ȃ̂ŃR���X�g���N�^��private�ɒu��
	GameDataManager();
	// �R�s�[��������֎~����
	GameDataManager(const GameDataManager&) = delete;		// �R�s�[�R���X�g���N�^
	void operator = (const GameDataManager&) = delete;		// ������֎~

private:
	// ���ԊǗ�
	DATEDATA m_lastDate;
	DATEDATA m_nowDate;
};