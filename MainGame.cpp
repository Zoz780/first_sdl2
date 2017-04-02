#include "MainGame.h"
#include <iostream>
#include <string>
#define _USE_MATH_DEFINES
#include <math.h>

using namespace std;

inline float ToRad(float angle_degrees) {
	return angle_degrees * M_PI / 180.0f;
}

inline float ToDegree(float angle_rad) {
	return (angle_rad * 180.0f) / M_PI;
}

void FatalError(string error)
{
	cout << error << endl;
	cout << "Enter any key to quit...\n";
	int tmp;
	cin >> tmp;
	SDL_QUIT;
}

double MainGame::CalcElapsedTime()
{
	int current_time;
	double elapsed_time;

	current_time = SDL_GetTicks();
	elapsed_time = (double)(current_time - m_time) / 1000.0;
	m_time = current_time;

	return elapsed_time;
}

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
	m_jump_flag = true;
	m_game_state = GameState::PLAY;
}

void MainGame::Run()
{
	Init();
	m_sprite.Init(-1.0f, -1.0f, 0.0f, 1.0f, 1.0f, 0.0f);
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
	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 4);

	LoadModels();

}

void MainGame::GameLoop()
{
	while (m_game_state != GameState::EXIT)
	{
		double elapsed_time;
		elapsed_time = CalcElapsedTime();
		
		ProcessInput();
		DrawGame();
		CameraMovementHandler();
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
	glClearDepth(1.0f);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();
	/*moving, rotating*/glMatrixMode(GL_MODELVIEW);
	float verticalAngle = ToRad(m_camera_x_rot);
	float horizontalAngle = ToRad(m_camera_y_rot);

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

	raptor.draw(0, -2, 20);
	floor.draw(0, 0, 0);

	/*glPushMatrix();
		glRotatef(180.0f, 0, 1, 0);
		glTranslatef(-m_camera_x_pos, m_camera_y_pos, -m_camera_z_pos);
		glRotatef(m_camera_x_rot, 1, 0, 0);
		glRotatef(m_camera_y_rot, 0, 1, 0);
		gun.draw(+0.03f, -0.07f, -0.1f);
	glPopMatrix();*/

	SDL_GL_SwapWindow(m_window);
}

void MainGame::LoadModels()
{
	raptor.load("Models/raptor.obj", 0.5f, "Textures/raptor.png");
	floor.load("Models/floor.obj", 1.0f, "Textures/floor.jpg");
	gun.load("Models/gun.obj", 0.2f, "Textures/gun.tga");
}

void MainGame::CameraMovementHandler()
{
	if (camera.needGoForward()) {
		m_camera_x_pos += (float)sin(ToRad(m_camera_y_rot)) * 0.5f;
		m_camera_z_pos += (float)cos(ToRad(m_camera_y_rot)) * 0.5f;
	}
	if (camera.needGoBackward()) {
		m_camera_x_pos -= (float)sin(ToRad(m_camera_y_rot)) * 0.5f;
		m_camera_z_pos -= (float)cos(ToRad(m_camera_y_rot)) * 0.5f;
	}
	if (camera.needStrafeLeft()) {
		m_camera_x_pos += (float)cos(ToRad(m_camera_y_rot)) * 0.5f;
		m_camera_z_pos += (float)sin(ToRad(m_camera_y_rot)) * -0.5f;
	}
	if (camera.needStrafeRight()) {
		m_camera_x_pos -= (float)cos(ToRad(m_camera_y_rot)) * 0.5f;
		m_camera_z_pos -= (float)sin(ToRad(m_camera_y_rot)) * -0.5f;
	}
	if (camera.needToJump())
	{
		JumpHandler();
	}
	else
	{
		m_jump_flag = true;
		m_gravity = 0.14f;
	}
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
		case 32:
			camera.startJump();
			break;
		case 27:
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
		m_camera_x_rot -= (evnt.motion.y - m_window_center_y) * m_mouse_speed;
		m_camera_y_rot -= (evnt.motion.x - m_window_center_x) * m_mouse_speed;

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

void MainGame::JumpHandler()
{
	const float m_max_jump_height = 3.0f;
	if (m_jump_flag)
	{
		if (m_camera_y_pos < m_max_jump_height)
		{
			m_gravity *= 0.97f;
			m_camera_y_pos += m_gravity;
		}
		else
			m_jump_flag = false;
		
	}
	else
	{
		if (m_camera_y_pos > 0.0f)
		{
			m_gravity *= 1.02f;
			m_camera_y_pos -= m_gravity;
		}
		else
		{
			m_camera_y_pos = 0.0f;
			camera.stopJump();
		}
	}
	//cout << m_camera_y_pos << "Need to: " << camera.needToJump() << endl;
}
