#include "HeightMap.h"
#include <SOIL.h>
#include <iostream>
#include <stdlib.h>

#define LINE_BUFFER_SIZE 1024

using namespace std;

HeightMap3D::HeightMap3D()
{
}

void HeightMap3D::Load(const char* height_map_name, struct HeightMap* height_map, const char* texture_name)
{
	if (m_vbo_id == 0)
	{
		glGenBuffers(1, &m_vbo_id);
	}
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo_id);
	load_texture(texture_name);
	load_height_map(height_map, height_map_name);
	m_vbo_vertex_maps = convert_map_to_vbo(*height_map);
	glBufferData(GL_ARRAY_BUFFER, sizeof(VboVertex3D) * m_vbo_vertex_maps.size(), m_vbo_vertex_maps.data(), GL_DYNAMIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}



double HeightMap3D::get_height_map_value(const struct HeightMap* height_map, int x_index, int y_index)
{
	int index;
	double value;

	index = y_index * height_map->n_columns + x_index;
	value = height_map->heights[index];

	return value;
}

GLuint HeightMap3D::GetTexture()
{
	return texture;
}

void HeightMap3D::load_texture(const char* filename)
{
	Pixel* image;
	int width;
	int height;

	glGenTextures(1, &texture);

	image = (Pixel*)SOIL_load_image(filename, &width, &height, 0, SOIL_LOAD_RGB);

	if (texture == 0)
	{
		cout << "ERROR: '" << filename << "' could not loaded (texture missing?)\n";
	}
	else
	{
		cout << "The '" << filename << "' has successfully loaded!" << endl;
	}

	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, (Pixel*)image);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
}

