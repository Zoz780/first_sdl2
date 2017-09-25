#include "Texture.h"

Texture::Texture()
{
}

bool Texture::Load(const char* filename)
{
	texture = SOIL_load_OGL_texture
	(
		filename,
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		0
	);

	if (texture == 0)
	{
		//cout << "ERROR: '" << filename << "' could not loaded (texture missing?)\n\n";
		return false;
	}
	else
	{
		//cout << "The '" << filename << "' has successfully loaded!\n" << endl;
	}

	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	return true;
}

GLuint Texture::GetTexture()
{
	return texture;
}
