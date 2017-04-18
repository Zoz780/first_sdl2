#pragma once
class Platform
{
public:
	Platform();
	Platform(float height_11, float height_12, float height_21, float height_22, float x1, float x2, float z1, float z2);
	float GetHeight(float x, float z);

	float Height();
	
private:
	bool IsOnPlatform(float x, float z) const;

	float m_height_11; 
	float m_height_12; 
	float m_height_21;
	float m_height_22; 
	float m_x1; 
	float m_x2; 
	float m_z1;
	float m_z2;
};

