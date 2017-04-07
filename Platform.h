#pragma once
class Platform
{
public:
	Platform();
	bool IsOnPlatform(float x, float y) const;
	float BilinearInterpolation(float height_11, float height_12, float height_21, float height_22, float x1, float x2, float z1, float z2, float x, float z);
};

