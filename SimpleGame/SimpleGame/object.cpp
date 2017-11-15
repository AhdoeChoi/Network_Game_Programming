
#include "stdafx.h"
#include "object.h"
#include "Renderer.h"

Objects::Objects() : m_pos(0,0,0), color(1,1,1,1), m_vector3(0,0,0)
{
	m_active = false;
	size = 0;
}

Objects::Objects(int type, bool active, float x, float y, float z, float vectorX, float vectorY, float vectorZ,int image) :
	m_type(type), m_pos(x, y, z), m_vector3(vectorX, vectorY, vectorZ), color(0, 0, 0, 1), size(10), image_id(image)
{

	m_active = active;
	if (type == OBJECT_BUILDING)
	{
		m_life = 500.0f;
		size = 50;
		color = float4(1, 1, 0, 1);
	}
	else if (type == OBJECT_CHARACTER)
	{
		m_life = 10.0f;
		color = float4(1, 1, 1, 1);
		size = 10;
	}
	else if (type == OBJECT_BULLET)
	{
		m_life = 20.0f;
		color = float4(1, 0, 0, 1);
		size = 2;
	}
	else if (type == OBJECT_ARROW)
	{
		m_life = 10.0f;
		color = float4(0, 1, 0, 1);
		size = 2;
	}
}

Objects::~Objects()
{
	m_active = false;
}

void Objects::Render(Renderer& g_Renderer)
{
	if (m_active)
	{
		if (m_type == OBJECT_BUILDING)
			g_Renderer.DrawTexturedRect(m_pos.x, m_pos.y, m_pos.z, size, color.x, color.y, color.z, color.w, image_id);
		else
			g_Renderer.DrawSolidRect(m_pos.x, m_pos.y, m_pos.z, size, color.x, color.y, color.z, color.w);
	}
}

void Objects::Update(float time)
{
	if (m_active)
	{
		ColiderCheck(time);
		if (m_life <= 0)
			m_active = false;
		/*m_pos += m_vector3 * (time * 0.001f);*/
		ArrowCooltime += (time * 0.001f);
		m_pos.x = m_pos.x + (m_vector3.x * time * 0.001f);
		m_pos.y = m_pos.y + (m_vector3.y * time * 0.001f);

	}
}

void Objects::Setvector(float vectorX, float vectorY, float vectorZ)
{
	m_vector3.x = vectorX;
	m_vector3.y = vectorY;
	m_vector3.z = vectorZ;
}

void Objects::Setposition(float x, float y, float z)
{
	m_pos.x = x;
	m_pos.y = y;
	m_pos.z = z;
}

void Objects::ColiderCheck(float time)
{
	if (m_vector3.x != 0 && m_pos.x + (m_vector3.x * time * 0.001f) + size/2 > 250)
		m_vector3.x = -m_vector3.x;
	else if(m_vector3.x != 0 && m_pos.x + (m_vector3.x * time * 0.001f) - size/2 < -250)
		m_vector3.x = -m_vector3.x;

	if (m_vector3.y != 0 && m_pos.y + (m_vector3.y * time * 0.001f) + size/2 > 250)
		m_vector3.y = -m_vector3.y;
	else if (m_vector3.y != 0 && m_pos.y + (m_vector3.y * time * 0.001f) - size/2 < -250)
		m_vector3.y = -m_vector3.y;
}

void Objects::ActiveOn(bool active)
{
	m_active = active;
}

bool Objects::collision(float3 target, float scale)
{
	if (m_pos.x + size / 2 > target.x - scale / 2 && m_pos.x - size / 2 < target.x + scale / 2 &&
		m_pos.y + size / 2 > target.y - scale / 2 && m_pos.y - size / 2 < target.y + scale / 2)
		return true;
	else
		return false;
}

void Objects::SetColor(float r, float g, float b, float a)
{
	color.x = r;
	color.y = g;
	color.z = b;
	color.w = a;
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
	if (m_type == OBJECT_BUILDING)
		color = float4(1, 1, 0, 1);

	else if (m_type == OBJECT_CHARACTER)
		color = float4(1, 1, 1, 1);

	else if (m_type == OBJECT_BULLET)
		color = float4(1, 0, 0, 1);

	else if (m_type == OBJECT_ARROW)
		color = float4(0, 1, 0, 1);

}