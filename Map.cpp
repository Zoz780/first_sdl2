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

	materal.SetMaterial();
}

bool Map::LoadHeightMaps()
{
	if (!height_map.Load("HeightMaps/terrain3.png", 500.0, 500.0, 25.0, "Textures/grass.jpg"))
	{
		return false;
	}
	else
		m_height_maps.push_back(height_map);
	m_triangles = height_map.specify_the_triangles();


	if (!height_map_objs.Load("HeightMaps/terrain_objs.png", 500.0, 500.0, 25.0, "Textures/base.png"))
	{
		return false;
	}
	else
		m_height_maps.push_back(height_map_objs);
	return true;
}

void Map::SetCameraDirectionVector(Vec3 Line[])
{
	m_camera_direction_vector[0].x = Line[0].x;
	m_camera_direction_vector[0].y = Line[0].y;
	m_camera_direction_vector[0].z = Line[0].z;

	//cout << "P1: Xpos: " << m_camera_direction_vector[0].x << ", Ypos: " << m_camera_direction_vector[0].y << ", Zpos: " << m_camera_direction_vector[0].z << "\n";

	m_camera_direction_vector[1].x = Line[1].x;
	m_camera_direction_vector[1].y = Line[1].y;
	m_camera_direction_vector[1].z = Line[1].z;

	//cout << "P2: Xpos: " << m_camera_direction_vector[1].x << ", Ypos: " << m_camera_direction_vector[1].y << ", Zpos: " << m_camera_direction_vector[1].z << "\n";
}

void Map::FreeHeightMaps()
{
	m_height_maps.pop_back();
}

bool Map::loadModels()
{
	gun.Load("Models/ak.obj", 0.2f, 0.2f, 0.2f, "Textures/ak.png");
	tree_lower.Load("Models/tree_lower.obj", 20.0f, 20.0f, 20.0f, "Textures/tree_lower.jpg");
	tree_upper.Load("Models/tree_upper.obj", 20.0f, 20.0f, 20.0f, "Textures/tree_upper.png");
	skybox.Load("Models/skybox.obj", 900.0f, 900.0f, 900.0f, "Textures/skybox.png");
	mountain.Load("Models/mountain.obj", 50.0f, 50.0f, 50.0f, "Textures/mountain.png");
	trap.Load("Models/trap.obj", 1.5f, 1.5f, 1.5f, "Textures/trap.png");
	intersection_marker.Load("Models/ball1.obj", 0.4f, 0.4f, 0.4f, "Textures/base.png");
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
	/*if (m_height_terrain >= m_height_objs)
	{
		height_map.calc_height_map_gradient(x, y, dx, dy);
	}
	else
		height_map_objs.calc_height_map_gradient(x, y, dx, dy);*/
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

	/*for (int i = 0; i < 50; i++)
	{
		/*Triangle[0].x = m_triangles[i].points[0].x;
		Triangle[0].y = m_triangles[i].points[0].y;
		Triangle[0].z = m_triangles[i].points[0].z;

		Triangle[1].x = m_triangles[i].points[2].x;
		Triangle[1].y = m_triangles[i].points[2].y;
		Triangle[1].z = m_triangles[i].points[2].z;

		Triangle[2].x = m_triangles[i].points[2].x;
		Triangle[2].y = m_triangles[i].points[2].y;
		Triangle[2].z = m_triangles[i].points[2].z;
		m_intersection_point = bullet.IntersectedPolygon(m_triangles[i].points, m_camera_direction_vector, 3);

	}*/

	//Just a test!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

	Triangle[0][0].x = 350;
	Triangle[0][0].y = 50;
	Triangle[0][0].z = 0;

	Triangle[0][1].x = 400;
	Triangle[0][1].y = 50;
	Triangle[0][1].z = 50;

	Triangle[0][2].x = 450;
	Triangle[0][2].y = 50;
	Triangle[0][2].z = 0;

	/*Triangle[1][0].x = 250;
	Triangle[1][0].y = 50;
	Triangle[1][0].z = 0;

	Triangle[1][1].x = 300;
	Triangle[1][1].y = 50;
	Triangle[1][1].z = 50;

	Triangle[1][2].x = 350;
	Triangle[1][2].y = 50;
	Triangle[1][2].z = 0;*/

	for (int i = 0; i < 1; i++)
	{
			m_intersection_point = bullet.IntersectedPolygon(Triangle[i], m_camera_direction_vector, 3);
	}

	glDisable(GL_TEXTURE_2D);
	glBegin(GL_TRIANGLES);
	glColor3f(0, 0.5, 1);
	glVertex3f(Triangle[0][0].x, Triangle[0][0].y, Triangle[0][0].z);

	glVertex3f(Triangle[0][1].x, Triangle[0][1].y, Triangle[0][1].z);

	glVertex3f(Triangle[0][2].x, Triangle[0][2].y, Triangle[0][2].z);
	glEnd();

	/*glBegin(GL_TRIANGLES);
	glColor3f(0, 0.5, 1);
	glVertex3f(Triangle[1][0].x, Triangle[1][0].y, Triangle[1][0].z);

	glVertex3f(Triangle[1][1].x, Triangle[1][1].y, Triangle[1][1].z);

	glVertex3f(Triangle[1][2].x, Triangle[1][2].y, Triangle[1][2].z);
	glEnd();*/
	glColor3f(1, 1, 1);
	glEnable(GL_TEXTURE_2D);
	//Test code end!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!


	//intersection_marker.DrawModel(m_camera_direction_vector[1].x, m_camera_direction_vector[1].y, m_camera_direction_vector[1].z);
	intersection_marker.DrawModel(m_intersection_point.x, m_intersection_point.y, m_intersection_point.z);

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
	height_map.specify_the_triangles();
	
}

void Map::DrawGun()
{
	gun.DrawModel(-0.01f, 0.01f, -0.35f);
}

void Map::DrawTrap()
{
	trap.DrawModel(0, 0, 0);
}

float Map::GetPlatformHeight(float x, float z)
{
	float height = 0.0f;

	for (const HeightMap3D& h : m_height_maps)
	{
		if (height_map.is_on_height_map(x, z)) 
		{
			m_height_terrain = height_map.get_height_map_height(x, z);
			m_height_objs = height_map_objs.get_height_map_height(x, z);


			height = m_height_terrain;
			/*if (m_height_terrain >= m_height_objs)
			{
				height = m_height_terrain;
			}
			else
				height = m_height_objs;*/
		}
	}
	return height;
}


