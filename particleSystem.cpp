#pragma warning(disable : 4786)

#include "particleSystem.h"


#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include <limits.h>


/***************
 * Constructors
 ***************/

ParticleSystem::ParticleSystem() 
{
	// TODO
	simulate = false;
	dirty = true;
	bake_fps = 30;
}





/*************
 * Destructor
 *************/

ParticleSystem::~ParticleSystem() 
{
	// TODO
	clearBaked();
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
void ParticleSystem::computeForcesAndUpdateParticles(float t)
{

	// TODO
	int x = (int)t * 30;
	list<Particle>* particles = bakingParticles[x];
	for (auto iter = particles->begin(); iter != particles->end(); iter++) {
		Particle p = *(iter);
		Vec3f f = Vec3f(0, p.mass*9.8, 0);
		p.acceleration = f / p.mass;
	}

}


/** Render particles */
void ParticleSystem::drawParticles(float t)
{

	// TODO
}





/** Adds the current configuration of particles to
  * your data structure for storing baked particles **/
void ParticleSystem::bakeParticles(float t) 
{

	// TODO
}

/** Clears out your data structure of baked particles */
void ParticleSystem::clearBaked()
{

	// TODO

	for (auto iter = bakingParticles.begin(); iter != bakingParticles.end(); iter++) {
		delete *iter;
	}

}





