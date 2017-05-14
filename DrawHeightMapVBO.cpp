#include "DrawHeightMapVBO.h"


DrawHeightMapVBO::DrawHeightMapVBO()
{
}

void DrawHeightMapVBO::DrawHeightMap()
{
	double scale_x, scale_y, scale_z;

	glBindBuffer(GL_ARRAY_BUFFER, m_vbo_id);
	glEnableVertexAttribArray(0);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	glBindTexture(GL_TEXTURE_2D, GetTexture());
	glTexCoordPointer(2, GL_FLOAT, 32, (const void*)24);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 32, 0);
	glPushMatrix();
	scale_x = map.max_corner.x - map.min_corner.x;
	scale_y = map.max_corner.y - map.min_corner.y;
	scale_z = map.max_corner.z - map.min_corner.z;
	glScalef(scale_x, scale_y, scale_z);
	glTranslatef(map.min_corner.x, map.min_corner.y, map.min_corner.z);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, m_vbo_vertex_maps.size());
	glPopMatrix();
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void DrawHeightMapVBO::draw_height_map_old()
{
	int i, j, k;
	int row;
	double x, y, z;
	double scale_x, scale_y, scale_z;

	Vec3 scale;
	Vec3 normal;

	//glPushMatrix();

	scale_x = map.max_corner.x - map.min_corner.x;
	scale_y = map.max_corner.y - map.min_corner.y;
	scale_z = map.max_corner.z - map.min_corner.z;

	glScalef(scale_x, scale_y, scale_z);
	glTranslatef(map.min_corner.x, map.min_corner.y, map.min_corner.z);

	for (i = 0; i < map.n_rows - 1; ++i) {
		glBegin(GL_TRIANGLE_STRIP);
		for (j = 0; j < map.n_columns; ++j) {
			for (k = 0; k < 2; ++k) {

				row = i + k;
				x = (double)j / map.n_columns;
				y = (double)row / map.n_rows;
				z = (double)get_height_map_value(j, row);

				glTexCoord2f(x, y);

				glVertex3d(x, y, z);
			}
		}
		glEnd();
	}

	//glPopMatrix();
}
