#pragma once
#define MAX_OBJECTS_COUNT	10
class Object;

class SceneMgr
{
	Object *m_objects[MAX_OBJECTS_COUNT];
	Renderer *m_objectsRenderer=NULL;
	int m_objectCnt=0;
	double t_current_time = 0, t_ElapsedTime = 0;
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
	bool CanObjectAdd()const { return m_objectCnt < MAX_OBJECTS_COUNT; }
	void AddObject(int x, int y);
};

