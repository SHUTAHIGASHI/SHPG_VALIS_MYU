#pragma once
#include "Game.h"
#include "Myu.h"

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
	void SetImage(int handle);
	// キャラクターの位置をセット
	void SetPos(float x, float y);
	// キャラクターのサイズをセット
	void SetSize(float size);
	// キャラクターの角度をセット
	void SetAngle(float angle);
	// キャラクターの感情をセット
	void SetEmotion(emotionState emotion);

private:
	// 描画画像
	int m_hImage;
	// 画像サイズ
	int m_imageSizeX;
	int m_imageSizeY;
	// 描画位置
	VECTOR m_pos;
	// 描画サイズ
	float m_size;
	// 描画角度
	float m_angle;
	// キャラクターの感情
	emotionState m_emotion;
};

