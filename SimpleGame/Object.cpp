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
}

void Object::Render()
{
	m_Renderer->DrawSolidRect(m_posX, m_posY, 0, 40, 1, 0, 1, 1);
}

void Object::InitializeRenderer()
{
	m_Renderer = new Renderer(500, 500);
	if (!m_Renderer->IsInitialized())
	{
		std::cout << "Renderer could not be initialized.. \n";
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
