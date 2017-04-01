#include "MainGame.h"
#include <iostream>
#include <string>

using namespace std;

void FatalError(string error)
{
	cout << error << endl;
	cout << "Enter any key to quit...\n";
	int tmp;
	cin >> tmp;
	SDL_QUIT;
}


MainGame::MainGame()
{
	m_window = nullptr;
	m_screen_width = 1280;
	m_screen_hight = 720;
	m_game_state = GameState::PLAY;
}

void MainGame::Run()
{
	Init();
	m_sprite.Init(-1.0f, -1.0f, 1.0f, 1.0f);
	GameLoop();
}

void MainGame::Init()
{
	SDL_Init(SDL_INIT_EVERYTHING);

	m_window = SDL_CreateWindow("FPS Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, m_screen_width, m_screen_hight, SDL_WINDOW_OPENGL);
	if (m_window == nullptr)
	{
		FatalError("The SDL window could not be created!\n");
	}

	SDL_GLContext glContext = SDL_GL_CreateContext(m_window);
	if (glContext == nullptr)
	{
		FatalError("The SDL_GL context could not be created!\n");
	}

	GLenum error = glewInit();
	if (error != GLEW_OK)
	{
		FatalError("Could not init glew!\n");
	}

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	LoadModels();

}

void MainGame::GameLoop()
{
	while (m_game_state != GameState::EXIT)
	{
		ProcessInput();
		DrawGame();
	}

}
void MainGame::ProcessInput()
{
	SDL_Event evnt;

	while (SDL_PollEvent(&evnt))
	{
		switch (evnt.type)
		{
		case SDL_QUIT:
			m_game_state = GameState::EXIT;
			break;
		
		}
	}
}

void MainGame::DrawGame()
{
	glClearDepth(1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//m_sprite.Draw();
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_DEPTH_TEST);
	raptor.draw(1, -5, -5);
	SDL_GL_SwapWindow(m_window);
}

void MainGame::LoadModels()
{
	raptor.load("Models/raptor.obj", 0.12f, "Models/raptor.png");
}
