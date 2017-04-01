#pragma once
#include <SDL2\SDL.h>
#include "ModelDrawer.h"
#include "Camera.h"
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
	double CalcElapsedTime();

	SDL_Window* m_window;
	GameState m_game_state;
	int m_screen_width;
	int m_screen_hight;

	Sprite m_sprite;
	Model_drawer raptor;
	Camera camera;

	float x, y, z;
	float m_camera_x_pos;
	float m_camera_y_pos;
	float m_camera_z_pos;
	float m_camera_x_rot;
	float m_camera_y_rot;
	float m_camera_z_rot;

	int m_time;
};

