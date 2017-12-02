#include "stdafx.h"
#include "GameFrameWork.h"


GameFrameWork::GameFrameWork()
{
	//���濡�� �� �۾���


	// ������ ���� �ڵ�� ä������


	///////////////////// Ŭ�󳢸��� �ۼ����ϱ� ���� ���� �ʱ�ȭ����

	int retval;

	// ���� �ʱ�ȭ
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
		return;

	// socket()
	client_socket = socket(AF_INET, SOCK_STREAM, 0);
	if (client_socket == INVALID_SOCKET) err_quit("socket()");

	// connect()
	SOCKADDR_IN serveraddr;
	ZeroMemory(&serveraddr, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_addr.s_addr = inet_addr(SERVERIP);
	serveraddr.sin_port = htons(SERVERPORT);
	retval = connect(client_socket, (SOCKADDR *)&serveraddr, sizeof(serveraddr));
	//if (retval == SOCKET_ERROR) err_quit("connect()");


	cout << "����" << endl;



	//// closesocket()
	//closesocket(listen_sock);

	//// ���� ����
	//WSACleanup();


}


GameFrameWork::~GameFrameWork()
{


}

void GameFrameWork::Update(float elapsedTime)
{
	if (m_pScene == NULL)
	{
		m_pScene = new SceneMgr;
	}
	m_pScene->Update(elapsedTime);
}

int	GameFrameWork::SendToOpponent(SOCKET *socket, Buildings building, int len, int flag)
{

	int retval = 0;
	// ================================

	//	�� ������ ��� Ŭ���̾�Ʈ���� �Ѱ���


	retval = send(*socket, (char*)&building, len, 0);
	if (retval == SOCKET_ERROR) 
	{
		err_display("send()");
		return 0;

	}

	// ================================
	return 0;


}
int	GameFrameWork::RecvFromOpponent(SOCKET *socket, Buildings building, int len, int flag)
{
	int retval = 0;


	//=============================



	//	���Ŭ���̾�Ʈ (��) �� ������ �޾ƿ�
	retval = recvn(*socket, (char *)&building, sizeof(building), 0);
	if (retval == SOCKET_ERROR)
	{
		err_display("send()");
		return 0; 
	}
	//=============================

	m_Enemy = building; // �޾ƿ� ������ ���� �Ѱ��� enemy

	m_pScene->SetOpponentData(m_Enemy); //���� ������ ������Ʈ

	return 0;

}

void GameFrameWork::ServerRunning()
{
	// ������ �ۼ��� ����

	for (int i = 0; i < 3; ++i)
	{
		m_Player.building[i] = (m_pScene->m_ppPlayerClass[i]->m_Building);
	}

	SendToOpponent(&client_socket, m_Player, sizeof(m_Player), 0); //�� ���� ������
	RecvFromOpponent(&client_socket, m_Enemy, sizeof(m_Enemy), 0); // ��� ���� �޾ƿ´�.
	//SendToOpponent()


}




//---------------------------------------------------------------------------------
void GameFrameWork::err_quit(char * msg)
{

}

void GameFrameWork::err_display(char * msg)
{
	LPVOID lpMsgBuf;
	FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
		NULL, WSAGetLastError(),
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR)&lpMsgBuf, 0, NULL);
	printf("[%s] %s", msg, (char *)lpMsgBuf);
	LocalFree(lpMsgBuf);
}

int GameFrameWork::recvn(SOCKET s, char * buf, int len, int flags)
{
	int received;
	char *ptr = buf;
	int left = len;

	while (left > 0) {
		received = recv(s, ptr, left, flags);
		if (received == SOCKET_ERROR)
			return SOCKET_ERROR;
		else if (received == 0)
			break;
		left -= received;
		ptr += received;
	}

	return (len - left);

}


void GameFrameWork::CloseSocket()
{
	closesocket(client_socket);
	WSACleanup();
}

