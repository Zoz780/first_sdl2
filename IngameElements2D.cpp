#include "IngameElements2D.h"

IngameElements2D::IngameElements2D()
{
}

IngameElements2D::IngameElements2D(int window_width, int window_height)
{
	vbo = 0;
	screen_width = window_width;
	screen_height = window_height;
}

void IngameElements2D::Init()
{
	ingame_hud.Load("Textures/hud_bg.png");
	if (vbo == 0)
	{
		glGenBuffers(1, &vbo);
	}
	int hud[16] =
	{
		0, 0, 0, 0,
		0, screen_height, 0, 1,
		screen_width, screen_height, 1, 1,
		screen_width, 0, 1, 0
	};
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(int) * sizeof(hud), hud, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void IngameElements2D::DrawCrosshair(int crosshair_distance)
{
	glPushMatrix();
	glDisable(GL_TEXTURE_2D);
	glColor4ub(240, 240, 240, 180);//white
	glLineWidth(2.0);

	int crossHair[16] =
	{
		screen_width / 2 - (15 + crosshair_distance), screen_height / 2, // horizontal line
		screen_width / 2 - (7 + crosshair_distance), screen_height / 2,

		screen_width / 2 + (7 + crosshair_distance), screen_height / 2, // horizontal line
		screen_width / 2 + (15 + crosshair_distance), screen_height / 2,

		screen_width / 2, screen_height / 2 + (15 + crosshair_distance), //vertical line
		screen_width / 2, screen_height / 2 + (7 + crosshair_distance),

		screen_width / 2, screen_height / 2 - (7 + crosshair_distance), //vertical line
		screen_width / 2, screen_height / 2 - (15 + crosshair_distance)
	};

	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(2, GL_INT, 0, crossHair);
	glDrawArrays(GL_LINES, 0, 2);
	glDrawArrays(GL_LINES, 2, 2);
	glDrawArrays(GL_LINES, 4, 2);
	glDrawArrays(GL_LINES, 6, 2);
	glDisableClientState(GL_VERTEX_ARRAY);
	glPopMatrix();
}

void IngameElements2D::DrawHud()
{
	glPushMatrix();
	glColor4f(1.0, 1.0, 1.0, 1.0);
	glEnable(GL_TEXTURE_2D);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glEnableVertexAttribArray(0);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	glBindTexture(GL_TEXTURE_2D, ingame_hud.GetTexture());
	glTexCoordPointer(2, GL_INT, 16, (const void*)8);
	glVertexAttribPointer(0, 2, GL_INT, GL_FALSE, 16, 0);
	glDrawArrays(GL_QUADS, 0, 16);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glPopMatrix();
}
