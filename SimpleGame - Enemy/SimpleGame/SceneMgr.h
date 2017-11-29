#pragma once
#pragma comment(lib, "winmm.lib")
#include "object.h"
#include "Renderer.h"
#include <Windows.h>

const int MAX_OBJECTS_COUNT = 11;
const int MAX_BULLET_COUNT = 100;
const int MAX_ARROW_COUNT = 10;
const int OBJECT_BUILDING = 0;
const int OBJECT_CHARACTER = 1;
const int OBJECT_BULLET = 2;
const int OBJECT_ARROW = 3;
class Objects;

class SceneMgr
{
private:
	int					m_iSetPlayerIndex;
private:
	Renderer			*m_renderer;

private:
	Building			*m_pPlayer;
	Building			*m_pEnemy;

	Objects				**m_ppPlayerClass = NULL;
	Objects				*m_pEnemyClass;

public:
	SceneMgr(int x, int y);
	~SceneMgr();
	void				Update(DWORD elapsedTime); // 오브잭트를 update 해주는 함수 (Renderer 포함)
	void				Render();
public: 
	//서버를 위한 함수부분
	void				SetOpponentData(Building *enemy); // 이함수를 실행하면 적 클라에서 받아온 enemy가 채워지면서 이 enemy를 그리면 됨
	void				BuildObject(int xpos, bool *BuildObjectFinish);	// 처음 배치 어떻게 할 것인지, 이 함수 종료하면 데이터 송수신 시작
public:
	bool				IsCollide(Bullet & bullet, Building & building);
	void				Animate(); //충돌검사 , 매 프레임마다 업데이트된 내용을 처리하는 부분
};