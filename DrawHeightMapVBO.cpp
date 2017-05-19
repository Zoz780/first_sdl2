#include "DrawHeightMapVBO.h"


DrawHeightMapVBO::DrawHeightMapVBO()
{
}

void DrawHeightMapVBO::DrawHeightMap()
{
	double scale_x, scale_y, scale_z;
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo_id);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_vbo_indeices_id);
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
	glDrawElements(GL_TRIANGLES, m_vbo_indices.size(), GL_UNSIGNED_INT, 0);
	glPopMatrix();

	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableVertexAttribArray(0);
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}