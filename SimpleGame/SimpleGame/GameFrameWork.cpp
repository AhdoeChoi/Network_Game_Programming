#include "stdafx.h"
#include "GameFrameWork.h"


GameFrameWork::GameFrameWork()
{
	//���濡�� �� �۾���


	// ������ ���� �ڵ�� ä������


	///////////////////// Ŭ�󳢸��� �ۼ���

	int retval;

	// ���� �ʱ�ȭ
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
		return;

	// socket()
	SOCKET listen_sock = socket(AF_INET, SOCK_STREAM, 0);
	if (listen_sock == INVALID_SOCKET) err_quit("socket()");

	// bind()
	SOCKADDR_IN serveraddr;
	ZeroMemory(&serveraddr, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
	serveraddr.sin_port = htons(SERVERPORT);
	retval = bind(listen_sock, (SOCKADDR *)&serveraddr, sizeof(serveraddr));
	//bind()�� ù��° ���� listen_sock�� Ŭ���̾�Ʈ ������ ������ �������� ���� ��������, ���� IP �ּҿ� ���� ��Ʈ��ȣ�� ���� �������� ���� ������

	if (retval == SOCKET_ERROR) err_quit("bind()");

	// listen()
	retval = listen(listen_sock, SOMAXCONN);
	if (retval == SOCKET_ERROR)
	{
		err_quit("listen()");
	}
	// ������ ��ſ� ����� ����
	client_socket;
	SOCKADDR_IN clientaddr;
	int addrlen;





	while (1) {
		// accept()
		addrlen = sizeof(clientaddr);
		client_socket = accept(listen_sock, (SOCKADDR *)&clientaddr /*������ Ŭ���̾�Ʈ�� �ּ������� ä����*/, &addrlen);
		if (client_socket == INVALID_SOCKET) {
			err_display("accept()");
			break;
		}

		// ������ Ŭ���̾�Ʈ ���� ���
		cout << "����" << endl;

		// ������ �ۼ��� ����

		m_pScene->BuildObject(); //ó�� ��ġ ��� �Ұ�����, ��ġ ������ ������ �ۼ��� ����
		

		while (1) {
			//RecvFromOpponent(); // ���� ���� �޾ƿ�
			//SendToOpponent(); // ������ ���濡�� ����

			//m_pScene->Update(); // �޾ƿ� ���� ������ Scene�� ������Ʈ
			//m_pScene->Render(); // Update�� ������ �׷�


		}

		// closesocket()
		closesocket(client_socket);
		/*printf("[TCP ����] Ŭ���̾�Ʈ ����: IP �ּ�=%s, ��Ʈ ��ȣ=%d\n",
			inet_ntoa(clientaddr.sin_addr), ntohs(clientaddr.sin_port));*/
	}

	// closesocket()
	closesocket(listen_sock);

	// ���� ����
	WSACleanup();


}


GameFrameWork::~GameFrameWork()
{


}

int	GameFrameWork::SendToOpponent(SOCKET socket, Building * building, int len, int flag)
{

	return 0;

	// ================================

	//	�� ������ ��� Ŭ���̾�Ʈ���� �Ѱ���

	// ================================
}
int	GameFrameWork::RecvFromOpponent(SOCKET socket, Building * building, int len, int flag)
{

	return 0;

	//=============================



	//	���Ŭ���̾�Ʈ (��) �� ������ �޾ƿ�
	

	
	//=============================

	m_pEnemy = building; // �޾ƿ� ������ ���� �Ѱ��� enemy

	m_pScene->SetOpponentData(m_pEnemy); //���� ������ ������Ʈ

}

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
