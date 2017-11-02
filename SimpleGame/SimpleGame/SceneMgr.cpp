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
	m_Character_objCnt = 0;
	m_Bullet_objCnt = 0;
	t_current_time = 0;
	t_ElapsedTime = 0;
	t_lastBulletCreate = 0;
	m_objectsRenderer = NULL;
	ZeroMemory(m_objects, sizeof(Object*)*MAX_OBJECTS_COUNT);

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
	/*for (int i = 0; i < MAX_OBJECTS_COUNT; ++i)
	{
		m_objects[i] = new Object;
		m_objects[i]->InitializeRand(m_objectsRenderer);
		++m_Character_objCnt;
	}*/
	AddActorObject(0, 0, ObjectType::OBJECT_BUILDING);
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
				switch (m_objects[i]->GetType())
				{
				case ObjectType::OBJECT_CHARACTER:
					--m_Character_objCnt;
					break;
				case ObjectType::OBJECT_BULLET:
					--m_Bullet_objCnt;
					break;
				default:
						break;
				}
				delete m_objects[i];
				m_objects[i] = NULL;
			}
		}
	}
	t_lastBulletCreate += t_ElapsedTime;
	if (t_lastBulletCreate >= 0.5f)
	{
		int index;
		t_lastBulletCreate = 0;
		index=AddActorObject(0, 0, ObjectType::OBJECT_BULLET);
		if (index != -1)
		{
			m_objects[index]->SetSpeed(300);
		}
	}
}
//#define COLLIDE_REACTION
void SceneMgr::Collide()
{
	for (int i = 0; i < MAX_OBJECTS_COUNT; ++i)
		if(m_objects[i]!=NULL)
			m_objects[i]->setFlagCollide(false);
	ObjectType iType, jType;
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
					iType = m_objects[i]->GetType(); jType = m_objects[j]->GetType();
					// 같은 타입이거나 같은편이면 충돌체크 패스
					if (iType == jType ||
						IsAlly(m_objects[i]->GetType(),
							m_objects[j]->GetType()))
						continue;

					m_objects[i]->setFlagCollide(true);
					//m_objects[i]->damage(1);
					m_objects[j]->setFlagCollide(true);
					//m_objects[j]->damage(1);
					if (iType == ObjectType::OBJECT_CHARACTER&&
						jType == ObjectType::OBJECT_BUILDING)
					{
						m_objects[j]->damage(m_objects[i]->getLife());
						m_objects[i]->die();
					}
					else if (iType == ObjectType::OBJECT_BUILDING&&
						jType == ObjectType::OBJECT_CHARACTER)
					{
						m_objects[i]->damage(m_objects[j]->getLife());
						m_objects[j]->die();
					}

					if (iType == ObjectType::OBJECT_CHARACTER&&
						jType == ObjectType::OBJECT_BULLET)
					{
						m_objects[i]->damage(m_objects[j]->getLife());
						m_objects[j]->die();
					}
					else if (iType == ObjectType::OBJECT_BULLET&&
						jType == ObjectType::OBJECT_CHARACTER)
					{
						m_objects[j]->damage(m_objects[i]->getLife());
						m_objects[i]->die();
					}
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
			++m_Character_objCnt;
			break;
		}
	}
}

int SceneMgr::AddActorObject(int x, int y, ObjectType type)
{
	switch (type)
	{
	case ObjectType::OBJECT_BUILDING:
			m_objects[MAX_OBJECTS_COUNT-1] = new Object;
			m_objects[MAX_OBJECTS_COUNT-1]->Initialize(ObjectType::OBJECT_BUILDING,
				m_objectsRenderer);
			m_objects[MAX_OBJECTS_COUNT-1]->SetPosition(0, 0);
			return MAX_OBJECTS_COUNT - 1;
		break;
	case ObjectType::OBJECT_CHARACTER:
		if (m_Character_objCnt < MAX_CHARACTER_COUNT)
		{
			for (int i = 0; i < MAX_OBJECTS_COUNT; ++i)
			{
				if (m_objects[i] == NULL)
				{
					m_objects[i] = new Object;
					m_objects[i]->Initialize(ObjectType::OBJECT_CHARACTER,
						m_objectsRenderer);
					m_objects[i]->SetPosition(x, y);
					m_objects[i]->SetLife(40);
					++m_Character_objCnt;
					return i;
				}
			}
		}
		break;
	case ObjectType::OBJECT_BULLET:
		if (m_Bullet_objCnt < MAX_BULLET_COUNT) {
			for (int i = 0; i < MAX_OBJECTS_COUNT; ++i)
			{
				if (m_objects[i] == NULL)
				{
					m_objects[i] = new Object;
					m_objects[i]->Initialize(ObjectType::OBJECT_BULLET,
						m_objectsRenderer);
					m_objects[i]->SetPosition(x, y);
					++m_Bullet_objCnt;
					return i;
				}
			}
		}
		break;
	case ObjectType::OBJECT_ARROW:
		break;
	}
	return -1;
}
