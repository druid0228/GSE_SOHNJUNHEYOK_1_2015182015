#include "stdafx.h"
#include "Object.h"
#include"Renderer.h"

Object::Object()
{
	m_posX = 0;
	m_posY = 0;
	m_hp = 0;
	m_Renderer = new Renderer(500, 500);
	if (!m_Renderer->IsInitialized())
	{
		std::cout << "Renderer could not be initialized.. \n";
	}
}

void Object::Render()
{
	m_Renderer->DrawSolidRect(m_posX, m_posY, 0, 4, 1, 0, 1, 1);
}

void Object::Updata()
{
	MouseInputProcess();
	KeyInputProcess();
	SpecialKeyInputProcess();
	Animate();

}

void Object::Animate()
{
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
