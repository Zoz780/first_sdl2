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
	loading_scene.Load("Models/floor.obj", 0.9f, 0.2f, 0.5f, "Textures/loading_menu.png");
	marker.Load("Models/floor.obj", 1.0f, 0.05f, 0.09f, "Textures/marker.png");
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
	glTranslatef(6.9, -2.0, -1.36);
	glRotatef(90.0f, 0, 0, 1);
	glRotatef(180.0f, 0, 1, 0);
	menu.DrawModel(0, 0, 0);
	glPopMatrix();

	if (m_menu_state == MenuState::START)
	{
		glPushMatrix();
		glTranslatef(6.2, -1.05, 0.43);
		glRotatef(90.0f, 0, 0, 1);
		glRotatef(180.0f, 0, 1, 0);
		marker.DrawModel(0, 0, 0);
		glPopMatrix();
	}
	if (m_menu_state == MenuState::QUIT)
	{
		glPushMatrix();
		glTranslatef(6.2 , -1.05, -0.4);
		glRotatef(90.0f, 0, 0, 1);
		glRotatef(180.0f, 0, 1, 0);
		marker.DrawModel(0, 0, 0);
		glPopMatrix();
	}
	if (m_menu_state == MenuState::LOADING)
	{
		glPushMatrix();
		glTranslatef(5.9, -1.0, -1.0);
		glRotatef(90.0f, 0, 0, 1);
		glRotatef(180.0f, 0, 1, 0);
		loading_scene.DrawModel(0, 0, 0);
		glPopMatrix();
	}
}

void MainMenu::OnStartButton()
{
	m_menu_state = MenuState::START;
}
void MainMenu::OnQuitButton()
{
	m_menu_state = MenuState::QUIT;
}

void MainMenu::LoadingScene()
{
	m_menu_state = MenuState::LOADING;
}
void MainMenu::DefaultState()
{
	m_menu_state = MenuState::DEFAULT;
}

