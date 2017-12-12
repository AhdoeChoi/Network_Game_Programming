#pragma once
#include "stdafx.h"
#include "Renderer.h"

class BulletObject
{
public:
	int		m_team;
	int		m_type;
	pos		m_pos;
	pos		m_vector;
	pos		m_color;
	int		m_hp;
	int		m_size;
	bool	m_active;

public:
	BulletObject();

	BulletObject(int type, float xpos, float ypos, float zpos, float vecx, float vecy, float vecz, int team);

	~BulletObject();

	void		update(Renderer *renderer, float elapsedTime);

	void		render(Renderer *renderer, int texture);

	bool		GetActive();

	void		LostBullet();

	bool		collision(pos target, int size);
};