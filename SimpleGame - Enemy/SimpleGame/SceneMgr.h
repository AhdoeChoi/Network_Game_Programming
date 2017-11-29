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
	void				Update(DWORD elapsedTime); // ������Ʈ�� update ���ִ� �Լ� (Renderer ����)
	void				Render();
public: 
	//������ ���� �Լ��κ�
	void				SetOpponentData(Building *enemy); // ���Լ��� �����ϸ� �� Ŭ�󿡼� �޾ƿ� enemy�� ä�����鼭 �� enemy�� �׸��� ��
	void				BuildObject(int xpos, bool *BuildObjectFinish);	// ó�� ��ġ ��� �� ������, �� �Լ� �����ϸ� ������ �ۼ��� ����
public:
	bool				IsCollide(Bullet & bullet, Building & building);
	void				Animate(); //�浹�˻� , �� �����Ӹ��� ������Ʈ�� ������ ó���ϴ� �κ�
};