#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>
#include <iostream>
#include <WinSock2.h>
#pragma comment(lib, "ws2_32")

using namespace std;

////////// const define은 여기에
#define SERVERPORT 9000
#define TOPA 1
#define TOPB 2
#define TOPC 3

#define TOPA_BULLET 4
#define TOPB_BULLET 5
#define TOPC_Bullet 6

#define PLAYER_TEAM 0
#define ENEMY_TEAM 1

#define DIR_LEFT			0x04
#define DIR_RIGHT			0x08
#define DIR_UP				0x10
#define DIR_DOWN			0x20

#define PLAYER_SIZE			50
#define MAX_HOST_NUM 10
#define SERVERIP   "127.0.0.1"
////////// 구조체 선언은 여기에 

typedef struct pos
{
	float		fxpos;
	float		fypos;
	float		fzpos;
}Pos;

typedef struct player_info
{
	Pos			Pos;
	int			ihp;
	int			istate; //어떤 종류의 탑인지
	int			isize;
}PInfo;

typedef struct bullet
{
	bool		IsCoolTime;
}Bullet;

typedef struct shield
{
	int			ihp;
	Pos			Pos;
	Bullet		Bullet;
}Shield;

typedef struct building
{
	PInfo		Info;

	Bullet		Bullet;
}Building;

typedef struct buildings
{
	building	building[3];
	Shield		Shield;
}Buildings;


typedef struct host //생성된 호스트 서버를 저장해 주기 위한 구조체
{
	SOCKADDR_IN ip;
	char name[20];
	int number;
}Host;
