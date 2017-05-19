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
	m_time_until_die = 2.0f;
	m_ground_height = -5.0f;
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

	SDL_GLContext glContext = SDL_GL_CreateContext(m_window);
	if (glContext == nullptr)
	{
		utils.FatalError("The SDL_GL context could not be created!\n");
	}

	GLenum error = glewInit();
	if (error != GLEW_OK)
	{
		utils.FatalError("Could not init glew!\n");
	}
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 4);
	SDL_GL_SetSwapInterval(1);
	SDL_SetWindowFullscreen(m_window, GL_FALSE);
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
		}
	}
	else
	{
		m_time_until_die = 2.0f;
		 //cout << "Alive!!!\n";
	}
	//cout << m_time_until_die << endl;
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
	gluPerspective(60.0f, (GLfloat)m_screen_width / (GLfloat)m_screen_hight, 0.01f, 100000.0f);

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
	}
	else if (m_game_state == GameState::MAINMENU)
	{
		menu.Draw();
	}

	//cout << "X: " << camera.GetPosX() << ",  Y:" << camera.GetPosY() << endl;

	SDL_GL_SwapWindow(m_window);
}

void MainGame::CameraMovementHandler(double elapsed_time)
{
	double distance;
	double dx, dy;
	float slide_speed = 15.0;

	map.HeightMapGrad(camera.GetPosX(), camera.GetPosY(), &dx, &dy);

	float camera_pos_x = camera.GetPosX();
	float camera_pos_y = camera.GetPosY();

	if (camera.GetPosZ() <= m_ground_height + m_character_height + 3)
	{
		camera_pos_x -= dx * elapsed_time * slide_speed;
		camera_pos_y -= dy * elapsed_time * slide_speed;
	}

	camera.SetPosX(camera_pos_x);
	camera.SetPosY(camera_pos_y);

	distance = elapsed_time * m_movement_speed;

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
	GravityHandler(elapsed_time);
	CalculatePlayerDeathTime(elapsed_time);
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
				break;
			}
		}
		else if (m_game_state == GameState::MAINMENU)
		{
			switch (evnt.key.keysym.sym)
			{
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
			if (evnt.type == SDL_MOUSEMOTION)
			{
				SDL_ShowCursor(SDL_DISABLE);
				SDL_WarpMouseInWindow(m_window, m_window_center_x, m_window_center_y);

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
		if (m_game_state == GameState::MAINMENU)
		{
			if (evnt.type == SDL_MOUSEMOTION)
			{
				SDL_ShowCursor(SDL_ENABLE);
				//cout << "x:" << evnt.motion.x << ", y:" << evnt.motion.y << endl;
				if ((evnt.motion.x >= 522) && (evnt.motion.x <= 750) && (evnt.motion.y >= 273) && (evnt.motion.y <= 328))
				{
					menu.OnStartButton();
				}
				else if ((evnt.motion.x >= 522) && (evnt.motion.x <= 750) && (evnt.motion.y >= 359) && (evnt.motion.y <= 411))
				{
					menu.OnQuitButton();
				}
				else
				{
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
					if (!map.loadPlatforms())
					{
						m_game_state = GameState::MAINMENU;
					}
					map.LoadHeightMaps();
					map.loadModels();
					camera.SetPosX(423);
					camera.SetPosY(352);
					camera.SetPosZ(8);
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
	m_ground_height = map.GetPlatformHeight(camera.GetPosX(), camera.GetPosY());

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
	cout << "Z pos: " << camera.GetPosZ() << ", Ground: " << m_ground_height << endl;

    if (camera.GetPosZ() <= m_character_height + m_ground_height) {
		camera.SetPosZ(m_character_height + m_ground_height);
        m_velocity_y = 0.0f;
    }

}
