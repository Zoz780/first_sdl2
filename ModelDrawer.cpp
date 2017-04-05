#include "ModelDrawer.h"

void Model_drawer::draw_triangles(const struct Model* model)
{
	int i, k;
	int vertex_index, texture_index;
	float x, y, z, u, v;

	glBegin(GL_TRIANGLES);

	for (i = 0; i < model->n_triangles; ++i)
	{
		for (k = 0; k < 3; ++k)
		{

			texture_index = model->triangles[i].points[k].texture_index;
			u = model->texture_vertices[texture_index].u;
			v = model->texture_vertices[texture_index].v;
			// NOTE: The 1-v is model file specific!
			glTexCoord2f(u, 1 - v);

			vertex_index = model->triangles[i].points[k].vertex_index;
			x = model->vertices[vertex_index].x;
			y = model->vertices[vertex_index].y;
			z = model->vertices[vertex_index].z;
			glVertex3d(x, y, z);
		}
	}

	glEnd();
}

void Model_drawer::draw_quads(const struct Model* model)
{
	int i, k;
	int vertex_index, texture_index;
	float x, y, z, u, v;

	glBegin(GL_QUADS);

	for (i = 0; i < model->n_quads; ++i)
	{
		for (k = 0; k < 4; ++k)
		{

			texture_index = model->quads[i].points[k].texture_index;
			u = model->texture_vertices[texture_index].u;
			v = model->texture_vertices[texture_index].v;
			// NOTE: The 1-v is model file specific!
			glTexCoord2f(u, 1 - v);

			vertex_index = model->quads[i].points[k].vertex_index;
			x = model->vertices[vertex_index].x;
			y = model->vertices[vertex_index].y;
			z = model->vertices[vertex_index].z;
			glVertex3d(x, y, z);
		}
	}

	glEnd();
}

void Model_drawer::draw_model(const struct Model* model)
{
	draw_triangles(model);
	draw_quads(model);
}

Model_drawer::Model_drawer()
{
}


Model_drawer::~Model_drawer()
{
}
