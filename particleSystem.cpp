#pragma warning(disable : 4786)

#include "particleSystem.h"


#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include <limits.h>
#include <FL/gl.h>
#include "modelerdraw.h"
#include <chrono>
#include <random>
#include "mat.h"


//extern GLfloat currViewMat[16];
//extern Mat4f currViewInv;
//extern Mat4f getCurrentModelViewMatrix();

/***************
 * Constructors
 ***************/

ParticleSystem::ParticleSystem() 
{
	// TODO
	simulate = false;
	dirty = true;
	bake_fps = 30;

	generatespeed = 10;

		
}





/*************
 * Destructor
 *************/

ParticleSystem::~ParticleSystem() 
{
	// TODO
	clearBaked();
}


int ParticleSystem::getIndex(float t)
{
	return (t - bake_start_time) * 30;
}

/******************
 * Simulation fxns
 ******************/

/** Start the simulation */
void ParticleSystem::startSimulation(float t)
{
    
	// TODO

	// These values are used by the UI ...
	// -ve bake_end_time indicates that simulation
	// is still progressing, and allows the
	// indicator window above the time slider
	// to correctly show the "baked" region
	// in grey.
	
	
	if (t < bake_start_time) {
		clearBaked();
	}

	bake_start_time = t;

	
	
	
	bake_end_time = -1;
	simulate = true;
	dirty = true;

}

/** Stop the simulation */
void ParticleSystem::stopSimulation(float t)
{
    
	// TODO

	// These values are used by the UI
	simulate = false;
	dirty = true;
	bake_end_time = t;
}

/** Reset the simulation */
void ParticleSystem::resetSimulation(float t)
{
    
	// TODO

	// These values are used by the UI
	simulate = false;
	dirty = true;
	bake_start_time = 0;
	bake_end_time = 0;
}

/** Compute forces and update particles **/
void ParticleSystem::computeForcesAndUpdateParticles(int idx)
{
	// right now, gravity and air resistance only
	static float arfact = 0.1;

	list<Particle>* lst = bakingParticles[idx];
	for (auto iter = lst->begin(); iter != lst->end(); ++iter)
	{
		auto& p = *iter;
		Vec3f force(0, -9.8 * p.mass, 0);
		force -= prod(p.velocity, p.velocity) * arfact;

		p.acceleration = force / p.mass;
	}
}



/** Render particles */
void ParticleSystem::drawParticles(float t)
{

	// TODO
	if (t < bake_start_time || (bake_end_time >= bake_start_time && t > bake_end_time))
	{
		return;
	}

	bakeParticles(t);
	
	int x = t * 30;
	list<Particle>* particles = bakingParticles[x-1];

	if (particles == nullptr) {
		return;
	}
	

	glPushMatrix();
	for (auto iter = particles->cbegin(); iter != particles->cend(); iter++) {
		glPushMatrix();
		/*
		if (iter->initMat != nullptr)
		{
			glLoadMatrixf(currViewMat);
			glMultMatrixf(iter->initMat);
		}
		*/
		glTranslatef(iter->position[0], iter->position[1], iter->position[2]);
		glScalef(iter->size[0], iter->size[1], iter->size[2]);
		drawBox(1, 1, 1);
		glPopMatrix();
	}
	glPopMatrix();
	
	
}





/** Adds the current configuration of particles to
  * your data structure for storing baked particles **/
void ParticleSystem::bakeParticles(float t) 
{

	// TODO

	int x = getIndex(t);

	
	
	

	int xx = bakingParticles.size();

	if (x < xx && bakingParticles[x] != nullptr)
		return;

	
	
	while (xx++ <=  x) {
		bakingParticles.push_back(nullptr);
		
	}

	int last = x;
	while (--last >= 0 && bakingParticles[last] == nullptr) {
		
	}


	if (last < 0)
	{
		list<Particle>* zeroLst = new list<Particle>;

		// construct the first frame
		for (int i = 0; i < generatespeed; ++i)
		{
			zeroLst->push_back(generateNewParticle());
		}
		bakingParticles[0] = zeroLst;

		last = 0;
		if (x == 0)
			return;
	}



	list<Particle>* newlist = new list<Particle>();
	if (last > 0) {
		
		const list<Particle>* particles = bakingParticles[last];

		int time = (x - last)/30;
		computeForcesAndUpdateParticles(last);
		for (auto iter = particles->begin(); iter != particles->end(); iter++) {

			const Particle& par = *iter;
			
			if (par.life > 10) {
				continue;
			}
			
			Vec3f pp = par.position;
			Vec3f vv = par.velocity;
			Vec3f aa = par.acceleration;
			int ll = par.life + 1;
			pp = pp + vv*time + aa*time*time / 2;
			vv = vv + aa*time;

			Particle p = Particle(vv, pp, aa, par.size, par.mass, ll);

			newlist->push_back(p);
		}
		for (int i = 0; i < generatespeed * time; ++i)
		{
			newlist->push_back(generateNewParticle());
		}

		
		last = x;
		bakingParticles[x] = newlist;
	}
	
	
}

/** Clears out your data structure of baked particles */
void ParticleSystem::clearBaked()
{

	// TODO

	for (auto iter = bakingParticles.begin(); iter != bakingParticles.end(); ++iter)
	{
		if (*iter)
		{
			(*iter)->clear();
			delete *iter;
		}
	}

	bakingParticles.clear();
	this->resetSimulation(0);


}

Particle ParticleSystem::generateNewParticle()
{
	
	Vec3f size = Vec3f(0.1, 0.1, 0.1);
	double mass = 1.0;
	Vec3f a = Vec3f(0, 0, 0);
	Vec3f pos = Vec3f(0, 0, 0);

	std::mt19937 rng;
	rng.seed(std::random_device()());
	std::uniform_int_distribution<std::mt19937::result_type> dist6(1, 6); // distribution in range [1, 6]

	Vec3f speed(0 + dist6(rng), 0.5 + dist6(rng), 3 + dist6(rng));
	Particle p = Particle(speed, pos, a, size, mass, 0);


	
/*
	Mat4f M = getCurrentModelViewMatrix();
	M = currViewInv * M;
	GLfloat* m = new GLfloat[16];
	M.getGLMatrix(m);*/

	return p;
}




