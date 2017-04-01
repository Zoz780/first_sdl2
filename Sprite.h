#pragma once
#include <glew.h>
class Sprite
{
public:
	Sprite();
	~Sprite();

	void Init(float x, float y, float z, float width, float height, float depth);
	void Draw();

private:
	float m_x;
	float m_y;
	float m_z;
	float m_width;
	float m_height;
	float m_depth;
	GLuint m_vboID;
};

