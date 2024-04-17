#pragma once
#include <memory>
#include "Myu.h"

class ActionMenu
{
public:
	// �R���X�g���N�^
	ActionMenu();
	// �f�X�g���N�^
	~ActionMenu();

	// ������
	void Init();
	// �X�V
	void Update(const InputState& input);
	// �`��
	void Draw();

	// �a��������
	void OnGiveFood();
	// �V��ł�����
	void OnPlay();
	// �Q��
	void OnSleep();

	// �L�����N�^�[��Ԏ擾
	actionState GetMyuState() const;

private:
	// ���ڑI�����̏���
	void OnSelectItem(int index);

private:
	// �L�����N�^�[
	std::shared_ptr<class Myu> m_pMyu;
	// �I�����j���[
	std::shared_ptr<class SelectMenu> m_pSelectMenu;
};

