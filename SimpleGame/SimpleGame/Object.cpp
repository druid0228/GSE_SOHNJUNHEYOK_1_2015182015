#include "stdafx.h"
#include "Object.h"
#include"Renderer.h"

Object::Object()
{
	m_posX = 0;
	m_posY = 0;
	m_hp = 0;
	m_vecX = m_vecY =0;
	m_speed = 1;
	m_size = 40;
	m_R  = m_B = m_A = 1;
	m_G = 0;
	m_collide = false;
}

void Object::Render()
{
	if (!m_SceneRender) {
		if (!m_collide)
			m_Renderer->DrawSolidRect(m_posX, m_posY, 0, m_size, m_R, m_G, m_B, m_A);
		else
			m_Renderer->DrawSolidRect(m_posX, m_posY, 0, m_size, m_R, 0, 0, m_A);
	}
	else
	{
		if (!m_collide)
			m_SceneRender->DrawSolidRect(m_posX, m_posY, 0, m_size, m_R, m_G, m_B, m_A);
		else
			m_SceneRender->DrawSolidRect(m_posX, m_posY, 0, m_size, m_R, 0, 0, m_A);
	}
}

void Object::InitializeRand(Renderer *Render)
{
	m_posX = rand() % 500 - 250;
	m_posY = rand() % 500 - 250;
	m_vecX = (rand() % 200 - 100)*0.01;
	m_vecY = (rand() % 200 - 100)*0.01;
	m_speed = rand() % 3+1;
	m_R = m_G = m_B = m_A = 1;
	m_size = rand() % 50 + 10;
	m_collide = false;
	m_SceneRender = Render;
	InitializeRenderer();
}

void Object::InitializeRenderer()
{
	if (!m_SceneRender) {
		m_Renderer = new Renderer(500, 500);
		if (!m_Renderer->IsInitialized())
		{
			std::cout << "Renderer could not be initialized.. \n";
		}
	}
}

void Object::Update()
{
	MouseInputProcess();
	KeyInputProcess();
	SpecialKeyInputProcess();
	Animate();
	Render();
}

void Object::Animate()
{
	if (!IsZero(m_vecX))m_posX += m_vecX*m_speed;
	if (!IsZero(m_vecY))m_posY += m_vecY*m_speed;
	if (m_posX > 250) {
		m_posX = 250;
		m_vecX = -m_vecX;
	}
	if (m_posX < -250) {
		m_posX = -250;
		m_vecX = -m_vecX;
	}
	if (m_posY > 250) {
		m_posY = 250;
		m_vecY = -m_vecY;
	}
	if (m_posY < -250) {
		m_posY = -250;
		m_vecY = -m_vecY;
	}
}

void Object::Idle()
{
}

void Object::MouseInputProcess()
{
}

void Object::KeyInputProcess()
{
}

void Object::SpecialKeyInputProcess()
{
}


Object::~Object()
{
	delete m_Renderer;
}
