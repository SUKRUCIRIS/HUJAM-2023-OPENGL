#include "quad.h"

GLfloat quad_vertices[] = {
	0, 10, 1, 0, 0, 0, 0, 1, 0,	 // A 0
	0, 0, 1, 0, 1, 0, 0, 1, 0,	 // B 1
	10, 0, 1, 1, 1, 0, 0, 1, 0,	 // C 2
	10, 10, 1, 1, 0, 0, 0, 1, 0, // D 3
};

GLuint quad_indices[] = {
	0,
	1,
	2,
	2,
	3,
	0,
};

GLfloat *get_quad_vertices(float x, float y, float w, float h, float z)
{
	quad_vertices[0] = x;
	quad_vertices[1] = y + h;
	quad_vertices[2] = z;
	quad_vertices[9] = x;
	quad_vertices[10] = y;
	quad_vertices[11] = z;
	quad_vertices[18] = x + w;
	quad_vertices[19] = y;
	quad_vertices[20] = z;
	quad_vertices[27] = x + w;
	quad_vertices[28] = y + h;
	quad_vertices[29] = z;

	return quad_vertices;
}

GLuint *get_quad_indices(void)
{
	return quad_indices;
}