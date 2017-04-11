#include "MainGame.h"
#include <iostream>

using namespace std;

MainGame::MainGame()
{
	m_window = nullptr;
	m_screen_width = 1280;
	m_screen_hight = 720;
	m_camera_x_pos = 0;
	m_camera_y_pos = 0;
	m_camera_z_pos = 0;
	m_camera_x_rot = 0;
	m_camera_y_rot = 0;
	m_mouse_speed = 0.05;
	m_movement_speed = 20.0f;
	m_game_state = GameState::PLAY;
    m_gravity = -60.0f;
	m_ground_height = 0.0f;
    m_velocity_y = 0.0f;
	m_character_height = 3.0f;
	m_time_until_die = 2.0f;
	m_ground_height = 0.0f;
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
	SDL_GL_SetSwapInterval(0);
	LoadModels();

}

void MainGame::GameLoop()
{
	while (m_game_state != GameState::EXIT)
	{
		double elapsed_time;
		elapsed_time = utils.CalcElapsedTime();

		ProcessInput();
		DrawGame();
		CameraMovementHandler(elapsed_time);
	}
}

void MainGame::CalculatePlayerDeathTime(double elapsed_time)
{
	if (camera.needToMove() == false)
	{
		m_time_until_die -= elapsed_time;
		if (m_time_until_die <= 0.0f)
		{
			// cout << "Died!!!\n";
		}
	}
	else
	{
		m_time_until_die = 2.0f;
		// cout << "Alive!!!\n";
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
	glClearDepth(1.0f);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();
	/*moving, rotating*/glMatrixMode(GL_MODELVIEW);
	float verticalAngle = utils.ToRad(m_camera_x_rot);
	float horizontalAngle = utils.ToRad(m_camera_y_rot);

	float dx = cos(verticalAngle) * sin(horizontalAngle);
	float dy = sin(verticalAngle);
	float dz = cos(verticalAngle) * cos(horizontalAngle);

	float cx = m_camera_x_pos + dx, cy = m_camera_y_pos + dy, cz = m_camera_z_pos + dz;
	gluLookAt(m_camera_x_pos, m_camera_y_pos, m_camera_z_pos, cx, cy, cz, 0, 1, 0);/*moving, rotating end*/
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f, (GLfloat)m_screen_width / (GLfloat)m_screen_hight, 0.01f, 1000.0f);
	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	raptor.DrawModel(0, 5, 100);
	floor.DrawModel(0, 0, 0);

	//floor.draw(0, 0, 0);

	glPushMatrix();
		glRotatef(180.0f, 0, 1, 0);
		glTranslatef(-m_camera_x_pos, m_camera_y_pos, -m_camera_z_pos);
		glRotatef(m_camera_y_rot, 0, 1, 0);
		glRotatef(m_camera_x_rot, 1, 0, 0);
		gun.DrawModel(+0.03f, -0.07f, -0.1f);
	glPopMatrix();

	SDL_GL_SwapWindow(m_window);
}

void MainGame::LoadModels()
{
	raptor.Load("Models/raptor.obj", 0.5f, 0.5f, 0.5f, "Textures/raptor.png");
	floor.Load("Models/floor.obj", 1.0f, 1.0f, 1.0f, "Textures/floor.jpg");
	gun.Load("Models/gun.obj", 0.2f, 0.2f, 0.2f, "Textures/gun.tga");
}

