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

void SceneMgr::AddObject(float x, float y, float z)
{
}

void SceneMgr::Collion()
{
	
}

void SceneMgr::Update()
{
	m_time_b = timeGetTime();
	m_deltime = m_time_b - m_time_a;
	m_time_a = m_time_b;
	Collion();
}

void SceneMgr::CreatBullet()
{
	
}