#include "stdafx.h"
#include "GameFrameWork.h"


GameFrameWork::GameFrameWork()
{
	//대기방에서 할 작업들


	// 대기방을 위한 코드로 채워야함


	///////////////////// 클라끼리의 송수신

	int retval;

	// 윈속 초기화
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
	//bind()에 첫번째 인자 listen_sock은 클라이언트 접속을 수용할 목적으로 만든 소켓으로, 지역 IP 주소와 지역 포트번호가 아직 결정되지 않은 상태임

	if (retval == SOCKET_ERROR) err_quit("bind()");

	// listen()
	retval = listen(listen_sock, SOMAXCONN);
	if (retval == SOCKET_ERROR)
	{
		err_quit("listen()");
	}
	// 데이터 통신에 사용할 변수
	client_socket;
	SOCKADDR_IN clientaddr;
	int addrlen;





	while (1) {
		// accept()
		addrlen = sizeof(clientaddr);
		client_socket = accept(listen_sock, (SOCKADDR *)&clientaddr /*접속한 클라이언트의 주소정보로 채워짐*/, &addrlen);
		if (client_socket == INVALID_SOCKET) {
			err_display("accept()");
			break;
		}

		// 접속한 클라이언트 정보 출력
		cout << "연걸" << endl;

		// 데이터 송수신 시작

		m_pScene->BuildObject(); //처음 배치 어떻게 할것인지, 배치 끝나면 데이터 송수신 시작
		

		while (1) {
			//RecvFromOpponent(); // 상대방 정보 받아와
			//SendToOpponent(); // 내정보 상대방에게 보내

			//m_pScene->Update(); // 받아온 상대방 정보로 Scene을 업데이트
			//m_pScene->Render(); // Update된 정보를 그려


		}

		// closesocket()
		closesocket(client_socket);
		/*printf("[TCP 서버] 클라이언트 종료: IP 주소=%s, 포트 번호=%d\n",
			inet_ntoa(clientaddr.sin_addr), ntohs(clientaddr.sin_port));*/
	}

	// closesocket()
	closesocket(listen_sock);

	// 윈속 종료
	WSACleanup();


}


GameFrameWork::~GameFrameWork()
{


}

int	GameFrameWork::SendToOpponent(SOCKET socket, Building * building, int len, int flag)
{

	return 0;

	// ================================

	//	내 정보를 상대 클라이언트에게 넘겨줌

	// ================================
}
int	GameFrameWork::RecvFromOpponent(SOCKET socket, Building * building, int len, int flag)
{

	return 0;

	//=============================



	//	상대클라이언트 (적) 의 정보를 받아옴
	

	
	//=============================

	m_pEnemy = building; // 받아온 정보를 씬에 넘겨줄 enemy

	m_pScene->SetOpponentData(m_pEnemy); //씬에 정보를 업데이트

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
