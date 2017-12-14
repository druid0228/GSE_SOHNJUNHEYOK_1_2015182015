#pragma once
class Renderer;

class CClimate
{
	bool b_on;
	Renderer *m_Render = NULL;
	unsigned int* m_tex;
	unsigned int n_tex;
	int m_size=1;
	float time=0;
	float gDirx=-0.1;
	float gDiry=-0.1;
public:
	void init(Renderer* render,unsigned int* tex_arr,unsigned int n_tex );
	void Render();
	void Update(float elapsed);
	void Toggle() { b_on = 1 - b_on; }
	CClimate();
	~CClimate();
};

