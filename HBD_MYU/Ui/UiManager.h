#pragma once
#include "Game.h"
#include <memory>
#include <vector>
#include "Players.h"

class SceneMain;
class UiPointBase;
class UiGetPoint;
class UiHpBar;
class UiStatus;
class Player;
class GameScore;

class UiManager
{
public:
	// �R���X�g���N�^
	UiManager();
	// �f�X�g���N�^
	virtual ~UiManager();

	void SetPlayer(Player* player) { m_Player = player; }
	void SetScore(GameScore* score) { m_Score = score; }

	// ������
	void Init();
	// �X�V
	void Update();
	// �`��
	void Draw();
	// �s�v��UI�폜����
	void DeleteUI();
	// �������̏���
	void OnBoost(BoostLevel type);
	// �|�C���g�l�����̏���
	void OnPointGet();
	// �|�C���g�r�����̏���
	void OnPointLost();
private:
	// ���UI�̐���
	void CreateUI();
	// �f�[�^�̃��[�h
	void LoadData();
	// �\��������̓���
	void UIinfoUpdate();
	// ���݂̃��x������Ή�����摜�n���h���̎擾
	int GetHandle(BoostLevel type);

private:
	// �摜�n���h��
	int m_hUltraImg;
	int m_hSuperImg;
	int m_hHyperImg;

private:
	// �u�[�X�g���Ƀ��x�����ꎞ�I�ɕ`�悷��
	//todo �u�[�X�gUI�폜
	
	// �l�������|�C���g���ꎞ�I�ɕ`�悷��
	UiPointBase* m_PointUI;
	// ���Ui
	UiHpBar* m_HpBar;
	UiStatus* m_StatusUI;

	// �v���C���[
	Player* m_Player;
	// �Q�[���X�R�A
	GameScore* m_Score;
};

