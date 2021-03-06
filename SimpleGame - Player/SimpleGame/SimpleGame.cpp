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
DWORD elapsedTime;

bool g_left_mouse = false;

bool bBuildObjectFinish = false;

int xpos = -300;
int iInputKey = 0;

int shiledXpos = 0;

 bool bShootState = false;
void RenderScene(void)
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0f, 0.3f, 0.3f, 1.0f);


	//서버와 연결 (대기방 입장)
	//gameFrameWork->m_pScene->BuildObject(); //빌딩배치

	
	if (!bBuildObjectFinish) //빌드 오브젝트가 끝나면 서버 동작
	{
		gameFrameWork->m_pScene->BuildObject(xpos, &bBuildObjectFinish, iInputKey);
		xpos = -300;
	}
	else
	{

		gameFrameWork->ServerRunning();
		DWORD currTime = timeGetTime();
		elapsedTime = currTime - CurrentTime; //한프레임 그리는데 걸리는 시간임

		//=============================================== 서버데이터 주고받어
		//send & recv 반복
		//gameFrameWork->RecvFromOpponent(); // enemy정보를 씬에 넘겨줘
		//gameFrameWork->SendToOpponent(); // 상대클라이언트에 내 정보를 보내
		//===============================================

		//받아온 정보를 업데이트하고 그린다.
		if (gameFrameWork->m_pScene->IsGameOver()  == RESULT_PLAYING)
		{
			gameFrameWork->Update(elapsedTime);
			gameFrameWork->Render();

			CurrentTime = currTime;
			cout << elapsedTime;
			//===============================================
		}
		else if (gameFrameWork->m_pScene->IsGameOver() == RESULT_LOSE)
		{
			gameFrameWork->m_pScene->m_renderer->DrawTexturedRect(0, 0, 0, 400, 1, 1, 1, 1, gameFrameWork->m_pScene->GetTexture(8), 0.5);
			
		}
	
		else if (gameFrameWork->m_pScene->IsGameOver() == RESULT_WIN)
		{
			gameFrameWork->m_pScene->m_renderer->DrawTexturedRect(0, 0, 0, 400, 1, 1, 1, 1,gameFrameWork->m_pScene->GetTexture(7), 0.5);

		}


	}


	////////////////////////////////////////////////
	UCHAR pKeyBuffer[256];
	DWORD dwDirection = 0;

	if (::GetKeyboardState(pKeyBuffer))
	{
		if (pKeyBuffer[VK_UP] & 0xF0)
			if (gameFrameWork->m_pScene->m_Player.Shield.Pos.fypos < 0)
				gameFrameWork->m_pScene->shieldYpos += 20 * elapsedTime * 0.03;
		if (pKeyBuffer[VK_DOWN] & 0xF0)
			if (gameFrameWork->m_pScene->m_Player.Shield.Pos.fypos > -400)
				gameFrameWork->m_pScene->shieldYpos -= 20 * elapsedTime * 0.03;
		if (pKeyBuffer[VK_LEFT] & 0xF0)
			gameFrameWork->m_pScene->shieldXpos -= 20 * elapsedTime * 0.03;
		if (pKeyBuffer[VK_RIGHT] & 0xF0)
			gameFrameWork->m_pScene->shieldXpos += 20 * elapsedTime * 0.03;
		if (pKeyBuffer[VK_SPACE] & 0xF0)
		{
			if (!bShootState)
			{
				
		
				gameFrameWork->m_pScene->m_Player.Shield.Bullet.IsCoolTime = true;
				bShootState = true;
			}
			else
			{
				gameFrameWork->m_pScene->m_Player.Shield.Bullet.IsCoolTime = false;
			}
		}
		else
		{
		
			bShootState = false;
		}
	}
////////////////////////////////////////////////////

	
	glutSwapBuffers();
}

void Idle(void)
{
	RenderScene();
}

void MouseInput(int button, int state, int x, int y)
{
	if (!bBuildObjectFinish)
	{
		if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
			g_left_mouse = true;
		if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
		{
			xpos = x - 250;
		}
	}
	else
	{
		if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		{
			shiledXpos = x - 250;

			gameFrameWork->m_pScene->shieldXpos = shiledXpos;
			gameFrameWork->m_pScene->shieldYpos = -y + 400;

		}
	}

	

	RenderScene();
}

void KeyInput(unsigned char key, int x, int y)
{
	if (key == 'c' || key == 'C')
	{
		iInputKey++;
	}
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
	glutInitWindowSize(500, 800);
	glutCreateWindow("NetworkGame");

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
	g_SceneMgr = new SceneMgr(500, 800);
	gameFrameWork = new GameFrameWork;

	gameFrameWork->m_pScene = g_SceneMgr;


	
	//////////////////////////////////////

	//소켓 초기화 해줄 곳

	//gameFrameWork->client_socket, gameFrameWork->server_socket 초기화 해주겟지

	///////////////////////////////////////


	glutDisplayFunc(RenderScene);
	glutIdleFunc(Idle);
	glutKeyboardFunc(KeyInput);
	glutMouseFunc(MouseInput);
	glutSpecialFunc(SpecialKeyInput);

	//CurrentTime = timeGetTime();


	glutMainLoop();

	gameFrameWork->CloseSocket();

	delete g_SceneMgr;
	delete gameFrameWork;
	return 0;
}
