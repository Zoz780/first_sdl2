#include "DrawHeightMapVBO.h"


DrawHeightMapVBO::DrawHeightMapVBO()
{
}

void DrawHeightMapVBO::DrawHeightMap(const struct HeightMap* height_map)
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
	scale_x = height_map->max_corner.x - height_map->min_corner.x;
	scale_y = height_map->max_corner.y - height_map->min_corner.y;
	scale_z = height_map->max_corner.z - height_map->min_corner.z;
	glScalef(scale_x, scale_y, scale_z);
	glTranslatef(height_map->min_corner.x, height_map->min_corner.y, height_map->min_corner.z);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, m_vbo_vertex_maps.size());
	glPopMatrix();
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
