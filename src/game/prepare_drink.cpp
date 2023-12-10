#include "prepare_drink.h"
#include "../../third_party/liquidfun/liquidfun/Box2D/Box2D/Box2D.h"
#include "quad.h"
#include <time.h>
#include "fluids.h"
#include "obstacle.h"

void prepare_drink_scene(GLFWwindow *window)
{
	b2Vec2 gravity(0.0f, 10.0f);
	b2World world(gravity);
	int32 velocityIterations = 6;
	int32 positionIterations = 4;

	br_object_manager *obj_manager = create_br_object_manager();
	br_texture_manager *text_manager = create_br_texture_manager();
	vec3 cam_position = {0, 0, 0};
	camera *cam = create_camera(1920, 1080, cam_position, 60, -100, 100, 1, 100, 0, cam_position);

	// create textures

	br_texture *tex_tmp = create_br_texture(text_manager, "./data/textures/fluids/blue.png", GL_TEXTURE_2D, GL_UNSIGNED_BYTE, GL_NEAREST, GL_NEAREST, 0);
	tex_tmp = create_br_texture(text_manager, "./data/textures/brick.jpg", GL_TEXTURE_2D, GL_UNSIGNED_BYTE, GL_NEAREST, GL_NEAREST, 1);

	// create glass physic

	obstacle *obstacle1 = new obstacle(300, 850, 400, 100, 1, &world, obj_manager, 1);

	obstacle *obstacle2 = new obstacle(100, 500, 200, 450, 1, &world, obj_manager, 1);

	obstacle *obstacle3 = new obstacle(700, 500, 200, 450, 1, &world, obj_manager, 1);

	// create fluid physic

	fluid *fluid1 = new fluid(350, 100, 100, 100, b2_waterParticle, 5, 1, 1, obj_manager, 0, &world);

	clock_t timer = 0;
	prepare_render_br_object_manager(obj_manager);
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

		fluid1->update();

		world.Step(0.16f, velocityIterations, positionIterations, positionIterations);
		while ((clock() - timer) / (CLOCKS_PER_SEC / 1000) < 16)
			;
	}
	delete obstacle1;
	delete obstacle2;
	delete obstacle3;
	delete fluid1;
	delete_br_object_manager(obj_manager);
	delete_br_texture_manager(text_manager);
	delete_camera(cam);
}