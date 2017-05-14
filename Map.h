#pragma once
#ifndef MAP_H
#define MAP_H

#include "DrawHeightMapVBO.h"
#include "VboDrawer.h"
#include "Platform.h"
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

	void LoadHeightMaps();

	void initMap();

	float GetPlatformHeight(float x, float z);

	/**
	* Load the platform.
	*/
	bool loadPlatforms();

	void HeightMapGrad(double x, double y, double* dx, double* dy);

protected:


private:
	void DrawTree(float x, float y, float z, float rotate_y);

    /**
     * The platforms for floor collision detection
     */
    std::vector<Platform> m_platforms;
	std::vector<HeightMap3D> m_height_maps;

	VboDrawer raptor;
	VboDrawer floor;
	VboDrawer gun;
	VboDrawer ground;
	VboDrawer tree_upper;
	VboDrawer tree_lower;
	VboDrawer skybox;

	Platform platform;
	DrawHeightMapVBO height_map;
	
};

#endif MAP_H

