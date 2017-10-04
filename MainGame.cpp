#include "MainGame.h"
#include <iostream>

using namespace std;

MainGame::MainGame()
{
	m_window = nullptr;
	m_screen_width = 1280;
	m_screen_hight = 720;
	m_mouse_speed = 0.05;
	m_movement_speed = 40.0f;
	m_game_state = GameState::MAINMENU;
    m_gravity = -90.0f;
    m_velocity_y = 0.0f;
	m_character_height = 8.0f;
	m_time_until_die = 5.0f;
	m_ground_height = -50.0f;
	m_time_bw_steps = 0.3;
	m_select_loop = 0;
	m_crosshair_distance = 3;
	m_trap_z_position = 0;
	m_trap = false;
	m_trap_anim = false;
	death_anim_time = 0.5f;
	m_time_after_trapped = 2.0f;
	m_die_sound_loop = 0;
	m_trap_sound_loop = 0;
	ingame_elements = IngameElements2D(m_screen_width, m_screen_hight);
}

void MainGame::Run()
{
	Init();
	GameLoop();
}

void MainGame::Init()
{
	SDL_Init(SDL_INIT_EVERYTHING);
	m_window = SDL_CreateWindow("FPS Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, m_screen_width, m_screen_hight, SDL_WINDOW_OPENGL);
	if (m_window == nullptr)
	{
		utils.FatalError("The SDL window could not be created!\n");
	}
	else
		cout << "The SDL window is created!\n";

	SDL_GLContext glContext = SDL_GL_CreateContext(m_window);
	if (glContext == nullptr)
	{
		utils.FatalError("The SDL_GL context could not be created!\n");
	}
	else
		cout << "The SDL_GL context window is created!\n";

	GLenum error = glewInit();
	if (error != GLEW_OK)
	{
		utils.FatalError("Could not init glew!\n");
	}
	else
		cout << "Glew is initalized!\n";

	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);

	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 32);

	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 2);

	SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);

	glEnable(GL_MULTISAMPLE);

	cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_HAND);
	SDL_SetCursor(cursor);

	SDL_GL_SetSwapInterval(1);
	SDL_SetWindowFullscreen(m_window, GL_TRUE);
	if((!sound.Init()) || (!sound.Load()))
	{
		utils.FatalError("Could not load or missing audio files!");
	}
	else
		cout << "All audio files loaded sucessfully!\n";
	sound.PlayMenuMusic();
	menu.Init();
	menu.Load();
}

void MainGame::GameLoop()
{
	while (m_game_state != GameState::EXIT)
	{
		double elapsed_time;
		elapsed_time = utils.CalcElapsedTime();

		if (m_game_state == GameState::PLAY)
		{
			CameraMovementHandler(elapsed_time);
		}
		ProcessInput();
		DrawGame();
	}
}

void MainGame::CalculatePlayerDeathTime(double elapsed_time)
{
	if (action.needToMove() == false)
	{
		m_time_until_die -= elapsed_time;
		if (m_time_until_die <= 0.0f)
		{
			 //cout << "Died!!!\n";
			m_trap = true;
			sound.StopMusic();
			m_trap_sound_loop++;
			if (m_trap_sound_loop == 1)
			{
				sound.PlayTrappedSound();
			}
		}
	}
	else
	{
		m_time_until_die = 5.0f;
		m_trap_sound_loop = 0;
		m_trap = false;
		 //cout << "Alive!!!\n";
	}
	//cout << m_time_until_die << endl;
}

void MainGame::CalcPlayerInTrapTime(double elapsed_time)
{
	m_time_after_trapped -= elapsed_time;
	if (m_time_after_trapped <= 0.0f)
	{
		m_trap_anim = true;
		m_die_sound_loop++;
		if (m_die_sound_loop == 1)
		{
			sound.PlayPlayerDieSound();
		}
	}
}

void MainGame::ProcessInput()
{
	while (SDL_PollEvent(&evnt))
	{
		if (evnt.type == SDL_QUIT)
		{
			m_game_state = GameState::EXIT;
		}
		ProcessKeyPress();
		ProcessKeyRelease();
		MouseMotionHandler();	
	}
}

