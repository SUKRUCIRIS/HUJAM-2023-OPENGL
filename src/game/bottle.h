#pragma once
#include "../core/core.h"
#include "../../third_party/liquidfun/liquidfun/Box2D/Box2D/Box2D.h"
#include "quad.h"
#include "obstacle.h"
#include "fluids.h"
#include <vector>

class bottle
{
public:
	std::vector<obstacle *> obstacles;
	fluid *fluid_class = 0;
	b2Vec2 pos = {0, 0};
	float angle = 0;
	br_object *obj = 0;
	bool rotate_over_time = false;
	float start_angle = 0;
	float target_angle = 0;
	float speed_ms = 0;
	float current_ms = 0;
	float current_ms2 = 0;
	bottle(fluid *fl, float x, float y, float w, float h, float z, br_object_manager *obj_manager, float texture_index)
	{
		this->fluid_class = fl;
		this->pos.x = x + w / 2;
		this->pos.y = y + h / 2;
		obj = create_br_object(obj_manager, get_quad_vertices(x, y, w, h, z), 4, get_quad_indices(), 6, texture_index);
	}
	~bottle()
	{
		for (auto &i : obstacles)
		{
			delete i;
		}
		obstacles.clear();
	}
	void addobstacle(b2Vec2 *points, int32 count, b2World *world)
	{
		obstacles.push_back(new obstacle(points, count, world, true));
	}
	void translate(float x, float y)
	{
		pos.x += x;
		pos.y += y;
		for (auto &i : obstacles)
		{
			i->translate(x, y);
		}
		if (obj)
		{
			vec3 translation = {x, y, 0};
			translate_br_object(obj, translation, 0);
		}
	}
	void setposition(float x, float y)
	{
		if (obj)
		{
			vec3 translation = {x - pos.x, y - pos.y, 0};
			translate_br_object(obj, translation, 0);
		}
		pos.x = x;
		pos.y = y;
	}
	void rotate(float desired_angle)
	{
		angle += desired_angle;
		if (obj)
		{
			vec3 axis = {0, 0, 1};
			vec3 translate = {-pos.x, -pos.y, 0};
			translate_br_object(obj, translate, 0);
			rotate_br_object(obj, desired_angle, axis, 0);
			translate[0] = -translate[0];
			translate[1] = -translate[1];
			translate_br_object(obj, translate, 0);
		}
	}
	void rotate_timed(float desired_angle, float deg_ms)
	{
		if (!(this->rotate_over_time && desired_angle == target_angle))
		{
			for (auto &i : obstacles)
			{
				i->rotate_timed(desired_angle, deg_ms, pos);
			}
			if (desired_angle != angle)
			{
				this->rotate_over_time = true;
				this->target_angle = desired_angle;
				this->speed_ms = deg_ms;
				this->start_angle = angle;
				this->current_ms = clock() / (CLOCKS_PER_SEC / 1000.0f);
				this->current_ms2 = current_ms;
			}
		}
	}
	void update()
	{
		for (auto &i : obstacles)
		{
			i->update();
		}
		if (this->rotate_over_time)
		{
			current_ms = clock() / (CLOCKS_PER_SEC / 1000.0f);
			float value = speed_ms * (current_ms - current_ms2) * ((target_angle - start_angle) / fabsf((target_angle - start_angle)));
			if ((start_angle > target_angle && angle + value < target_angle) ||
				(start_angle < target_angle && angle + value > target_angle))
			{
				value = target_angle - angle;
			}
			this->rotate(value);
			if (angle == target_angle)
			{
				this->rotate_over_time = false;
			}
			current_ms2 = current_ms;
		}
		b2Transform x = obstacles[0]->groundBody->GetTransform();
		this->rotate(-angle);
		this->rotate(glm_deg(x.q.GetAngle()));
		this->setposition(x.p.x, x.p.y);
	}
	void SetLinearVelocity(b2Vec2 x)
	{
		for (auto &i : obstacles)
		{
			i->SetLinearVelocity(x);
		}
	}
	void SetAngularVelocity(float x)
	{
		for (auto &i : obstacles)
		{
			i->SetAngularVelocity(x);
		}
	}
};