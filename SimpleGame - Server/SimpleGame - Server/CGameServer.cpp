#include "stdafx.h"
#include "CGameServer.h"

SOCKET	CGameServer::client_socket;
Host CGameServer::hostlist[100];
int CGameServer::hostnum = 0;

CGameServer::CGameServer()
{
	::ZeroMemory(&hostlist, sizeof(hostlist));
	hostnum = 0;
	::ZeroMemory(&hThread, sizeof(hThread));
}


CGameServer::~CGameServer()
{
	//���� �� �ٽ� ���ƿ���
	//else { CloseHandle(hThread); }
}

void CGameServer::Operation()
{
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
		return;

	int retval = 0;
	// socket()
	listen_sock = socket(AF_INET, SOCK_STREAM, 0);
	if (listen_sock == INVALID_SOCKET) err_quit("socket()");

	// bind()
	SOCKADDR_IN serveraddr;
	ZeroMemory(&serveraddr, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
	serveraddr.sin_port = htons(8999);
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

	while (1)
	{
		// accept() �̺κ� while�� ���鼭 ��ƼŬ���̾�Ʈ ó���ϰ� �ٲ����
		addrlen = sizeof(clientaddr);
		client_socket = accept(listen_sock, (SOCKADDR *)&clientaddr /*������ Ŭ���̾�Ʈ�� �ּ������� ä����*/, &addrlen);
		if (client_socket == INVALID_SOCKET)
		{
			err_display("accept()");
			return;
		}

		// ������ Ŭ���̾�Ʈ ���� ���
		printf("\n[TCP ����] Ŭ���̾�Ʈ ����: IP �ּ�=%s, ��Ʈ ��ȣ=%d\n",
			inet_ntoa(clientaddr.sin_addr), ntohs(clientaddr.sin_port));

		// ������ ����
		for (int i = 0; i < HANDLECNT; ++i)
		{
			if (hThread[i] == NULL)
			{
				hThread[i] = CreateThread(NULL, 0, ProcessClient,
					(LPVOID)client_socket, 0, NULL);
				if (hThread == NULL)
				{
					closesocket(client_socket);
				}
				break;
			}
		}
	}
	


	//switch (a)
	//{
	//case 1: //�� �����
	//	
	//	break;
	//case 2: // �� ����
	//	break;
	//case 3: // �� ��� ����
	//	break;

	//}

	

}

bool CGameServer::MainServerConnect(SOCKET s)
{
	return false;
}

bool CGameServer::CreateHostServer(SOCKET s, SOCKADDR_IN client_addr)
{
	char name[20];
	// ���̸� recv �޾ƾ���
	for(int i = 0; i < MAX_HOST_NUM; i++)
		if (hostlist[i].number == 0)
		{
			hostnum++;
			hostlist[i].number == hostnum;
			hostlist[i].ip = client_addr;
			//strcpy(hostlist[i].name, name);
			return true;
		}
	return false;
}

bool CGameServer::EnterHostServer(int number)
{
	if (SearchHostList(number))
	{
		return true;
	}
	
	return false;
}

void CGameServer::WaitAnotehrClient()
{
	//�̰� Ŭ�� ������ �־�� �ҰŰ�ƴ ���⿡�� ���� player�� enemy��ٸ��ºκ� ������ ��
}

bool CGameServer::RefreshHostList()
{
	return false;
}

bool CGameServer::IsChangeClient()
{
	//������
	return false;
}

unsigned int CGameServer::RecvClientRequest(LPVOID sock)
{
	return 0;
}

void CGameServer::SaveResult(bool result)
{
}

Host CGameServer::AddHostList(char * name)
{
	return Host();
	//�ʿ�����Ű���
}

bool CGameServer::SearchHostList(int num)
{
	for (int i = 0; i < MAX_HOST_NUM; i++)
		if (hostlist[i].number == num)
			return true;
	return false;
}

void CGameServer::SendHostList()
{
	//send() �ϸ� ��
}

DWORD WINAPI CGameServer::ProcessClient(LPVOID arg)
{


	SOCKET client_sock_req = (SOCKET)arg;

	SOCKADDR_IN clientaddr;

	int choiceNumber;
	int retval = 0;
	int addrlen = sizeof(clientaddr);
	getpeername(client_sock_req, (SOCKADDR *)&clientaddr, &addrlen);


	retval = recv(client_sock_req, (char*)&choiceNumber, sizeof(int), 0);
	if (retval == SOCKET_ERROR) {
		err_display("recv()");

	}
	int sendRequest = 999;
	switch (choiceNumber)
	{
	case 1:
		if (CreateHostServer(client_sock_req, clientaddr))
		{
			send(client_sock_req, (char*)&sendRequest, sizeof(sendRequest), 0);
		}
		break;
	case 2:
		break;
	case 3:
		break;
	}
	return 0;
}

void CGameServer::err_quit(char * msg)
{

}

void CGameServer::err_display(char * msg)
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

int CGameServer::recvn(SOCKET s, char * buf, int len, int flags)
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