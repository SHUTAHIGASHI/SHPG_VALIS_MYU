#pragma once
#include "Game.h"

// キャラクターの感情の種類
enum class CharaEmotion
{
	Normal,
	Happy,
	Sad,
	Angry,
	Max
};

class CharaDraw
{
public:
	// コンストラクタ
	CharaDraw();
	// デストラクタ
	~CharaDraw();
	// 描画
	void Draw();

	// キャラクターの画像をセット
	void SetImage(const char* fileName);
	// キャラクターの位置をセット
	void SetPos(float x, float y);
	// キャラクターのサイズをセット
	void SetSize(float size);
	// キャラクターの角度をセット
	void SetAngle(float angle);
	// キャラクターの感情をセット
	void SetEmotion(CharaEmotion emotion);

private:
	// 描画画像
	int m_hImage;
	// 描画位置
	VECTOR m_pos;
	// 描画サイズ
	float m_size;
	// 描画角度
	float m_angle;
	// キャラクターの感情
	CharaEmotion m_emotion;
};

