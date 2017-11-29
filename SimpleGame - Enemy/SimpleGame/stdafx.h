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
#define SERVERIP   "127.0.0.1"



#define TOPA 1
#define TOPB 2
#define TOPC 3

#define TOPA_BULLET 4
#define TOPB_BULLET 5
#define TOPC_Bullet 6





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
	Pos			Velocity;
	Pos			Pos;
	int			isize;
}Bullet;

typedef struct shield
{
	int			ihp;
	Pos			Pos;
}Shield;

typedef struct building
{
	PInfo		Info;
	Shield		Shield;
	Bullet		Bullet;
}Building;

typedef struct buildings
{
	building	building[3];
}Buildings;