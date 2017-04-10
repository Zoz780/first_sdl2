#include "Platform.h"


Platform::Platform()
{
}

bool Platform::IsOnPlatform(float x, float y) const
{
	return true;
}

float Platform::GetHeight(float height_11, float height_12, float height_21, float height_22, float x1, float x2, float z1, float z2, float x, float z)
{

	float actual_height;
	float distance_x2x1, distance_z2z1, distance_x2x, distance_z2z, distance_xx1, distance_zz1;
	distance_x2x1 = x2 - x1;
	distance_z2z1 = z2 - z1;
	distance_x2x = x2 - x;
	distance_z2z = z2 - z;
	distance_xx1 = x - x1;
	distance_zz1 = z - z1;
	actual_height = 1.0 / (distance_x2x1 * distance_z2z1) * (
		height_11 * distance_x2x * distance_z2z +
		height_21 * distance_xx1 * distance_z2z +
		height_12 * distance_x2x * distance_zz1 +
		height_22 * distance_xx1 * distance_zz1);
	return actual_height;
}
