#include "stdafx.h"
#include "SceneMgr.h"
#include <random>

SceneMgr::SceneMgr()
{
}

SceneMgr::SceneMgr(int x, int y)
{
	m_renderer = new Renderer(x, y);
	m_iSetPlayerIndex = 0;

	m_ppPlayerClass = NULL;


	for (int i = 0; i < 3; ++i)
	{
		m_bOverlap[i] = false;
	}
	memset(&m_Enemy, 0, sizeof(m_Enemy));
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
	delete m_pEnemyClass;
}

void SceneMgr::Update(DWORD elapsedTime)
{
	////////////////////////////
	
	if (m_pEnemyClass == NULL)
	{
		m_pEnemyClass = new Objects;
	}
	//m_pPlayer�� ä�������(���������Ʈ�Ѱɷ�)


	m_Player.Shield.Pos.fxpos = shieldXpos;

	m_Player.Shield.Pos.fypos = shieldYpos;

	/*�÷��̾� ������Ʈ*/
	//m_ppPlayerClass->Update(m_pPlayer,elapsedTime);


	////////////////////////////

	/*�� ������Ʈ*/

	m_pEnemyClass->Update(m_Enemy, elapsedTime);
}

void SceneMgr::Render()
{
	//////////////////////////////////////

	//�� ���� �׷� m_pPlayer
	//1.���� ���� �׷�
	for (int i = 0; i < 3; ++i)
	{
		if (m_Player.building[i].Info.istate == TOPA)
			m_renderer->DrawSolidRect(m_Player.building[i].Info.Pos.fxpos,
				m_Player.building[i].Info.Pos.fypos,
				m_Player.building[i].Info.Pos.fzpos,
				50,
				1, 0, 0, 1
			);
		if (m_Player.building[i].Info.istate == TOPB)
			m_renderer->DrawSolidRect(m_Player.building[i].Info.Pos.fxpos,
				m_Player.building[i].Info.Pos.fypos,
				m_Player.building[i].Info.Pos.fzpos,
				50,
				0, 1, 0, 1
			);
		if (m_Player.building[i].Info.istate == TOPC)
			m_renderer->DrawSolidRect(m_Player.building[i].Info.Pos.fxpos,
				m_Player.building[i].Info.Pos.fypos,
				m_Player.building[i].Info.Pos.fzpos,
				50,
				0, 0, 1, 1
			);
	}

	//2.���� �Ѿ� �׷�

	//3.���� ���� �׷�
	if (m_Player.Shield.Pos.fxpos != 0 && m_Player.Shield.Pos.fypos != 0)
		m_renderer->DrawSolidRect(m_Player.Shield.Pos.fxpos,
			m_Player.Shield.Pos.fypos,
			m_Player.Shield.Pos.fzpos,
			50,
			0, 0, 1, 1
		);
	//m_ppPlayerClass->Render();



	//m_renderer->DrawSolidRect(0/*x��ǥ*/,
	//	0/*y��ǥ*/,
	//	0/*z��ǥ*/,
	//	10/*ũ��*/,
	//	1/*red*/, 1/*green*/, 1/*blue*/, 1/*alpha*/);

	//////////////////////////////////////

	//�� Ŭ���̾�Ʈ ���� �׷� m_pEnemy
	
	//1. �� ���� �׷�
	//2. �� �Ѿ� �׷�



	for (int i = 0; i < 3; ++i)
	{
//<<<<<<< HEAD
		m_renderer->DrawSolidRect((-m_Enemy.building[i].Info.Pos.fxpos),
			(-m_Enemy.building[i].Info.Pos.fypos),
			(-m_Enemy.building[i].Info.Pos.fzpos),
			50,
			1, 0, 1, 1
		);
//=======
		if (m_Enemy.building[i].Info.istate == TOPA)
			m_renderer->DrawSolidRect(-m_Enemy.building[i].Info.Pos.fxpos,
				-m_Enemy.building[i].Info.Pos.fypos,
				m_Enemy.building[i].Info.Pos.fzpos,
				50,
				1, 0, 0, 1
			);
		if (m_Enemy.building[i].Info.istate == TOPB)
			m_renderer->DrawSolidRect(-m_Enemy.building[i].Info.Pos.fxpos,
				-m_Enemy.building[i].Info.Pos.fypos,
				m_Enemy.building[i].Info.Pos.fzpos,
				50,
				0, 1, 0, 1
			);
		if (m_Enemy.building[i].Info.istate == TOPC)
			m_renderer->DrawSolidRect(-m_Enemy.building[i].Info.Pos.fxpos,
				-m_Enemy.building[i].Info.Pos.fypos,
				m_Enemy.building[i].Info.Pos.fzpos,
				50,
				0, 0, 1, 1
			);
//>>>>>>> c84b196718a2d6ae25bcee6ba025a0aff97e8c51
	}

	//m_renderer->DrawSolidRect(m_pEnemy);

	// 3. �� ���� �׷�
	if (m_Enemy.Shield.Pos.fxpos != 0 && m_Enemy.Shield.Pos.fypos)
	m_renderer->DrawSolidRect(m_Enemy.Shield.Pos.fxpos,
		m_Enemy.Shield.Pos.fypos,
		m_Enemy.Shield.Pos.fzpos,
		50,
		1, 1, 1, 1
	);
}

bool SceneMgr::IsCollide(Bullet & bullet, Building & building)
{
	return false;

	//bullet�� building�� �浹 üũ
}

void SceneMgr::SetOpponentData(Buildings enemy)
{
	 m_Enemy = enemy; 
}

