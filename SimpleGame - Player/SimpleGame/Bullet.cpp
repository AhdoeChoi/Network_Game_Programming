#include "stdafx.h"
#include "Bullet.h"

BulletObject::BulletObject() : m_hp(0), m_size(0), m_type(0)
{
	m_active = true;
	m_pos.fxpos = 0;
	m_pos.fypos = 0;
	m_pos.fzpos = 0;

	m_vector.fxpos = 0;
	m_vector.fypos = 0;
	m_vector.fzpos = 0;

	m_color.fxpos = 0;
	m_color.fypos = 0;
	m_color.fzpos = 0;
}

BulletObject::BulletObject(int type, float xpos, float ypos, float zpos, float vecx, float vecy, float vecz, int team) :
	m_type(type)
{
	m_active = true;
	m_pos.fxpos = xpos;
	m_pos.fypos = ypos;
	m_pos.fzpos = zpos;

	m_vector.fxpos = vecx;
	m_vector.fypos = vecy;
	m_vector.fzpos = vecz;

	switch (type)
	{
	case TOPA:
		m_hp = 20;
		m_size = 10;
		break;
	case TOPB:
		m_hp = 5;
		m_size = 5;
		break;
	case TOPC:
		m_hp = 50;
		m_size = 50;
		break;
	}		 

	if (team == PLAYER_TEAM)
	{
		m_color.fxpos = 0.0f;
		m_color.fypos = 0.0f;
		m_color.fzpos = 1.0f;
	}
	else
	{
		m_color.fxpos = 1.0f;
		m_color.fypos = 0.0f;
		m_color.fzpos = 0.0f;
	}
}			 

BulletObject::~BulletObject()
{
	m_active = false;
}


void BulletObject::update(Renderer *renderer, float elapsedTime)
{
	m_pos.fxpos += m_vector.fxpos* 0.01* elapsedTime;
	m_pos.fypos += m_vector.fypos*0.01 * elapsedTime;
	m_pos.fzpos += m_vector.fzpos*0.01 * elapsedTime;
	LostBullet();
}

void BulletObject::render(Renderer *renderer)
{
	renderer->DrawSolidRect(m_pos.fxpos, m_pos.fypos, m_pos.fzpos, m_size, m_color.fxpos, m_color.fypos, m_color.fzpos, 1);
}

bool BulletObject::GetActive()
{
	return m_active;
}

void BulletObject::LostBullet()
{
	if (m_pos.fxpos > 250)
		m_active = false;
	else if (m_pos.fxpos < -250)
		m_active = false;
	else if (m_pos.fypos > 400)
		m_active = false;
	else if (m_pos.fypos < -400)
		m_active = false;
}