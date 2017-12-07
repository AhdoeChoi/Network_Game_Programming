#include "stdafx.h"
#include "SceneMgr.h"
#include <random>

SceneMgr::SceneMgr()
{

}

SceneMgr::SceneMgr(int x, int y)
{
	total_frame = 0;

	m_renderer = new Renderer(x, y);
	m_iSetPlayerIndex = 0;

	m_ppPlayerClass = NULL;

	for (int i = 0; i < 3; ++i)
	{
		m_bOverlap[i] = false;
	}
	memset(&m_Enemy, 0, sizeof(m_Enemy));

	m_textureid[0] = m_renderer->CreatePngTexture("TOPA.png");
	m_textureid[1] = m_renderer->CreatePngTexture("TOPB.png");
	m_textureid[2] = m_renderer->CreatePngTexture("TOPC.png");
	map_id = m_renderer->CreatePngTexture("Map.png");
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

	CreateBullet(m_Player);
	CreateBullet(m_Enemy);

	total_frame += elapsedTime;
	if (total_frame > 2000)
	{
		m_Player.building[0].Bullet.IsCoolTime = true;
		m_Player.building[1].Bullet.IsCoolTime = true;
		m_Player.building[2].Bullet.IsCoolTime = true;

		total_frame = 0;
	}
	else
	{
		m_Player.building[0].Bullet.IsCoolTime = false;
		m_Player.building[1].Bullet.IsCoolTime = false;
		m_Player.building[2].Bullet.IsCoolTime = false;
	}


	
	m_Player.Shield.Pos.fxpos = shieldXpos;

	m_Player.Shield.Pos.fypos = shieldYpos;


	/*�÷��̾� ������Ʈ*/
	//m_pPlayerClass->Update(m_pPlayer,elapsedTime);


	////////////////////////////

	/*�� ������Ʈ*/

	m_pEnemyClass->Update(m_Enemy, elapsedTime);
	for (int i = 0; i < 500; i++)
	{
		if (m_pbullet[i])
		{
			m_pbullet[i]->update(m_renderer, elapsedTime);
			if (!m_pbullet[i]->GetActive())
				m_pbullet[i]->~BulletObject();
		}
	}
	
	Animate();
}

void SceneMgr::Render()
{
	//////////////////////////////////////
	//�� �׷�
	m_renderer->DrawTexturedRect(0, 0, 1, 800, 1, 1, 1, 1, map_id);
	//�� ���� �׷� m_pPlayer
	//1.���� ���� �׷�
	for (int i = 0; i < 3; ++i)
	{
		if (m_Player.building[i].Info.istate == TOPA)
			m_renderer->DrawTexturedRect(m_Player.building[i].Info.Pos.fxpos,
				m_Player.building[i].Info.Pos.fypos,
				m_Player.building[i].Info.Pos.fzpos,
				50,
				1, 0, 0, 1,
				m_textureid[0]
			);
		if (m_Player.building[i].Info.istate == TOPB)
			m_renderer->DrawTexturedRect(m_Player.building[i].Info.Pos.fxpos,
				m_Player.building[i].Info.Pos.fypos,
				m_Player.building[i].Info.Pos.fzpos,
				50,
				1, 0, 0, 1,
				m_textureid[1]
			);
		if (m_Player.building[i].Info.istate == TOPC)
			m_renderer->DrawTexturedRect(m_Player.building[i].Info.Pos.fxpos,
				m_Player.building[i].Info.Pos.fypos,
				m_Player.building[i].Info.Pos.fzpos,
				50,
				1, 0, 0, 1,
				m_textureid[2]
			);
	}
	//2.���� �Ѿ� �׷�

	//3.���� ���� �׷�

	if(m_Player.Shield.Pos.fxpos != 0 && m_Player.Shield.Pos.fypos != 0)
	m_renderer->DrawSolidRect(m_Player.Shield.Pos.fxpos,
		m_Player.Shield.Pos.fypos,
		m_Player.Shield.Pos.fzpos,
		50,
		0, 0, 1, 1
	);

	//m_pPlayerClass->Render();



	//m_renderer->DrawSolidRect(0/*x��ǥ*/,
	//	0/*y��ǥ*/,
	//	0/*z��ǥ*/,
	//	10/*ũ��*/,
	//	1/*red*/, 1/*green*/, 1/*blue*/, 1/*alpha*/);

	//////////////////////////////////////

	//�� Ŭ���̾�Ʈ ���� �׷� m_pEnemy
	


	for (int i = 0; i < 3; ++i)
	{
//<<<<<<< HEAD
//=======
		if (m_Enemy.building[i].Info.istate == TOPA)
			m_renderer->DrawTexturedRect(m_Enemy.building[i].Info.Pos.fxpos,
				m_Enemy.building[i].Info.Pos.fypos,
				m_Enemy.building[i].Info.Pos.fzpos,
				50,
				1, 0, 0, 1,
				m_textureid[0]
			);
		if (m_Enemy.building[i].Info.istate == TOPB)
			m_renderer->DrawTexturedRect(m_Enemy.building[i].Info.Pos.fxpos,
				m_Enemy.building[i].Info.Pos.fypos,
				m_Enemy.building[i].Info.Pos.fzpos,
				50,
				1, 0, 0, 1,
				m_textureid[1]
			);
		if (m_Enemy.building[i].Info.istate == TOPC)
			m_renderer->DrawTexturedRect(m_Enemy.building[i].Info.Pos.fxpos,
				m_Enemy.building[i].Info.Pos.fypos,
				m_Enemy.building[i].Info.Pos.fzpos,
				50,
				1, 0, 0, 1,
				m_textureid[2]
			);
//>>>>>>> c84b196718a2d6ae25bcee6ba025a0aff97e8c51
	}
	
	//1. �� ���� �׷�
	//2. �� �Ѿ� �׷�
	// 3. �� ���� �׷�
	if(m_Enemy.Shield.Pos.fxpos!= 0 && m_Enemy.Shield.Pos.fypos)
	m_renderer->DrawSolidRect(m_Enemy.Shield.Pos.fxpos,
		m_Enemy.Shield.Pos.fypos,
		m_Enemy.Shield.Pos.fzpos,
		50,
		1, 1, 1, 1);
	//m_renderer->DrawSolidRect(m_pEnemy);
	for (int i = 0; i < 500; i++)
	{
		if (m_pbullet[i])
			m_pbullet[i]->render(m_renderer);
	}
}

