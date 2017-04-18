#include "Map.h"

Map::Map()
{
    loadPlatforms();
}

void Map::loadPlatforms()
{
    // From file ...
    /*for () {
        Platform platform(1, 2, 3, 4, );
        m_platforms.push_back(platform);
    }*/

	platform1 = Platform(0, 5, 0, 5, -40, 40, 30, 50);
	//Platform platform2 = Platform(5, 5, 5, 5, -40, 40, 50, 175);
}

void Map::loadModels()
{
	raptor.Load("Models/raptor.obj", 0.5f, 0.5f, 0.5f, "Textures/raptor.png");
	floor.Load("Models/floor.obj", 10.0f, 4.0f, 10.0f, "Textures/floor.jpg");
	gun.Load("Models/gun.obj", 0.2f, 0.2f, 0.2f, "Textures/gun.tga");
}

void Map::DrawObjects()
{
	raptor.DrawModel(0, 0, 100);

	glPushMatrix();
	for (int i = -90; i < 90; i += 76)
	{
		for (int j = -50; j < 175; j += 76)
		{
			floor.DrawModel(i, -2.8, j);
		}
	}
	glPopMatrix();
}

void Map::DrawGun()
{
	gun.DrawModel(+0.03f, -0.07f, -0.1f);
}

void Map::GetPlatformHeight()
{

}

