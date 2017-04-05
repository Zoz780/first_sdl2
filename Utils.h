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
};

