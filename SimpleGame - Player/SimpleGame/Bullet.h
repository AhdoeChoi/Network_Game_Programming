#pragma once
#include "stdafx.h"
#include "Renderer.h"

class BulletObject
{
private:
	int		m_type;
	pos		m_pos;
	pos		m_vector;
	int		m_hp;
	int		m_size;
	bool	m_active;

public:
	BulletObject();

	BulletObject(int type, float xpos, float ypos, float zpos, float vecx, float vecy, float vecz);

	~BulletObject();

	void		update(Renderer *renderer, float elapsedTime);

	void		render(Renderer *renderer);

	bool		GetActive();
};