void SceneMgr::BuildObject(int xpos, bool *BuildObjectFinish, int keystate)
{
	keystate = keystate % 3;
	if (xpos < -80 && xpos > -250)
	{
		if (m_bOverlap[0])
		{
			return;
		}
		xpos = -150;
		m_bOverlap[0] = true;
	}
	else if (xpos > -80 && xpos < 80)
	{
		if (m_bOverlap[1])
		{
			return;
		}
		xpos = 0;
		m_bOverlap[1] = true;
	}
	else if (xpos > 80)
	{
		if (m_bOverlap[2])
		{
			return;
		}
		xpos = 150;
		m_bOverlap[2] = true;
	}

	if (BuildObjectFinish)
	{
		if (keystate == 0)
			m_renderer->DrawSolidRect(0, 100, 0, 50, 1, 0, 0, 1);
		if (keystate == 1)
			m_renderer->DrawSolidRect(0, 100, 0, 50, 0, 1, 0, 1);
		if (keystate == 2)
			m_renderer->DrawSolidRect(0, 100, 0, 50, 0, 0, 1, 1);
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
		pNewObject->m_Building.Info.Pos.fypos = -200;
//<<<<<<< HEAD
//=======

//>>>>>>> c84b196718a2d6ae25bcee6ba025a0aff97e8c51
		//���⸦ ���� �ڼ��� ä������

		if (keystate == 0)
			pNewObject->m_Building.Info.istate = TOPA;
		if (keystate == 1)
			pNewObject->m_Building.Info.istate = TOPB;
		if (keystate == 2)
			pNewObject->m_Building.Info.istate = TOPC;


		m_ppPlayerClass[m_iSetPlayerIndex] = pNewObject;
		m_iSetPlayerIndex++;

	}

	for (int i = 0; i < m_iSetPlayerIndex; ++i)
	{
		if (m_ppPlayerClass[i]->m_Building.Info.istate == TOPA)
			m_renderer->DrawSolidRect(m_ppPlayerClass[i]->m_Building.Info.Pos.fxpos, -300, 0, 50, 1, 0, 0, 1);
		if (m_ppPlayerClass[i]->m_Building.Info.istate == TOPB)
			m_renderer->DrawSolidRect(m_ppPlayerClass[i]->m_Building.Info.Pos.fxpos, -300, 0, 50, 0, 1, 0, 1);
		if (m_ppPlayerClass[i]->m_Building.Info.istate == TOPC)
			m_renderer->DrawSolidRect(m_ppPlayerClass[i]->m_Building.Info.Pos.fxpos, -300, 0, 50, 0, 0, 1, 1);
	}

	if (m_iSetPlayerIndex == 3) // ��ġ �Ϸ�
	{
		*BuildObjectFinish = true;
	}
}
void SceneMgr::Animate()
{

}

void SceneMgr::CreateBullet(buildings building) // �Ѿ� ���� �Լ�
{
	float3 position(0, 0, 0);
	int vecx, vecy;

	for (int i = 0; i < 3; i++)
	{
		switch (building.building[i].Info.istate)
		{
		case TOPA:
			if (building.building->Bullet.IsCoolTime)
			{
				for (int j = 0; j < 9; j++)
				{
					position.x = building.building[i].Info.Pos.fxpos - 40 * cos((45 + j * 10)*3.14 / 180) * building.building[i].Info.Pos.fypos / abs(building.building[i].Info.Pos.fypos);
					position.y = building.building[i].Info.Pos.fypos - 40 * sin((45 + j * 10)*3.14 / 180) * building.building[i].Info.Pos.fypos / abs(building.building[i].Info.Pos.fypos);

					vecx = position.x - building.building[i].Info.Pos.fxpos;
					vecy = position.y - building.building[i].Info.Pos.fypos;

					Objects * newobject = new Objects;
					for (int k = 0; k < MAX_BULLET_COUNT; k++)
					{
						/*if (!m_bullets[k])
						{
						m_bullets[k] = newobject;
						break;
						}
						else if (!m_bullets[k]->m_active)
						{
						m_bullets[k] = newobject;
						break;
						}*/
					}
				}
			}
			break;
		case TOPB:
			if (building.building->Bullet.IsCoolTime)
			{
				for (int j = 0; j < 6; j++)
				{
					position.x = building.building[i].Info.Pos.fxpos - (50 + (20 * j))* building.building[i].Info.Pos.fypos / abs(building.building[i].Info.Pos.fypos);
					position.y = building.building[i].Info.Pos.fypos - 40 * building.building[i].Info.Pos.fypos / abs(building.building[i].Info.Pos.fypos);

					vecx = 0;
					vecy = position.y - building.building[i].Info.Pos.fypos;

					Objects * newobject = new Objects;
					for (int k = 0; k < MAX_BULLET_COUNT; k++)
					{
						/*if (!m_bullets[k])
						{
						m_bullets[k] = newobject;
						break;
						}
						else if (!m_bullets[k]->m_active)
						{
						m_bullets[k] = newobject;
						break;
						}*/
					}
				}
			}
			break;
		case TOPC:
			if (building.building->Bullet.IsCoolTime)
			{
				position.x = building.building[i].Info.Pos.fxpos - 60 * building.building[i].Info.Pos.fypos / abs(building.building[i].Info.Pos.fypos);
				position.y = building.building[i].Info.Pos.fypos - 40 * building.building[i].Info.Pos.fypos / abs(building.building[i].Info.Pos.fypos);

				vecy = position.y - building.building[i].Info.Pos.fypos;

				Objects * newobject = new Objects;
				for (int k = 0; k < MAX_BULLET_COUNT; k++)
				{
					/*if (!m_bullets[k])
					{
					m_bullets[k] = newobject;
					break;
					}
					else if (!m_bullets[k]->m_active)
					{
					m_bullets[k] = newobject;
					break;
					}*/
				}
			}
			break;
		}
	}
}