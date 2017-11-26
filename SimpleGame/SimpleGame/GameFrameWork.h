#pragma once

#include "SceneMgr.h"
class GameFrameWork
{
public: //소켓
	SOCKET				server_socket;
	SOCKET				client_socket;
	SOCKADDR_IN			clientaddr; //추가
	SOCKET				listen_sock; //추가
public:
	SceneMgr			*m_pScene;
	Building			*m_pEnemy; //Scene에 넘겨줄 enemy
public:
	void				Update(float elapsedTime) { m_pScene->Update(elapsedTime); }
	void				Render() { m_pScene->Render(); }
	
//서버함수 부분
public:
	int					SendToOpponent(SOCKET socket, Building * building, int len, int flag);   //내 정보를 상대방 클라이언트에 보냄
	int					RecvFromOpponent(SOCKET socket, Building * building, int len, int flag); //enemy정보를 받아옴

	void				SetOpponentData() { m_pScene->SetOpponentData(m_pEnemy); }
	void				err_quit(char *msg);
	void				err_display(char *msg);
	int					recvn(SOCKET s, char *buf, int len, int flags);

	void				ServerRunning();
	void				CloseSocket();

public:
	GameFrameWork();
	~GameFrameWork();
};