void MainGame::CameraMovementHandler(double elapsed_time)
{
	//cout << camera.needToMove() << endl;
	if (camera.needGoForward()) {
		m_camera_x_pos += (float)sin(utils.ToRad(m_camera_y_rot)) * m_movement_speed * elapsed_time;
		m_camera_z_pos += (float)cos(utils.ToRad(m_camera_y_rot)) * m_movement_speed * elapsed_time;
		camera.playerMoving();
	}
	else
	{
		camera.playerNotMoving();
	}

	if (camera.needGoBackward()) {
		m_camera_x_pos -= (float)sin(utils.ToRad(m_camera_y_rot)) * m_movement_speed * elapsed_time;
		m_camera_z_pos -= (float)cos(utils.ToRad(m_camera_y_rot)) * m_movement_speed * elapsed_time;
		camera.playerMoving();
	}


	if (camera.needStrafeLeft()) {
		m_camera_x_pos += (float)cos(utils.ToRad(m_camera_y_rot)) * m_movement_speed * elapsed_time;
		m_camera_z_pos += (float)sin(utils.ToRad(m_camera_y_rot)) * -m_movement_speed * elapsed_time;
		camera.playerMoving();
	}


	if (camera.needStrafeRight()) {
		m_camera_x_pos -= (float)cos(utils.ToRad(m_camera_y_rot)) * m_movement_speed * elapsed_time;
		m_camera_z_pos -= (float)sin(utils.ToRad(m_camera_y_rot)) * -m_movement_speed * elapsed_time;
		camera.playerMoving();
	}

	if (camera.needToRun())
	{
		m_movement_speed = 30.0f;
	}
	else
		m_movement_speed = 20.0f;
	if (camera.needToCrouch())
	{
		if (m_character_height >= 2.0f)
		{
			m_character_height -= 12.0f * elapsed_time;
			//cout << m_character_height << endl;
		}
		m_movement_speed = 12.0f;
	}
	else
	{
		if (m_character_height <= 3.0f)
		{
			m_character_height += 6.0f * elapsed_time;
			//cout << m_character_height << endl;
		}
	}
	CalculatePlayerDeathTime(elapsed_time);
	GravityHandler(elapsed_time);
}

void MainGame::ProcessKeyPress()
{
	if (evnt.type == SDL_KEYDOWN)
	{
		//Select surfaces based on key press
		switch (evnt.key.keysym.sym)
		{
		case 'w':
			camera.startGoForward();
			break;
		case 's':
			camera.startGoBackward();
			break;
		case 'a':
			camera.startStrafeLeft();
			break;
		case 'd':
			camera.startStrafeRight();
			break;
		case SDLK_LSHIFT:
			camera.startRun();
			break;
		case SDLK_LCTRL:
			camera.startCrouch();
			break;
		case SDLK_SPACE:
            if (m_camera_y_pos <= m_character_height + m_ground_height) {
                m_velocity_y = 16.0f;
            }
			break;
		case SDLK_ESCAPE:
			m_game_state = GameState::EXIT;
			exit(0);
			break;
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
			camera.stopForward();
			break;
		case 's':
			camera.stopBackward();
			break;
		case 'a':
			camera.stopStrafeLeft();
			break;
		case 'd':
			camera.stopStrafeRight();
			break;
		case SDLK_LCTRL:
			camera.stopCrouch();
			break;
		case SDLK_LSHIFT:
			camera.stopRun();
			break;
		}
	}
}

void MainGame::MouseMotionHandler()
{
	float m_window_center_x = m_screen_width / 2;
	float m_window_center_y = m_screen_hight / 2;

	if (evnt.type == SDL_MOUSEMOTION)
	{	
		SDL_ShowCursor(SDL_DISABLE);
		SDL_WarpMouseInWindow(m_window, m_window_center_x, m_window_center_y);
		m_camera_x_rot -= (float)(evnt.motion.y - m_window_center_y) * m_mouse_speed;
		m_camera_y_rot -= (float)(evnt.motion.x - m_window_center_x) * m_mouse_speed;

		if (m_camera_x_rot >= 87.0f)
		{
			m_camera_x_rot = 87.0f;
		}
		if (m_camera_x_rot <= -87.0f)
		{
			m_camera_x_rot = -87.0f;
		}
		//cout << "x: " << m_camera_x_rot << "; y: " << m_camera_y_rot << endl;
	}
	else if (evnt.type == SDL_MOUSEWHEEL)
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

void MainGame::GravityHandler(double elapsed_time)
{
    //cout << elapsed_time << endl;
    
    m_velocity_y += m_gravity * elapsed_time;
    m_camera_y_pos += m_velocity_y * elapsed_time;

	//Bilinear interpolation test code
	if ((m_camera_z_pos > 30.0f) && (m_camera_z_pos < 50.0f))
	{
		m_ground_height = platform.GetHeight(0, 5, 0, 5, -10, 10, 30, 50, m_camera_x_pos, m_camera_z_pos);
	}
	else if (m_camera_z_pos >= 50.0f)
	{
		m_ground_height = 5.0f;
	}
	else if (m_camera_z_pos <= 30.0f)
	{
		m_ground_height = 0.0f;
	}
	//Bilinear interpolation test code end

    if (m_camera_y_pos <= m_character_height + m_ground_height) {
        m_camera_y_pos = m_character_height + m_ground_height;
        m_velocity_y = 0.0f;
    }
}
