#include "HeightMap.h"
#include <SOIL.h>
#include <iostream>
#include <stdlib.h>

#define LINE_BUFFER_SIZE 10240

using namespace std;

HeightMap3D::HeightMap3D()
{
	texture = 0;
	m_vbo_id = 0;
	m_vbo_indeices_id = 0;
}

bool HeightMap3D::Load(const char* height_map_name, double max_corner_x, double max_corner_y, double max_corner_z, const char* texture_name)
{
	map.min_corner.x = 0.0;
	map.min_corner.y = 0.0;
	map.min_corner.z = 0.0;
	map.max_corner.x = max_corner_x;
	map.max_corner.y = max_corner_y;
	map.max_corner.z = max_corner_z;
	if (!load_height_map(height_map_name))
	{
		return false;
	}
	if (!load_texture(texture_name))
	{
		return false;
	}
	m_vbo_vertex_maps = convert_map_to_vbo();
	m_vbo_indices = calculate_indices();
	if (m_vbo_id == 0)
	{
		glGenBuffers(1, &m_vbo_id);
	}
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo_id);
	glBufferData(GL_ARRAY_BUFFER, sizeof(VboVertex3D) * m_vbo_vertex_maps.size(), m_vbo_vertex_maps.data(), GL_STATIC_DRAW);

	if (m_vbo_indeices_id == 0)
	{
		glGenBuffers(1, &m_vbo_indeices_id);
	}
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_vbo_indeices_id);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * m_vbo_indices.size(), m_vbo_indices.data(), GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	return true;
}



double HeightMap3D::get_height_map_value(int x_index, int y_index)
{
	int index;
	double value;

	index = y_index * map.n_columns + x_index;
	value = map.heights[index];

	return value;
}

GLuint HeightMap3D::GetTexture()
{
	return texture;
}

bool HeightMap3D::load_texture(const char* filename)
{
	texture = SOIL_load_OGL_texture
	(
		filename,
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		//SOIL_FLAG_MIPMAPS | SOIL_FLAG_POWER_OF_TWO
		0
	);

	if (texture == 0)
	{
		cout << "ERROR: '" << filename << "' could not loaded (texture missing?)\n\n";
		return false;
	}
	else
	{
		cout << "The '" << filename << "' has successfully loaded!\n" << endl;
	}

	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	return true;
}

std::vector<GLuint> HeightMap3D::calculate_indices()
{
	std::vector<GLuint> indices;
	int index = 0;

	for (int i = 0; i < map.n_rows - 1; i++)
	{
		for (int j = 0; j < map.n_columns - 1; j++)
		{
			indices.push_back(index);
			indices.push_back(index + 1);
			indices.push_back(index + map.n_columns);
			indices.push_back(index + 1);
			indices.push_back(index + map.n_columns);
			indices.push_back(index + map.n_columns + 1);
			index++;
		}
		index++;
	}
	return indices;
}

std::vector<VboVertex3D> HeightMap3D::convert_map_to_vbo()
{
	std::vector<VboVertex3D> vertices;
	VboVertex3D vbo_vertex;

	int row;
	double x, y, z;

	Vec3 scale;
	Vec3 normal;

	for (int i = 0; i < map.n_rows; ++i)
	{
		for (int j = 0; j < map.n_columns; ++j)
		{
			row = i;
			x = (double)j / map.n_columns;
			y = (double)row / map.n_rows;
			z = (double)get_height_map_value(j, row); 

			vbo_vertex.x = x;
			vbo_vertex.y = y;
			vbo_vertex.z = z;
			vbo_vertex.r = 1.0f;
			vbo_vertex.g = 1.0f;
			vbo_vertex.b = 1.0f;
			vbo_vertex.u = x;
			vbo_vertex.v = y;

			vertices.push_back(vbo_vertex);
		}
	}
	return vertices;
}


bool HeightMap3D::load_height_map(const char* filename)
{
	Pixel* image;
	int width;
	int height;

	check_height_map_bounding_rect();

	image = (Pixel*)SOIL_load_image(filename, &width, &height, 0, SOIL_LOAD_RGB);
	if (image == NULL) {
		cout << "ERROR: '" << filename << "' could not loaded (image missing?)\n\n";
		return false;
	}
	else
	{
		cout << "The '" << filename << "' has successfully loaded!\n" << endl;
	}

	map.n_rows = height;
	map.n_columns = width;

	load_height_map_values(image);
	calc_height_map_normals();
	return true;
}

void HeightMap3D::check_height_map_bounding_rect()
{
	if (map.min_corner.x > map.max_corner.x) {
		printf("ERROR: The x values of the bounding box are invalid! %lf > %lf\n", map.min_corner.x, map.max_corner.x);
		return;
	}

	if (map.min_corner.y > map.max_corner.y) {
		printf("ERROR: The y values of the bounding box are invalid! %lf > %lf\n", map.min_corner.y, map.max_corner.y);
		return;
	}

	if (map.min_corner.z > map.max_corner.z) {
		printf("ERROR: The z values of the bounding box are invalid! %lf > %lf\n", map.min_corner.z, map.max_corner.z);
		return;
	}
}

