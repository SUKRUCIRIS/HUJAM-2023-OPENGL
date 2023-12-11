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
	float start_angle = 0;
	float target_angle = 0;
	float speed_ms = 0;
	float current_ms = 0;
	float current_ms2 = 0;
	b2Vec2 overtimecenter;
	bool kinematic = false;
	obstacle(b2Vec2 *points, int32 count, b2World *world, bool kinematic)
	{
		this->kinematic = kinematic;
		for (int i = 0; i < count; i++)
		{
			points[i].x -= 121;
			points[i].y -= 379;
		}
		if (kinematic)
		{
			this->world = world;
			b2BodyDef groundBodyDef;
			groundBodyDef.position.Set(121, 379);
			groundBodyDef.type = b2_kinematicBody;
			groundBody = world->CreateBody(&groundBodyDef);
			b2PolygonShape groundBox;
			groundBox.Set(points, count);
			groundBody->CreateFixture(&groundBox, 0);
		}
		else
		{
			this->world = world;
			b2BodyDef groundBodyDef;
			groundBodyDef.position.Set(121, 379);
			groundBody = world->CreateBody(&groundBodyDef);
			b2PolygonShape groundBox;
			groundBox.Set(points, count);
			b2FixtureDef fix;
			fix.shape = &groundBox;
			fix.density = 0;
			groundBody->CreateFixture(&fix);
		}
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
	void rotate(float desired_angle, b2Vec2 center)
	{
		b2Vec2 oldt = groundBody->GetTransform().p;
		groundBody->SetTransform(center, groundBody->GetTransform().q.GetAngle() + glm_rad(desired_angle));
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
	void rotate_timed(float desired_angle, float deg_ms, b2Vec2 center)
	{
		if (glm_rad(desired_angle) != groundBody->GetTransform().q.GetAngle())
		{
			this->rotate_over_time = true;
			this->target_angle = desired_angle;
			this->speed_ms = deg_ms;
			this->start_angle = glm_deg(groundBody->GetTransform().q.GetAngle());
			this->current_ms = clock() / (CLOCKS_PER_SEC / 1000.0f);
			this->current_ms2 = current_ms;
			this->overtimecenter = center;
		}
	}
	void update()
	{
		if (this->rotate_over_time)
		{
			current_ms = clock() / (CLOCKS_PER_SEC / 1000.0f);
			float value = speed_ms * (current_ms - current_ms2) * ((target_angle - start_angle) / fabsf((target_angle - start_angle)));
			if ((start_angle > target_angle && glm_deg(groundBody->GetTransform().q.GetAngle()) + value < target_angle) ||
				(start_angle < target_angle && glm_deg(groundBody->GetTransform().q.GetAngle()) + value > target_angle))
			{
				value = target_angle - glm_deg(groundBody->GetTransform().q.GetAngle());
			}
			this->rotate(value, this->overtimecenter);
			if (glm_deg(groundBody->GetTransform().q.GetAngle()) == target_angle)
			{
				this->rotate_over_time = false;
			}
			current_ms2 = current_ms;
		}
	}
	~obstacle()
	{
		world->DestroyBody(groundBody);
	}
	void SetLinearVelocity(b2Vec2 x)
	{
		groundBody->SetLinearVelocity(x);
	}
	void SetAngularVelocity(float x)
	{
		groundBody->SetAngularVelocity(x);
	}
	b2Vec2 getlocalpoint(b2Vec2 x)
	{
		return groundBody->GetLocalPoint(x);
	}
	void create_joint(obstacle *obs, b2Vec2 selfanchor, b2Vec2 otheranchor)
	{
		b2RevoluteJointDef jointDef;
		jointDef.bodyA = this->groundBody;
		jointDef.bodyB = obs->groundBody;
		jointDef.collideConnected = false;
		jointDef.localAnchorA = selfanchor;
		jointDef.localAnchorB = otheranchor;
		b2RevoluteJoint *revoluteJoint = (b2RevoluteJoint *)world->CreateJoint(&jointDef);
	}
};