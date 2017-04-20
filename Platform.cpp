#include "Platform.h"

Platform::Platform()
{
	
}

Platform::Platform(float height_11, float height_12, float height_21, float height_22, float x1, float x2, float z1, float z2)
{
	m_height_11 = height_11;
	m_height_12 = height_12;
	m_height_21 = height_21;
	m_height_22 = height_22;
	m_x1 = x1;
	m_x2 = x2;
	m_z1 = z1;
	m_z2 = z2;
}

bool Platform::IsOnPlatform(float x, float z) const
{
	if((x >= m_x1) && (x <= m_x2) && (z >= m_z1) && (z <= m_z2))
	{
		return true;
	}
	else
		return false;
}

float Platform::GetHeight(float x, float z) const
{
	if(IsOnPlatform(x,z))
	{
		float actual_height;
		float distance_x2x1, distance_z2z1, distance_x2x, distance_z2z, distance_xx1, distance_zz1;
		distance_x2x1 = m_x2 - m_x1;
		distance_z2z1 = m_z2 - m_z1;
		distance_x2x = m_x2 - x;
		distance_z2z = m_z2 - z;
		distance_xx1 = x - m_x1;
		distance_zz1 = z - m_z1;
		actual_height = 1.0 / (distance_x2x1 * distance_z2z1) * (
				m_height_11 * distance_x2x * distance_z2z +
				m_height_21 * distance_xx1 * distance_z2z +
				m_height_12 * distance_x2x * distance_zz1 +
				m_height_22 * distance_xx1 * distance_zz1);
		return actual_height;
	}
	else
	{
		return 0;
	}
}
