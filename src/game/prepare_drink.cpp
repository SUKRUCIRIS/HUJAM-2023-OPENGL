#include "prepare_drink.h"
#include "../../third_party/liquidfun/liquidfun/Box2D/Box2D/Box2D.h"
#include "quad.h"
#include <time.h>
#include <math.h>

#define SCALE_BOX2D 0.05f

void prepare_drink_scene(GLFWwindow *window)
{
	b2Vec2 gravity(0.0f, 10.0f);
	b2World world(gravity);
	int32 velocityIterations = 6;
	int32 positionIterations = 5;

	br_object_manager *obj_manager = create_br_object_manager();
	br_texture_manager *text_manager = create_br_texture_manager();
	camera *cam = create_camera(1920, 1080, (0, 0, 0), 60, 0.1f, 100, 1, 100, 0, (0, 0, 0));

	// create textures
	{
		br_texture *tmp = create_br_texture(text_manager, "./data/textures/fluids/blue.png", GL_TEXTURE_2D, GL_UNSIGNED_BYTE, GL_NEAREST, GL_NEAREST, 0);
	}

	// create glass physic
	{
		b2BodyDef groundBodyDef;
		groundBodyDef.position.Set(500.0f * SCALE_BOX2D, 900.0f * SCALE_BOX2D);
		b2Body *groundBody = world.CreateBody(&groundBodyDef);
		b2PolygonShape groundBox;
		groundBox.SetAsBox(200.0f * SCALE_BOX2D, 50.0f * SCALE_BOX2D);
		groundBody->CreateFixture(&groundBox, 0.0f);

		br_object *tmp = create_br_object(obj_manager, get_quad_vertices(300, 850, 400, 100), 4, get_quad_indices(), 6, 0);

		b2BodyDef groundBodyDef2;
		groundBodyDef2.position.Set(200.0f * SCALE_BOX2D, 775.0f * SCALE_BOX2D);
		b2Body *groundBody2 = world.CreateBody(&groundBodyDef2);
		b2PolygonShape groundBox2;
		groundBox2.SetAsBox(100.0f * SCALE_BOX2D, 225.0f * SCALE_BOX2D);
		groundBody2->CreateFixture(&groundBox2, 0.0f);

		tmp = create_br_object(obj_manager, get_quad_vertices(100, 500, 200, 450), 4, get_quad_indices(), 6, 0);

		b2BodyDef groundBodyDef3;
		groundBodyDef3.position.Set(800.0f * SCALE_BOX2D, 775.0f * SCALE_BOX2D);
		b2Body *groundBody3 = world.CreateBody(&groundBodyDef3);
		b2PolygonShape groundBox3;
		groundBox3.SetAsBox(100.0f * SCALE_BOX2D, 225.0f * SCALE_BOX2D);
		groundBody3->CreateFixture(&groundBox3, 0.0f);

		tmp = create_br_object(obj_manager, get_quad_vertices(700, 500, 200, 450), 4, get_quad_indices(), 6, 0);
	}
	clock_t timer = 0;
	clock_t frame_ms = 0;
	while (1)
	{
		timer = clock();
		glfwPollEvents();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glUseProgram(get_def_tex_br_program());
		use_camera(cam, get_def_tex_br_program(), 1);
		use_br_texture_manager(text_manager, get_def_tex_br_program());
		use_br_object_manager(obj_manager);
		glfwSwapBuffers(window);

		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		{
			break;
		}
		frame_ms = (clock() - timer) / (CLOCKS_PER_SEC / 1000);
		world.Step(__min(frame_ms, 0.15f), velocityIterations, positionIterations);
	}
	delete_br_object_manager(obj_manager);
	delete_br_texture_manager(text_manager);
	delete_camera(cam);
}