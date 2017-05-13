#include "Utils.h"

Utils::Utils()
{
	m_time = 0;
	elapsed_time_in_secs = 0.0;
}

float Utils::ToRad(float angle_degrees) {
	return angle_degrees * M_PI / 180.0f;
}

float Utils::ToDegree(float angle_rad) {
	return (angle_rad * 180.0f) / M_PI;
}

void Utils::FatalError(string error)
{
	cout << error << endl;
	cout << "Enter any key to quit...\n";
	int tmp;
	cin >> tmp;
	SDL_QUIT;
}


double Utils::CalcElapsedTime()
{
	int current_time;
	double elapsed_time;

	current_time = SDL_GetTicks();
	elapsed_time = (double)(current_time - m_time);
	elapsed_time_in_secs = elapsed_time / 1000.0;
	m_time = current_time;

	if (elapsed_time_in_secs < 0.0 || elapsed_time_in_secs > 1.0) {
		elapsed_time_in_secs = 0.0;
	}

	return elapsed_time_in_secs;
}

void Utils::CalculateFrameRate()
{
	static float framesPerSecond = 0.0f;
	static float lastTime = 0.0f;
	static float frameTime = 0.0f;
	float currentTime = SDL_GetTicks() * 0.001f;

	m_FrameInterval = currentTime - frameTime;
	frameTime = currentTime;
	++framesPerSecond;
	if (currentTime - lastTime > 1.0f)
	{
		lastTime = currentTime;
		m_FPS = (int)framesPerSecond;
		sprintf(m_strFrameRate, "FPS Game ---- FPS: %d", m_FPS);
		framesPerSecond = 0.0f;
	}
}

int Utils::GetFPS()
{
	return m_FPS;
}

char* Utils::GetFPString()
{
	return m_strFrameRate;
}

