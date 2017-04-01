#include "MainGame.h"
#include <iostream>
#include <string>
#define _USE_MATH_DEFINES
#include <math.h>

using namespace std;

inline float ToRad(float angle_degrees) {
	return angle_degrees * M_PI / 180.0f;
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
	m_game_state = GameState::PLAY;
	x = 0.0f;
	y = 0.0f;
	z = 0.0f;
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

		if (camera.needGoForward()) {
			m_camera_x_pos += (float)sin(ToRad(m_camera_y_rot)) * 0.02f;
			m_camera_z_pos += (float)cos(ToRad(m_camera_y_rot)) * 0.02f;
		}
		if (camera.needGoBackward()) {
			m_camera_x_pos -= (float)sin(ToRad(m_camera_y_rot)) * 0.02f;
			m_camera_z_pos -= (float)cos(ToRad(m_camera_y_rot)) * 0.02f;
		}
		if (camera.needStrafeLeft()) {
			m_camera_x_pos += (float)cos(ToRad(m_camera_y_rot)) * 0.02f;
			m_camera_z_pos += (float)sin(ToRad(m_camera_y_rot)) * -0.02f;
		}
		if (camera.needStrafeRight()) {
			m_camera_x_pos -= (float)cos(ToRad(m_camera_y_rot)) * 0.02f;
			m_camera_z_pos -= (float)sin(ToRad(m_camera_y_rot)) * -0.02f;
		}
		if (camera.needLookUp()) {
			if (m_camera_x_rot >= 87.0f) {
				m_camera_x_rot = 87.0f;
			}
			else {
				m_camera_x_rot += 1.0f;
			}
		}
		if (camera.needLookDown()) {
			if (m_camera_x_rot <= -87.0f) {
				m_camera_x_rot = -87.0f;
			}
			else {
				m_camera_x_rot -= 1.0f;
			}
		}
		if (camera.needTurnLeft()) {
			m_camera_y_rot += 1.0f;
		}
		if (camera.needTurnRight()) {
			m_camera_y_rot -= 1.0f;
		}
	}

}
void MainGame::ProcessInput()
{
	SDL_Event evnt;

	while (SDL_PollEvent(&evnt))
	{
		if (evnt.type == SDL_QUIT)
		{
			m_game_state = GameState::EXIT;
		}
		//User presses a key
		else if (evnt.type == SDL_KEYDOWN)
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
			case 'i':
				camera.startLookUp();
				break;
			case 'k':
				camera.startLookDown();
				break;
			case 'j':
				camera.startTurnLeft();
				break;
			case 'l':
				camera.startTurnRight();
				break;
			}
		}
		else if (evnt.type == SDL_KEYUP)
		{
			//Select surfaces based on key press
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
			case 'i':
				camera.stopLookUp();
				break;
			case 'k':
				camera.stopLookDown();
				break;
			case 'j':
				camera.stopTurnLeft();
				break;
			case 'l':
				camera.stopTurnRight();
				break;
			}
		}
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
	gluPerspective(45.0f, (GLfloat)m_screen_width / (GLfloat)m_screen_hight, 0.1f, 1000.0f);
	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	raptor.draw(x, y, z);
	//cout << "x: " << x << "; y: " << y << "; z: " << z << endl;

	SDL_GL_SwapWindow(m_window);
}

void MainGame::LoadModels()
{
	raptor.load("Models/raptor.obj", 0.009f, "Models/raptor.png");
}
