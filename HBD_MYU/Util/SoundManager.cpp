#include "SoundManager.h"
#include "Game.h"
#include <cassert>

namespace
{
	constexpr char sound_file_signature[] = "SND_";
	constexpr char sound_config_file_path[] = "./sound.conf";
	constexpr float sound_config_version = 1.0f;
}

void SoundManager::LoadSoundConfig()
{
	SoundConfigInfo conf = {};
	FILE* fp = nullptr;
	fopen_s(&fp, sound_config_file_path, "rb");
	if (fp)
	{
		fread(&conf, sizeof(conf), 1, fp);
		fclose(fp);
		m_volumeBGM = conf.volumeBGM;
		m_volumeSE = conf.volumeSE;
	}
}

void SoundManager::SaveSoundConfig()
{
	SoundConfigInfo conf = {};
	memcpy_s(conf.signature, sizeof(conf.signature), sound_file_signature, sizeof(sound_file_signature));

	conf.version = sound_config_version;
	conf.volumeSE = m_volumeSE;
	conf.volumeBGM = m_volumeBGM;

	FILE* fp = nullptr;
	fopen_s(&fp, sound_config_file_path, "wb");
	if (fp)
	{
		fwrite(&conf, sizeof(conf), 1, fp);
		fclose(fp);
	}
}

SoundManager::~SoundManager()
{
	SaveSoundConfig();

	// ���ʉ��f�[�^
	for (auto& soundData : m_soundData)
	{
		DeleteSoundMem(soundData.soundHandle);
	}
	m_soundData.clear();

	// �ȃf�[�^
	DeleteSoundMem(m_hCurrentMusic);
}

void SoundManager::SetBGM(const std::string& name)
{
	// ���łɍĐ����̋Ȃ�����Β�~
	if (m_hCurrentMusic != -1)
	{
		StopSoundMem(m_hCurrentMusic);
	}

	// �Ȃ�ύX
	m_hCurrentMusic = m_hMusic[name];

	// ���ʂ�ݒ�
	int volumePal = (255 / 100) * m_volumeBGM;
	ChangeVolumeSoundMem(volumePal, m_hCurrentMusic);
}

void SoundManager::UpdateBGM()
{
	if (CheckSoundMem(m_hCurrentMusic) == 0)
	{
		int volumePal = (255 / 100) * m_volumeBGM;
		ChangeVolumeSoundMem(volumePal, m_hCurrentMusic);
		PlaySoundMem(m_hCurrentMusic, DX_PLAYTYPE_BACK);
	}
}

void SoundManager::PlaySE(SoundType sound)
{
	int volumePal = (255 / 100) * m_volumeSE;
	ChangeVolumeSoundMem(m_volumeSE, GetCurrentSoundHandle(sound));
	PlaySoundMem(GetCurrentSoundHandle(sound), DX_PLAYTYPE_BACK);
}

void SoundManager::SetSEVolume(int volume)
{
	m_volumeSE = volume;
}

int SoundManager::GetSEVolume() const
{
	return m_volumeSE;
}

void SoundManager::SetBGMVolume(int volume)
{
	m_volumeBGM = volume;
	int volumePal = (255 / 100) * m_volumeBGM;
	ChangeVolumeSoundMem(volumePal, m_hCurrentMusic);
}

int SoundManager::GetBGMVolume() const
{
	return m_volumeBGM;
}

void SoundManager::SetBGMRate(float rate)
{
	assert(0.0f <= rate && rate <= 1.0f);
	ChangeVolumeSoundMem(static_cast<int>(static_cast<float>(m_volumeBGM) * rate), m_hCurrentMusic);
}

SoundManager::SoundManager() :
	m_soundData(),
	m_hMusic(),
	m_hCurrentMusic(-1)
{
	// ���f�[�^�ǂݍ���
	LoadSoundConfig();
	LoadData();

	// BGM�ݒ�
	m_hCurrentMusic = m_hMusic["katsuairon"];
}

int SoundManager::GetCurrentSoundHandle(SoundType sound)
{
	int currentSound = -1;

	for (auto& soundData : m_soundData)
	{
		if (soundData.soundType == sound)
		{
			currentSound = soundData.soundHandle;
			break;
		}
	}

	return currentSound;
}

void SoundManager::LoadData()
{
	// �T�E���h
	m_soundData.push_back(SoundData(LoadSoundMem("Data/SoundData/Select.wav"), SoundType::select));

	// �~���[�W�b�N
	m_hMusic["katsuairon"] = LoadSoundMem("Data/MusicData/Katsuairon.mp3");
	m_hMusic["henitai"] = LoadSoundMem("Data/MusicData/Hen-itai.mp3");
}
