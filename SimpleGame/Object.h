#pragma once
#include<iostream>
#include<math.h>
class Renderer;

//	need e 
inline bool IsZero(double n) { return abs(n)<FLT_EPSILON; }

class Object
{
public:
	double m_posX, m_posY;
	double m_vecX, m_vecY;
	double m_speed;

	double m_hp;
	Renderer *m_Renderer = NULL;
public:
	void SetPosition(double x, double y) { m_posX = x; m_posY = y; }
	void SetVector(double x, double y) { m_vecX = x; m_vecY = y; }
	void PlusVector(double x, double y)
	{
		m_vecX += x;
		m_vecY += y;
		double norm = sqrt(m_vecX*m_vecX + m_vecY*m_vecY);
		if (norm <= 0)norm = 1;
		m_vecX = m_vecX / norm;
		m_vecY = m_vecY / norm;
		if (abs(m_vecX)<0.1)m_vecX = 0;
		if (abs(m_vecY)<0.1)m_vecY = 0;
	}

public:
	Object();
	virtual void Render();

	virtual void InitializeRenderer();
	virtual void Update();
	virtual void Animate();
	virtual void Idle();
	virtual void MouseInputProcess();
	virtual void KeyInputProcess();
	virtual void SpecialKeyInputProcess();
	
	virtual ~Object();
};

