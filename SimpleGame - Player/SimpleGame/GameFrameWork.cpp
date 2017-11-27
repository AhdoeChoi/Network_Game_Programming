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
	listen_sock = socket(AF_INET, SOCK_STREAM, 0);
	if (listen_sock == INVALID_SOCKET) err_quit("socket()");

	// bind()
	SOCKADDR_IN serveraddr;
	ZeroMemory(&serveraddr, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
	serveraddr.sin_port = htons(SERVERPORT);
	retval = bind(listen_sock, (SOCKADDR *)&serveraddr, sizeof(serveraddr));

	if (retval == SOCKET_ERROR) err_quit("bind()");

	// listen()
	retval = listen(listen_sock, SOMAXCONN);
	if (retval == SOCKET_ERROR)
	{
		err_quit("listen()");
	}
	// ������ ��ſ� ����� ����

	int addrlen;

	// accept() �̺κ� while�� ���鼭 ��ƼŬ���̾�Ʈ ó���ϰ� �ٲ����
	addrlen = sizeof(clientaddr);
	client_socket = accept(listen_sock, (SOCKADDR *)&clientaddr /*������ Ŭ���̾�Ʈ�� �ּ������� ä����*/, &addrlen);
	if (client_socket == INVALID_SOCKET)
	{
		err_display("accept()");
		return;
	}

	// ������ Ŭ���̾�Ʈ ���� ���
	cout << "����" << endl;

	

	//// closesocket()
	//closesocket(listen_sock);

	//// ���� ����
	//WSACleanup();


}


GameFrameWork::~GameFrameWork()
{


}

int	GameFrameWork::SendToOpponent(SOCKET *socket, Building * building, int len, int flag)
{

	int retval = 0;

	// ================================

	//	�� ������ ��� Ŭ���̾�Ʈ���� �Ѱ���

	retval = send(*socket, (char*)building, len, 0);
	if (retval == SOCKET_ERROR)
	{
		err_display("send()");
		return 0;

	}


	// ================================

	return 0;
}
int	GameFrameWork::RecvFromOpponent(SOCKET *socket, Building * building, int len, int flag)
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

	m_pEnemy = building; // �޾ƿ� ������ ���� �Ѱ��� enemy

	m_pScene->SetOpponentData(m_pEnemy); //���� ������ ������Ʈ

	return 0;

}

void GameFrameWork::ServerRunning()
{
	// ������ �ۼ��� ����


	RecvFromOpponent(&client_socket, m_pEnemy, sizeof(m_pEnemy), 0);
	SendToOpponent(&client_socket, m_pPlayer, sizeof(m_pPlayer), 0); //�� ���� ������



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

