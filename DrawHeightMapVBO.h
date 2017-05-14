#pragma once
#include "HeightMap.h"
#include <glut.h>
class DrawHeightMapVBO : public HeightMap3D
{
public:
	DrawHeightMapVBO();

	void DrawHeightMap();

	void draw_height_map_old();
};

