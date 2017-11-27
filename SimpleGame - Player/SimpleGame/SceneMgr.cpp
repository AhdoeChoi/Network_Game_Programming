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
	

	//m_pPlayer�� ä�������(���������Ʈ�Ѱɷ�)



	/*�÷��̾� ������Ʈ*/
	m_pPlayerClass->Update(m_pPlayer,elapsedTime);


	////////////////////////////

	/*�� ������Ʈ*/

	m_pEnemyClass->Update(m_pEnemy, elapsedTime);
}

void SceneMgr::Render()
{
	//////////////////////////////////////

	//�� ���� �׷� m_pPlayer
	//1.���� ���� �׷�
	//2.���� �Ѿ� �׷�


	m_pPlayerClass->Render();



	//m_renderer->DrawSolidRect(0/*x��ǥ*/,
	//	0/*y��ǥ*/,
	//	0/*z��ǥ*/,
	//	10/*ũ��*/,
	//	1/*red*/, 1/*green*/, 1/*blue*/, 1/*alpha*/);

	//////////////////////////////////////

	//�� Ŭ���̾�Ʈ ���� �׷� m_pEnemy
	
	//1. �� ���� �׷�
	//2. �� �Ѿ� �׷�

	m_pEnemyClass->Render();
	//m_renderer->DrawSolidRect(m_pEnemy);

}

bool SceneMgr::IsCollide(Bullet & bullet, Building & building)
{
	return false;

	//bullet�� building�� �浹 üũ
}

void SceneMgr::SetOpponentData(Building * enemy)
{
	 m_pEnemy = enemy; 
}

void SceneMgr::BuildObject()
{
	//��ġ�ϴ� ���� �ʿ� (���콺Ŭ���ϰ�)
}
void SceneMgr::Animate()
{

}