/*
Copyright 2017 Lee Taek Hee (Korea Polytech University)

This program is free software: you can redistribute it and/or modify
it under the terms of the What The Hell License. Do it plz.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY.
*/

#include "stdafx.h"
#include <iostream>
#include "Dependencies\glew.h"
#include "Dependencies\freeglut.h"

#include "Renderer.h"
#include"SceneMgr.h"
//#include"Object.h"
#include<math.h>

Renderer *g_Renderer = NULL;
SceneMgr g_Scene;

//Object object;
int g = -250;
void RenderScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0f, 0.3f, 0.3f, 1.0f);

	g_Scene.Update();
	//object.Update();
	// Renderer Test
	//g_Renderer->DrawSolidRect(++g > 250 ? g = -250 : g, 0, 0, 100, 1, 1, 1, 1);
	glutSwapBuffers();
}

void Idle(void)
{
	RenderScene();
}

void MouseInput(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON&&state == GLUT_UP)
	{
		//object.SetPosition(x - 500 / 2, 500 / 2 - y);
		//object.SetVector(rand()%100/(float)100, rand() % 100 / (float)100);
	}
	if (button == GLUT_LEFT_BUTTON&&state == GLUT_DOWN)
	{
		//object.SetPosition(x - 500 / 2, 500 / 2 - y);
		//object.SetPosition(0, 0);
		//object.SetVector(0, 0);
	}

	RenderScene();
}

void KeyInput(unsigned char key, int x, int y)
{
	RenderScene();
}

void SpecialKeyInput(int key, int x, int y)
{
	if (key == GLUT_KEY_DOWN)
	{
		//object.PlusVector(0, -1);
	}
	if (key == GLUT_KEY_UP)
	{
		//object.PlusVector(0, 1);
	}
	if (key == GLUT_KEY_LEFT)
	{
		//object.PlusVector(-1, 0);
	}
	if (key == GLUT_KEY_RIGHT)
	{
	//	object.PlusVector(1,0);
	}

	RenderScene();
}

int main(int argc, char **argv)
{
	// Initialize GL things
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(500, 500);
	glutCreateWindow("Game Software Engineering KPU");

	glewInit();
	if (glewIsSupported("GL_VERSION_3_0"))
	{
		std::cout << " GLEW Version is 3.0\n ";
	}
	else
	{
		std::cout << "GLEW 3.0 not supported\n ";
	}

	// Initialize Renderer
	//g_Renderer = new Renderer(500, 500);
	//if (!g_Renderer->IsInitialized())
	//{
	//	std::cout << "Renderer could not be initialized.. \n";
	//}
	//object.InitializeRenderer();

	g_Scene.Initalize();

	glutDisplayFunc(RenderScene);
	glutIdleFunc(Idle);
	glutKeyboardFunc(KeyInput);
	glutMouseFunc(MouseInput);
	glutSpecialFunc(SpecialKeyInput);

	glutMainLoop();

	delete g_Renderer;

    return 0;
}

