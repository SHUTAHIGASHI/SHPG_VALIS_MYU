#include "GameDataManager.h"

GameDataManager::~GameDataManager()
{
	// ���ԃf�[�^�̕ۑ�
	SaveDateData();
}

void GameDataManager::SaveCharacterData(class Myu charaData)
{
	// �L�����N�^�[�f�[�^�̕ۑ�
}

void GameDataManager::LoadCharacterData()
{
}

void GameDataManager::SaveDateData()
{
}

void GameDataManager::LoadDateData()
{
}

GameDataManager::GameDataManager():
	m_lastDate(),
	m_nowDate()
{
	// ���ԃf�[�^�̓ǂݍ���
	LoadDateData();
}