#include "GameDataManager.h"

GameDataManager::~GameDataManager()
{
	// 時間データの保存
	SaveDateData();
}

void GameDataManager::SaveCharacterData(class Myu charaData)
{
	// キャラクターデータの保存
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
	// 時間データの読み込み
	LoadDateData();
}