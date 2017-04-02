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
	void CameraMovementHandler();
	void MouseMotionHandler();
	void ProcessKeyPress();
	void JumpHandler();
	void ProcessKeyRelease();
	double CalcElapsedTime();

	SDL_Window* m_window;
	SDL_Event evnt;
	GameState m_game_state;
	int m_screen_width;
	int m_screen_hight;

	Sprite m_sprite;
	Model_drawer raptor;
	Model_drawer floor;
	Model_drawer gun;
	Camera camera;

	float m_camera_x_pos;
	float m_camera_y_pos;
	float m_camera_z_pos;
	float m_camera_x_rot;
	float m_camera_y_rot;

	float m_mouse_speed;
	float m_gravity = 0.14f;
	bool m_jump_flag;

	int m_time;
};

