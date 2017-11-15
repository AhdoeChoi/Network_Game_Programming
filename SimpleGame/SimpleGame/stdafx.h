#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>
#include <iostream>
#include <WinSock2.h>

#pragma comment(lib, "ws2_32")


typedef struct pos
{
	float		fxpos;
	float		fypos;
	float		fzpos;
}Pos;

typedef struct player_info
{
	Pos			*pPos;
	int			ihp;
	int			istate; //어떤 종류의 탑인지
	int			isize;
}PInfo;

typedef struct bullet
{
	Pos			*pPos;
	int			isize;
}Bullet;

typedef struct shield
{
	int			ihp;
	Pos			*pPos;
}Shield;

typedef struct building
{
	PInfo		*pInfo;
	Shield		*pShield;
	Bullet		*pBullet;
}Building;

