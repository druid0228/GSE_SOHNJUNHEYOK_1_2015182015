#include "stdafx.h"
#include "Climate.h"
#include"Renderer.h"

CClimate::CClimate()
{
}


CClimate::~CClimate()
{
}

void CClimate::init(Renderer * render, unsigned int * tex_arr, unsigned int ntex)
{
	b_on = true;
	m_Render = render;
	m_tex = tex_arr;
	n_tex = ntex;
	m_size = 1;
	gDirx = -0.3;
	gDiry = 0;
}

void CClimate::Render()
{
	if (b_on&&m_Render) {
		for (int i = 0; i < n_tex; ++i)
		{
			m_Render->DrawParticleClimate(0, 0, 0, m_size, 1, 1, 1, 1,
				gDirx, gDiry, m_tex[i], time, RENDERLEVEL(LEVEL_GOD));
		}
	}
}

void CClimate::Update(float elapsed)
{
	if(b_on)
		time += elapsed;
}

