#include "object.h"
#include <stdlib.h>

DA *objects = 0;

void scale_object(object *obj, vec3 v, unsigned char effect_physic)
{
	glm_scale(obj->model, v);
}

void rotate_object(object *obj, float angle, vec3 axis, unsigned char effect_physic)
{
	glm_rotate(obj->model, glm_rad(angle), axis);
}

void translate_object(object *obj, vec3 v, unsigned char effect_physic)
{
	glm_translate(obj->model, v);
}

object *create_object(GLfloat *vertices, unsigned int vertex_number, GLenum usage, GLuint *indices,
					  unsigned int indice_number, unsigned char is_tex_vertex, unsigned char is_norm_vertex, unsigned char has_physics,
					  unsigned char priority, float mass, float friction, float bounce)
{
	if (vertices == 0 || vertex_number == 0)
	{
		return 0;
	}
	if (indices == 0 || indice_number == 0)
	{
		indices = 0;
		indice_number = 0;
	}
	glBindVertexArray(0);
	object *obj = calloc(1, sizeof(object));
	glGenVertexArrays(1, &(obj->VAO));
	glGenBuffers(1, &(obj->VBO));
	if (indices != 0 && indice_number != 0)
	{
		glGenBuffers(1, &(obj->EBO));
	}
	glBindVertexArray(obj->VAO);
	glBindBuffer(GL_ARRAY_BUFFER, obj->VBO);
	if (!is_tex_vertex)
	{
		if (!is_norm_vertex)
		{
			glBufferData(GL_ARRAY_BUFFER, vertex_number * sizeof(GLfloat) * 7, vertices, usage);
		}
		else
		{
			glBufferData(GL_ARRAY_BUFFER, vertex_number * sizeof(GLfloat) * 10, vertices, usage);
		}
	}
	else
	{
		if (!is_norm_vertex)
		{
			glBufferData(GL_ARRAY_BUFFER, vertex_number * sizeof(GLfloat) * 5, vertices, usage);
		}
		else
		{
			glBufferData(GL_ARRAY_BUFFER, vertex_number * sizeof(GLfloat) * 8, vertices, usage);
		}
	}
	if (!is_tex_vertex)
	{
		if (!is_norm_vertex)
		{
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), 0);
			glEnableVertexAttribArray(0);
			glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), (void *)(3 * sizeof(GLfloat)));
			glEnableVertexAttribArray(1);
		}
		else
		{
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 10 * sizeof(GLfloat), 0);
			glEnableVertexAttribArray(0);
			glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 10 * sizeof(GLfloat), (void *)(3 * sizeof(GLfloat)));
			glEnableVertexAttribArray(1);
			glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 10 * sizeof(GLfloat), (void *)(7 * sizeof(GLfloat)));
			glEnableVertexAttribArray(2);
		}
	}
	else
	{
		if (!is_norm_vertex)
		{
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), 0);
			glEnableVertexAttribArray(0);
			glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void *)(3 * sizeof(GLfloat)));
			glEnableVertexAttribArray(1);
		}
		else
		{
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), 0);
			glEnableVertexAttribArray(0);
			glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void *)(3 * sizeof(GLfloat)));
			glEnableVertexAttribArray(1);
			glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void *)(5 * sizeof(GLfloat)));
			glEnableVertexAttribArray(2);
		}
	}
	if (indices != 0 && indice_number != 0)
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, obj->EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indice_number * sizeof(GLuint), indices, GL_STATIC_DRAW);
	}
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	obj->vertex_number = vertex_number;
	obj->indice_number = indice_number;
	glm_mat4_copy(GLM_MAT4_IDENTITY, obj->model);
	glm_mat4_copy(GLM_MAT4_IDENTITY, obj->normal);
	obj->copy = 0;
	obj->programs = create_DA(sizeof(GLuint));
	obj->uniforms = create_DA(sizeof(GLint));

	if (objects == 0)
	{
		objects = create_DA(sizeof(object *));
	}
	pushback_DA(objects, &obj);
	return obj;
}

void delete_all_object(void)
{
	if (objects == 0)
	{
		return;
	}
	object **x = 0;
	while (get_size_DA(objects) > 0)
	{
		x = get_data_DA(objects);
		delete_object(x[0]);
	}
	delete_DA(objects);
	objects = 0;
}

void delete_object(object *obj)
{
	if (obj)
	{
		remove_DA(objects, get_index_DA(objects, &obj));
		if (obj->copy == 0)
		{
			glDeleteVertexArrays(1, &(obj->VAO));
			glDeleteBuffers(1, &(obj->VBO));
			glDeleteBuffers(1, &(obj->EBO));
			delete_DA(obj->programs);
			delete_DA(obj->uniforms);
		}
		free(obj);
	}
}

void use_object(object *obj, GLuint program)
{
	if (get_index_DA(obj->programs, &program) == UINT_MAX)
	{
		pushback_DA(obj->programs, &program);
		GLint uniform = glGetUniformLocation(program, "model");
		pushback_DA(obj->uniforms, &uniform);
		uniform = glGetUniformLocation(program, "normalMatrix");
		pushback_DA(obj->uniforms, &uniform);
	}
	GLint *uniforms = get_data_DA(obj->uniforms);
	glUniformMatrix4fv(uniforms[get_index_DA(obj->programs, &program) * 2], 1, GL_FALSE, obj->model[0]);
	glm_mat4_inv(obj->model, obj->normal);
	glm_mat4_transpose(obj->normal);
	glUniformMatrix4fv(uniforms[get_index_DA(obj->programs, &program) * 2 + 1], 1, GL_FALSE, obj->normal[0]);
	glBindVertexArray(obj->VAO);
	if (obj->indice_number == 0)
	{
		glDrawArrays(GL_TRIANGLES, 0, obj->vertex_number);
	}
	else
	{
		glDrawElements(GL_TRIANGLES, obj->indice_number, GL_UNSIGNED_INT, 0);
	}
	glBindVertexArray(0);
}

object *create_object_copy(object *obj, unsigned char has_physics)
{
	if (!obj)
	{
		return 0;
	}
	object *obj_new = calloc(1, sizeof(object));
	obj_new->VAO = obj->VAO;
	obj_new->VBO = obj->VBO;
	obj_new->EBO = obj->EBO;
	obj_new->vertex_number = obj->vertex_number;
	obj_new->indice_number = obj->indice_number;
	glm_mat4_copy(GLM_MAT4_IDENTITY, obj_new->model);
	obj_new->copy = 1;
	obj_new->programs = obj->programs;
	obj_new->uniforms = obj->uniforms;
	if (objects == 0)
	{
		objects = create_DA(sizeof(object *));
	}
	pushback_DA(objects, &obj_new);
	return obj_new;
}