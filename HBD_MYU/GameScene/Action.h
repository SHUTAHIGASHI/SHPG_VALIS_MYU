#pragma once
#include <list>
#include <memory>
#include <map>
#include "Myu.h"

class Action
{
public:
	// �R���X�g���N�^
	Action();
	// �f�X�g���N�^
	~Action();

	// UI����̃|�C���^���Z�b�g
	void SetUiManager(class UiManager* ui) { m_pUi = ui; }

	// ������
	void Init();
	// �X�V
	void Update(const InputState& input);
	// �`��
	void Draw();

	// �L�����N�^�[�X�e�[�^�X�擾
	const charaState GetCharaStatus() const;

private:
	// �ҋ@��Ԃɖ߂�
	void OnIdle();
	// �a��������
	void OnGiveFood();
	// �Q��
	void OnSleep();
	// ���b�X���ɍs��
	void OnLesson();
	// �O�o
	void OnOuting();
	// �Z�[�u
	void OnSave();

	// ���ڑI�����̏���
	void OnSelectItem(int index);
	// �����_���ŃL��������I��
	void SetRandomCharaName();
	// �J�[�\���͈͓̔��`�F�b�N
	bool CheckCursorRange();

	// �����o�֐��|�C���^(�X�V)
	using m_tUpdateFunc = void (Action::*) (const InputState& input);
	m_tUpdateFunc m_updateFunc = nullptr;
	// ��Ԃ��Ƃ̍X�V
	void UpdateIdle(const InputState& input);
	void UpdateActioning(const InputState& input);

	// �e�s�����̏����Ǘ��}�b�v
	using m_tSelectFunc = void (Action::*) ();
	std::map<std::string, m_tSelectFunc> m_selectFuncMap;

private:
	// ���o�������̃L������
	std::list<std::string> m_outingCharaName;
	// �J�[�\�����W
	float m_cursorPosX;
	float m_cursorPosY;

private:
	// �L�����N�^�[
	std::shared_ptr<class Myu> m_pMyu;
	// �I�����j���[
	std::shared_ptr<class SelectMenuBase> m_pSelectMenu;
	// UI����
	class UiManager* m_pUi;
};
