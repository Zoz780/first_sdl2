#include "Map.h"

Map::Map()
{
}

void Map::loadPlatforms()
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
	}
	else
		cout << "Cannot find and/or open 'Data/platforms.csv' file!\n";
	file.close();
}

void Map::initMap()
{
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDepthFunc(GL_LESS);

	glEnable(GL_NORMALIZE);
	glEnable(GL_COLOR_MATERIAL);
}

void Map::loadModels()
{
	raptor.Load("Models/raptor.obj", 0.5f, 0.5f, 0.5f, "Textures/raptor.png");
	floor.Load("Models/floor.obj", 10.0f, 4.0f, 10.0f, "Textures/floor.jpg");
	gun.Load("Models/gun.obj", 0.2f, 0.2f, 0.2f, "Textures/gun.tga");
	ground.Load("Models/ground.obj", 100.0f, 1.0f, 100.0f, "Textures/ground.png");
	tree_lower.Load("Models/tree_lower.obj", 10.0f, 10.0f, 10.0f, "Textures/tree_lower.jpg");
	tree_upper.Load("Models/tree_upper.obj", 10.0f, 10.0f, 10.0f, "Textures/tree_upper.png");
	skybox.Load("Models/skybox.obj", 2000.0f, 2000.0f, 2000.0f, "Textures/skybox.png");
}

void Map::DrawTree(float x, float y, float z, float rotate_y)
{
	glPushMatrix();
	glTranslatef(x, y, z);
	glRotatef(rotate_y, 0, 1, 0);
	tree_lower.DrawModel(0, 0, 0);
	tree_upper.DrawModel(0, 0, 0);
	glPopMatrix();
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

	//skybox
	glPushMatrix();
	glRotatef(180.0f, 0, 1, 0);
	skybox.DrawModel(0, 0, 0);
	glPopMatrix();

	raptor.DrawModel(0, 3.6, 100);

	ground.DrawModel(0, -4, 0);

	DrawTree(95, -5.3, 45, 0);
	
	//front
	glPushMatrix();
	glTranslatef(-90, -5.3, 30);
	glRotatef(-15.0f, 1, 0, 0);
	floor.DrawModel(0,0,0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-14, -5.3, 30);
	glRotatef(-15.0f, 1, 0, 0);
	floor.DrawModel(0, 0, 0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(62, -5.3, 30);
	glRotatef(-15.0f, 1, 0, 0);
	floor.DrawModel(0, 0, 0);
	glPopMatrix();

	//back
	glPushMatrix();
	glTranslatef(-90, -12.3, 178);
	glRotatef(15.0f, 1, 0, 0);
	floor.DrawModel(0, 0, 0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-14, -12.3, 178);
	glRotatef(15.0f, 1, 0, 0);
	floor.DrawModel(0, 0, 0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(62, -12.3, 178);
	glRotatef(15.0f, 1, 0, 0);
	floor.DrawModel(0, 0, 0);
	glPopMatrix();

	//left
	glPushMatrix();
	glTranslatef(-164.3, -5.9, 105);
	glRotatef(15.0f, 0, 0, 1);
	floor.DrawModel(0, 0, 0);
	glPopMatrix();

	//right
	glPushMatrix();
	glTranslatef(135.3, -11.3, 105);
	glRotatef(-15.0f, 0, 0, 1);
	floor.DrawModel(0, 0, 0);
	glPopMatrix();

	floor.DrawModel(-90, 1, 104.5);
	floor.DrawModel(-14, 1, 104.5);
	floor.DrawModel(62, 1, 104.5);
}

void Map::DrawGun()
{
	gun.DrawModel(+0.03f, -0.07f, -0.1f);
}

float Map::GetPlatformHeight(float x, float z)
{
	float height = -20.0f;
	for (const Platform& platform : m_platforms) 
	{
		if (platform.IsOnPlatform(x,z))
		{
			height = platform.GetHeight(x, z);
		}
	}
	return height;
}