void MainGame::DrawGame()
{
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);

	camera.set_view_point();

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if ((m_trap_anim) && (m_ground_height <= -2.0f))
	{
		gluPerspective(60.0f, (GLfloat)m_screen_width / (GLfloat)m_screen_hight, 0.01f, 3.0f);
	}
	else
		gluPerspective(60.0f, (GLfloat)m_screen_width / (GLfloat)m_screen_hight, 0.01f, 100000.0f);
	glColor4f(1.0, 1.0, 1.0, 1.0);

	if (m_game_state == GameState::PLAY)
	{
		camera.set_game_area();
		map.DrawObjects();

		float gun_pose = camera.GetPoseX();

		glPushMatrix();
			glTranslatef(camera.GetPosX(), camera.GetPosY(), camera.GetPosZ());
			glRotatef(camera.GetPoseY(), 0, 0, 1);
			glRotatef(-gun_pose, 0, 1, 0);
			map.DrawGun();
		glPopMatrix();

		if (m_trap)
		{
			if (m_trap_anim)
			{
				camera.rotate_camera(0, -7, -0.5f);
			}
			m_trap_z_position = map.GetPlatformHeight(camera.GetPosX(), camera.GetPosY());
			glPushMatrix();
				glTranslatef(camera.GetPosX(), camera.GetPosY(), m_trap_z_position);
				map.DrawTrap();
			glPopMatrix();
		}
	}
	else if (m_game_state == GameState::MAINMENU)
	{
		menu.Draw();
	}

	glPushMatrix();
	glViewport(0, 0, m_screen_width, m_screen_hight);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, m_screen_width, m_screen_hight, 0, -1, 1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	if (m_game_state == GameState::PLAY)
	{
		if (action.needToMove())
		{
			m_crosshair_distance = 12;
		}
		if (camera.GetPosZ() >= m_ground_height + m_character_height + 2)
		{
			m_crosshair_distance = 60;
		}
		if ((action.needToMove()) && (camera.GetPosZ() >= m_ground_height + m_character_height + 2))
		{
			m_crosshair_distance = 60;
		}
		if ((!action.needToMove()) && (camera.GetPosZ() < m_ground_height + m_character_height + 2))
			m_crosshair_distance = 3;

		ingame_elements.DrawCrosshair(m_crosshair_distance);
		ingame_elements.DrawHud();
	}
	glPopMatrix();
	
	//cout << "X: " << camera.GetPosX() << ",  Y:" << camera.GetPosY() << endl;

	SDL_GL_SwapWindow(m_window);
}

void MainGame::CameraMovementHandler(double elapsed_time)
{
	double distance, sound_lateness;
	double dx, dy;
	float slide_speed = 15.0f;

	map.HeightMapGrad(camera.GetPosX(), camera.GetPosY(), &dx, &dy);

	float camera_pos_x = camera.GetPosX();
	float camera_pos_y = camera.GetPosY();

	if (camera.GetPosZ() <= m_ground_height + m_character_height + 4)
	{
		camera_pos_x -= dx * elapsed_time * slide_speed;
		camera_pos_y -= dy * elapsed_time * slide_speed;
	}

	camera.SetPosX(camera_pos_x);
	camera.SetPosY(camera_pos_y);

	distance = elapsed_time * m_movement_speed;

	if (!m_trap)
	{
		if (((action.needGoForward()) || (action.needGoBackward()) || (action.needStrafeLeft()) || (action.needStrafeRight()))
			&& (camera.GetPosZ() <= m_ground_height + m_character_height + 0.4)
			&& (!action.needToCrouch()))
		{
			if (action.needToRun())
			{
				if (m_time_bw_steps < 0.25)
				{
					m_time_bw_steps += elapsed_time;
				}
				else
				{
					sound.PlaySteps();
					m_time_bw_steps = 0.0;
				}
			}
			else
			{
				if (m_time_bw_steps < 0.3)
				{
					m_time_bw_steps += elapsed_time;
				}
				else
				{
					sound.PlaySteps();
					m_time_bw_steps = 0.0;
				}
			}
		}

		if (action.needGoForward()) {
			camera.move_camera_forward(distance);
			action.playerMoving();
		}
		else
		{
			action.playerNotMoving();
		}

		if (action.needGoBackward()) {
			camera.move_camera_backward(distance);
			action.playerMoving();
		}


		if (action.needStrafeLeft()) {
			camera.step_camera_left(distance);
			action.playerMoving();
		}


		if (action.needStrafeRight()) {
			camera.step_camera_right(distance);
			action.playerMoving();
		}

		if (action.needToRun())
		{
			m_movement_speed = 50.0f;
		}
		else
			m_movement_speed = 40.0f;
		if (action.needToCrouch())
		{
			if (m_character_height >= 5.5f)
			{
				m_character_height -= 25.0f * elapsed_time;
				//cout << m_character_height << endl;
			}
			m_movement_speed = 15.0f;
		}
		else
		{
			if (m_character_height < 8.0f)
			{
				m_character_height += 15.0f * elapsed_time;
				//cout << m_character_height << endl;
			}
		}
	}

	GravityHandler(elapsed_time);
	CalculatePlayerDeathTime(elapsed_time);
	if (m_trap)
	{
		CalcPlayerInTrapTime(elapsed_time);
	}
}

