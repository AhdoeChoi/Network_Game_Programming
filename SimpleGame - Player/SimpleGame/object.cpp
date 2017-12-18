
#include "stdafx.h"
#include "object.h"
#include "Renderer.h"


Objects::Objects()
{
	::ZeroMemory(&m_Building, sizeof(Building));
	::ZeroMemory(&m_Buildings, sizeof(Buildings));
	m_renderer = NULL;

	m_pBuildings = NULL;
	 ArrowCooltime = 0;
}

Objects::Objects(Buildings * pBuildings , Renderer * pRenderer)
{
}

Objects::~Objects()
{
}

void Objects::Render()
{
}

void Objects::Update(Buildings  buildings ,float time)
{
	m_pBuildings = &buildings;
}

void Objects::Setvector(float vectorX, float vectorY, float vectorZ)
{
}

void Objects::Setposition(float x, float y, float z)
{
}

void Objects::ColiderCheck(float time)
{
}

void Objects::ActiveOn(bool active)
{
}

bool Objects::collision(float3 target, float scale)
{
	return false;
}

void Objects::SetColor(float r, float g, float b, float a)
{
}

float Objects::GetCooltime()
{
	return ArrowCooltime;
}

void Objects::SetCooltime()
{
	ArrowCooltime = 0;
}

void Objects::SetStandardColor()
{
}