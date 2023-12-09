#include "prepare_drink.h"
#include "../../third_party/liquidfun/liquidfun/Box2D/Box2D/Box2D.h"
#include "quad.h"
#include <time.h>
#include <math.h>

#define SCALE_BOX2D 1.0f

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

	b2BodyDef groundBodyDef;
	groundBodyDef.position.Set(500.0f * SCALE_BOX2D, 900.0f * SCALE_BOX2D);
	b2Body *groundBody = world.CreateBody(&groundBodyDef);
	b2PolygonShape groundBox;
	groundBox.SetAsBox(200.0f * SCALE_BOX2D, 50.0f * SCALE_BOX2D);
	groundBody->CreateFixture(&groundBox, 0.0f);

	br_object *tmp = create_br_object(obj_manager, get_quad_vertices(300, 850, 400, 100), 4, get_quad_indices(), 6, 1);

	b2BodyDef groundBodyDef2;
	groundBodyDef2.position.Set(200.0f * SCALE_BOX2D, 725.0f * SCALE_BOX2D);
	b2Body *groundBody2 = world.CreateBody(&groundBodyDef2);
	b2PolygonShape groundBox2;
	groundBox2.SetAsBox(100.0f * SCALE_BOX2D, 225.0f * SCALE_BOX2D);
	groundBody2->CreateFixture(&groundBox2, 0.0f);

	tmp = create_br_object(obj_manager, get_quad_vertices(100, 500, 200, 450), 4, get_quad_indices(), 6, 1);

	b2BodyDef groundBodyDef3;
	groundBodyDef3.position.Set(800.0f * SCALE_BOX2D, 725.0f * SCALE_BOX2D);
	b2Body *groundBody3 = world.CreateBody(&groundBodyDef3);
	b2PolygonShape groundBox3;
	groundBox3.SetAsBox(100.0f * SCALE_BOX2D, 225.0f * SCALE_BOX2D);
	groundBody3->CreateFixture(&groundBox3, 0.0f);

	tmp = create_br_object(obj_manager, get_quad_vertices(700, 500, 200, 450), 4, get_quad_indices(), 6, 1);

	// create fluid physic

	float particle_width = 5;

	b2ParticleSystemDef particleSystemDef;
	particleSystemDef.radius = particle_width * SCALE_BOX2D;
	b2ParticleSystem *fluid1 = world.CreateParticleSystem(&particleSystemDef);

	b2ParticleDef pd;
	pd.flags = b2_waterParticle;
	for (int i = 0; i < 50; i++)
	{
		for (int i2 = 0; i2 < 50; i2++)
		{
			pd.position.Set((350 + (particle_width + 2) * i) * SCALE_BOX2D, (100 + (particle_width + 2) * i2) * SCALE_BOX2D);
			fluid1->CreateParticle(pd);
		}
	}
	b2Vec2 *particlePositions = fluid1->GetPositionBuffer();
	int particleCount = fluid1->GetParticleCount();
	DA *particle_objects = create_DA(sizeof(br_object *));
	for (int i = 0; i < particleCount; ++i)
	{
		tmp = create_br_object(obj_manager, get_quad_vertices(particlePositions[i].x / SCALE_BOX2D - particle_width / 2, particlePositions[i].y / SCALE_BOX2D - particle_width / 2, particle_width, particle_width), 4, get_quad_indices(), 6, 0);
		pushback_DA(particle_objects, &tmp);
	}
	fluid1->SetStuckThreshold(3);
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
		particleCount = fluid1->GetParticleCount();
		for (int i = 0; i < particleCount; i++)
		{
			br_object **objects = (br_object **)get_data_DA(particle_objects);
			float posx = fluid1->GetPositionBuffer()[i].x / SCALE_BOX2D - particle_width / 2;
			float posy = fluid1->GetPositionBuffer()[i].y / SCALE_BOX2D - particle_width / 2;
			modify_br_object(objects[i], 0, posx);
			modify_br_object(objects[i], 1, posy + particle_width);
			modify_br_object(objects[i], 9, posx);
			modify_br_object(objects[i], 10, posy);
			modify_br_object(objects[i], 18, posx + particle_width);
			modify_br_object(objects[i], 19, posy);
			modify_br_object(objects[i], 27, posx + particle_width);
			modify_br_object(objects[i], 28, posy + particle_width);
		}
		world.Step(0.16f, velocityIterations, positionIterations, positionIterations);
		while ((clock() - timer) / (CLOCKS_PER_SEC / 1000) < 16)
			;
	}
	delete_br_object_manager(obj_manager);
	delete_br_texture_manager(text_manager);
	delete_camera(cam);
}