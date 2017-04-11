#include "ModelLoader.h"
#include <glut.h>

#pragma once
class VboDrawer : public Model_loader
{
public:
	VboDrawer();
	~VboDrawer();

	void DrawModel(float x, float y, float z);

};

