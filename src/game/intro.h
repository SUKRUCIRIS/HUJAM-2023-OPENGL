#pragma once
#include "../core/core.h"
#include "quad.h"
#include <time.h>

void intro(GLFWwindow *window)
{
	br_object_manager *obj_manager = create_br_object_manager();
	br_texture_manager *text_manager = create_br_texture_manager();
	vec3 cam_position = {0, 0, 0};
	camera *cam = create_camera(1920, 1080, cam_position, 60, -100, 100, 1, 100, 0, cam_position);

	br_texture *tex_tmp = create_br_texture(text_manager, "./data/textures/intro/A NESK.png", GL_TEXTURE_2D, GL_UNSIGNED_BYTE, GL_LINEAR, GL_LINEAR, 0);
	tex_tmp = create_br_texture(text_manager, "./data/textures/intro/sc engn.png", GL_TEXTURE_2D, GL_UNSIGNED_BYTE, GL_LINEAR, GL_LINEAR, 1);
	tex_tmp = create_br_texture(text_manager, "./data/textures/intro/title.png", GL_TEXTURE_2D, GL_UNSIGNED_BYTE, GL_LINEAR, GL_LINEAR, 2);

	br_object *nesk = create_br_object(obj_manager, get_quad_vertices(0, 0, 1920, 1080, 1), 4, get_quad_indices(), 6, 0);
	br_object *engn = create_br_object(obj_manager, get_quad_vertices(0, 0, 1920, 1080, 1), 4, get_quad_indices(), 6, 1);
	br_object *title = create_br_object(obj_manager, get_quad_vertices(0, 0, 1920, 1080, 1), 4, get_quad_indices(), 6, 2);

	prepare_render_br_object_manager(obj_manager);
	clock_t timer = 0;
	vec3 v = {0, 2000, 2000};
	vec3 v2 = {0, -2000, -2000};
	translate_br_object(nesk, v, 0);
	translate_br_object(title, v, 0);
	for (int i = 0; i < 120; i++)
	{
		timer = clock();
		glfwPollEvents();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glUseProgram(get_def_tex_br_program());
		use_camera(cam, get_def_tex_br_program(), 1);
		use_br_texture_manager(text_manager, get_def_tex_br_program());
		use_br_object_manager(obj_manager);
		glfwSwapBuffers(window);
		while ((clock() - timer) / (CLOCKS_PER_SEC / 1000) < 16)
			;
	}
	translate_br_object(engn, v, 0);
	for (int i = 0; i < 20; i++)
	{
		timer = clock();
		glfwPollEvents();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glUseProgram(get_def_tex_br_program());
		use_camera(cam, get_def_tex_br_program(), 1);
		use_br_texture_manager(text_manager, get_def_tex_br_program());
		use_br_object_manager(obj_manager);
		glfwSwapBuffers(window);
		while ((clock() - timer) / (CLOCKS_PER_SEC / 1000) < 16)
			;
	}
	translate_br_object(nesk, v2, 0);
	for (int i = 0; i < 120; i++)
	{
		timer = clock();
		glfwPollEvents();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glUseProgram(get_def_tex_br_program());
		use_camera(cam, get_def_tex_br_program(), 1);
		use_br_texture_manager(text_manager, get_def_tex_br_program());
		use_br_object_manager(obj_manager);
		glfwSwapBuffers(window);
		while ((clock() - timer) / (CLOCKS_PER_SEC / 1000) < 16)
			;
	}
	translate_br_object(nesk, v, 0);
	for (int i = 0; i < 20; i++)
	{
		timer = clock();
		glfwPollEvents();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glUseProgram(get_def_tex_br_program());
		use_camera(cam, get_def_tex_br_program(), 1);
		use_br_texture_manager(text_manager, get_def_tex_br_program());
		use_br_object_manager(obj_manager);
		glfwSwapBuffers(window);
		while ((clock() - timer) / (CLOCKS_PER_SEC / 1000) < 16)
			;
	}
	translate_br_object(title, v2, 0);
	for (int i = 0; i < 120; i++)
	{
		timer = clock();
		glfwPollEvents();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glUseProgram(get_def_tex_br_program());
		use_camera(cam, get_def_tex_br_program(), 1);
		use_br_texture_manager(text_manager, get_def_tex_br_program());
		use_br_object_manager(obj_manager);
		glfwSwapBuffers(window);
		while ((clock() - timer) / (CLOCKS_PER_SEC / 1000) < 16)
			;
	}
	translate_br_object(title, v, 0);
	for (int i = 0; i < 20; i++)
	{
		timer = clock();
		glfwPollEvents();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glUseProgram(get_def_tex_br_program());
		use_camera(cam, get_def_tex_br_program(), 1);
		use_br_texture_manager(text_manager, get_def_tex_br_program());
		use_br_object_manager(obj_manager);
		glfwSwapBuffers(window);
		while ((clock() - timer) / (CLOCKS_PER_SEC / 1000) < 16)
			;
	}
	delete_br_object_manager(obj_manager);
	delete_br_texture_manager(text_manager);
	delete_camera(cam);
}