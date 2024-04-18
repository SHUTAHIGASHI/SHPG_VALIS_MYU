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
	// �O�o
	void OnOuting();

	// �L�����N�^�[��Ԏ擾
	actionState GetMyuState() const;

private:
	// ���ڑI�����̏���
	void OnSelectItem(int index);

private:
	// ���o�������̃L������
	std::vector<std::string> m_outingCharaName;

private:
	// �L�����N�^�[
	std::shared_ptr<class Myu> m_pMyu;
	// �A�C�e��
	std::shared_ptr<class ItemManager> m_pItem;
	// �I�����j���[
	std::shared_ptr<class SelectMenu> m_pSelectMenu;
};

