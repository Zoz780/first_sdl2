#include "Materials.h"

double material_data[][10] = {
	{ 0.19125, 0.0735, 0.0225, 0.7038, 0.27048, 0.0828, 0.256777, 0.137622, 0.086014, 0.1 },
};

Materials::Materials()
{
}

void Materials::SetMaterial()
{
	float ambient_material_color[] = { material.ambient.red, material.ambient.green, material.ambient.blue };
	float diffuse_material_color[] = { material.diffuse.red, material.diffuse.green, material.diffuse.blue };
	float specular_material_color[] = { material.specular.red, material.specular.green, material.specular.blue };
	float shininess[] = { material.shininess };

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient_material_color);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse_material_color);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular_material_color);

	glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, shininess);
}

void Materials::SetMaterialValues()
{
	double* material_values;

	material_values = &material_data[0][0];

	material.ambient.red = material_values[0];
	material.ambient.green = material_values[1];
	material.ambient.blue = material_values[2];

	material.diffuse.red = material_values[3];
	material.diffuse.green = material_values[4];
	material.diffuse.blue = material_values[5];

	material.specular.red = material_values[6];
	material.specular.green = material_values[7];
	material.specular.blue = material_values[8];

	material.shininess = material_values[9];
}


