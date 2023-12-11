#pragma once
#include "../core/core.h"
#include "quad.h"
#include <time.h>
#include "../../third_party/liquidfun/liquidfun/Box2D/Box2D/Box2D.h"
#include "game.h"

b2Vec2 getmouse(GLFWwindow *window)
{
	b2Vec2 res;
	double x, y;
	int width, height;
	glfwGetCursorPos(window, &x, &y);
	glfwGetWindowSize(window, &width, &height);

	return {((float)x * 1920.0f) / (float)width, ((float)y * 1080.0f) / (float)height};
}

void mainmenu(GLFWwindow *window)
{
	br_object_manager *obj_manager = create_br_object_manager();
	br_texture_manager *text_manager = create_br_texture_manager();
	vec3 cam_position = {0, 0, 0};
	camera *cam = create_camera(1920, 1080, cam_position, 60, -100, 100, 1, 100, 0, cam_position);

	br_texture *tex_tmp = create_br_texture(text_manager, "./data/textures/menus/credits.png", GL_TEXTURE_2D, GL_UNSIGNED_BYTE, GL_LINEAR, GL_LINEAR, 0);
	tex_tmp = create_br_texture(text_manager, "./data/textures/menus/menu.png", GL_TEXTURE_2D, GL_UNSIGNED_BYTE, GL_LINEAR, GL_LINEAR, 1);
	tex_tmp = create_br_texture(text_manager, "./data/textures/menus/menu1.png", GL_TEXTURE_2D, GL_UNSIGNED_BYTE, GL_LINEAR, GL_LINEAR, 2);
	tex_tmp = create_br_texture(text_manager, "./data/textures/menus/menu2.png", GL_TEXTURE_2D, GL_UNSIGNED_BYTE, GL_LINEAR, GL_LINEAR, 3);
	tex_tmp = create_br_texture(text_manager, "./data/textures/menus/menu3.png", GL_TEXTURE_2D, GL_UNSIGNED_BYTE, GL_LINEAR, GL_LINEAR, 4);

	br_object *credits = create_br_object(obj_manager, get_quad_vertices(0, 0, 1920, 1080, 1), 4, get_quad_indices(), 6, 0);
	br_object *menu = create_br_object(obj_manager, get_quad_vertices(0, 0, 1920, 1080, 1), 4, get_quad_indices(), 6, 1);
	br_object *menu1 = create_br_object(obj_manager, get_quad_vertices(0, 0, 1920, 1080, 1), 4, get_quad_indices(), 6, 2);
	br_object *menu2 = create_br_object(obj_manager, get_quad_vertices(0, 0, 1920, 1080, 1), 4, get_quad_indices(), 6, 3);
	br_object *menu3 = create_br_object(obj_manager, get_quad_vertices(0, 0, 1920, 1080, 1), 4, get_quad_indices(), 6, 4);

	prepare_render_br_object_manager(obj_manager);
	clock_t timer = 0;
	vec3 v = {0, 2000, 2000};
	vec3 v2 = {0, -2000, -2000};

	translate_br_object(menu1, v, 0);
	translate_br_object(menu2, v, 0);
	translate_br_object(menu3, v, 0);
	translate_br_object(credits, v, 0);

	b2Vec2 mouse;
	int visible = 1; // text_index

	while (1)
	{
		mouse = getmouse(window);
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
		if (visible == 1)
		{
			if (mouse.x < 659 && mouse.x > 527 && mouse.y < 761 && mouse.y > 699)
			{
				translate_br_object(menu, v, 0);
				translate_br_object(menu1, v2, 0);
				visible = 2;
			}
			else if (mouse.x < 1051 && mouse.x > 863 && mouse.y < 756 && mouse.y > 697)
			{
				translate_br_object(menu, v, 0);
				translate_br_object(menu2, v2, 0);
				visible = 3;
			}
			else if (mouse.x < 1393 && mouse.x > 1280 && mouse.y < 755 && mouse.y > 700)
			{
				translate_br_object(menu, v, 0);
				translate_br_object(menu3, v2, 0);
				visible = 4;
			}
		}
		else if (visible == 2)
		{
			if (!(mouse.x < 659 && mouse.x > 527 && mouse.y < 761 && mouse.y > 699))
			{
				translate_br_object(menu1, v, 0);
				translate_br_object(menu, v2, 0);
				visible = 1;
			}
			if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
			{
				game(window);
				translate_br_object(menu1, v, 0);
				translate_br_object(menu, v2, 0);
				visible = 1;
			}
		}
		else if (visible == 3)
		{
			if (!(mouse.x < 1051 && mouse.x > 863 && mouse.y < 756 && mouse.y > 697))
			{
				translate_br_object(menu2, v, 0);
				translate_br_object(menu, v2, 0);
				visible = 1;
			}
			if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
			{
				translate_br_object(menu2, v, 0);
				translate_br_object(credits, v2, 0);
				visible = 0;
			}
		}
		else if (visible == 4)
		{
			if (!(mouse.x < 1393 && mouse.x > 1280 && mouse.y < 755 && mouse.y > 700))
			{
				translate_br_object(menu3, v, 0);
				translate_br_object(menu, v2, 0);
				visible = 1;
			}
			if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
			{
				break;
			}
		}
		else if (visible == 0)
		{
			if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
			{
				translate_br_object(credits, v, 0);
				translate_br_object(menu, v2, 0);
				visible = 1;
			}
		}
	}
	delete_br_object_manager(obj_manager);
	delete_br_texture_manager(text_manager);
	delete_camera(cam);
}