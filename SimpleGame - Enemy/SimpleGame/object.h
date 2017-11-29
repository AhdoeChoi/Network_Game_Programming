#pragma once
#include "SceneMgr.h"
class Renderer;



typedef struct float3
{
	float x, y, z;
	float3(float a, float b, float c) {
		x = a; y = b; z = c;
	}

	float3 operator+=(const float3& number)
	{
		x = x + number.x;
		y = y + number.y;
		z = z + number.z;
		return float3(x, y, z);
	}
	
	float3 operator*(const float& number)
	{
		x = x * number;
		y = y * number;
		z = z * number;
		return float3(x, y, z);
	}
}float3, vector3;

struct float4
{
	float x, y, z, w;
	float4(float a, float b, float c, float d) {
		x = a; y = b; z = c; w = d;
	}

	float4 operator=(const float4& number)
	{
		x = number.x;
		y = number.y;
		z = number.z;
		w = number.w;

		return float4(x, y, z, w);
	}
};

class Objects
{
public:
	Renderer			*m_renderer;
	Building			m_Building;

	float ArrowCooltime;

	Objects();
	Objects(Building * pBuilding, Renderer * pRenderer);

	~Objects();

	void Render();

	void Update(Building pBuilding , float time);

	void Setvector(float vectorX, float vectorY, float vectorZ);

	void Setposition(float x, float y, float z);

	void SetColor(float r, float g, float b, float a);

	void ColiderCheck(float time);

	void ActiveOn(bool active);

	bool collision(float3 target, float scale);

	float GetCooltime();

	void SetCooltime();

	void SetStandardColor();
};