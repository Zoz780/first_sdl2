#pragma once
#include <glew.h>
#include "Texture.h"
class IngameElements2D
{
public:
	IngameElements2D();

	IngameElements2D(int window_width, int window_height);

	void Init();

	void DrawCrosshair(int crosshair_distance);

	void DrawHud();

private:
	Texture ingame_hud;
	GLuint vbo;

	int screen_width;
	int	screen_height;

};

