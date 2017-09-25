#include "Map.h"

Map::Map()
{
}

bool Map::loadPlatforms()
{
	ifstream file("Data/platforms.csv");
	if (file.is_open())
	{
		string item;
		int values_array[9];
		while (!file.eof())
		{
			for (int i = 0; i < 9; i++)
			{
				getline(file, item);
				if (item.find("Platform") == 0)
				{
					cout << "New platform: ";
				}
				else
				{
					int value = atoi(item.c_str());
					values_array[i] = value;
					cout << values_array[i] << " ";
				}
			}
			platform = Platform(values_array[1], values_array[2], values_array[3], values_array[4], values_array[5], values_array[6], values_array[7], values_array[8]);
			m_platforms.push_back(platform);
			cout << endl;
		}
		return true;
	}
	else
	{
		cout << "Cannot find and/or open 'Data/platforms.csv' file!\n";
		return false;
	}
	file.close();
}

void Map::initMap()
{
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDepthFunc(GL_LESS);
	glShadeModel(GL_SMOOTH);

	glEnable(GL_NORMALIZE);
	glEnable(GL_COLOR_MATERIAL);
}

bool Map::LoadHeightMaps()
{
	if (!height_map.Load("HeightMaps/terrain3.png", 500.0, 500.0, 25.0, "Textures/grass.jpg"))
	{
		return false;
	}
	else
		m_height_maps.push_back(height_map);
	return true;
}

void Map::FreeHeightMaps()
{
	height_map.free_height_map();
	m_height_maps.pop_back();
}

bool Map::loadModels()
{
	raptor.Load("Models/raptor.obj", 0.5f, 0.5f, 0.5f, "Textures/raptor.png");
	floor.Load("Models/floor.obj", 10.0f, 4.0f, 10.0f, "Textures/floor.jpg");
	gun.Load("Models/gun.obj", 0.2f, 0.2f, 0.2f, "Textures/gun.tga");
	tree_lower.Load("Models/tree_lower.obj", 20.0f, 20.0f, 20.0f, "Textures/tree_lower.jpg");
	tree_upper.Load("Models/tree_upper.obj", 20.0f, 20.0f, 20.0f, "Textures/tree_upper.png");
	skybox.Load("Models/skybox.obj", 900.0f, 900.0f, 900.0f, "Textures/skybox.png");
	mountain.Load("Models/mountain.obj", 50.0f, 50.0f, 50.0f, "Textures/mountain.png");
	trap.Load("Models/trap.obj", 5.0f, 5.0f, 5.0f, "Textures/trap.png");
	return true;
}

void Map::DrawTree(float x, float y, float z, float rotate_z)
{
	glPushMatrix();
	glRotatef(90, 1, 0, 0);
	glTranslatef(x, z, -y);
	glRotatef(rotate_z, 0, 1, 0);
	tree_lower.DrawModel(0, 0, 0);
	tree_upper.DrawModel(0, 0, 0);
	glPopMatrix();
}

void Map::HeightMapGrad(double x, double y, double* dx, double* dy)
{
	height_map.calc_height_map_gradient(x, y, dx, dy);
}

void Map::DrawObjects()
{
	glClearDepth(1.0f);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_TEXTURE_2D);

	materal.SetMaterial();

	glPushMatrix();
	glTranslatef(0, 0, -0.1);
	height_map.DrawHeightMap();
	glPopMatrix();

	//skybox
	glPushMatrix();
	glRotatef(90.0f, 1, 0, 0);
	skybox.DrawModel(250, -3, -250);
	glPopMatrix();

	//mountains
	mountain.DrawModel(-80, -210, -3);
	mountain.DrawModel(150, -210, -3);
	mountain.DrawModel(450, -210, -3);
	mountain.DrawModel(650, -210, -15);

	mountain.DrawModel(750, -40, -3);
	mountain.DrawModel(750, 150, -3);
	mountain.DrawModel(750, 350, -20);
	mountain.DrawModel(750, 550, -50);
	
	glPushMatrix();
	glRotatef(90.0f, 1, 0, 0);
	raptor.DrawModel(0, 0, 100);
	glPopMatrix();

	DrawTree(495, 392, 10, 0);
	DrawTree(480, 285, 10, 0);

	DrawTree(233, 142, 12, 0);
	DrawTree(186, 186, 15, 0);
	DrawTree(141, 340, 13, 0);
	DrawTree(182, 195, 11, 0);
	DrawTree(194, 182.5, 13, 0);
	DrawTree(228, 267, 10, 0);

	DrawTree(0, 0, 10, 0);
	DrawTree(505, 10, 13, 0);
	DrawTree(274.5, 321, 20, 90);
	DrawTree(339, 500, 15, 0);
	DrawTree(72, 500, 13, 0);
	
}

void Map::DrawGun()
{
	gun.DrawModel(0.1f, -0.03f, -0.07f);
}

void Map::DrawTrap()
{
	trap.DrawModel(0, 0, 0);
}

float Map::GetPlatformHeight(float x, float z)
{
	float height = 0.0f;
	/*for (const Platform& platform : m_platforms) 
	{
		if (platform.IsOnPlatform(x,z))
		{
			height = platform.GetHeight(x, z);
		}
	}*/

	for (const HeightMap3D& h : m_height_maps)
	{
		if (height_map.is_on_height_map(x, z)) 
		{
			height = height_map.get_height_map_height(x, z);
		}
	}
	return height;
}


