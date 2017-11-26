#pragma once

#include "SceneMgr.h"
class GameFrameWork
{
public: //����
	SOCKET				server_socket;
	SOCKET				client_socket;
	SOCKADDR_IN			clientaddr; //�߰�
	SOCKET				listen_sock; //�߰�
public:
	SceneMgr			*m_pScene;
	Building			*m_pEnemy; //Scene�� �Ѱ��� enemy
public:
	void				Update(float elapsedTime) { m_pScene->Update(elapsedTime); }
	void				Render() { m_pScene->Render(); }
	
//�����Լ� �κ�
public:
	int					SendToOpponent(SOCKET socket, Building * building, int len, int flag);   //�� ������ ���� Ŭ���̾�Ʈ�� ����
	int					RecvFromOpponent(SOCKET socket, Building * building, int len, int flag); //enemy������ �޾ƿ�

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

