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
#include "object.h"
#include "SceneMgr.h"
#include "GameFrameWork.h"
#include "Renderer.h"

SceneMgr *g_SceneMgr = NULL;
GameFrameWork * gameFrameWork = NULL;
DWORD CurrentTime;


bool g_left_mouse = false;

void RenderScene(void)
{

	DWORD currTime = timeGetTime();
	DWORD elapsedTime = currTime - CurrentTime; //한프레임 그리는데 걸리는 시간임


	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0f, 0.3f, 0.3f, 1.0f);


	//===============================================

	gameFrameWork->Render();
	gameFrameWork->Update(elapsedTime);

	//===============================================


	//send & recv 반복
	//gameFrameWork->RecvFromOpponent(); // enemy정보를 씬에 넘겨줘
	//gameFrameWork->SendToOpponent(); // 상대클라이언트에 내 정보를 보내줘


	glutSwapBuffers();
}

void Idle(void)
{
	RenderScene();
}

void MouseInput(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		g_left_mouse = true;
	if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
	{
	
	}
	RenderScene();
}

void KeyInput(unsigned char key, int x, int y)
{
	RenderScene();
}

void SpecialKeyInput(int key, int x, int y)
{
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
	//if (!g_Renderer->IsInitialized())
	//{
	//	std::cout << "Renderer could not be initialized.. \n";
	//}
	g_SceneMgr = new SceneMgr(500, 500);
	gameFrameWork = new GameFrameWork;

	gameFrameWork->m_pScene = g_SceneMgr;

	gameFrameWork->m_pScene->BuildObject(); //배치 끝나면 송수신 시작
	//////////////////////////////////////


	
	//소켓 초기화 해줄 곳

	//gameFrameWork->client_socket, gameFrameWork->server_socket 초기화 해주겟지





	///////////////////////////////////////


	glutDisplayFunc(RenderScene);
	glutIdleFunc(Idle);
	glutKeyboardFunc(KeyInput);
	glutMouseFunc(MouseInput);
	glutSpecialFunc(SpecialKeyInput);

	CurrentTime = timeGetTime();


	glutMainLoop();

	delete g_SceneMgr;
	delete gameFrameWork;
	return 0;
}
