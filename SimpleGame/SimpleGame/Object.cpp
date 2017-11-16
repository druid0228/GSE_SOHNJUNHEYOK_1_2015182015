#include "stdafx.h"
#include "Object.h"
#include"Renderer.h"

Object::Object()
{
	m_posX = 0;
	m_posY = 0;
	m_life = 10;
	m_vecX = m_vecY =0;
	m_speed = 1;
	m_size = 40;
	m_R  = m_B = m_A = 1;
	m_G = 0;
	m_collide = false;
}

#define COLLIDE_CHECK_RED
void Object::Render()
{
#ifdef COLLIDE_CHECK_RED
	if (!m_SceneRender) {
		if (!m_collide)
			m_Renderer->DrawSolidRect(m_posX, m_posY, 0, m_size, m_R, m_G, m_B, m_A);
		else
			m_Renderer->DrawSolidRect(m_posX, m_posY, 0, m_size, m_R, 0, 0, m_A);
	}
	else
	{
		if(m_haveTex)
		{
			m_SceneRender->DrawTexturedRect(m_posX, m_posY, 0, m_size, m_R, m_G, m_B, m_A, m_TextureID);
		}
		else {
			if (!m_collide)
				m_SceneRender->DrawSolidRect(m_posX, m_posY, 0, m_size, m_R, m_G, m_B, m_A);
			else
				m_SceneRender->DrawSolidRect(m_posX, m_posY, 0, m_size, m_R, 0, 0, m_A);
		}
	}
#else
	if (!m_SceneRender) {
		m_Renderer->DrawSolidRect(m_posX, m_posY, 0, m_size, m_R, m_G, m_B, m_A);
	}
	else {
		m_SceneRender->DrawSolidRect(m_posX, m_posY, 0, m_size, m_R, m_G, m_B, m_A);
	}
#endif
}
//#define RANDOM_SIZE

void Object::Initialize(ObjectType type, Renderer * SceneRender,int team)
{
	m_SceneRender = SceneRender;
	m_type = type;
	m_team = team;
	t_Arrow_CoolTime = ARROW_COOL_TIME;
	float norm;
	switch (m_type)
	{
	case ObjectType::OBJECT_BUILDING:
		m_size = 100;
		m_life = 500;
		m_speed = 0;
		m_R = 1.0f;
		m_G = 1.0f;
		m_B = 0.0f;
		m_collide = false;
		m_id = 0;
		break;
	case ObjectType::OBJECT_CHARACTER:
		m_size = 10;
		m_life = 10;
		m_speed = 300;
		if (m_team == TEAM_1)	{
			m_R = 1.0f;
			m_G = 0.0f;
			m_B = 0.0f;
		}
		else if (m_team == TEAM_2){
			m_R = 0.0f;
			m_G = 0.0f;
			m_B = 1.0f;
		}
		m_vecX = (rand() % 200 - 100)*0.01;
		m_vecY = (rand() % 200 - 100)*0.01;
		norm = sqrt(m_vecX*m_vecX + m_vecY*m_vecY);
		if (IsZero(norm))norm = 1;
		m_vecX /= norm;
		m_vecY /= norm;
		m_collide = false;
		m_id = 0;
		break;
	case ObjectType::OBJECT_BULLET:
		m_size = 2;
		m_life = 20;
		m_speed = 600;
		if (m_team == TEAM_1) {
			m_R = 1.0f;
			m_G = 0.0f;
			m_B = 0.0f;
		}
		else if (m_team == TEAM_2) {
			m_R = 0.0f;
			m_G = 0.0f;
			m_B = 1.0f;
		}
		m_vecX = (rand() % 200 - 100)*0.01;
		m_vecY = (rand() % 200 - 100)*0.01;
		norm = sqrt(m_vecX*m_vecX + m_vecY*m_vecY);
		if (IsZero(norm))norm = 1;
		m_vecX /= norm;
		m_vecY /= norm;
		m_collide = false;
		m_id = 0;
		break;
	case ObjectType::OBJECT_ARROW:
		m_size = 2;
		m_life = 10;
		m_speed = 100;
		if (m_team == TEAM_1) {
			m_R = 0.5f;
			m_G = 0.2f;
			m_B = 0.7f;
		}
		else if (m_team == TEAM_2) {
			m_R = 1.0f;
			m_G = 1.0f;
			m_B = 0.0f;
		}
		m_vecX = (rand() % 200 - 100)*0.01;
		m_vecY = (rand() % 200 - 100)*0.01;
		norm = sqrt(m_vecX*m_vecX + m_vecY*m_vecY);
		if (IsZero(norm))norm = 1;
		m_vecX /= norm;
		m_vecY /= norm;
		m_collide = false;
		m_id = 0;
		break;
	}
}

// NOT	USE
void Object::InitializeRand(Renderer *Render)
{
	m_posX = rand() % 500 - 250;
	m_posY = rand() % 500 - 250;
	m_vecX = (rand() % 200 - 100)*0.01;
	m_vecY = (rand() % 200 - 100)*0.01;
	m_speed = rand() % 100+50;
	m_R = m_G = m_B = m_A = 1;
#ifdef RANDOM_SIZE
	m_size = rand() % 50 + 10;
#else
	m_size = 40;
#endif 
	m_life = 10;
	m_collide = false;
	m_SceneRender = Render;
	m_lifeTime = 10;
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

void Object::Update(double ElapsedTime)
{
	m_lifeTime -= ElapsedTime;
	if(m_type==ObjectType::OBJECT_CHARACTER)
		t_Arrow_CoolTime += ElapsedTime;
	if (m_type == ObjectType::OBJECT_BUILDING)
		t_Bullet_CoolTime += ElapsedTime;
	MouseInputProcess();
	KeyInputProcess();
	SpecialKeyInputProcess();
	Animate(ElapsedTime);
	Render();
}

void Object::Animate(double ElapsedTime)
{
	if (!IsZero(m_vecX))m_posX += m_vecX*m_speed*ElapsedTime;
	if (!IsZero(m_vecY))m_posY += m_vecY*m_speed*ElapsedTime;
	if (m_posX > HALFWIDTH) {
		m_posX = HALFWIDTH;
		m_vecX = -m_vecX;
	}
	if (m_posX < -HALFWIDTH) {
		m_posX = -HALFWIDTH;
		m_vecX = -m_vecX;
	}
	if (m_posY > HALFHEIGHT) {
		m_posY = HALFHEIGHT;
		m_vecY = -m_vecY;
	}
	if (m_posY < -HALFHEIGHT) {
		m_posY = -HALFHEIGHT;
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
{}
Object::~Object()
{
	if(m_Renderer)delete m_Renderer;
}