void MainGame::ProcessKeyPress()
{
	if (evnt.type == SDL_KEYDOWN)
	{
		if (m_game_state == GameState::PLAY)
		{
			//Select surfaces based on key press
			switch (evnt.key.keysym.sym)
			{
			case 'w':
				action.startGoForward();
				break;
			case 's':
				action.startGoBackward();
				break;
			case 'a':
				action.startStrafeLeft();
				break;
			case 'd':
				action.startStrafeRight();
				break;
			case SDLK_KP_PLUS:
				sound.VolumeUp();
				break;
			case SDLK_KP_MINUS:
				sound.VolumeDown();
				break;
			case SDLK_LSHIFT:
				action.startRun();
				break;
			case SDLK_LCTRL:
				action.startCrouch();
				break;
			case SDLK_SPACE:
				if (camera.GetPosZ() <= m_character_height + m_ground_height + 0.2) {
					m_velocity_y = 40.0f;
				}
				break;
			case SDLK_ESCAPE:
				m_game_state = GameState::MAINMENU;
				menu.Init();
				menu.Load();
				camera.SetPosX(0);
				camera.SetPosY(0);
				camera.SetPosZ(0);
				camera.SetPoseX(0);
				camera.SetPoseY(0);
				map.FreeHeightMaps();
				sound.StopMusic();
				m_ground_height = 0.0f;
				sound.PlayMenuMusic();
				break;
			}
		}
		else if (m_game_state == GameState::MAINMENU)
		{
			switch (evnt.key.keysym.sym)
			{
			case SDLK_KP_PLUS:
				sound.MenuVolumeUp();
				break;
			case SDLK_KP_MINUS:
				sound.MenuVolumeDown();
				break;
			case SDLK_ESCAPE:
				m_game_state = GameState::EXIT;
				exit(0);
				break;
			}
		}
	}
}

void MainGame::ProcessKeyRelease()
{
	if (evnt.type == SDL_KEYUP)
	{
		//Select surfaces based on key release
		switch (evnt.key.keysym.sym)
		{
		case 'w':
			action.stopForward();
			break;
		case 's':
			action.stopBackward();
			break;
		case 'a':
			action.stopStrafeLeft();
			break;
		case 'd':
			action.stopStrafeRight();
			break;
		case SDLK_LCTRL:
			action.stopCrouch();
			break;
		case SDLK_LSHIFT:
			action.stopRun();
			break;
		}
	}
}

