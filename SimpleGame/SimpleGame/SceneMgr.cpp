#include "stdafx.h"
#include "SceneMgr.h"
#include <random>

SceneMgr::SceneMgr(int x, int y)
{
	m_renderer = new Renderer(x, y);

}

SceneMgr::~SceneMgr()
{

}

void SceneMgr::Update(DWORD elapsedTime)
{
	////////////////////////////

	/*플레이어 업데이트*/

	////////////////////////////

	/*적 업데이트*/
}

void SceneMgr::Render()
{
	//////////////////////////////////////

	//내 정보 그려 m_pPlayer
	//1.내꺼 빌딩 그려
	//2.내꺼 총알 그려

	m_renderer->DrawSolidRect(0/*x좌표*/,
		0/*y좌표*/,
		0/*z좌표*/,
		10/*크기*/,
		1/*red*/, 1/*green*/, 1/*blue*/, 1/*alpha*/);

	//////////////////////////////////////

	//적 클라이언트 정보 그려 m_pEnemy
	
	//1. 적 빌딩 그려
	//2. 적 총알 그려


}

bool SceneMgr::IsCollide(Bullet & bullet, Building & building)
{
	return false;

	//bullet과 building의 충돌 체크
}

void SceneMgr::BuildObject()
{

}
void SceneMgr::Animate()
{

}