bool SceneMgr::IsCollide(BulletObject * bullet, Building & building)
{
	
	
	
	
	return false;

	//bullet�� building�� �浹 üũ
}

void SceneMgr::SetOpponentData(Buildings  enemy)
{
	 m_Enemy = enemy; 
}

void SceneMgr::BuildObject(int xpos, bool *BuildObjectFinish, int keystate)
{
	//cout << xpos << endl;
	keystate = keystate % 3;
	//cout << keystate << endl;
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
			//m_renderer->DrawSolidRect(0, 100, 0, 50, 1, 0, 0, 1);
			m_renderer->DrawTexturedRect(0, 100, 0, 100, 1, 0, 0, 1, m_textureid[0]);
		if (keystate == 1)
			//m_renderer->DrawSolidRect(0, 100, 0, 50, 0, 1, 0, 1);
			m_renderer->DrawTexturedRect(0, 100, 0, 100, 1, 0, 0, 1, m_textureid[1]);
		if (keystate == 2)
			//m_renderer->DrawSolidRect(0, 100, 0, 50, 0, 0, 1, 1);
			m_renderer->DrawTexturedRect(0, 100, 0, 100, 1, 0, 0, 1, m_textureid[2]);
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
//<<<<<<< HEAD
		//pNewObject->m_Building.Bullet.
//=======

		if (keystate == 0)
			pNewObject->m_Building.Info.istate = TOPA;
		if (keystate == 1)
			pNewObject->m_Building.Info.istate = TOPB;
		if (keystate == 2)
			pNewObject->m_Building.Info.istate = TOPC;

//>>>>>>> 576b14d990433183edde7deaa4612d5d0c275d45

		m_ppPlayerClass[m_iSetPlayerIndex] = pNewObject;
		m_iSetPlayerIndex++;
		
	}

	for (int i = 0; i < m_iSetPlayerIndex; ++i)
	{
		if(m_ppPlayerClass[i]->m_Building.Info.istate == TOPA)
			//m_renderer->DrawSolidRect(m_ppPlayerClass[i]->m_Building.Info.Pos.fxpos, -300, 0, 50, 1, 0, 0, 1);
			m_renderer->DrawTexturedRect(m_ppPlayerClass[i]->m_Building.Info.Pos.fxpos, -300, 0, 50, 1, 0, 0, 1, m_textureid[0]);
		if (m_ppPlayerClass[i]->m_Building.Info.istate == TOPB)
			//m_renderer->DrawSolidRect(m_ppPlayerClass[i]->m_Building.Info.Pos.fxpos, -300, 0, 50, 0, 1, 0, 1);
			m_renderer->DrawTexturedRect(m_ppPlayerClass[i]->m_Building.Info.Pos.fxpos, -300, 0, 50, 1, 0, 0, 1, m_textureid[1]);
		if (m_ppPlayerClass[i]->m_Building.Info.istate == TOPC)
			//m_renderer->DrawSolidRect(m_ppPlayerClass[i]->m_Building.Info.Pos.fxpos, -300, 0, 50, 0, 0, 1, 1);
			m_renderer->DrawTexturedRect(m_ppPlayerClass[i]->m_Building.Info.Pos.fxpos, -300, 0, 50, 1, 0, 0, 1, m_textureid[2]);
	}

	if (m_iSetPlayerIndex == 3) // ��ġ �Ϸ�
	{
		*BuildObjectFinish = true;
		for (int i = 0; i < 3; ++i)
		{
			m_Player.building[i] = (m_ppPlayerClass[i]->m_Building);
		}
	}


	
	//cout << *BuildObjectFinish << endl;

}
void SceneMgr::Animate()
{
	
	
}

