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
#define COLLIDE_COLOR	1.0f , 0.0f, 1.0f, 1.0f
void Object::Render()
{
#ifdef COLLIDE_CHECK_RED
	if (!m_SceneRender) {		// NOT USED
		if (!m_collide)
			m_Renderer->DrawSolidRect(m_posX, m_posY, 0, m_size, m_R, m_G, m_B, m_A,RENDERLEVEL(m_RenderLevel));
		else
			m_Renderer->DrawSolidRect(m_posX, m_posY, 0, m_size, m_R, 0, 0, m_A, RENDERLEVEL(m_RenderLevel));
	}
	else
	{
		if(m_haveTex)
		{
			if (m_haveSprite)
			{
				m_SceneRender->DrawTexturedRectSeq(m_posX, m_posY, 0, m_size, m_R, m_G, m_B, 1, m_TextureID,
					curSpriteX,curSpriteY,totalSpriteX,totalSpriteY,RENDERLEVEL(m_RenderLevel));
			}
			else if (m_isParticle) {
				m_SceneRender->DrawParticle(m_posX, m_posY, 0, m_size*0.8,
					m_R, m_G, m_B, 1, -m_vecX, -m_vecY, m_TextureID, m_accumulateTime,RENDERLEVEL(LEVEL_SKY));
			}
			else {
				m_SceneRender->DrawTexturedRect(m_posX, m_posY, 0, m_size, 1, 1, 1, 1, m_TextureID, RENDERLEVEL(m_RenderLevel));
			}
		}
		else {
			if (!m_collide)
				m_SceneRender->DrawSolidRect(m_posX, m_posY, 0, m_size, m_R, m_G, m_B, m_A, RENDERLEVEL(m_RenderLevel));
			else
				m_SceneRender->DrawSolidRect(m_posX, m_posY, 0, m_size, 1 - m_R, 1 - m_G, 1 - m_B, m_A, RENDERLEVEL(m_RenderLevel));
		}
		if (f_lifeGague)
			m_SceneRender->DrawSolidRectGauge(m_posX, m_posY + m_size / 2 + 2 * LIFE_GAGUE_HEIGHT, 0,
				m_size, LIFE_GAGUE_HEIGHT, m_R, m_G, m_B, m_A, (float)(m_life / m_maxlife), RENDERLEVEL(LEVEL_SKY));
	}
#else
	if (!m_SceneRender) {
		m_Renderer->DrawSolidRect(m_posX, m_posY, 0, m_size, m_R, m_G, m_B, m_A, RENDERLEVEL(m_RenderLevel));
	}
	else {
		m_SceneRender->DrawSolidRect(m_posX, m_posY, 0, m_size, m_R, m_G, m_B, m_A, RENDERLEVEL(m_RenderLevel));
	}
#endif
}
//#define RANDOM_SIZE

void Object::Initialize(ObjectType type, Renderer * SceneRender, int team)
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
		m_collide = false;
		m_id = 0;
		m_RenderLevel = LEVEL_SKY;
		f_lifeGague = true;
		break;
	case ObjectType::OBJECT_CHARACTER:
		m_size = 50;
		m_life = 100;
		m_speed = 100;
		m_haveSprite = true;
		m_haveTex = true;
		totalSpriteX = 1;
		totalSpriteY = 11;
		if (m_team == TEAM_1) {
			m_R = 1.0f;
			m_G = 0.2f;
			m_B = 0.2f;
		}
		else if (m_team == TEAM_2) {
			m_R = 0.2f;
			m_G = 0.2f;
			m_B = 1.0f;
		}
		m_RenderLevel = LEVEL_GROUND;
		m_vecX = (rand() % 200 - 100)*0.01;
		m_vecY = (rand() % 200 - 100)*0.01;
		norm = sqrt(m_vecX*m_vecX + m_vecY*m_vecY);
		if (IsZero(norm))norm = 1;
		m_vecX /= norm;
		m_vecY /= norm;
		m_collide = false;
		m_id = 0;
		f_lifeGague = true;
		break;
	case ObjectType::OBJECT_BULLET:
		m_size = 4;
		m_life = 15;
		m_speed = 150;
		m_haveTex = true;
		m_isParticle = true;

		if (m_team == TEAM_1) {
			m_R = 1.0f;
			m_G = 0.3f;
			m_B = 0.3f;
		}
		else if (m_team == TEAM_2) {
			m_R = 0.3f;
			m_G = 0.3f;
			m_B = 1.0f;
		}
		m_RenderLevel = LEVEL_UNDERGROUND;
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
		m_size = 4;
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
		m_RenderLevel = LEVEL_UNDERGROUND;
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

	m_maxlife = m_life;
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
	m_accumulateTime += ElapsedTime;
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
	float fhalfSize = m_size / 2;

	if (m_posX  > HALFWIDTH-fhalfSize) {
		m_posX = HALFWIDTH-fhalfSize;
		if (m_type == ObjectType::OBJECT_ARROW || m_type == ObjectType::OBJECT_BULLET)
			m_life = 0;
		m_vecX = -m_vecX;
	}
	if (m_posX  < -HALFWIDTH+fhalfSize) {
		m_posX = -HALFWIDTH+fhalfSize;
		if (m_type == ObjectType::OBJECT_ARROW || m_type == ObjectType::OBJECT_BULLET)
			m_life = 0;
		m_vecX = -m_vecX;
	}
	if (m_posY- fhalfSize > HALFHEIGHT-fhalfSize) {
		m_posY = HALFHEIGHT-fhalfSize;
		if (m_type == ObjectType::OBJECT_ARROW || m_type == ObjectType::OBJECT_BULLET)
			m_life = 0;
		m_vecY = -m_vecY;
	}
	if (m_posY + fhalfSize< -HALFHEIGHT+fhalfSize) {
		m_posY = -HALFHEIGHT+fhalfSize;
		if (m_type == ObjectType::OBJECT_ARROW || m_type == ObjectType::OBJECT_BULLET)
			m_life = 0;
		m_vecY = -m_vecY;
	}

	if (m_haveSprite) {
		curSpriteX += ElapsedTime*10;
		curSpriteY += ElapsedTime*10;

		if ((int)curSpriteX > totalSpriteX)curSpriteX = 0;
		if ((int)curSpriteY > totalSpriteY)curSpriteY = 0;
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
