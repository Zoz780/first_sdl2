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

void Map::loadModels()
{
	raptor.Load("Models/raptor.obj", 0.5f, 0.5f, 0.5f, "Textures/raptor.png");
	floor.Load("Models/floor.obj", 10.0f, 4.0f, 10.0f, "Textures/floor.jpg");
	gun.Load("Models/gun.obj", 0.2f, 0.2f, 0.2f, "Textures/gun.tga");
}

void Map::DrawObjects()
{
	raptor.DrawModel(0, 5, 100);

	glPushMatrix();
	for (int i = -90; i < 90; i += 76)
	{
		for (int j = -50; j < 27; j += 76)
		{
			floor.DrawModel(i, -2.8, j);
		}
	}
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-90, -2.8, 30);
	glRotatef(-15.0f, 1, 0, 0);
	floor.DrawModel(0,0,0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-14, -2.8, 30);
	glRotatef(-15.0f, 1, 0, 0);
	floor.DrawModel(0, 0, 0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(62, -2.8, 30);
	glRotatef(-15.0f, 1, 0, 0);
	floor.DrawModel(0, 0, 0);
	glPopMatrix();

	floor.DrawModel(-90, 3.4, 104.5);
	floor.DrawModel(-14, 3.4, 104.5);
	floor.DrawModel(62, 3.4, 104.5);
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

