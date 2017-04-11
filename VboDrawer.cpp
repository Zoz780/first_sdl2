#include "VboDrawer.h"



VboDrawer::VboDrawer()
{
}


VboDrawer::~VboDrawer()
{
}

void VboDrawer::DrawModel(float x, float y, float z)
{
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo_id);
	glEnableVertexAttribArray(0);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	glBindTexture(GL_TEXTURE_2D, get_texture());
	glTexCoordPointer(2, GL_FLOAT, 32, (const void*)24);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 32, 0);
	glPushMatrix();
	glTranslatef(x, y, z);
	glDrawArrays(GL_TRIANGLES, 0, m_vbo_vertex_triangles.size());
	glDrawArrays(GL_QUADS, 0, m_vbo_vertex_quads.size());
	glPopMatrix();
	glDisableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}