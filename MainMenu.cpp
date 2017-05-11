#include "MainMenu.h"


MainMenu::MainMenu()
{
}

void MainMenu::Init()
{
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDepthFunc(GL_LESS);

	glEnable(GL_NORMALIZE);
	glEnable(GL_COLOR_MATERIAL);
}

void MainMenu::Load()
{
	menu.Load("Models/floor.obj", 1.8f, 0.5f, 1.0f, "Textures/menu.png");
}

void MainMenu::Draw()
{
	glClearDepth(1.0f);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_TEXTURE_2D);

	glPushMatrix();
	glTranslatef(-1.9, -1.4, 6.9);
	glRotatef(90.0f, 1, 0, 0);
	glRotatef(180.0f, 0, 0, 1);
	menu.DrawModel(0, 0, 0);
	glPopMatrix();
}

