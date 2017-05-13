#pragma once
typedef unsigned char Pixel[3];

class Vec3
{
public:
	Vec3();

	void SetX(double x);
	double GetX();

	void SetY(double y);
	double GetY();

	void SetZ(double z);
	double GetZ();

	double x;
	double y;
	double z;
};

