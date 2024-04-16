#pragma once
#include "Game.h"

enum class ObjectType
{
	Spike,
	Booster
};

enum class LaneType
{
	Lower,
	Upper,
	Right,
	Left,
	UpperRight,
	UpperLeft,
	LowerRight,
	LowerLeft,
	End = LowerLeft
};

namespace LanePos
{
	// �e�|�W�V����
	//��
	constexpr float LowerX = 0.0f;
	constexpr float LowerY = -500.0f;

	//��
	constexpr float UpperX = 0.0f;
	constexpr float UpperY = 500.0f;

	//�E
	constexpr float RightX = 500.0f;
	constexpr float RightY = 0.0f;

	//��
	constexpr float LeftX = -500.0f;
	constexpr float LeftY = 0.0f;

	//�E��
	constexpr float UpperRightX = 500.0f;
	constexpr float UpperRightY = -500.0f;

	//����
	constexpr float UpperLeftX = -500.0f;
	constexpr float UpperLeftY = -500.0f;

	//�E��
	constexpr float LowerRightX = 500.0f;
	constexpr float LowerRightY = 500.0f;

	//����
	constexpr float LowerLeftX = -500.0f;
	constexpr float LowerLeftY = 500.0f;
}

struct Object
{
	ObjectType type;
	int handle;
	LaneType laneType;

	Object(ObjectType tType, int tHandle, LaneType tLaneType):
		type(tType),
		handle(tHandle),
		laneType(tLaneType)
	{
	}
	virtual ~Object()
	{
	}
};