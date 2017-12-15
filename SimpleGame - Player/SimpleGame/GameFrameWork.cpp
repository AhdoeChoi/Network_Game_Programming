#include "stdafx.h"
#include "GameFrameWork.h"


void GameFrameWork::ConnectServer()
{
	///*대기방에서 할 작업들
	// 대기방을 위한 코드로 채워야함*/
	///////////////////// 클라끼리의 송수신하기 위한 소켓 초기화만함

	int retval;

	// 윈속 초기화
	

	// socket()
	server_socket = socket(AF_INET, SOCK_STREAM, 0);
	if (server_socket == INVALID_SOCKET) err_quit("socket()");

	// connect()
	SOCKADDR_IN serveraddr;
	ZeroMemory(&serveraddr, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_addr.s_addr = inet_addr(SERVERIP);
	serveraddr.sin_port = htons(8999);
	retval = connect(server_socket, (SOCKADDR *)&serveraddr, sizeof(serveraddr));
	//if (retval == SOCKET_ERROR) err_quit("connect()");
}

void GameFrameWork::PrintMenu()
{
	cout << "1. 방 만들기 " << endl;
	cout << "2. 방 참가" << endl;
	cout << "3. 방 목록 보기" << endl;
	cout << "선택 : ";
}

bool GameFrameWork::SendRequest()
{
	PrintMenu();
	cin >> PlayerChoiceNumber;

	int recvResult = 0;

	send(server_socket, (char*)&PlayerChoiceNumber, sizeof(PlayerChoiceNumber), 0);
	if (PlayerChoiceNumber == 1)
	{
		recv(server_socket, (char*)&recvResult, sizeof(recvResult), 0);
		cout << recvResult << endl;
		return false;
	}
	return true;
}

GameFrameWork::GameFrameWork()
{
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
		return;
	//대기방에서 할 작업들
	ConnectServer();

	while (SendRequest()) //새로 추가한 함수
	{

	}
	// 대기방을 위한 코드로 채워야함


	///////////////////// 클라끼리의 송수신하기 위한 소켓 초기화만함

	int retval;

	// 윈속 초기화


	// socket()
	listen_sock = socket(AF_INET, SOCK_STREAM, 0);
	if (listen_sock == INVALID_SOCKET)
		err_quit("socket()");

	// bind()
	SOCKADDR_IN serveraddr;
	ZeroMemory(&serveraddr, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
	serveraddr.sin_port = htons(SERVERPORT);

	int nSockOpt = 1;
	setsockopt(listen_sock, SOL_SOCKET, SO_REUSEADDR, (char*)&nSockOpt, sizeof(nSockOpt));
	retval = bind(listen_sock, (SOCKADDR *)&serveraddr, sizeof(serveraddr));
	
	if (retval == SOCKET_ERROR) 
		err_display("bind()");

	// listen()
	retval = listen(listen_sock, SOMAXCONN);
	if (retval == SOCKET_ERROR)
	{
		err_quit("listen()");
	}
	// 데이터 통신에 사용할 변수

	int addrlen;
	
	// accept() 이부분 while문 돌면서 멀티클라이언트 처리하게 바꿔야함
	addrlen = sizeof(clientaddr);
	client_socket = accept(listen_sock, (SOCKADDR *)&clientaddr /*접속한 클라이언트의 주소정보로 채워짐*/, &addrlen);
	if (client_socket == INVALID_SOCKET)
	{
		err_display("accept()");
		return;
	}

	// 접속한 클라이언트 정보 출력
	cout << "연걸" << endl;

	

	//// closesocket()
	//closesocket(listen_sock);

	//// 윈속 종료
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

	//	내 정보를 상대 클라이언트에게 넘겨줌

	building.building[0].Info.Pos.fxpos = -building.building[0].Info.Pos.fxpos;
	building.building[1].Info.Pos.fxpos = -building.building[1].Info.Pos.fxpos;
	building.building[2].Info.Pos.fxpos = -building.building[2].Info.Pos.fxpos;

	building.building[0].Info.Pos.fypos = -building.building[0].Info.Pos.fypos;
	building.building[1].Info.Pos.fypos = -building.building[1].Info.Pos.fypos;
	building.building[2].Info.Pos.fypos = -building.building[2].Info.Pos.fypos;


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


	//	상대클라이언트 (적) 의 정보를 받아옴
	retval = recvn(*socket, (char *)&building, sizeof(building), 0);
	if (retval == SOCKET_ERROR)
	{
		err_display("send()");
		return 0;
	}
	//=============================

	m_Enemy = building; // 받아온 정보를 씬에 넘겨줄 enemy

	m_pScene->SetOpponentData(m_Enemy); //씬에 정보를 업데이트

	return 0;

}

void GameFrameWork::ServerRunning()
{
	// 데이터 송수신 시작

	/*for (int i = 0; i < 3; ++i)
	{
		m_Player.building[i] = (m_pScene->m_ppPlayerClass[i]->m_Building);
	}
	m_pScene->m_Player = m_Player;*/
	m_Player = m_pScene->m_Player;

	m_Player.Shield.Pos.fxpos = -m_pScene->shieldXpos;
	m_Player.Shield.Pos.fypos = -m_pScene->shieldYpos;
	RecvFromOpponent(&client_socket, m_Enemy, sizeof(m_Enemy), 0);
	SendToOpponent(&client_socket, m_Player, sizeof(m_Player), 0); //내 정보 보내고



}




//---------------------------------------------------------------------------------
void GameFrameWork::err_quit(char * msg)
{

		LPVOID lpMsgBuf;
		FormatMessage(
			FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
			NULL, WSAGetLastError(),
			MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
			(LPTSTR)&lpMsgBuf, 0, NULL);
		cout << msg << endl;
		LocalFree(lpMsgBuf);
		exit(1);
	
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
	closesocket(listen_sock);

	WSACleanup();
}

