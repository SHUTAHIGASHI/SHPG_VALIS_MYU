#pragma once

// �w�i�̕`��N���X
class MapDraw
{
public:
	// �R���X�g���N�^
	MapDraw();
	// �f�X�g���N�^
	~MapDraw();

	// ������
	void Init();
	// �X�V
	void Update();
	// �`��
	void Draw();

private:
	// �w�i�摜
	int m_bgImage;
};

