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
	tex_tmp = create_br_texture(text_manager, "./data/textures/scene/bardak.png", GL_TEXTURE_2D, GL_UNSIGNED_BYTE, GL_NEAREST, GL_NEAREST, 1);
	tex_tmp = create_br_texture(text_manager, "./data/textures/scene/bottle.png", GL_TEXTURE_2D, GL_UNSIGNED_BYTE, GL_NEAREST, GL_NEAREST, 2);
	tex_tmp = create_br_texture(text_manager, "./data/textures/scene/prepare_drink_bg.png", GL_TEXTURE_2D, GL_UNSIGNED_BYTE, GL_NEAREST, GL_NEAREST, 3);

	// background
	br_object *obj_bg = create_br_object(obj_manager, get_quad_vertices(0, 0, 1920, 1080, -50), 4, get_quad_indices(), 6, 3);
	br_object *obj_glass = create_br_object(obj_manager, get_quad_vertices(0, 0, 1920, 1080, 1), 4, get_quad_indices(), 6, 1);

	// create glass physic
	obstacle *obstacle1 = new obstacle(300, 850, 400, 100, 1, &world, obj_manager, 1);

	obstacle *obstacle2 = new obstacle(100, 500, 200, 450, 1, &world, obj_manager, 1);

	obstacle *obstacle3 = new obstacle(700, 500, 200, 450, 1, &world, obj_manager, 1);

	// create scene borders
	obstacle *obstacle4 = new obstacle(-10, 0, 10, 1080, &world);

	obstacle *obstacle5 = new obstacle(0, 1080, 1920, 10, &world);

	obstacle *obstacle6 = new obstacle(1920, 0, 10, 1080, &world);

	obstacle *obstacle7 = new obstacle(0, -10, 1920, 10, &world);

	// create fluid physic
	fluid *fluid1 = new fluid(350, 100, 100, 200, 0, b2_waterParticle, 5, 1, 1, obj_manager, 0, &world);

	clock_t timer = 0;
	prepare_render_br_object_manager(obj_manager);
	obstacle3->rotate_timed(90, 10000);
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
		obstacle1->update();
		obstacle2->update();
		obstacle3->update();
		obstacle4->update();
		obstacle5->update();
		obstacle6->update();
		obstacle7->update();

		world.Step(0.16f, velocityIterations, positionIterations, positionIterations);
		while ((clock() - timer) / (CLOCKS_PER_SEC / 1000) < 16)
			;
	}
	delete obstacle1;
	delete obstacle2;
	delete obstacle3;
	delete obstacle4;
	delete obstacle5;
	delete obstacle6;
	delete obstacle7;
	delete fluid1;
	delete_br_object_manager(obj_manager);
	delete_br_texture_manager(text_manager);
	delete_camera(cam);
}