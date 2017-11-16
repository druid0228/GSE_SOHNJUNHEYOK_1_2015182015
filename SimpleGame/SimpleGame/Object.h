#pragma once

class Renderer;

class Object
{
	double m_posX, m_posY;
	double m_vecX, m_vecY;
	double m_speed;
	float m_size;
	float m_R, m_G, m_B, m_A;
	bool m_collide;
	int	m_id;

	int m_team = 0;


	double m_life;
	double m_lifeTime;
	bool f_lifeTime = false;

	bool m_haveTex = false;
	unsigned int m_TextureID;

	Renderer *m_Renderer = NULL;
	Renderer *m_SceneRender = NULL;
	ObjectType m_type;

public:
	double t_Arrow_CoolTime = 0;
	double t_Bullet_CoolTime = 0;
	

public:
	ObjectType GetType()const { return m_type; }
	
	void SetID(int id) { m_id = id; }
	int GetID()const { return m_id; }

	void SetTexture(unsigned int ID)
	{
		m_TextureID = ID;
		m_haveTex = true;
	}
public:
	void damage(double d) { m_life -= d; }
	double getLife()const { return m_life; }
	void die() { m_life = 0; }
	double IsDead() const {
		return m_life <= 0 || 
			(f_lifeTime&&m_lifeTime <= 0);};
public:
	void SetPosition(double x, double y) { m_posX = x; m_posY = y; }
	void SetVector(double x, double y) { 
		m_vecX = x; m_vecY = y; 
		float norm = sqrt(x*x + y*y);
		if (IsZero(norm))norm = 1;
		m_vecX /= norm;
		m_vecY /= norm;
	}
	void PlusVector(double x, double y)
	{
		m_vecX += x;
		m_vecY += y;
		double norm = sqrt(m_vecX*m_vecX + m_vecY*m_vecY);
		if (norm <= 0)norm = 1;
		m_vecX = m_vecX / norm;
		m_vecY = m_vecY / norm;
		if (abs(m_vecX)<0.1)m_vecX = 0;
		if (abs(m_vecY)<0.1)m_vecY = 0;
	}
	void SetSpeed(double speed) { m_speed = speed; }
	void SetLife(double life) { m_life = life; }
	void SetTeam(int t) { m_team = t; }
	int GetTeam()const { return m_team; }

public:
	collideRect getCollideRect()const {
		return collideRect(m_posX, m_posY, m_size);
	}
	double getVecX()const { return m_vecX; }
	double getVecY()const { return m_vecY; }
	double getPosX()const { return m_posX; }
	double getPosY()const { return m_posY; }
	void setFlagCollide(bool b) { m_collide = b; }
	bool getFlagCollide()const { return m_collide; }

public:
	Object();
	virtual void Render();

	virtual void Initialize(ObjectType type,Renderer* SceneRender,int team=0);
	virtual void InitializeRand(Renderer *SceneRender);
	virtual void InitializeRenderer();
	virtual void Update(double ElapsedTime);
	virtual void Animate(double ElapsedTime);
	virtual void Idle();
	virtual void MouseInputProcess();
	virtual void KeyInputProcess();
	virtual void SpecialKeyInputProcess();
	
	virtual ~Object();
};

