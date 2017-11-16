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



enum class ObjectType {
	OBJECT_BUILDING,
	OBJECT_CHARACTER,
	OBJECT_BULLET,
	OBJECT_ARROW,
};

enum {
	TEAM_1,TEAM_2,TEAM_COUNT
};

//	need e 
#include<math.h>
#include<iostream>
inline bool IsZero(double n) { return abs(n)<FLT_EPSILON; }

#define CLEARCOLORBLACK	0.0f, 0.0f, 0.0f, 1.0f
#define CLEARCOLOR	0.0f, 0.3f, 0.3f, 1.0f
#define CLIENTWIDTH 500
#define HALFWIDTH	(CLIENTWIDTH/2)
#define CLIENTHEIGHT	800
#define HALFHEIGHT	 (CLIENTHEIGHT/2)

#define MAX_OBJECTS_COUNT		500
#define MAX_CHARACTER_COUNT	10
#define MAX_BULLET_COUNT			50
#define MAX_ARROW_COUNT			30

#define ARROW_COOL_TIME			3.0f
#define BULLET_COOL_TIME			10.0f

#define CHAR1_COOL_TIME			3.0f
#define CHAR2_COOL_TIME			7.0f

#include<Windows.h>



