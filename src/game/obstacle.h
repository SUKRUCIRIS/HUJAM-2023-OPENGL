#pragma once
#include "../core/core.h"
#include "../../third_party/liquidfun/liquidfun/Box2D/Box2D/Box2D.h"
#include "quad.h"
#include "time.h"

class obstacle
{
public:
	b2Body *groundBody = 0;
	b2World *world = 0;
	br_object *obj = 0;
	bool rotate_over_time = false;
	float target_angle = 0;
	float duration_ms = 0;
	float start_ms = 0;
	float current_ms = 0;
	obstacle(b2Vec2 *points, int32 count, b2World *world)
	{
		float x = 0;
		float y = 0;
		for (int i = 0; i < count; i++)
		{
			x += points[i].x;
			y += points[i].y;
		}
		x /= count;
		y /= count;
		this->world = world;
		b2BodyDef groundBodyDef;
		groundBodyDef.position.Set(x, y);
		groundBody = world->CreateBody(&groundBodyDef);
		b2PolygonShape groundBox;
		groundBox.Set(points, count);
		groundBody->CreateFixture(&groundBox, 0.0f);
	}
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
	obstacle(float x, float y, float w, float h, b2World *world)
	{
		this->world = world;
		b2BodyDef groundBodyDef;
		groundBodyDef.position.Set(x + w / 2, y + h / 2);
		groundBody = world->CreateBody(&groundBodyDef);
		b2PolygonShape groundBox;
		groundBox.SetAsBox(w / 2, h / 2);
		groundBody->CreateFixture(&groundBox, 0.0f);
	}
	void rotate(float desired_angle)
	{
		groundBody->SetTransform(groundBody->GetTransform().p, groundBody->GetTransform().q.GetAngle() + glm_rad(desired_angle));
		if (obj)
		{
			vec3 axis = {0, 0, 1};
			vec3 translate = {-groundBody->GetTransform().p.x, -groundBody->GetTransform().p.y, 0};
			translate_br_object(obj, translate, 0);
			rotate_br_object(obj, desired_angle, axis, 0);
			translate[0] = -translate[0];
			translate[1] = -translate[1];
			translate_br_object(obj, translate, 0);
		}
	}
	void setposition(float x, float y)
	{
		b2Vec2 oldt = groundBody->GetTransform().p;
		groundBody->SetTransform(b2Vec2(x, y), groundBody->GetTransform().q.GetAngle());
		if (obj)
		{
			vec3 translation = {x - oldt.x, y - oldt.y, 0};
			translate_br_object(obj, translation, 0);
		}
	}
	void translate(float x, float y)
	{
		b2Vec2 oldt = groundBody->GetTransform().p;
		groundBody->SetTransform(b2Vec2(x + oldt.x, y + oldt.y), groundBody->GetTransform().q.GetAngle());
		if (obj)
		{
			vec3 translation = {x, y, 0};
			translate_br_object(obj, translation, 0);
		}
	}
	void rotate_timed(float desired_angle, float ms)
	{
		if (glm_rad(desired_angle) != groundBody->GetTransform().q.GetAngle())
		{
			this->rotate_over_time = true;
			this->target_angle = desired_angle;
			this->start_ms = clock() / (CLOCKS_PER_SEC / 1000.0f);
			this->duration_ms = ms;
			this->current_ms = start_ms;
		}
	}
	void update()
	{
		if (this->rotate_over_time)
		{
			current_ms = clock() / (CLOCKS_PER_SEC / 1000.0f);
			this->rotate(-glm_deg(groundBody->GetTransform().q.GetAngle()));
			this->rotate(this->target_angle * (__min(current_ms - start_ms, duration_ms) / duration_ms));
			if (current_ms - start_ms >= duration_ms)
			{
				this->rotate_over_time = false;
			}
		}
	}
	~obstacle()
	{
		world->DestroyBody(groundBody);
	}
};