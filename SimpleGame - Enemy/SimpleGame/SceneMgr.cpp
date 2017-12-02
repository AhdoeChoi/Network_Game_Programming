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
	//m_pPlayer를 채워줘야함(빌드오브젝트한걸로)



	/*플레이어 업데이트*/
	//m_ppPlayerClass->Update(m_pPlayer,elapsedTime);


	////////////////////////////

	/*적 업데이트*/

	m_pEnemyClass->Update(m_Enemy, elapsedTime);
}

void SceneMgr::Render()
{
	//////////////////////////////////////

	//내 정보 그려 m_pPlayer
	//1.내꺼 빌딩 그려
	//2.내꺼 총알 그려


	//m_ppPlayerClass->Render();



	//m_renderer->DrawSolidRect(0/*x좌표*/,
	//	0/*y좌표*/,
	//	0/*z좌표*/,
	//	10/*크기*/,
	//	1/*red*/, 1/*green*/, 1/*blue*/, 1/*alpha*/);

	//////////////////////////////////////

	//적 클라이언트 정보 그려 m_pEnemy
	
	//1. 적 빌딩 그려
	//2. 적 총알 그려

	m_pEnemyClass->Render();
	//m_renderer->DrawSolidRect(m_pEnemy);

}

bool SceneMgr::IsCollide(Bullet & bullet, Building & building)
{
	return false;

	//bullet과 building의 충돌 체크
}

void SceneMgr::SetOpponentData(Buildings enemy)
{
	 m_Enemy = enemy; 
}

void SceneMgr::BuildObject(int xpos, bool *BuildObjectFinish)
{
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



	//배치하는 로직 필요 (마우스클릭하고)

	if (m_ppPlayerClass == NULL)
	{
		m_ppPlayerClass = new Objects*[3];
	}

	if (xpos > -250 && m_iSetPlayerIndex < 3)
	{
		//cout << xpos << endl;
		Objects * pNewObject = new Objects;

		pNewObject->m_Building.Info.Pos.fxpos = xpos;
		//여기를 좀더 자세히 채워야함


		m_ppPlayerClass[m_iSetPlayerIndex] = pNewObject;
		m_iSetPlayerIndex++;

	}

	for (int i = 0; i < m_iSetPlayerIndex; ++i)
	{
		m_renderer->DrawSolidRect(m_ppPlayerClass[i]->m_Building.Info.Pos.fxpos, -40, 0, 50, 1, 0, 0, 1);
	}

	if (m_iSetPlayerIndex == 3) // 배치 완료
	{
		*BuildObjectFinish = true;
	}
}
void SceneMgr::Animate()
{

}

void SceneMgr::CreateBullet(buildings building) // 총알 생성 함수
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