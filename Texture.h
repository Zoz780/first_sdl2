#pragma once
#include <glut.h>
#include <SOIL.h>
class Texture
{
public:
	Texture();

	bool Load(const char* filename);

	GLuint GetTexture();

private:
	GLuint texture;
};

