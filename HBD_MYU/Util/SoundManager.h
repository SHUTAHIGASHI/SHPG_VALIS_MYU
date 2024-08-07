#pragma once
#include <unordered_map>
#include <map>
#include <string>
#include <vector>

enum class SoundType
{
	select,
};

/// <summary>
/// SEの管理を行うシングルトンクラス
/// </summary>
class SoundManager
{
public:
	~SoundManager();
	/// <summary>
	/// SoundManager使用者はGetInstance()を通した参照からしか利用できない
	/// </summary>
	/// <returns></returns>
	static SoundManager& GetInstance()
	{
		// 唯一の実態
		static SoundManager instance;

		// それの参照を返す
		return instance;
	}

	// BGMの変更
	void SetBGM(const std::string& name);

	// BGMの更新
	void UpdateBGM();

	/// <summary>
	/// 指定のサウンドを鳴らす
	/// </summary>
	/// <param name="name">サウンド名</param>
	void PlaySE(SoundType sound);

	/// <summary>
	/// SEのボリュームを設定する
	/// </summary>
	/// <param name="volume"></param>
	void SetSEVolume(int volume);
	int GetSEVolume() const;

	/// <summary>
	/// BGMのボリュームを設定する
	/// </summary>
	/// <param name="volume"></param>
	void SetBGMVolume(int volume);
	int GetBGMVolume() const;

	/// <summary>
	/// BGMの現在の鳴らす音量の割合
	/// </summary>
	/// <param name="rate">音量の割合(一時的なもの0.0〜1.0)</param>
	void SetBGMRate(float rate);

	// サウンド情報をセーブ
	void SaveSoundConfig();
private:
	// サウンドデータ
	struct SoundData
	{
		SoundData(int h, SoundType t):
			soundHandle(h),
			soundType(t)
		{}

		int soundHandle = -1;
		SoundType soundType;
	};
	
	// 変更したサウンド情報をファイルに書き込む
	struct SoundConfigInfo
	{
		char signature[5];			// "SND_"
		float version;				// 1.0
		unsigned short volumeSE;	// 0〜255	
		unsigned short volumeBGM;	// 0〜255
	};

	// 効果音と音楽の音量
	int m_volumeSE = 100;
	int m_volumeBGM = 40;

	// シングルトンパターンなのでコンストラクタはprivateに置く
	SoundManager();
	// コピーも代入も禁止する
	SoundManager(const SoundManager&) = delete;			// コピーコンストラクタ
	void operator = (const SoundManager&) = delete;		// 代入も禁止

	// 選択したサウンドタイプのハンドルを返す
	int GetCurrentSoundHandle(SoundType sound);

	// 音データ読込
	void LoadData();

	// 音の設定を読込
	void LoadSoundConfig();

private:
	// 音データ
	std::vector<SoundData> m_soundData;

	// ミュージックデータハンドル
	std::map<std::string,int> m_hMusic;
	// 現在再生中の音楽ハンドル
	int m_hCurrentMusic;
};