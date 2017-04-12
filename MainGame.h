#pragma once
#include <SDL2/SDL.h>
#include "VboDrawer.h"
#include "Camera.h"
#include "Platform.h"
#include "Utils.h"
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
	void CameraMovementHandler(double elapsed_time);
	void MouseMotionHandler();
	void ProcessKeyPress();
	void GravityHandler(double elapsed_time);
	void ProcessKeyRelease();
	void CalculatePlayerDeathTime(double elapsed_time);

	SDL_Window* m_window;
	SDL_Event evnt;
	GameState m_game_state;
	int m_screen_width;
	int m_screen_hight;
	
	VboDrawer raptor;
	VboDrawer floor;
	VboDrawer gun;

	Camera camera;
	Utils utils;
	Platform platform1;

	float m_camera_x_pos;
	float m_camera_y_pos;
	float m_camera_z_pos;
	float m_camera_x_rot;
	float m_camera_y_rot;

	float m_mouse_speed;
	float m_movement_speed;
	float m_gravity;
	float m_ground_height;
	float m_character_height;
	float m_time_until_die;

    float m_velocity_y;
};

