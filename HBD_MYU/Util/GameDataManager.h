#pragma once
#include <unordered_map>
#include <string>
#include <DxLib.h>
#include "Myu.h"

/// <summary>
/// SEの管理を行うシングルトンクラス
/// </summary>
class GameDataManager
{
public:
	~GameDataManager();
	/// <summary>
	/// SoundManager使用者はGetInstance()を通した参照からしか利用できない
	/// </summary>
	/// <returns></returns>
	static GameDataManager& GetInstance()
	{
		// 唯一の実態
		static GameDataManager instance;
		// それの参照を返す
		return instance;
	}

private:
	// キャラクターデータの保存
	void SaveCharacterData(class Myu charaData);
	// キャラクターデータの読み込み
	void LoadCharacterData();

	// 時間データの保存
	void SaveDateData();
	// 時間データの読み込み
	void LoadDateData();

	// シングルトンパターンなのでコンストラクタはprivateに置く
	GameDataManager();
	// コピーも代入も禁止する
	GameDataManager(const GameDataManager&) = delete;		// コピーコンストラクタ
	void operator = (const GameDataManager&) = delete;		// 代入も禁止

private:
	// 時間管理
	DATEDATA m_lastDate;
	DATEDATA m_nowDate;
};