#include "Game.h"
#include "SceneManager.h"
#include "SceneTitle.h"
#include "SceneDebug.h"
#include "Load.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// �E�B���h�E�I�����Ă��Ȃ��Ă����s
	SetAlwaysRunFlag(true);
	// ���O������
	SetOutApplicationLogValidFlag(false);
	// �E�B���h�E���[�h�ݒ�
	ChangeWindowMode(Game::kWindowMode);
	// �E�B���h�E���[�h�̃T�C�Y�ύX
	SetWindowSizeChangeEnableFlag(true);
	// �E�B���h�E���ݒ�
	SetMainWindowText(Game::kTitleText);
	// ��ʃT�C�Y�̐ݒ�
	SetGraphMode(Game::kScreenWidth, Game::kScreenHeight, Game::kColorDepth);
	// �_�u���o�b�t�@���[�h
	SetDrawScreen(DX_SCREEN_BACK);

	if (DxLib_Init() == -1)		// �c�w���C�u��������������
	{
		return -1;			// �G���[���N�����璼���ɏI��
	}

	// ���\�[�X�̓ǂݍ���
	LPCSTR font = Game::kFontFileName;	// �ǂݍ��ރt�H���g�t�@�C���̃p�X
	if (AddFontResourceEx(font, FR_PRIVATE, NULL) > 0) {
	}
	else {
		// �t�H���g�ǂݍ��݃G���[����
		MessageBox(NULL, "�t�H���g�ǂݍ��ݎ��s", "", MB_OK);
	}
	// �W���t�H���g�ݒ�
	ChangeFont(Game::kFontName);
	SetFontSize(Game::kFontSize);

	// �J�[�\���摜�ǂݍ���
	int hCursorImg = LoadGraph("Data/ImageData/Chalk.png");
	// �Q�[�����̃}�E�X�|�C���^�`��ݒ�
	SetMouseDispFlag(false);
	// �}�E�X�J�[�\���ʒu�ݒ�
	SetMousePoint(Game::kScreenWidthHalf, Game::kScreenHeightHalf);

	// �T�E���h�}�l�[�W���[�錾
	auto& soundManager = SoundManager::GetInstance();
	// �Q�[���}�l�[�W���[�錾
	auto& gameManager = GameDataManager::GetInstance();
	// �L�[���͏�ԃN���X�錾
	InputState input;
	// �V�[���}�l�[�W���[�錾
	SceneManager scene;

	//���[�h
	Load::GetInstance().AllLoadData();

#ifdef _DEBUG
	scene.ChangeScene(new SceneDebug(scene));
#else
	scene.ChangeScene(new SceneTitleMenu(scene));
#endif

	while (ProcessMessage() == 0)
	{
		LONGLONG time = GetNowHiPerformanceCount();
		// ���y�Đ��J�n
		if (SoundManager::GetInstance().IsPlayingMusic() != 1)
		{
			SoundManager::GetInstance().PlayMusic();
		}

		// ��ʂ̃N���A
		ClearDrawScreen();

		// ���͏�ԍX�V
		input.Update();

		// ���݂̃V�[���̍X�V
		scene.Update(input);

		// ���݂̃V�[���̕`��
		scene.Draw();

		// �}�E�X�J�[�\���`��
		DrawRotaGraph(input.GetMousePosX() + 12, input.GetMousePosY() + 12, 0.2, 0.0, hCursorImg, true, false, true);

		// ����ʂ�\��ʂƓ���ւ���
		ScreenFlip();

#ifdef _DEBUG
		// esc�L�[����������I������
		if (CheckHitKey(KEY_INPUT_L)) scene.ChangeScene(new SceneDebug(scene));
#endif

		if (scene.IsGameEnd()) break;

		while (GetNowHiPerformanceCount() - time < 16667)
		{

		}
	}
	// �J�[�\���摜�폜
	DeleteGraph(hCursorImg);
	// �}�E�X�J�[�\���`��
	SetMouseDispFlag(true);

	//�f�[�^�폜
	Load::GetInstance().DeleteAllData();

	DxLib_End();				// �c�w���C�u�����g�p�̏I������

	return 0;				// �\�t�g�̏I�� 
}