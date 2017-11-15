#pragma once

#include "SceneMgr.h"
class GameFrameWork
{
public:
	SOCKET			server_socket;
	SOCKET			client_socket;
public:
	SceneMgr		*m_pScene;
	Building		*m_pEnemy; //Scene에 넘겨줄 enemy
public:
	void			Update(float elapsedTime) { m_pScene->Update(elapsedTime); }
	void			Render() { m_pScene->Render(); }
	
//서버함수 부분
public:
	int				SendToOpponent(SOCKET socket, Building * building, int len, int flag);   //내 정보를 상대방 클라이언트에 보냄
	int				RecvFromOpponent(SOCKET socket, Building * building, int len, int flag); //enemy정보를 받아옴

	void			SetOpponentData() { m_pScene->SetOpponentData(m_pEnemy); }

public:
	GameFrameWork();
	~GameFrameWork();
};

