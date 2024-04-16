#pragma once
#include <vector>
#include "Subject.h"

class SceneMain;

struct SubjectData;

class SubjectManager
{
public:
	// �R���X�g���N�^
	SubjectManager();
	// �f�X�g���N�^
	virtual ~SubjectManager();

	// �V�[�����C���̃|�C���^�Z�b�g
	void SetMain(SceneMain* main) { m_pMain = main; }

	// �`��
	void Draw();
	// �v�f�̕ύX
	void OnSubChange();
	// ���̐悪�I�����ꂽ�Ƃ�
	void OnChino();
	// ���̐悶��Ȃ����I�����ꂽ�Ƃ�
	void OnNotChino();
	// �������I�����ꂽ�Ƃ�
	void OnSought();

	// �S�v�f�����擾
	int GetSubjectNum();
	// �v�f��ނ��擾
	SubjectType GetSubjectType() { return m_currentSubjectData->subType; }
private:
	// �S�Ă̗v�f�̓ǂݍ���
	void LoadAllSubject();
	// �����_���ŗv�f���擾
	SubjectData* GetRandSubject();
	// �S�Ă̗v�f�̏�ԃ��Z�b�g
	void AllSubjectReset();

private:
	// ���݂̗v�f�f�[�^
	SubjectData* m_currentSubjectData;
	// �S�Ă̗v�f�f�[�^
	std::vector<SubjectData> m_subjects;

private:
	// �V�[�����C���̃|�C���^
	SceneMain* m_pMain;
};
