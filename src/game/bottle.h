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
	std::vector<obstacle> obstacles;
	fluid *fluid_class = 0;
	b2Vec2 pos = {0, 0};
	float angle = 0;
	br_object *obj = 0;
	bool rotate_over_time = false;
	float target_angle = 0;
	float duration_ms = 0;
	float start_ms = 0;
	float current_ms = 0;
	bottle(fluid *fl, float x, float y, float w, float h, float z, br_object_manager *obj_manager, float texture_index)
	{
		this->fluid_class = fl;
		this->pos.x = x + w / 2;
		this->pos.y = y + h / 2;
		obj = create_br_object(obj_manager, get_quad_vertices(x, y, w, h, z), 4, get_quad_indices(), 6, texture_index);
	}
	~bottle()
	{
	}
	void addobstacle(obstacle x)
	{
		obstacles.push_back(x);
	}
	void translate(float x, float y)
	{
		pos.x += x;
		pos.y += y;
		for (auto &i : obstacles)
		{
			i.translate(x, y);
		}
		if (obj)
		{
			vec3 translation = {x, y, 0};
			translate_br_object(obj, translation, 0);
		}
	}
	void setposition(float x, float y)
	{
		for (auto &i : obstacles)
		{
			i.translate(x - pos.x, y - pos.y);
		}
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
		for (auto &i : obstacles)
		{
			i.rotate(desired_angle);
		}
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
	void rotate_timed(float desired_angle, float ms)
	{
		for (auto &i : obstacles)
		{
			i.rotate_timed(desired_angle, ms);
		}
		if (desired_angle != angle)
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
		for (auto &i : obstacles)
		{
			i.update();
		}
		if (this->rotate_over_time)
		{
			current_ms = clock() / (CLOCKS_PER_SEC / 1000.0f);
			this->rotate(-angle);
			this->rotate(this->target_angle * (__min(current_ms - start_ms, duration_ms) / duration_ms));
			if (current_ms - start_ms >= duration_ms)
			{
				this->rotate_over_time = false;
			}
		}
	}
};