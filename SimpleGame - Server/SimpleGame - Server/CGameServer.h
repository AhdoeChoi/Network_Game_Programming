#pragma once
class CGameServer
{
public:
	bool MainServerConnect(SOCKET s); // s소켓으로 메인서버에 연결 시도, 성공시 true
	bool CreateHostServer(SOCKET s, char *name); // s소켓 사용하여 새로운 1:1통신을 지원해주는 
												 //서버를 만들어주며, 그 서버는 name이라는 대기방을 만든다. 성공시 true
	bool EnterHostServer(int number); //만들어진 number번의 대기방에 참가를 시도한다. -> 성공시 true반환, 씬 전환
	void WaitAnotehrClient(); // 또 다른 클라이언트의 접속 요청을 기다린다.
	bool RefreshHostList(); // 만들어진 대기방 목록 받아온다. char*형의 대기방 이름과, int 형태의 번호를 받는다.
	bool IsChangeClient(); //지울듯

	unsigned int WINAPI RecvClientRequest(LPVOID sock); //멀티 쓰레드를 지원하기 위한 쓰레드 함수, 클라이언트 소켓을 인자로 받은다음
	void SaveResult(bool result); // return값이 true면 host 1승 참가자 패
	Host AddHostList(char *name); //HostServer를 생성한다는 요청을 받으면 대기실의 이름을 받아와서 host IP와
								  //비어있는 번호를 할당해서 구조체를 만든 후 리턴해준다.
	bool SearchHostList(int num); //특정 방 번호를 가진 HostServer의 , Ip 포트번호를 send해준다.
	void SendHostList(); // 서버에 등록된 Host의 번호, 이름을 Send()해준다.
public:
	CGameServer();
	~CGameServer();
};

