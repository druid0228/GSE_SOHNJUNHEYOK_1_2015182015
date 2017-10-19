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
	if (!m_objectsRenderer->IsInitialized())
	{
		std::cout << "Renderer could not be initialized.. \n";
	}
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
	for (int i = 0; i < m_objectCnt; ++i)
	{
		m_objects[i]->Update();
	}
}

void SceneMgr::Collide()
{
	for (int i = 0; i < MAX_OBJECTS_COUNT; ++i)
		m_objects[i]->setFlagCollide(false);
	for (int i = 0; i < MAX_OBJECTS_COUNT-1; ++i)
	{
		for (int j = i + 1; j < MAX_OBJECTS_COUNT; ++j)
		{
			//	Collide
			if (m_objects[i]->getCollideRect().Check(
				m_objects[j]->getCollideRect()))
			{
				/*double vecx, vecy;
				vecx = m_objects[i]->getVecX();
				vecy = m_objects[i]->getVecY();
				m_objects[i]->SetVector(m_objects[j]->getVecX(), m_objects[j]->getVecY());
				m_objects[j]->SetVector(vecx, vecy);*/
				m_objects[i]->setFlagCollide(true);
				m_objects[j]->setFlagCollide(true);
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
		}
	}
}
