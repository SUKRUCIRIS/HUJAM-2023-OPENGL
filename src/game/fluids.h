#pragma once
#include "../core/core.h"
#include "../../third_party/liquidfun/liquidfun/Box2D/Box2D/Box2D.h"
#include "quad.h"

class fluid
{
public:
	b2ParticleFlag particle_flag = b2_waterParticle;
	float particle_width = 5;
	float density = 1.0f;
	float gravityScale = 1.0f;
	DA *particle_objects = create_DA(sizeof(br_object *));
	b2ParticleSystem *particle_system = 0;
	b2World *world = 0;
	// particle system will be created
	fluid(float startx, float starty, int32 width, int32 height, b2ParticleFlag particle_flag, float particle_width, float density,
		  float gravityScale, br_object_manager *obj_manager, float texture_index, b2World *world)
	{
		this->particle_flag = particle_flag;
		this->particle_width = particle_width;
		this->density = density;
		this->gravityScale = gravityScale;
		this->world = world;

		b2ParticleSystemDef particleSystemDef;
		particleSystemDef.radius = this->particle_width / 2;
		particleSystemDef.density = this->density;
		particleSystemDef.gravityScale = this->gravityScale;
		this->particle_system = world->CreateParticleSystem(&particleSystemDef);

		b2ParticleDef pd;
		pd.flags = this->particle_flag;
		for (int i = 0; i < width; i++)
		{
			for (int i2 = 0; i2 < height; i2++)
			{
				pd.position.Set((startx + (this->particle_width) * i), (starty + (this->particle_width) * i2));
				this->particle_system->CreateParticle(pd);
			}
		}
		b2Vec2 *particlePositions = this->particle_system->GetPositionBuffer();
		int particleCount = this->particle_system->GetParticleCount();
		br_object *tmp = 0;
		for (int i = 0; i < particleCount; ++i)
		{
			tmp = create_br_object(obj_manager, get_quad_vertices(particlePositions[i].x - particle_width / 2, particlePositions[i].y - particle_width / 2, particle_width, particle_width, 0), 4, get_quad_indices(), 6, texture_index);
			pushback_DA(particle_objects, &tmp);
		}
	}
	void update()
	{
		int32 particleCount = particle_system->GetParticleCount();
		for (int i = 0; i < particleCount; i++)
		{
			br_object **objects = (br_object **)get_data_DA(particle_objects);
			float posx = particle_system->GetPositionBuffer()[i].x - particle_width / 2;
			float posy = particle_system->GetPositionBuffer()[i].y - particle_width / 2;
			modify_br_object(objects[i], 0, posx);
			modify_br_object(objects[i], 1, posy + particle_width);
			modify_br_object(objects[i], 9, posx);
			modify_br_object(objects[i], 10, posy);
			modify_br_object(objects[i], 18, posx + particle_width);
			modify_br_object(objects[i], 19, posy);
			modify_br_object(objects[i], 27, posx + particle_width);
			modify_br_object(objects[i], 28, posy + particle_width);
		}
	}
	~fluid()
	{
		world->DestroyParticleSystem(this->particle_system);
		delete_DA(particle_objects);
	}
};