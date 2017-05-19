#pragma once

#include "Vec3.h"
#include "Utils.h"
#include <vector>
#include <glew.h>
#include <glut.h>

#include <string.h>

class HeightMap
{
public:
	int n_rows;
	int n_columns;
	double* heights;
	Vec3 min_corner;
	Vec3 max_corner;
	Vec3* normals;
	Vec3* gradients;
};

class VboVertex3D
{
public:
	GLfloat x;
	GLfloat y;
	GLfloat z;
	GLfloat r;
	GLfloat g;
	GLfloat b;
	GLfloat u;
	GLfloat v;
};

class HeightMap3D
{
public:
	HeightMap3D();

	void Load(const char* height_map_name, double max_corner_x, double max_corner_y, double max_corner_z, const char* texture_name);

	/**
	* Check the bounding rect of the height map.
	*/
	void check_height_map_bounding_rect();

	/**
	* Load the height values of the height map from image.
	*/
	void load_height_map_values(const Pixel* image);

	/**
	* Calculate the height of the surface at the given point.
	*/
	double get_height_map_height(double x, double y);

	/**
	* Is the given coordinate above the surface?
	*/
	bool is_on_height_map(double x, double y);

	/**
	* Get the height of the map at the given point.
	*/
	double get_height_map_value(int x_index, int y_index);

	/**
	* Get the normal vector at the given point.
	*/
	void get_height_map_normal(int row, int column, Vec3* normal);
	/**
	* Calculate the gradients of the height map.
	*/
	void calc_height_map_gradient(double x, double y, double* dx, double* dy);

protected:
	HeightMap map;
	VboVertex3D vbo_3d;

	GLuint texture;
	GLuint m_vbo_id;
	GLuint m_vbo_indeices_id;
	std::vector<VboVertex3D> m_vbo_vertex_maps;
	std::vector<GLuint> m_vbo_indices;

	std::vector<VboVertex3D> convert_map_to_vbo();

	std::vector<GLuint> calculate_indices();

	void load_texture(const char* filename);

	GLuint GetTexture();
	/**
	* Load height map from image file.
	*/
	void load_height_map(const char* filename);

	/**
	* Free the allocated memory.
	*/
	void free_height_map();

	/**
	* Calculate the position on image coordinate system.
	*/
	void calc_height_image_position(double x, double y, double* scaled_x, double* scaled_y);

	/**
	* Calculate height map surface normal vectors.
	*/
	void calc_height_map_normals();

	void normalize_vector(Vec3* vector);

	double calc_vector_length(const Vec3* vector);
};
