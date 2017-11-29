#include "stdafx.h"
#include "SceneMgr.h"
#include <random>

SceneMgr::SceneMgr(int x, int y)
{
	m_renderer = new Renderer(x, y);
	m_iSetPlayerIndex = 0;

}

SceneMgr::~SceneMgr()
{
	if (m_ppPlayerClass)
	{
		for (int j = 0; j < m_iSetPlayerIndex; j++)
			if (m_ppPlayerClass[j])
			{
				delete m_ppPlayerClass[j];
			
			}
		delete[] m_ppPlayerClass;

	}
}

void SceneMgr::Update(DWORD elapsedTime)
{
	////////////////////////////
	

	//m_pPlayer�� ä�������(���������Ʈ�Ѱɷ�)



	/*�÷��̾� ������Ʈ*/
	//m_pPlayerClass->Update(m_pPlayer,elapsedTime);


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


	//m_pPlayerClass->Render();



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

void SceneMgr::BuildObject(int xpos, bool *BuildObjectFinish)
{
	//cout << xpos << endl;
	if (xpos < -80 && xpos > -250)
	{
		xpos = -150;
	}
	else if (xpos > -80 && xpos < 80)
	{
		xpos = 0;
	}
	else if (xpos > 80)
	{
		xpos = 150;
	}



	//��ġ�ϴ� ���� �ʿ� (���콺Ŭ���ϰ�)
	
	if (m_ppPlayerClass == NULL)
	{
		m_ppPlayerClass = new Objects*[3];
	}

	if (xpos > -250 && m_iSetPlayerIndex < 3)
	{
		//cout << xpos << endl;
		Objects * pNewObject = new Objects;

		pNewObject->m_Building.Info.Pos.fxpos = xpos;


		m_ppPlayerClass[m_iSetPlayerIndex] = pNewObject;
		m_iSetPlayerIndex++;
		
	}

	for (int i = 0; i < m_iSetPlayerIndex; ++i)
	{
		m_renderer->DrawSolidRect(m_ppPlayerClass[i]->m_Building.Info.Pos.fxpos, -40, 0, 50, 1, 0, 0, 1);
	}

	if (m_iSetPlayerIndex == 3) // ��ġ �Ϸ�
	{
		*BuildObjectFinish = true;
	}


	
	//cout << *BuildObjectFinish << endl;

}
void SceneMgr::Animate()
{

}