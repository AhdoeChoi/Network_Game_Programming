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
}

BulletObject::BulletObject(int type, float xpos, float ypos, float zpos, float vecx, float vecy, float vecz) :
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
		break;
	case TOPB:
		m_hp = 5;
		break;
	case TOPC:
		m_hp = 50;
		break;
	}		 
}			 

void BulletObject::update(Renderer *renderer)
{
	m_pos.fxpos += m_vector.fxpos;
	m_pos.fypos += m_vector.fypos;
	m_pos.fzpos += m_vector.fzpos;
	render(renderer);
}

void BulletObject::render(Renderer *renderer)
{
	renderer->DrawSolidRect(m_pos.fxpos, m_pos.fypos, m_pos.fzpos, 10, 0, 1, 1, 1);
}

bool BulletObject::GetActive()
{
	return m_active;
}