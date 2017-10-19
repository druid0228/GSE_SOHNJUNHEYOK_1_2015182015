#pragma once
#define MAX_OBJECTS_COUNT	50
class Object;

class SceneMgr
{
	Object *m_objects[MAX_OBJECTS_COUNT];
	Renderer *m_objectsRenderer=NULL;
	int m_objectCnt=0;
public:
	SceneMgr();
	~SceneMgr();
	void Initalize();
	void Update();
	void Collide();
	void Destory();
};

