#pragma once
#ifndef MAP_H
#define MAP_H

#include "DrawHeightMapVBO.h"
#include "VboDrawer.h"
#include "Platform.h"
#include "Position.h"
#include "Materials.h"
#include "BulletCalcs3D.h"
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

	void DrawTrap();

	void DrawObjects();

	bool loadModels();

	bool LoadHeightMaps();

	void FreeHeightMaps();

	void initMap();

	float GetPlatformHeight(float x, float z);

	/**
	* Load the platform.
	*/
	bool loadPlatforms();

	void SetCameraDirectionVector(Vec3 Line[]);

	void HeightMapGrad(double x, double y, double* dx, double* dy);

protected:


private:
	void DrawTree(float x, float y, float z, float rotate_y);

    /**
     * The platforms for floor collision detection
     */
    std::vector<Platform> m_platforms;
	std::vector<HeightMap3D> m_height_maps;

	VboDrawer gun;
	VboDrawer ground;
	VboDrawer tree_upper;
	VboDrawer tree_lower;
	VboDrawer skybox;
	VboDrawer mountain;
	VboDrawer trap;
	VboDrawer intersection_marker;

	Platform platform;
	Materials materal;
	BulletCalcs3D bullet;
	DrawHeightMapVBO height_map;
	DrawHeightMapVBO height_map_objs;

	std::vector<Triangles> m_triangles;
	Vec3 m_camera_direction_vector[2];
	Vec3 Triangle[3];
	Vec3 m_intersection_point;

	float m_height_terrain = 0.0f;
	float m_height_objs = 0.0f;
	
};

#endif MAP_H

