#include "stdafx.h"
#include"Object.h"
#include "SceneMgr.h"
#include"Renderer.h"

SceneMgr::SceneMgr()
{
}


SceneMgr::~SceneMgr()
{
}

void SceneMgr::Initalize()
{
	m_objectsRenderer = new Renderer(500, 500);
	srand(time(NULL));
	if (!m_objectsRenderer->IsInitialized())
	{
		std::cout << "Renderer could not be initialized.. \n";
	}
	InitializeObjects();
	TimeInit();
}

void SceneMgr::InitializeObjects()
{
	for (int i = 0; i < MAX_OBJECTS_COUNT; ++i)
	{
		m_objects[i] = new Object;
		m_objects[i]->InitializeRand(m_objectsRenderer);
		++m_objectCnt;
	}
}

void SceneMgr::Update()
{
	Collide();
	for (int i = 0; i < MAX_OBJECTS_COUNT; ++i)
	{
		if (m_objects[i]!=NULL) 
		{
			m_objects[i]->Update(t_ElapsedTime);
			if (m_objects[i]->IsDead())
			{
				delete m_objects[i];
				m_objects[i] = NULL;
				--m_objectCnt;
			}
		}
	}
}
//#define COLLIDE_REACTION
void SceneMgr::Collide()
{
	for (int i = 0; i < MAX_OBJECTS_COUNT; ++i)
		if(m_objects[i]!=NULL)
			m_objects[i]->setFlagCollide(false);
	for (int i = 0; i < MAX_OBJECTS_COUNT-1; ++i)
	{
		for (int j = i + 1; j < MAX_OBJECTS_COUNT; ++j)
		{
			//	Collide
			if (m_objects[i]!=NULL && m_objects[j]!=NULL) {
				if (m_objects[i]->getCollideRect().Check(
					m_objects[j]->getCollideRect()))
				{
#ifdef COLLIDE_REACTION
					double vecx, vecy;
					vecx = m_objects[i]->getVecX();
					vecy = m_objects[i]->getVecY();
					m_objects[i]->SetVector(m_objects[j]->getVecX(), m_objects[j]->getVecY());
					m_objects[j]->SetVector(vecx, vecy);
#endif // COLLIDE_REACTION
					m_objects[i]->setFlagCollide(true);
					m_objects[i]->damage(1);
					m_objects[j]->setFlagCollide(true);
					m_objects[j]->damage(1);
				}
			}
		}
	}
}

void SceneMgr::Destory()
{
	for (int i = 0; i < MAX_OBJECTS_COUNT; ++i)
	{
		if (m_objects[i])
		{
			//m_objects[i].destroy();
			delete m_objects[i];
			m_objects[i] = NULL;
			--m_objectCnt;
		}
	}
}

void SceneMgr::AddObject(int x, int y)
{
	for (int i = 0; i < MAX_OBJECTS_COUNT; ++i)
	{
		if (m_objects[i] == NULL)
		{
			m_objects[i] = new Object;
			m_objects[i]->InitializeRand(m_objectsRenderer);
			m_objects[i]->SetPosition(x, y);
			++m_objectCnt;
			break;
		}
	}
}
