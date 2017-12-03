
#include "stdafx.h"
#include "object.h"
#include "Renderer.h"
//
//Objects::Objects(Building * pBuilding)
//{
//
//}



Objects::Objects()
{
	::ZeroMemory(&m_Building, sizeof(Building));
	m_pBuildings = NULL;
	m_renderer = NULL;

	m_pBuildings = NULL;
	ArrowCooltime = 0;
}

Objects::Objects(Building * pBuilding , Renderer * pRenderer)
{
	//m_Building = pBuilding;
	//m_renderer = pRenderer;


}




Objects::~Objects()
{
	
}

void Objects::Render()
{
	/*if (m_active)
	{
		if (m_type == OBJECT_BUILDING)
			g_Renderer.DrawTexturedRect(m_pos.x, m_pos.y, m_pos.z, size, color.x, color.y, color.z, color.w, image_id);
		else
			g_Renderer.DrawSolidRect(m_pos.x, m_pos.y, m_pos.z, size, color.x, color.y, color.z, color.w);
	}*/

	/*if (m_Building.Info.istate == TOPA)
	{

	}
	else if (m_Building.Info.istate == TOPB)
	{

	}
	else if (m_Building.Info.istate == TOPC)
	{

	}*/

}

void Objects::Update(Buildings buildings,float time)
{
	m_pBuildings = &buildings;

	//m_Building = pBuilding;

	//if (m_active)
	//{
	//	ColiderCheck(time);
	//	if (m_life <= 0)
	//		m_active = false;
	//	/*m_pos += m_vector3 * (time * 0.001f);*/
	//	ArrowCooltime += (time * 0.001f);
	//	m_pos.x = m_pos.x + (m_vector3.x * time * 0.001f);
	//	m_pos.y = m_pos.y + (m_vector3.y * time * 0.001f);

	//}


}

void Objects::Setvector(float vectorX, float vectorY, float vectorZ)
{
	//m_vector3.x = vectorX;
	//m_vector3.y = vectorY;
	//m_vector3.z = vectorZ;
}

void Objects::Setposition(float x, float y, float z)
{
	/*m_pos.x = x;
	m_pos.y = y;
	m_pos.z = z;*/
}

void Objects::ColiderCheck(float time)
{
	/*if (m_vector3.x != 0 && m_pos.x + (m_vector3.x * time * 0.001f) + size/2 > 250)
		m_vector3.x = -m_vector3.x;
	else if(m_vector3.x != 0 && m_pos.x + (m_vector3.x * time * 0.001f) - size/2 < -250)
		m_vector3.x = -m_vector3.x;

	if (m_vector3.y != 0 && m_pos.y + (m_vector3.y * time * 0.001f) + size/2 > 250)
		m_vector3.y = -m_vector3.y;
	else if (m_vector3.y != 0 && m_pos.y + (m_vector3.y * time * 0.001f) - size/2 < -250)
		m_vector3.y = -m_vector3.y;*/
}

void Objects::ActiveOn(bool active)
{
	//m_active = active;
}

bool Objects::collision(float3 target, float scale)
{
	/*if (m_pos.x + size / 2 > target.x - scale / 2 && m_pos.x - size / 2 < target.x + scale / 2 &&
		m_pos.y + size / 2 > target.y - scale / 2 && m_pos.y - size / 2 < target.y + scale / 2)
		return true;
	else
		return false;*/
	return false;
}

void Objects::SetColor(float r, float g, float b, float a)
{
	/*color.x = r;
	color.y = g;
	color.z = b;
	color.w = a;*/
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
	//if (m_type == OBJECT_BUILDING)
	//	color = float4(1, 1, 0, 1);

	//else if (m_type == OBJECT_CHARACTER)
	//	color = float4(1, 1, 1, 1);

	//else if (m_type == OBJECT_BULLET)
	//	color = float4(1, 0, 0, 1);

	//else if (m_type == OBJECT_ARROW)
	//	color = float4(0, 1, 0, 1);

}