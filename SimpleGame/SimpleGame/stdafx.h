#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>
#include<time.h>

struct collideRect
{
	float posX, posY;
	float size;
	collideRect() :posX(0),posY(0),size(0){}
	collideRect(float x, float y, float s) :
		posX(x), posY(y), size(s) {}
	inline bool Check(const collideRect& other)
	{
		float half = size / 2;
		float othalf = other.size / 2;
		if (posX - half > other.posX + othalf)return false;
		if (posX + half < other.posX - othalf)return false;
		if (posY - half > other.posY + othalf)return false;
		if (posY + half < other.posY - othalf)return false;
		return true;
	}
};

#define CLEARCOLORBLACK	0.0f, 0.0f, 0.0f, 1.0f
#define CLEARCOLOR	0.0f, 0.3f, 0.3f, 1.0f

#include<Windows.h>