void MainGame::MouseMotionHandler()
{
	float m_window_center_x = m_screen_width / 2;
	float m_window_center_y = m_screen_hight / 2;

	float delta_rotate_y, delta_rotate_x;

		if (m_game_state == GameState::PLAY)
		{
			SDL_ShowCursor(SDL_DISABLE);
			SDL_WarpMouseInWindow(m_window, m_window_center_x, m_window_center_y);
			if (!m_trap_anim)
			{
				if (evnt.type == SDL_MOUSEMOTION)
				{

					delta_rotate_x = evnt.motion.x - m_window_center_x;
					delta_rotate_y = evnt.motion.y - m_window_center_y;

					camera.rotate_camera(delta_rotate_x, delta_rotate_y, m_mouse_speed);

				}
				if (evnt.type == SDL_MOUSEWHEEL)
				{
					if ((evnt.wheel.y == 1) && (m_mouse_speed < 0.5f))
					{
						m_mouse_speed += 0.02;
						//cout << "Mouse speed: " << m_mouse_speed << endl;
					}
					else if ((evnt.wheel.y == -1) && (m_mouse_speed > 0.02f))
					{
						m_mouse_speed -= 0.02;
						//cout << "Mouse speed: " << m_mouse_speed << endl;
					}
					//cout << "y: " << evnt.wheel.y << endl;
				}
			}
		}
		if (m_game_state == GameState::MAINMENU)
		{
			if (evnt.type == SDL_MOUSEMOTION)
			{
				SDL_ShowCursor(SDL_ENABLE);
				//cout << "x:" << evnt.motion.x << ", y:" << evnt.motion.y << endl;
				if ((evnt.motion.x >= 522) && (evnt.motion.x <= 750) && (evnt.motion.y >= 273) && (evnt.motion.y <= 328))
				{
					m_select_loop++;
					menu.OnStartButton();
					if (m_select_loop == 1)
					{
						sound.PlayMenuSelectSound();
					}
				}
				else if ((evnt.motion.x >= 522) && (evnt.motion.x <= 750) && (evnt.motion.y >= 359) && (evnt.motion.y <= 411))
				{
					m_select_loop++;
					menu.OnQuitButton();
					if (m_select_loop == 1)
					{
						sound.PlayMenuSelectSound();
					}
				}
				else
				{
					m_select_loop = 0;
					menu.DefaultState();
				}
			}
			if (evnt.type == SDL_MOUSEBUTTONUP)
			{
				if ((evnt.button.x >= 522) && (evnt.button.x <= 750) && (evnt.button.y >= 273) && (evnt.button.y <= 328))
				{
					menu.LoadingScene();
					m_game_state = GameState::PLAY;
					map.initMap();
					/*if (!map.loadPlatforms())
					{
						m_game_state = GameState::MAINMENU;
					}*/
					m_time_until_die = 5.0f;
					death_anim_time = 0.5f;
					m_trap = false;
					m_trap_anim = false;
					m_time_after_trapped = 2.0f;
					ingame_elements.Init();
					map.LoadHeightMaps();
					map.loadModels();
					camera.SetPosX(423);
					camera.SetPosY(352);
					camera.SetPosZ(8);
					sound.StopMusic();
					sound.PlayIngameMusic();
					m_trap_sound_loop = 0;
					m_die_sound_loop = 0;
				}
				else if ((evnt.button.x >= 522) && (evnt.button.x <= 750) && (evnt.button.y >= 359) && (evnt.button.y <= 411))
				{
					m_game_state = GameState::EXIT;
					exit(0);
				}
			}
			if (evnt.type == SDL_MOUSEBUTTONDOWN)
			{
				if ((evnt.button.x >= 522) && (evnt.button.x <= 750) && (evnt.button.y >= 273) && (evnt.button.y <= 328))
				{
					menu.LoadingScene();
				}
				else
				{
					menu.DefaultState();
				}
			}
		}
}

void MainGame::GravityHandler(double elapsed_time)
{
    //cout << elapsed_time << endl;
    
    m_velocity_y += m_gravity * elapsed_time;
	float camera_z = camera.GetPosZ();
	camera_z += m_velocity_y * elapsed_time;
	camera.SetPosZ(camera_z);

	if (m_trap_anim)
	{
		death_anim_time -= elapsed_time;
		if (death_anim_time <= 0.0f)
		{
			m_ground_height = -250.0f;
		}
	}
	else
	{
		m_ground_height = map.GetPlatformHeight(camera.GetPosX(), camera.GetPosY());
	}

	if (camera.GetPosZ() > m_character_height + m_ground_height)
	{
		if (action.needToRun())
		{
			m_movement_speed = 35.0f;
		}
		else
			m_movement_speed = 25.0f;
	}

    //cout << "Velocity y: " << m_velocity_y << endl;
	//cout << "Z pos: " << camera.GetPosZ() << ", Ground: " << m_ground_height << endl;

    if (camera.GetPosZ() <= m_character_height + m_ground_height) {
		camera.SetPosZ(m_character_height + m_ground_height);
        m_velocity_y = 0.0f;
    }
}
