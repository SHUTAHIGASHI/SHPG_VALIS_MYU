#pragma once
#include <memory>
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

	// �ҋ@��Ԃɖ߂�
	void OnIdle();
	// �a��������
	void OnGiveFood();
	// �V��ł�����
	void OnPlay();
	// �Q��
	void OnSleep();
	// �O�o
	void OnOuting();
	// �L�����N�^�[�X�e�[�^�X�擾
	const state GetCharaStatus() const;

private:
	// ���ڑI�����̏���
	void OnSelectItem(int index);
	// �����_���ŃL��������I��
	void SetRandomCharaName();

	// �����o�֐��|�C���^(�X�V)
	using m_tUpdateFunc = void (Action::*) ();
	m_tUpdateFunc m_updateFunc = nullptr;
	// ��Ԃ��Ƃ̍X�V
	void UpdateIdle();
	void UpdateEat();
	void UpdateSleep();
	void UpdatePlay();
	void UpdateOuting();

private:
	// ���o�������̃L������
	std::vector<std::string> m_outingCharaName;
	// ���o�������ԃJ�E���g
	int m_outingTimeCount;

private:
	// �L�����N�^�[
	std::shared_ptr<class Myu> m_pMyu;
	// �A�C�e��
	std::shared_ptr<class ItemManager> m_pItem;
	// �I�����j���[
	std::shared_ptr<class SelectMenu> m_pSelectMenu;
	// UI����
	class UiManager* m_pUi;
};

