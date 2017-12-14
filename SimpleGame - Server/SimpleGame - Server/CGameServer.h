#pragma once
class CGameServer
{
public:
	bool MainServerConnect(SOCKET s); // s�������� ���μ����� ���� �õ�, ������ true
	bool CreateHostServer(SOCKET s, char *name); // s���� ����Ͽ� ���ο� 1:1����� �������ִ� 
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

