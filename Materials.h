#pragma once
#include <glut.h>
class Color
{
public:
	double red;
	double green;
	double blue;
};

class OneMaterial
{
public:
	Color ambient;
	Color diffuse;
	Color specular;
	double shininess;
};


class Materials
{
public:
	Materials();
	void SetMaterial();
	void SetMaterialValues();

private:
	OneMaterial material;
};

