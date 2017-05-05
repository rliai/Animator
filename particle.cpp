#include "particle.h"
// SAMPLE_SOLUTION



Particle::Particle(const Particle & p)
{
	this->acceleration = p.acceleration;
	this->mass = p.mass;
	this->position = p.position;
	this->size = p.size;
	this->velocity = p.velocity;
	this->life = p.life;
}

Particle::Particle(Vec3f v, Vec3f p, Vec3f a,  Vec3f s, double m, int l)
{
	velocity = v;
	position = p;
	acceleration = a;
	size = s;
	mass = m;
	life = l;
}

Particle::~Particle()
{
}
