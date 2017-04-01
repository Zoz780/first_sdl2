#pragma once
#include "ModelLoader.h"
#include <iostream>

using namespace std;

/**
* Draw the model.
*/
void draw_model(const struct Model* model);

/**
* Draw the triangles of the model.
*/
void draw_triangles(const struct Model* model);

/**
* Draw the quads of the model.
*/
void draw_quads(const struct Model* model);

class Model_drawer : Model_loader
{
	Model_loader load_M;

public:
	Model_drawer();
	~Model_drawer();

	int load(const char *model_name, float scale, const char *texture_file)
	{
		free();     // hatha mar egyszer volt betoltve, felszabaditjuk az elozot

		if (!load_model(model_name, &model))
			return FALSE;

		scale_model(&model, scale, scale, scale);   // atmeretezzuk, hogy ne logjon ki a vilagunkbol

		texture = SOIL_load_OGL_texture
		(
			texture_file,
			SOIL_LOAD_AUTO,
			SOIL_CREATE_NEW_ID,
			0
		);

		if (texture == 0)   // ha nem sikerult a textura betoltese
		{
			free();         // a model-t felszabaditjuk
			return FALSE;
		}

		glBindTexture(GL_TEXTURE_2D, texture);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		//cout << "load...................\n";
		//cout << model_name << " + " << scale << " + " << texture_file << "\n";
		return TRUE;
	}

	void draw(float x, float y, float z)
	{
		glPushMatrix();
		glTranslatef(x, y, z);
		//cout << x << " " << y << " " << z << "\n";
		glColor3f(1, 1, 1);
		if (texture)
			glBindTexture(GL_TEXTURE_2D, texture);

		draw_model(&model);

		glPopMatrix();
	}

	void free()
	{
		free_model(&model);
		if (texture != 0)
			glDeleteTextures(1, &texture);
	}
};

