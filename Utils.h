#pragma once
#include <SDL2/SDL.h>
#define _USE_MATH_DEFINES
#include <iostream>
#include <string>

using namespace std;

class Utils
{
public:
	Utils();
	void FatalError(string error);
	float ToRad(float angle_degrees);
	float ToDegree(float angle_rad);
	double CalcElapsedTime();
	void CalculateFrameRate();
	int GetFPS();
	char* GetFPString();

private:
	int m_FPS;
	char m_strFrameRate[35];
	int m_time;
	double elapsed_time_in_secs;
	double m_FrameInterval;
};

