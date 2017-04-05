#include "Utils.h"

Utils::Utils()
{
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

