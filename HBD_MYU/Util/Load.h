#pragma once
#include <unordered_map>
#include <string>
#include "Subject.h"

class Load
{
public:
	~Load();
	/// <summary>
	/// SoundManager�g�p�҂�GetInstance()��ʂ����Q�Ƃ��炵�����p�ł��Ȃ�
	/// </summary>
	/// <returns></returns>
	static Load& GetInstance()
	{
		// �B��̎���
		static Load instance;

		// ����̎Q�Ƃ�Ԃ�
		return instance;
	}

	/// <summary>
	/// �S�Ẵf�[�^�����[�h����
	/// </summary>
	void AllLoadData();

	/// <summary>
	/// �S�Ẵf�[�^���폜����
	/// </summary>
	void AllDeleteData();
	
	/// <summary>
	/// �n���h�����擾����
	/// </summary>
	/// <param name="key">���[�h�f�[�^�̃L�[</param>
	/// <returns>�n���h��</returns>
	int GetHandle(std::string key)
	{
		return m_data[key];
	}

	// �v�f�f�[�^�S�Ď擾
	std::vector<SubjectData> GetAllData()
	{
		return m_subjects;
	}
private:
	//���[�h�f�[�^��unordered_map�ŊǗ�
	std::unordered_map<std::string, int> m_data;

	std::vector<SubjectData> m_subjects;

	// �V���O���g���p�^�[���Ȃ̂ŃR���X�g���N�^��private�ɒu��
	Load() {};

	// �R�s�[��������֎~����
	Load(const Load&) = delete;			// �R�s�[�R���X�g���N�^
	void operator = (const Load&) = delete;		// ������֎~
};

