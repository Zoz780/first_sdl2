#pragma once
#include <SDL2\SDL.h>
#include "ModelDrawer.h"
#include "Sprite.h"
#include <glut.h>

enum class GameState
{
	PLAY,
	EXIT
};

class MainGame
{
public:
	MainGame();

	void Run();

private:
	//functions
	void Init();
	void GameLoop();
	void ProcessInput();
	void DrawGame();
	void LoadModels();

	SDL_Window* m_window;
	GameState m_game_state;
	int m_screen_width;
	int m_screen_hight;

	Sprite m_sprite;
	Model_drawer raptor;
};

