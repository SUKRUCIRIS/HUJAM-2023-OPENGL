#pragma once
#include "../core/core.h"
#include "quad.h"
#include <time.h>
#include "../../third_party/liquidfun/liquidfun/Box2D/Box2D/Box2D.h"
#include "prepare_drink.h"

void game(GLFWwindow *window)
{
	br_object_manager *obj_manager = create_br_object_manager();
	br_texture_manager *text_manager = create_br_texture_manager();
	vec3 cam_position = {0, 0, 0};
	camera *cam = create_camera(1920, 1080, cam_position, 60, -100, 100, 1, 100, 0, cam_position);

	br_texture *tex_tmp = create_br_texture(text_manager, "./data/textures/scene/stripe.png", GL_TEXTURE_2D, GL_UNSIGNED_BYTE, GL_LINEAR, GL_LINEAR, 0);
	tex_tmp = create_br_texture(text_manager, "./data/textures/scene/fore.png", GL_TEXTURE_2D, GL_UNSIGNED_BYTE, GL_LINEAR, GL_LINEAR, 1);
	tex_tmp = create_br_texture(text_manager, "./data/textures/scene/a1.png", GL_TEXTURE_2D, GL_UNSIGNED_BYTE, GL_LINEAR, GL_LINEAR, 2);
	tex_tmp = create_br_texture(text_manager, "./data/textures/scene/a2.png", GL_TEXTURE_2D, GL_UNSIGNED_BYTE, GL_LINEAR, GL_LINEAR, 3);
	tex_tmp = create_br_texture(text_manager, "./data/textures/scene/a3.png", GL_TEXTURE_2D, GL_UNSIGNED_BYTE, GL_LINEAR, GL_LINEAR, 4);
	tex_tmp = create_br_texture(text_manager, "./data/textures/scene/b1.png", GL_TEXTURE_2D, GL_UNSIGNED_BYTE, GL_LINEAR, GL_LINEAR, 5);
	tex_tmp = create_br_texture(text_manager, "./data/textures/scene/b2.png", GL_TEXTURE_2D, GL_UNSIGNED_BYTE, GL_LINEAR, GL_LINEAR, 6);
	tex_tmp = create_br_texture(text_manager, "./data/textures/scene/b3.png", GL_TEXTURE_2D, GL_UNSIGNED_BYTE, GL_LINEAR, GL_LINEAR, 7);
	tex_tmp = create_br_texture(text_manager, "./data/textures/scene/c1.png", GL_TEXTURE_2D, GL_UNSIGNED_BYTE, GL_LINEAR, GL_LINEAR, 8);
	tex_tmp = create_br_texture(text_manager, "./data/textures/scene/c2.png", GL_TEXTURE_2D, GL_UNSIGNED_BYTE, GL_LINEAR, GL_LINEAR, 9);
	tex_tmp = create_br_texture(text_manager, "./data/textures/scene/d1.png", GL_TEXTURE_2D, GL_UNSIGNED_BYTE, GL_LINEAR, GL_LINEAR, 10);
	tex_tmp = create_br_texture(text_manager, "./data/textures/scene/d2.png", GL_TEXTURE_2D, GL_UNSIGNED_BYTE, GL_LINEAR, GL_LINEAR, 11);
	tex_tmp = create_br_texture(text_manager, "./data/textures/scene/e1.png", GL_TEXTURE_2D, GL_UNSIGNED_BYTE, GL_LINEAR, GL_LINEAR, 12);
	tex_tmp = create_br_texture(text_manager, "./data/textures/scene/e2.png", GL_TEXTURE_2D, GL_UNSIGNED_BYTE, GL_LINEAR, GL_LINEAR, 13);
	tex_tmp = create_br_texture(text_manager, "./data/textures/scene/f1.png", GL_TEXTURE_2D, GL_UNSIGNED_BYTE, GL_LINEAR, GL_LINEAR, 14);
	tex_tmp = create_br_texture(text_manager, "./data/textures/scene/f2.png", GL_TEXTURE_2D, GL_UNSIGNED_BYTE, GL_LINEAR, GL_LINEAR, 15);

	br_object *stripe = create_br_object(obj_manager, get_quad_vertices(0, 0, 1920, 1080, 50), 4, get_quad_indices(), 6, 0);
	br_object *fore = create_br_object(obj_manager, get_quad_vertices(0, 0, 1920, 1080, 30), 4, get_quad_indices(), 6, 1);
	br_object *a1 = create_br_object(obj_manager, get_quad_vertices(0, 0, 1920, 1080, 15), 4, get_quad_indices(), 6, 2);
	br_object *a2 = create_br_object(obj_manager, get_quad_vertices(0, 0, 1920, 1080, 14), 4, get_quad_indices(), 6, 3);
	br_object *a3 = create_br_object(obj_manager, get_quad_vertices(0, 0, 1920, 1080, 13), 4, get_quad_indices(), 6, 4);
	br_object *b1 = create_br_object(obj_manager, get_quad_vertices(0, 0, 1920, 1080, 12), 4, get_quad_indices(), 6, 5);
	br_object *b2 = create_br_object(obj_manager, get_quad_vertices(0, 0, 1920, 1080, 11), 4, get_quad_indices(), 6, 6);
	br_object *b3 = create_br_object(obj_manager, get_quad_vertices(0, 0, 1920, 1080, 10), 4, get_quad_indices(), 6, 7);
	br_object *c1 = create_br_object(obj_manager, get_quad_vertices(0, 0, 1920, 1080, 9), 4, get_quad_indices(), 6, 8);
	br_object *c2 = create_br_object(obj_manager, get_quad_vertices(0, 0, 1920, 1080, 8), 4, get_quad_indices(), 6, 9);
	br_object *d1 = create_br_object(obj_manager, get_quad_vertices(0, 0, 1920, 1080, 7), 4, get_quad_indices(), 6, 10);
	br_object *d2 = create_br_object(obj_manager, get_quad_vertices(0, 0, 1920, 1080, 6), 4, get_quad_indices(), 6, 11);
	br_object *e1 = create_br_object(obj_manager, get_quad_vertices(0, 0, 1920, 1080, 5), 4, get_quad_indices(), 6, 12);
	br_object *e2 = create_br_object(obj_manager, get_quad_vertices(0, 0, 1920, 1080, 4), 4, get_quad_indices(), 6, 13);
	br_object *f1 = create_br_object(obj_manager, get_quad_vertices(0, 0, 1920, 1080, 3), 4, get_quad_indices(), 6, 14);
	br_object *f2 = create_br_object(obj_manager, get_quad_vertices(0, 0, 1920, 1080, 2), 4, get_quad_indices(), 6, 15);

	prepare_render_br_object_manager(obj_manager);
	clock_t timer = 0;
	vec3 v = {0, 2000, 2000};
	vec3 v2 = {0, -2000, -2000};

	int visible = 1;
	char previouspressed = 1;
	char pressed = 0;
	char pressedonce = 0;
	for (int i = 0; i < 5; i++)
	{
		timer = clock();
		glfwPollEvents();
		while ((clock() - timer) / (CLOCKS_PER_SEC / 1000) < 16)
			;
	}
	while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS)
	{
		timer = clock();
		glfwPollEvents();
		if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
		{
			pressed = 1;
		}
		else
		{
			pressed = 0;
		}
		if (pressed != previouspressed && pressed == 1)
		{
			pressedonce = 1;
		}
		else
		{
			pressedonce = 0;
		}
		previouspressed = pressed;
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glUseProgram(get_def_tex_br_program());
		use_camera(cam, get_def_tex_br_program(), 1);
		use_br_texture_manager(text_manager, get_def_tex_br_program());
		use_br_object_manager(obj_manager);
		glfwSwapBuffers(window);
		while ((clock() - timer) / (CLOCKS_PER_SEC / 1000) < 16)
			;
		if (visible == 1 && pressedonce == 1)
		{
			translate_br_object(a1, v, 0);
			visible = 2;
		}
		else if (visible == 2 && pressedonce == 1)
		{
			translate_br_object(a2, v, 0);
			visible = 3;
		}
		else if (visible == 3 && pressedonce == 1)
		{
			prepare_drink_scene(window);
			translate_br_object(a3, v, 0);
			visible = 4;
		}
		else if (visible == 4 && pressedonce == 1)
		{
			translate_br_object(b1, v, 0);
			visible = 5;
		}
		else if (visible == 5 && pressedonce == 1)
		{
			translate_br_object(b2, v, 0);
			visible = 6;
		}
		else if (visible == 6 && pressedonce == 1)
		{
			translate_br_object(b3, v, 0);
			visible = 7;
		}
		else if (visible == 7 && pressedonce == 1)
		{
			prepare_drink_scene(window);
			translate_br_object(c1, v, 0);
			visible = 8;
		}
		else if (visible == 8 && pressedonce == 1)
		{
			translate_br_object(c2, v, 0);
			visible = 9;
		}
		else if (visible == 9 && pressedonce == 1)
		{
			prepare_drink_scene(window);
			translate_br_object(d1, v, 0);
			visible = 10;
		}
		else if (visible == 10 && pressedonce == 1)
		{
			translate_br_object(d2, v, 0);
			visible = 11;
		}
		else if (visible == 11 && pressedonce == 1)
		{
			prepare_drink_scene(window);
			translate_br_object(e1, v, 0);
			visible = 12;
		}
		else if (visible == 12 && pressedonce == 1)
		{
			translate_br_object(e2, v, 0);
			visible = 13;
		}
		else if (visible == 13 && pressedonce == 1)
		{
			prepare_drink_scene(window);
			translate_br_object(f1, v, 0);
			visible = 14;
		}
		else if (visible == 14 && pressedonce == 1)
		{
			translate_br_object(f2, v, 0);
			visible = 15;
			break;
		}
	}

	delete_br_object_manager(obj_manager);
	delete_br_texture_manager(text_manager);
	delete_camera(cam);
}