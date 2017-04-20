#pragma once
#ifndef MAP_H
#define MAP_H

#include "Platform.h"
#include "VboDrawer.h"
#include "Position.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>

#include <vector>

using namespace std;

class Map
{
public:

    /**
     * Construct new map.
     */
    Map();

    /**
     * Calculate the character position from the required position.
     */
    Position CalcReqPosition(const Position& requiredPosition);

    /**
     * Calculate the position from original position and the velocity.
     */
    Position CalcOrigPosition(const Position& position/*, const Velocity& velocity*/);

	void DrawGun();

	void DrawObjects();

	void loadModels();

	float GetPlatformHeight(float x, float z);

	/**
	* Load the platform.
	*/
	void loadPlatforms();

protected:


private:

    /**
     * The platforms for floor collision detection
     */
    std::vector<Platform> m_platforms;

	VboDrawer raptor;
	VboDrawer floor;
	VboDrawer gun;

	Platform platform;
};

#endif MAP_H

