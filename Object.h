#pragma once
#include<iostream>
class Renderer;

class Object
{
public:
	double m_posX,m_posY;
	double m_hp;
	Renderer *m_Renderer = NULL;
public:
	Object();
	virtual void Render();

	virtual void Updata();
	virtual void Animate();
	virtual void Idle();
	virtual void MouseInputProcess();
	virtual void KeyInputProcess();
	virtual void SpecialKeyInputProcess();

	virtual ~Object();
};

