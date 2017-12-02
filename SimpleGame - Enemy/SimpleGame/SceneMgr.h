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
	bool				m_bOverlap[3];
private:
	Renderer			*m_renderer;

public:
	Buildings			m_Player;
	Buildings			m_Enemy;


	Objects				*m_pEnemyClass = NULL;

	Objects				**m_ppPlayerClass;

public:
	SceneMgr();
	SceneMgr(int x, int y);
	~SceneMgr();
	void				Update(DWORD elapsedTime); // ������Ʈ�� update ���ִ� �Լ� (Renderer ����)
	void				Render();
public: 
	//������ ���� �Լ��κ�
	void				SetOpponentData(Buildings enemy); // ���Լ��� �����ϸ� �� Ŭ�󿡼� �޾ƿ� enemy�� ä�����鼭 �� enemy�� �׸��� ��
	void				BuildObject(int xpos, bool * BuildObjectFinish, int keystate);	// ó�� ��ġ ��� �� ������, �� �Լ� �����ϸ� ������ �ۼ��� ����
public:
	bool				IsCollide(Bullet & bullet, Building & building);	
	void				Animate(); //�浹�˻� , �� �����Ӹ��� ������Ʈ�� ������ ó���ϴ� �κ�
	void				CreateBullet(buildings building); //�Ѿ� ����
};