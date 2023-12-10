#pragma once
#include "../core/core.h"
#include "../../third_party/liquidfun/liquidfun/Box2D/Box2D/Box2D.h"
#include "quad.h"

class obstacle
{
public:
	b2Body *groundBody = 0;
	b2World *world = 0;
	br_object *obj = 0;
	obstacle(float x, float y, float w, float h, float z, b2World *world, br_object_manager *obj_manager, float texture_index)
	{
		this->world = world;
		b2BodyDef groundBodyDef;
		groundBodyDef.position.Set(x + w / 2, y + h / 2);
		groundBody = world->CreateBody(&groundBodyDef);
		b2PolygonShape groundBox;
		groundBox.SetAsBox(w / 2, h / 2);
		groundBody->CreateFixture(&groundBox, 0.0f);

		obj = create_br_object(obj_manager, get_quad_vertices(x, y, w, h, z), 4, get_quad_indices(), 6, texture_index);
	}
	~obstacle()
	{
		world->DestroyBody(groundBody);
	}
};