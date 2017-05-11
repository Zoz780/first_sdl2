#pragma once
#include "VboDrawer.h"
#include <iostream>
#include <glut.h>
#include <SOIL.h>

using namespace std;
class MainMenu
{
public:
	MainMenu();

	void Init();

	void Load();

	void Draw();

private:

	VboDrawer menu;

};

