#include "stdafx.h"
#include "CGameServer.h"


CGameServer::CGameServer()
{
}


CGameServer::~CGameServer()
{
}

bool CGameServer::MainServerConnect(SOCKET s)
{
	return false;
}

bool CGameServer::CreateHostServer(SOCKET s, char * name)
{
	return false;
}

bool CGameServer::EnterHostServer(int number)
{
	return false;
}

void CGameServer::WaitAnotehrClient()
{
}

bool CGameServer::RefreshHostList()
{
	return false;
}

bool CGameServer::IsChangeClient()
{
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
}

bool CGameServer::SearchHostList(int num)
{
	return false;
}

void CGameServer::SendHostList()
{
}