void SceneMgr::CreateBullet(buildings building) // �Ѿ� ���� �Լ�
{
	float3 position(0, 0, 0);
	int vecx = 0;
	int vecy = 0;
	int team;

	for (int i = 0; i < 3; i++)
	{
		switch (building.building[i].Info.istate)
		{
		case TOPA:
			if (building.building[i].Bullet.IsCoolTime)
			{
				for (int j = 0; j < 9; j++)
				{
					position.x = building.building[i].Info.Pos.fxpos - 10 * cos((45 + j * 10)*3.14 / 180) * building.building[i].Info.Pos.fypos / abs(building.building[i].Info.Pos.fypos);
					position.y = building.building[i].Info.Pos.fypos - 10 * sin((45 + j * 10)*3.14 / 180) * building.building[i].Info.Pos.fypos / abs(building.building[i].Info.Pos.fypos);

					vecx = position.x - building.building[i].Info.Pos.fxpos;
					vecy = position.y - building.building[i].Info.Pos.fypos;
					if (building.building[i].Info.Pos.fypos > 0)
						team = ENEMY_TEAM;
					else
						team = PLAYER_TEAM;

					BulletObject * newobject = new BulletObject(building.building[i].Info.istate, building.building[i].Info.Pos.fxpos, building.building[i].Info.Pos.fypos, building.building[i].Info.Pos.fzpos,
						vecx, vecy, 0, team);
					for (int k = 0; k < MAX_BULLET_COUNT; k++)
					{
						if (!m_pbullet[k])
						{
							m_pbullet[k] = newobject;
							break;
						}
						else if (!m_pbullet[k]->GetActive())
						{
							m_pbullet[k] = newobject;
							break;
						}
					}
				}
			}
			break;
		case TOPB:
			if (building.building[i].Bullet.IsCoolTime)
			{
				for (int j = 0; j < 6; j++)
				{
					position.x = building.building[i].Info.Pos.fxpos - (((50 - (20 * j))* building.building[i].Info.Pos.fypos / abs(building.building[i].Info.Pos.fypos))* building.building[i].Info.Pos.fypos / abs(building.building[i].Info.Pos.fypos));
					position.y = building.building[i].Info.Pos.fypos - 10 * building.building[i].Info.Pos.fypos / abs(building.building[i].Info.Pos.fypos);

					vecx = 0;
					vecy = position.y - building.building[i].Info.Pos.fypos;
					if (building.building[i].Info.Pos.fypos > 0)
						team = ENEMY_TEAM;
					else
						team = PLAYER_TEAM;

					BulletObject * newobject = new BulletObject(building.building[i].Info.istate, position.x, building.building[i].Info.Pos.fypos, building.building[i].Info.Pos.fzpos,
						vecx, vecy, 0, team);
					for (int k = 0; k < MAX_BULLET_COUNT; k++)
					{
						if (!m_pbullet[k])
						{
							m_pbullet[k] = newobject;
							break;
						}
						else if (!m_pbullet[k]->GetActive())
						{
							m_pbullet[k] = newobject;
							break;
						}
					}
				}
			}
			break;
		case TOPC:
			if (building.building[i].Bullet.IsCoolTime)
			{
				position.x = building.building[i].Info.Pos.fxpos - 60 * building.building[i].Info.Pos.fypos / abs(building.building[i].Info.Pos.fypos);
				position.y = building.building[i].Info.Pos.fypos - 10 * building.building[i].Info.Pos.fypos / abs(building.building[i].Info.Pos.fypos);

				vecx = 0;
				vecy = position.y - building.building[i].Info.Pos.fypos;
				if (building.building[i].Info.Pos.fypos > 0)
					team = ENEMY_TEAM;
				else
					team = PLAYER_TEAM;

				BulletObject * newobject = new BulletObject(building.building[i].Info.istate, building.building[i].Info.Pos.fxpos, building.building[i].Info.Pos.fypos, building.building[i].Info.Pos.fzpos,
					vecx, vecy, 0, team);
				for (int k = 0; k < MAX_BULLET_COUNT; k++)
				{
					if (!m_pbullet[k])
					{
						m_pbullet[k] = newobject;
						break;
					}
					else if (!m_pbullet[k]->GetActive())
					{
						m_pbullet[k] = newobject;
						break;
					}
				}
			}
			break;
		}
		building.building[i].Bullet.IsCoolTime = false;
	}
}