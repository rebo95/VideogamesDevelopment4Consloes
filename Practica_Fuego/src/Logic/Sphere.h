
#ifndef __SPHERE_H__
#define __SPHERE_H__



#include "../Renderer/PC/RendererPC.h"
#include <math.h>
#define PI 3.14159265

class Sphere {

private :

	int posX_ = 500;
	int posY_ = 250;

	int vel = 10;
	int velY = 10;

	int sphereRadius = 10;
	static const int NUM_POINTS_SPHERE = 100;

	float angles[NUM_POINTS_SPHERE];
	int posX[NUM_POINTS_SPHERE];
	int posY[NUM_POINTS_SPHERE];

	int findX(float degrees);
	int findY(float degrees);

	
public:
	Sphere();
	~Sphere(); 

	void renderCircunference ();
	void renderCircle();

	void sphereMovement();
	void buildSphere();
};

#endif // !__SPHERE_H__