#include "vec.h"
//#include "FL/gl.h"



class Particle {

public:
	
	Particle(const Particle& p);
	Particle(Vec3f v, Vec3f p, Vec3f a, Vec3f s, double m, int life);
	~Particle();

	Vec3f velocity;
	Vec3f position;
	Vec3f acceleration;
	Vec3f size;

	int life;
	double mass;



};