std::vector<VboVertex3D> HeightMap3D::convert_map_to_vbo(const struct HeightMap& height_map)
{
	std::vector<VboVertex3D> vertices;
	VboVertex3D vbo_vertex;

	int row;
	double x, y, z;

	Vec3 scale;
	Vec3 normal;

	for (int i = 0; i < height_map.n_rows - 1; ++i) {
		for (int j = 0; j < height_map.n_columns; ++j) {
			for (int k = 0; k < 2; ++k) {

				row = i + k;
				x = (double)j / height_map.n_columns;
				y = (double)row / height_map.n_rows;
				z = (double)get_height_map_value(&height_map, j, row); 

				//get_height_map_normal(&height_map, row, j, &normal);
				//glNormal3d(normal.x, normal.y, normal.z);

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
	}
	return vertices;
}


void HeightMap3D::load_height_map(struct HeightMap* height_map, const char* filename)
{
	Pixel* image;
	int width;
	int height;

	check_height_map_bounding_rect(height_map);

	image = (Pixel*)SOIL_load_image(filename, &width, &height, 0, SOIL_LOAD_RGB);
	if (image == NULL) {
		printf("ERROR: Unable to load the height map from \"%s\" image file!\n", filename);
		return;
	}

	height_map->n_rows = height;
	height_map->n_columns = width;

	load_height_map_values(height_map, image);
	calc_height_map_normals(height_map);
}

void HeightMap3D::check_height_map_bounding_rect(const struct HeightMap* height_map)
{
	if (height_map->min_corner.x > height_map->max_corner.x) {
		printf("ERROR: The x values of the bounding box are invalid! %lf > %lf\n", height_map->min_corner.x, height_map->max_corner.x);
		return;
	}

	if (height_map->min_corner.y > height_map->max_corner.y) {
		printf("ERROR: The y values of the bounding box are invalid! %lf > %lf\n", height_map->min_corner.y, height_map->max_corner.y);
		return;
	}

	if (height_map->min_corner.z > height_map->max_corner.z) {
		printf("ERROR: The z values of the bounding box are invalid! %lf > %lf\n", height_map->min_corner.z, height_map->max_corner.z);
		return;
	}
}

void HeightMap3D::load_height_map_values(struct HeightMap* height_map, const Pixel* image)
{
	int i;
	int n_heights;

	n_heights = height_map->n_rows * height_map->n_columns;
	height_map->heights = (double*)malloc(n_heights * sizeof(double));

	for (i = 0; i < n_heights; ++i) {
		height_map->heights[i] = (double)image[i][0] / 255.0;
	}
}

double HeightMap3D::get_height_map_height(const struct HeightMap* height_map, double x, double y)
{
	double translated_x, translated_y;
	double scaled_x, scaled_y;
	double x_diff, y_diff;
	int x0, y0, x1, y1;
	double z00, z01, z10, z11;
	double h0, h1, h;
	double height;

	if (is_on_height_map(height_map, x, y) == false) {
		return 0.0;
	}

	translated_x = x - height_map->min_corner.x;
	translated_y = y - height_map->min_corner.y;

	calc_height_image_position(height_map, translated_x, translated_y, &scaled_x, &scaled_y);

	printf("(%lf, %lf)\n", scaled_x, scaled_y);

	x0 = (int)scaled_x;
	y0 = (int)scaled_y;
	x1 = x0 + 1;
	y1 = y0 + 1;

	z00 = get_height_map_value(height_map, x0, y0);
	z01 = get_height_map_value(height_map, x0, y1);
	z10 = get_height_map_value(height_map, x1, y0);
	z11 = get_height_map_value(height_map, x1, y1);

	h0 = z00 + (z01 - z00) * (scaled_y - y0) / (y1 - y0);
	h1 = z10 + (z11 - z10) * (scaled_y - y0) / (y1 - y0);

	h = h0 + (h1 - h0) * (scaled_x - x0) / (x1 - x0);

	height = height_map->min_corner.z + h * (height_map->max_corner.z - height_map->min_corner.z);

	return height;
}

int HeightMap3D::is_on_height_map(const struct HeightMap* height_map, double x, double y)
{
	if (x < height_map->min_corner.x) {
		return false;
	}

	if (x > height_map->max_corner.x) {
		return false;
	}

	if (y < height_map->min_corner.y) {
		return false;
	}

	if (y > height_map->max_corner.y) {
		return false;
	}

	return true;
}

void HeightMap3D::calc_height_image_position(const struct HeightMap* height_map, double x, double y, double* scaled_x, double* scaled_y)
{
	double x_diff, y_diff;

	x_diff = height_map->max_corner.x - height_map->min_corner.x;
	y_diff = height_map->max_corner.y - height_map->min_corner.y;

	*scaled_x = (double)(height_map->n_columns) * (x - height_map->min_corner.x) / x_diff;
	*scaled_y = (double)(height_map->n_rows) * (y - height_map->min_corner.y) / y_diff;
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

void HeightMap3D::calc_height_map_normals(struct HeightMap* height_map)
{
	int i, j, index;
	int n_normals;
	double h1, h2;
	double x_unit, y_unit;
	double x_diff, y_diff, z_diff;

	x_unit = 1.0 / height_map->n_columns;
	y_unit = 1.0 / height_map->n_rows;

	x_diff = height_map->max_corner.x - height_map->min_corner.x;
	y_diff = height_map->max_corner.y - height_map->min_corner.y;
	z_diff = height_map->max_corner.z - height_map->min_corner.z;

	n_normals = height_map->n_rows * height_map->n_columns;
	height_map->normals = (Vec3*)malloc(n_normals * sizeof(Vec3));

	index = 0;
	for (i = 0; i < height_map->n_rows; ++i) {
		for (j = 0; j < height_map->n_columns; ++j) {
			height_map->normals[index].x = 0.0;
			height_map->normals[index].y = 0.0;
			height_map->normals[index].z = 0.0;
			if (i >= 1 && i <= height_map->n_rows - 1) {
				h1 = get_height_map_value(height_map, j, i - 1);
				h2 = get_height_map_value(height_map, j, i + 1);
				height_map->normals[index].x += (h1 - h2) * z_diff;
				height_map->normals[index].z += (2.0 * x_unit) * x_diff;
			}
			if (j >= 1 && j <= height_map->n_columns - 1) {
				h1 = get_height_map_value(height_map, j - 1, i);
				h2 = get_height_map_value(height_map, j + 1, i);
				height_map->normals[index].y = (h1 - h2) * z_diff;
				height_map->normals[index].z += (2.0 * y_unit) * x_diff;
			}
			normalize_vector(&height_map->normals[index]);
			++index;
		}
	}
}

void HeightMap3D::get_height_map_normal(
	const struct HeightMap* height_map,
	int row, int column,
	Vec3* normal)
{
	int index;

	index = row * height_map->n_columns + column;

	normal->x = height_map->normals[index].x;
	normal->y = height_map->normals[index].y;
	normal->z = height_map->normals[index].z;
}

void HeightMap3D::calc_height_map_gradient(struct HeightMap* height_map, double x, double y, double* dx, double* dy)
{
	double delta;
	double h, hx, hy;

	delta = (height_map->max_corner.x - height_map->min_corner.x) / (4.0 * height_map->n_rows);

	h = get_height_map_height(height_map, x, y);
	hx = get_height_map_height(height_map, x + delta, y);
	hy = get_height_map_height(height_map, x, y + delta);

	*dx = (hx - h) / delta;
	*dy = (hy - h) / delta;
}

void HeightMap3D::free_height_map(struct HeightMap* height_map)
{
	// TODO: Free the allocated memory!
}

