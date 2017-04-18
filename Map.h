#pragma once
#ifndef MAP_H
#define MAP_H

#include "Platform.h"
#include "VboDrawer.h"
#include "Position.h"

#include <vector>

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

	void GetPlatformHeight();

protected:

    /**
     * Load the platform.
     */
    void loadPlatforms();


private:

    /**
     * The platforms for floor collision detection
     */
    std::vector<Platform> m_platforms;

	VboDrawer raptor;
	VboDrawer floor;
	VboDrawer gun;

	Platform platform1;
};

#endif MAP_H