void HeightMap3D::load_height_map_values(const Pixel* image)
{
	int i;
	int n_heights;

	n_heights = map.n_rows * map.n_columns;
	map.heights = (double*)malloc(n_heights * sizeof(double));

	for (i = 0; i < n_heights; ++i) {
		map.heights[i] = (double)image[i][0] / 255.0;
	}
}

double HeightMap3D::get_height_map_height(double x, double y)
{
	double translated_x, translated_y;
	double scaled_x, scaled_y;
	int x0, y0, x1, y1;
	double z00, z01, z10, z11;
	double h0, h1, h;
	double height;

	if (is_on_height_map(x, y) == false) {
		return 0.0;
	}

	translated_x = x - map.min_corner.x;
	translated_y = y - map.min_corner.y;

	calc_height_image_position(translated_x, translated_y, &scaled_x, &scaled_y);

	//printf("(%lf, %lf)\n", scaled_x, scaled_y);

	x0 = (int)scaled_x;
	y0 = (int)scaled_y;
	x1 = x0 + 1;
	y1 = y0 + 1;

	z00 = get_height_map_value(x0, y0);
	z01 = get_height_map_value(x0, y1);
	z10 = get_height_map_value(x1, y0);
	z11 = get_height_map_value(x1, y1);

	h0 = z00 + (z01 - z00) * (scaled_y - y0) / (y1 - y0);
	h1 = z10 + (z11 - z10) * (scaled_y - y0) / (y1 - y0);

	h = h0 + (h1 - h0) * (scaled_x - x0) / (x1 - x0);

	height = map.min_corner.z + h * (map.max_corner.z - map.min_corner.z);

	return height;
}

bool HeightMap3D::is_on_height_map(double x, double y)
{
	if (x < map.min_corner.x) {
		return false;
	}

	if (x > map.max_corner.x) {
		return false;
	}

	if (y < map.min_corner.y) {
		return false;
	}

	if (y > map.max_corner.y) {
		return false;
	}

	return true;
}

void HeightMap3D::calc_height_image_position(double x, double y, double* scaled_x, double* scaled_y)
{
	double x_diff, y_diff;

	x_diff = map.max_corner.x - map.min_corner.x;
	y_diff = map.max_corner.y - map.min_corner.y;

	*scaled_x = (double)(map.n_columns) * (x - map.min_corner.x) / x_diff;
	*scaled_y = (double)(map.n_rows) * (y - map.min_corner.y) / y_diff;
}

double HeightMap3D::calc_vector_length(const Vec3* vector)
{
	double s;
	double length;

	s = vector->x * vector->x + vector->y * vector->y + vector->z * vector->z;
	length = sqrt(s);

	return length;
}

void HeightMap3D::normalize_vector(Vec3* vector)
{
	double length;

	length = calc_vector_length(vector);

	if (length != 0.0) {
		vector->x /= length;
		vector->y /= length;
		vector->z /= length;
	}
}

void HeightMap3D::calc_height_map_normals()
{
	int i, j, index;
	int n_normals;
	double h1, h2;
	double x_unit, y_unit;
	double x_diff, y_diff, z_diff;

	x_unit = 1.0 / map.n_columns;
	y_unit = 1.0 / map.n_rows;

	x_diff = map.max_corner.x - map.min_corner.x;
	y_diff = map.max_corner.y - map.min_corner.y;
	z_diff = map.max_corner.z - map.min_corner.z;

	n_normals = map.n_rows * map.n_columns;
	map.normals = (Vec3*)malloc(n_normals * sizeof(Vec3));

	index = 0;
	for (i = 0; i < map.n_rows; ++i) {
		for (j = 0; j < map.n_columns; ++j) {
			map.normals[index].x = 0.0;
			map.normals[index].y = 0.0;
			map.normals[index].z = 0.0;
			if (i >= 1 && i <= map.n_rows - 1) {
				h1 = get_height_map_value(j, i - 1);
				h2 = get_height_map_value(j, i + 1);
				map.normals[index].x += (h1 - h2) * z_diff;
				map.normals[index].z += (2.0 * x_unit) * x_diff;
			}
			if (j >= 1 && j <= map.n_columns - 1) {
				h1 = get_height_map_value(j - 1, i);
				h2 = get_height_map_value(j + 1, i);
				map.normals[index].y = (h1 - h2) * z_diff;
				map.normals[index].z += (2.0 * y_unit) * x_diff;
			}
			normalize_vector(&map.normals[index]);
			++index;
		}
	}
}

void HeightMap3D::get_height_map_normal(int row, int column, Vec3* normal)
{
	int index;

	index = row * map.n_columns + column;

	normal->x = map.normals[index].x;
	normal->y = map.normals[index].y;
	normal->z = map.normals[index].z;
}

void HeightMap3D::calc_height_map_gradient(double x, double y, double* dx, double* dy)
{
	double delta;
	double h, hx, hy;

	delta = (map.max_corner.x - map.min_corner.x) / (4.0 * map.n_rows);

	h = get_height_map_height(x, y);
	hx = get_height_map_height(x + delta, y);
	hy = get_height_map_height(x, y + delta);

	*dx = (hx - h) / delta;
	*dy = (hy - h) / delta;
}

void HeightMap3D::free_height_map()
{
	// TODO: Free the allocated memory!
	free(map.heights);
	free(map.normals);
}

