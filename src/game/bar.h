#pragma once
#include "../core/core.h"
#include "quad.h"

class bar
{
public:
	float maxh;
	float currenth;
	float maxvalue;
	br_object *obj = 0;
	br_object *obj_bg;
	bar(float x, float maxy, float w, float z, float maxh, float value, float maxvalue, br_object_manager *obj_manager, float texture_index, float texture_index_bg)
	{
		this->maxh = maxh;
		this->maxvalue = maxvalue;
		this->currenth = (value / maxvalue) * maxh;
		obj = create_br_object(obj_manager, get_quad_vertices(x, maxy - currenth, w, currenth, z), 4, get_quad_indices(), 6, texture_index);
		obj_bg = create_br_object(obj_manager, get_quad_vertices(x, maxy - maxh, w, maxh, z - 0.5f), 4, get_quad_indices(), 6, texture_index_bg);
	}
	void update(float value)
	{
		this->currenth = (value / maxvalue) * maxh;
		GLfloat *vertices = (GLfloat *)get_data_DA(obj->manager->vertices);
		vertices[obj->vertex_start * 9 + 10] = vertices[obj->vertex_start * 9 + 1] - currenth;
		vertices[obj->vertex_start * 9 + 19] = vertices[obj->vertex_start * 9 + 10];
		obj->manager->subdata = 1;
	}
};