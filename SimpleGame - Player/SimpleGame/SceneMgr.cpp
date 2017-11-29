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
	

	//m_pPlayer를 채워줘야함(빌드오브젝트한걸로)



	/*플레이어 업데이트*/
	//m_pPlayerClass->Update(m_pPlayer,elapsedTime);


	////////////////////////////

	/*적 업데이트*/

	m_pEnemyClass->Update(m_pEnemy, elapsedTime);
}

void SceneMgr::Render()
{
	//////////////////////////////////////

	//내 정보 그려 m_pPlayer
	//1.내꺼 빌딩 그려
	//2.내꺼 총알 그려


	//m_pPlayerClass->Render();



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


	
	//cout << *BuildObjectFinish << endl;

}
void SceneMgr::Animate()
{

}