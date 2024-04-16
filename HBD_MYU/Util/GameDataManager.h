#pragma once
#include <unordered_map>
#include <string>

enum class GameMode
{
	empty,
	QUESTIONLIMIT,
	TIMELIMIT,
	ALLCHALLENGE
};

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

	void SetGameMode(GameMode mode) { m_gameMode = mode; }
	void SetGameScore(int score, int qNum) { m_gameScore = score , m_questionNum = qNum; }
	void SetGameTime(int time) { m_attackTime = time; }

	GameMode GetGameMode() { return m_gameMode; }
	int GetGameScore() { return m_gameScore; }
	int GetQuestionNum() { return m_questionNum; }
	int GetGameTime() { return m_attackTime; }
private:
	// �V���O���g���p�^�[���Ȃ̂ŃR���X�g���N�^��private�ɒu��
	GameDataManager();
	// �R�s�[��������֎~����
	GameDataManager(const GameDataManager&) = delete;			// �R�s�[�R���X�g���N�^
	void operator = (const GameDataManager&) = delete;		// ������֎~

private:
	// �Q�[�����[�h
	GameMode m_gameMode;
	// �X�R�A
	int m_gameScore;
	// ��萔
	int m_questionNum;
	// �Q�[������
	int m_attackTime;
};