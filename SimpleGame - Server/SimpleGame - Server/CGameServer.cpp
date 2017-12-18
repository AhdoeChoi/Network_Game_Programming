#include "stdafx.h"
#include "CGameServer.h"

SOCKET	CGameServer::client_socket;
Host CGameServer::hostlist[100];
int CGameServer::hostnum = 0;
bool CGameServer::posible_enter[100];
CGameServer::CGameServer()
{
	::ZeroMemory(&hostlist, sizeof(hostlist));
	hostnum = 0;
	::ZeroMemory(&hThread, sizeof(hThread));
}


CGameServer::~CGameServer()
{
	//여기 꼭 다시 돌아오렴
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
	// 데이터 통신에 사용할 변수

	int addrlen;

	while (1)
	{
		// accept() 이부분 while문 돌면서 멀티클라이언트 처리하게 바꿔야함
		addrlen = sizeof(clientaddr);
		client_socket = accept(listen_sock, (SOCKADDR *)&clientaddr /*접속한 클라이언트의 주소정보로 채워짐*/, &addrlen);
		if (client_socket == INVALID_SOCKET)
		{
			err_display("accept()");
			return;
		}

		// 접속한 클라이언트 정보 출력
		printf("\n[TCP 서버] 클라이언트 접속: IP 주소=%s, 포트 번호=%d\n",
			inet_ntoa(clientaddr.sin_addr), ntohs(clientaddr.sin_port));

		// 스레드 생성
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


}

bool CGameServer::MainServerConnect(SOCKET s)
{
	return false;
}

bool CGameServer::CreateHostServer(SOCKET s, SOCKADDR_IN client_addr)
{
	char name[20];
	memset(name, '0', sizeof(name));
	// 방이름 recv 받아야함
	
	int sendRequest = 0;

	for (int i = 0; i < MAX_HOST_NUM; i++)
	{
		/*cout << hostlist[i].name << endl;
		cout << inet_ntoa(hostlist[i].ip.sin_addr) << endl;
		cout << hostlist[i].number << endl;*/

		if (hostlist[i].number == 0)
		{

			sendRequest = 1; //방 잘만들어 졌다고 알림
			send(s, (char*)&sendRequest, sizeof(sendRequest), 0);
			recv(s, name, strlen(name) + 1, 0);

			cout << name << endl;

			hostnum++;
			//strcpy_s(hostlist[i].name,sizeof(name) * 20, name);
			strncpy_s(hostlist[i].name,strlen(name)+1, name, strlen(name));

			hostlist[i].number = hostnum;
			hostlist[i].ip = client_addr;
			posible_enter[i] = true;
			/*cout << hostlist[i].name << endl;
			cout << inet_ntoa(hostlist[i].ip.sin_addr) << endl;
			cout << hostlist[i].number << endl;*/
			//strcpy(hostlist[i].name, name);
			return true;
		}
	}
		
	send(s, (char*)&sendRequest, sizeof(sendRequest), 0); //방만들기 실패했다고 알림

	return false;
}

bool CGameServer::EnterHostServer(int number)
{
	return false;
}

void CGameServer::WaitAnotehrClient()
{
	//이건 클라가 가지고 있어야 할거가틈 여기에서 원래 player가 enemy기다리는부분 넣으면 됨
}

bool CGameServer::RefreshHostList()
{
	return false;
}

bool CGameServer::IsChangeClient()
{
	//무쓸모
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
	//필요없을거같음
}

bool CGameServer::SearchHostList(int num, Host * findHost)
{
	for (int i = 0; i < MAX_HOST_NUM; i++)
		if (hostlist[i].number == num && posible_enter[i])
		{
			*findHost = hostlist[i];
			posible_enter[i] = false;
			return true;
		}
	return false;
}

void CGameServer::SendHostList(SOCKET s, SOCKADDR_IN client_addr) //방 목록 보내주는거
{

	for (int i = 0; i < MAX_HOST_NUM; ++i)
	{
		send(s, (char*)&hostlist[i], sizeof(Host), 0);
	}
	//send(s, (char*)&hostlist, sizeof(hostlist) * MAX_HOST_NUM, 0);
	
	//send() 하면 끝
}

DWORD WINAPI CGameServer::ProcessClient(LPVOID arg)
{
	Host FindHost;

	SOCKET client_sock_req = (SOCKET)arg;

	SOCKADDR_IN clientaddr;

	int choiceNumber; //클라이언트의 요청값
	int retval = 0;

	int iRequestEnterRoomNumber = 0;
	int addrlen = sizeof(clientaddr);
	getpeername(client_sock_req, (SOCKADDR *)&clientaddr, &addrlen);

	while (true)
	{
		retval = recv(client_sock_req, (char*)&choiceNumber, sizeof(int), 0); //클라이언트의 요청값 받아옴
		if (retval == SOCKET_ERROR) {
			err_display("recv()");

		}
		int SearchResult = 0;

		switch (choiceNumber)
		{
		case 1: //클라이언트가 방을 만들고 싶어 하면
			CreateHostServer(client_sock_req, clientaddr);

			break;
		case 2:
			recv(client_sock_req, (char*)&iRequestEnterRoomNumber, sizeof(iRequestEnterRoomNumber), 0);

			if (SearchHostList(iRequestEnterRoomNumber, &FindHost) == true)
			{
				SearchResult = 1;
				send(client_sock_req, (char*)&SearchResult, sizeof(SearchResult), 0);  //방을 찾았다고 알림

				send(client_sock_req, (char*)&FindHost.ip, sizeof(FindHost.ip), 0);
				//
			}
			else
			{
				SearchResult = 0;
				send(client_sock_req, (char*)&SearchResult, sizeof(SearchResult), 0);
			}
			break;
		case 3:
			SendHostList(client_sock_req, clientaddr);
			break;
		}
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