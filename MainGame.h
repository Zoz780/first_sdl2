#pragma once
#include "Action.h"
#include "Camera.h"
#include "Sound.h"
#include "MainMenu.h"
#include "Map.h"
#include "Utils.h"
#include "IngameElements2D.h"
#include <SDL2/SDL.h>

enum class GameState
{
	PLAY,
	MAINMENU,
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
	void CameraMovementHandler(double elapsed_time);
	void MouseMotionHandler();
	void ProcessKeyPress();
	void GravityHandler(double elapsed_time);
	void ProcessKeyRelease();
	void CalculatePlayerDeathTime(double elapsed_time);
	void CalcPlayerInTrapTime(double elapsed_time);

	SDL_Window *m_window;
	SDL_Cursor* cursor;
	SDL_Event evnt;
	GameState m_game_state;
	int m_screen_width;
	int m_screen_hight;

	Map map;
	MainMenu menu;

	Action action;
	Camera camera;
	Sound sound;
	Utils utils;
	IngameElements2D ingame_elements;

	float m_time_bw_steps;
	int m_select_loop;
	float m_mouse_speed;
	float m_movement_speed;
	float m_gravity;
	float m_ground_height;
	float m_character_height;
	float m_time_until_die;
    float m_velocity_y;
	bool m_trap;
	bool m_trap_anim;
	float m_time_after_trapped;
	float m_trap_z_position;
	float death_anim_time;
	int m_die_sound_loop, m_trap_sound_loop;
	int m_crosshair_distance;
};

