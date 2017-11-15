#include "stdafx.h"
#include "GameFrameWork.h"


GameFrameWork::GameFrameWork()
{
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
}