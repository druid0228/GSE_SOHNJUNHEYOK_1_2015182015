#pragma once
#define MAX_OBJECTS_COUNT		100
#define MAX_CHARACTER_COUNT	10
#define MAX_BULLET_COUNT			50

class Object;

class SceneMgr
{
	Object *m_objects[MAX_OBJECTS_COUNT];
	Renderer *m_objectsRenderer=NULL;
	int m_Character_objCnt=0;
	double t_current_time = 0, t_ElapsedTime = 0;
	
	int m_Bullet_objCnt = 0;
	double t_lastBulletCreate = 0;
public:
	SceneMgr();
	~SceneMgr();
	void Initalize();
	void InitializeObjects();
	void Update();
	void Collide();
	void Destory();
	void Tick() {
		t_ElapsedTime = (timeGetTime() - t_current_time)*0.001;
		t_current_time = timeGetTime();
	};
	void TimeInit(){ t_current_time = timeGetTime(); }
	void PrintTime() {
		printf("%lf	%lf\n", t_current_time, t_ElapsedTime);
	}
public:
	bool CanObjectAdd()const { return m_Character_objCnt < MAX_OBJECTS_COUNT; }
	void AddObject(int x, int y);
	int AddActorObject(int x, int y, ObjectType type);
};

