// stdafx.h : 자주 사용하지만 자주 변경되지는 않는
// 표준 시스템 포함 파일 또는 프로젝트 관련 포함 파일이
// 들어 있는 포함 파일입니다.
//

#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>
#include <WinSock2.h>
#include <process.h>
#pragma comment(lib, "ws2_32")

using namespace std;
#include "CGameServer.h"



typedef struct host //생성된 호스트 서버를 저장해 주기 위한 구조체
{
	SOCKADDR_IN ip;
	char name[20];
	int number;
}Host;

typedef struct Player //클라이언트 전적을 저장해주는 구조체
{
	SOCKADDR_IN ip;
	int win;
	int lose;
};

// TODO: 프로그램에 필요한 추가 헤더는 여기에서 참조합니다.
