#include "quad.h"

GLfloat quad_vertices[] = {
	0, 10, 1, 0, 0, 0, 0, 1, 0,	 // A 0
	0, 0, 1, 0, 1, 0, 0, 1, 0,	 // B 1
	10, 0, 1, 1, 1, 0, 0, 1, 0,	 // C 2
	10, 10, 1, 1, 0, 0, 0, 1, 0, // D 3
};

GLuint quad_indices[] = {
	2,
	1,
	0,
	0,
	3,
	2,
};

GLfloat *get_quad_vertices(float x, float y, float w, float h)
{
	quad_vertices[0] = x;
	quad_vertices[1] = y + h;
	quad_vertices[9] = x;
	quad_vertices[10] = y;
	quad_vertices[18] = x + w;
	quad_vertices[19] = y;
	quad_vertices[27] = x + w;
	quad_vertices[28] = y + h;

	return quad_vertices;
}

GLuint *get_quad_indices(void)
{
	return quad_indices;
}