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

	/*�÷��̾� ������Ʈ*/

	////////////////////////////

	/*�� ������Ʈ*/
}

void SceneMgr::Render()
{
	//////////////////////////////////////

	//�� ���� �׷� m_pPlayer
	//1.���� ���� �׷�
	//2.���� �Ѿ� �׷�

	m_renderer->DrawSolidRect(0/*x��ǥ*/,
		0/*y��ǥ*/,
		0/*z��ǥ*/,
		10/*ũ��*/,
		1/*red*/, 1/*green*/, 1/*blue*/, 1/*alpha*/);

	//////////////////////////////////////

	//�� Ŭ���̾�Ʈ ���� �׷� m_pEnemy
	
	//1. �� ���� �׷�
	//2. �� �Ѿ� �׷�


}

bool SceneMgr::IsCollide(Bullet & bullet, Building & building)
{
	return false;

	//bullet�� building�� �浹 üũ
}

void SceneMgr::BuildObject()
{

}
void SceneMgr::Animate()
{

}