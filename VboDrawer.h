#pragma once
#include "ModelLoader.h"
#include <glut.h>
class VboDrawer : public Model_loader
{
public:
	VboDrawer();

	void DrawModel(float x, float y, float z);

};

