#ifndef __PARTICLE_H_
#define __PARTICLE_H_
#include<ext.hpp>

struct Particle
{
	glm::vec3 position;
	glm::vec3 velocity;
	glm::vec4 colour;
	float size;
	float lifetime;
	float lifespan;
};
struct ParticleVertex {
	glm::vec4 position;
	glm::vec4 colour;
};

#endif