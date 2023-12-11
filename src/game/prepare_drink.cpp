#include "prepare_drink.h"
#include "../../third_party/liquidfun/liquidfun/Box2D/Box2D/Box2D.h"
#include "quad.h"
#include <time.h>
#include "fluids.h"
#include "obstacle.h"
#include "bottle.h"
#include "bar.h"

void prepare_drink_scene(GLFWwindow *window)
{
	b2Vec2 gravity(0.0f, 10.0f);
	b2World world(gravity);
	int32 velocityIterations = 6;
	int32 positionIterations = 6;

	br_object_manager *obj_manager = create_br_object_manager();
	br_texture_manager *text_manager = create_br_texture_manager();
	vec3 cam_position = {0, 0, 0};
	camera *cam = create_camera(1920, 1080, cam_position, 60, -100, 100, 1, 100, 0, cam_position);

	// create textures
	br_texture *tex_tmp = create_br_texture(text_manager, "./data/textures/fluids/blue.png", GL_TEXTURE_2D, GL_UNSIGNED_BYTE, GL_LINEAR, GL_LINEAR, 0);
	tex_tmp = create_br_texture(text_manager, "./data/textures/scene/glass.png", GL_TEXTURE_2D, GL_UNSIGNED_BYTE, GL_LINEAR, GL_LINEAR, 1);
	tex_tmp = create_br_texture(text_manager, "./data/textures/scene/bottle.png", GL_TEXTURE_2D, GL_UNSIGNED_BYTE, GL_LINEAR, GL_LINEAR, 2);
	tex_tmp = create_br_texture(text_manager, "./data/textures/scene/pd_bg.png", GL_TEXTURE_2D, GL_UNSIGNED_BYTE, GL_LINEAR, GL_LINEAR, 3);
	tex_tmp = create_br_texture(text_manager, "./data/textures/scene/stripe.png", GL_TEXTURE_2D, GL_UNSIGNED_BYTE, GL_LINEAR, GL_LINEAR, 4);

	// background
	br_object *obj_bg = create_br_object(obj_manager, get_quad_vertices(0, 0, 1920, 1080, -50), 4, get_quad_indices(), 6, 3);
	br_object *obj_glass = create_br_object(obj_manager, get_quad_vertices(0, 0, 1920, 1080, 1), 4, get_quad_indices(), 6, 1);
	br_object *obj_stripe = create_br_object(obj_manager, get_quad_vertices(0, 0, 1920, 1080, 50), 4, get_quad_indices(), 6, 4);

	// create glass physic
	b2Vec2 points[4];
	points[0].x = 820;
	points[0].y = 961;
	points[1].x = 817;
	points[1].y = 966;
	points[2].x = 966;
	points[2].y = 966;
	points[3].x = 966;
	points[3].y = 951;
	obstacle *obstacle1 = new obstacle(points, 4, &world, false);
	points[0].x = 966;
	points[0].y = 951;
	points[1].x = 966;
	points[1].y = 966;
	points[2].x = 987;
	points[2].y = 966;
	points[3].x = 987;
	points[3].y = 951;
	obstacle *obstacle2 = new obstacle(points, 4, &world, false);
	points[0].x = 987;
	points[0].y = 951;
	points[1].x = 987;
	points[1].y = 966;
	points[2].x = 1117;
	points[2].y = 966;
	points[3].x = 1115;
	points[3].y = 962;
	obstacle *obstacle3 = new obstacle(points, 4, &world, false);
	points[0].x = 960;
	points[0].y = 805;
	points[1].x = 966;
	points[1].y = 951;
	points[2].x = 975;
	points[2].y = 951;
	points[3].x = 978;
	points[3].y = 804;
	obstacle *obstacle4 = new obstacle(points, 4, &world, false);
	points[0].x = 978;
	points[0].y = 804;
	points[1].x = 975;
	points[1].y = 951;
	points[2].x = 987;
	points[2].y = 951;
	points[3].x = 992;
	points[3].y = 805;
	obstacle *obstacle5 = new obstacle(points, 4, &world, false);
	points[0].x = 767;
	points[0].y = 657;
	points[1].x = 960;
	points[1].y = 805;
	points[2].x = 978;
	points[2].y = 804;
	points[3].x = 769;
	points[3].y = 655;
	obstacle *obstacle6 = new obstacle(points, 4, &world, false);
	points[0].x = 978;
	points[0].y = 804;
	points[1].x = 992;
	points[1].y = 805;
	points[2].x = 1138;
	points[2].y = 654;
	points[3].x = 1137;
	points[3].y = 652;
	obstacle *obstacle7 = new obstacle(points, 4, &world, false);

	// create scene borders
	obstacle *obstacle8 = new obstacle(-1000, 966, 4000, 100, &world);
	obstacle *obstacle9 = new obstacle(-1000, 950, 10, 100, &world);
	obstacle *obstacle10 = new obstacle(2900, 950, 10, 100, &world);

	// create bottle
	bottle *bottle1 = new bottle(0, 0, 0, 242, 758, 1, obj_manager, 2);
	points[0].x = 3;
	points[0].y = 754;
	points[1].x = 237;
	points[1].y = 754;
	points[2].x = 228;
	points[2].y = 738;
	points[3].x = 13;
	points[3].y = 738;
	bottle1->addobstacle(points, 4, &world);
	points[0].x = 3;
	points[0].y = 258;
	points[1].x = 3;
	points[1].y = 754;
	points[2].x = 13;
	points[2].y = 738;
	points[3].x = 13;
	points[3].y = 264;
	bottle1->addobstacle(points, 4, &world);
	points[0].x = 3;
	points[0].y = 258;
	points[1].x = 13;
	points[1].y = 264;
	points[2].x = 86;
	points[2].y = 204;
	points[3].x = 80;
	points[3].y = 200;
	bottle1->addobstacle(points, 4, &world);
	points[0].x = 80;
	points[0].y = 200;
	points[1].x = 86;
	points[1].y = 204;
	points[2].x = 86;
	points[2].y = 4;
	points[3].x = 80;
	points[3].y = 4;
	bottle1->addobstacle(points, 4, &world);
	points[0].x = 228;
	points[0].y = 738;
	points[1].x = 237;
	points[1].y = 754;
	points[2].x = 237;
	points[2].y = 258;
	points[3].x = 230;
	points[3].y = 263;
	bottle1->addobstacle(points, 4, &world);
	points[0].x = 230;
	points[0].y = 263;
	points[1].x = 237;
	points[1].y = 258;
	points[2].x = 164;
	points[2].y = 202;
	points[3].x = 158;
	points[3].y = 205;
	bottle1->addobstacle(points, 4, &world);
	points[0].x = 158;
	points[0].y = 205;
	points[1].x = 164;
	points[1].y = 202;
	points[2].x = 164;
	points[2].y = 4;
	points[3].x = 158;
	points[3].y = 4;
	bottle1->addobstacle(points, 4, &world);

	// create fluid physic
	fluid *fluid1 = new fluid(bottle1->pos.x - 80, bottle1->pos.y - 60, 60, 100, 0, 5, 1, 1, obj_manager, 0, &world);
	bottle1->fluid_class = fluid1;

	clock_t timer = 0;
	float angular_v = 0;
	b2Vec2 linear = {0, 0};

	// move bottle
	float desired_x = 400;
	float desired_y = 595;
	float error = 1;
	while (1)
	{
		glfwPollEvents();
		if (fabsf(desired_x - bottle1->pos.x) < error && fabsf(desired_y - bottle1->pos.y) < error)
		{
			break;
		}
		linear.x = __min(fabsf(desired_x - bottle1->pos.x), 5);
		linear.y = __min(fabsf(desired_y - bottle1->pos.y), 5);
		linear.x *= (desired_x - bottle1->pos.x) / fabsf(desired_x - bottle1->pos.x);
		linear.y *= (desired_y - bottle1->pos.y) / fabsf(desired_y - bottle1->pos.y);
		bottle1->SetLinearVelocity(linear);
		bottle1->update();
		world.Step(0.2f, velocityIterations, positionIterations, positionIterations);
	}

	// aabb
	b2AABB ground;
	ground.lowerBound.Set(-1000, 960);
	ground.upperBound.Set(3000, 1060);
	b2AABB glass;
	glass.lowerBound.Set(765, 653);
	glass.upperBound.Set(1140, 807);

	int inglass;
	int wasted;
	int maxglass = 3000;
	int maxwasted = 3000;

	bar *glassbar = new bar(60, 500, 50, 51, 300, 0, (float)maxglass, obj_manager, 0);
	bar *wastebar = new bar(1810, 500, 50, 51, 300, 0, (float)maxwasted, obj_manager, 0);
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
		else if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		{
			angular_v = -0.1f;
		}
		else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		{
			angular_v = 0.1f;
		}
		else
		{
			angular_v = 0;
		}
		bottle1->SetAngularVelocity(angular_v);
		b2Vec2 maxy = bottle1->getmaxy();
		float maxx = bottle1->getmaxx();
		float minx = bottle1->getminx();
		if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS &&
			((maxy.y < 665 && (maxx > 760 && minx < 1140)) ||
			 (maxy.y < 980 && (maxx < 760 || minx > 1140))))
		{
			linear.x = -200;
		}
		else if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS &&
				 ((maxy.y < 665 && (maxx > 760 && minx < 1140)) ||
				  (maxy.y < 980 && (maxx < 760 || minx > 1140))))
		{
			linear.x = 200;
		}
		else
		{
			linear.x = 0;
		}
		if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS ||
			(maxy.y > 655 && maxx > 760 && minx < 1140))
		{
			linear.y = -200;
		}
		else if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS &&
				 ((maxy.y < 645 && (maxx > 760 && minx < 1140)) ||
				  (maxy.y < 970 && (maxx < 760 || minx > 1140))))
		{
			linear.y = 200;
		}
		else
		{
			linear.y = 0;
		}
		bottle1->SetLinearVelocity(linear);
		bottle1->update();
		fluid1->update();
		obstacle1->update();
		obstacle2->update();
		obstacle3->update();
		obstacle4->update();
		obstacle5->update();
		obstacle6->update();
		obstacle7->update();
		obstacle8->update();

		inglass = fluid1->get_number_aabb(glass);
		wasted = fluid1->get_number_aabb(ground);

		glassbar->update((float)inglass);
		wastebar->update((float)wasted);

		world.Step(0.16f, velocityIterations, positionIterations, positionIterations);
		while ((clock() - timer) / (CLOCKS_PER_SEC / 1000) < 16)
			;
	}
	delete bottle1;
	delete obstacle1;
	delete obstacle2;
	delete obstacle3;
	delete obstacle4;
	delete obstacle5;
	delete obstacle6;
	delete obstacle7;
	delete obstacle8;
	delete obstacle9;
	delete obstacle10;
	delete fluid1;
	delete glassbar;
	delete wastebar;
	delete_br_object_manager(obj_manager);
	delete_br_texture_manager(text_manager);
	delete_camera(cam);
}