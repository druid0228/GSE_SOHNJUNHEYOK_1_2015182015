#pragma once

class Object;
struct coolTimeUI {
	double t_t1Char;
	double t_t2Char;
	double t1Posx = -HALFWIDTH + 20, t1PosY = HALFHEIGHT - 10;
	double t2Posx = -HALFWIDTH + 20, t2PosY = -HALFHEIGHT + 10;
	int size = 8;
	Renderer *Render = NULL;

	void SetRenderer(Renderer *r) { Render = r; }
	void Update(double t1, double t2,bool c2)
	{
		t_t1Char = t1;
		t_t2Char = t2;
		if (t_t1Char > CHAR1_COOL_TIME)
			t_t1Char = CHAR1_COOL_TIME;
		if (t_t2Char > CHAR2_COOL_TIME)
			t_t2Char = CHAR2_COOL_TIME;
		if (c2)t_t2Char = CHAR2_COOL_TIME;
		if (Render != NULL) {
			for (int i = 0; i < (int)t_t1Char; ++i)
			{
				Render->DrawSolidRect(t1Posx + (size + 1)*i, t1PosY, 0, size, 1, 0, 0, 1);
			}
			for (int i = 0; i < (int)t_t2Char; ++i)
			{
				Render->DrawSolidRect(t2Posx + (size + 1)*i, t2PosY, 0, size, 0, 0, 1, 1);
			}
		}
	}
};

class SceneMgr
{
	Object *m_objects[MAX_OBJECTS_COUNT];
	Renderer *m_objectsRenderer=NULL;
	int m_Character_objCnt=0;
	double t_current_time = 0, t_ElapsedTime = 0;

	int m_Bullet_objCnt = 0;
	double t_lastBulletCreate = 0;

	double t_Team1Character = 0;
	double t_Team2Character = 0;
	bool f_CreateCharcter = false;
	
	int m_idAlignment = 0;
	int m_Arrow_objCnt = 0;
	bool Team1_building[3];
	bool Team2_building[3];

	unsigned int buildingTex1, buildingTex2;

	//tmp
	coolTimeUI CTui;
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
	int AddActorObject(int x, int y, ObjectType type,int team=TEAM_1);
	bool CanCharacterAdd()const{return f_CreateCharcter;}
};



