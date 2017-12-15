#pragma once

#include "MagicNumber.h"


typedef struct host //������ ȣ��Ʈ ������ ������ �ֱ� ���� ����ü
{
	SOCKADDR_IN ip;
	char name[20];
	int number;
}Host;

typedef struct player //Ŭ���̾�Ʈ ������ �������ִ� ����ü
{
	SOCKADDR_IN ip;
	int win;
	int lose;
}Player;


class CGameServer
{
public:
	HANDLE hThread[HANDLECNT]; //���ӿ�û�� Ŭ���̾�Ʈ ������ �ڵ�
public:
	static DWORD WINAPI ProcessClient(LPVOID arg);
public:
	WSADATA wsa;
public: //����
	static SOCKET		client_socket;
	SOCKADDR_IN			clientaddr; //�߰�
	SOCKET				listen_sock; //�߰�
public:
	void err_quit(char * msg);
	static void err_display(char * msg);
	int recvn(SOCKET s, char * buf, int len, int flags);
public:
	void Operation();
	static Host hostlist[100]; // Ŭ���̾�Ʈ ȣ��Ʈ�� ������ ���� �� ����ü
	static int hostnum;

	bool MainServerConnect(SOCKET s); // s�������� ���μ����� ���� �õ�, ������ true
	static bool CreateHostServer(SOCKET s, SOCKADDR_IN client_addr); // s���� ����Ͽ� ���ο� 1:1����� �������ִ� 
												 //������ ������ָ�, �� ������ name�̶�� ������ �����. ������ true
	bool EnterHostServer(int number); //������� number���� ���濡 ������ �õ��Ѵ�. -> ������ true��ȯ, �� ��ȯ
	void WaitAnotehrClient(); // �� �ٸ� Ŭ���̾�Ʈ�� ���� ��û�� ��ٸ���.
	bool RefreshHostList(); // ������� ���� ��� �޾ƿ´�. char*���� ���� �̸���, int ������ ��ȣ�� �޴´�.
	bool IsChangeClient(); //�����

	unsigned int WINAPI RecvClientRequest(LPVOID sock); //��Ƽ �����带 �����ϱ� ���� ������ �Լ�, Ŭ���̾�Ʈ ������ ���ڷ� ��������
	void SaveResult(bool result); // return���� true�� host 1�� ������ ��
	Host AddHostList(char *name); //HostServer�� �����Ѵٴ� ��û�� ������ ������ �̸��� �޾ƿͼ� host IP��
								  //����ִ� ��ȣ�� �Ҵ��ؼ� ����ü�� ���� �� �������ش�.
	bool SearchHostList(int num); //Ư�� �� ��ȣ�� ���� HostServer�� , Ip ��Ʈ��ȣ�� send���ش�.
	void SendHostList(); // ������ ��ϵ� Host�� ��ȣ, �̸��� Send()���ش�.
public:
	CGameServer();
	~CGameServer();
};

