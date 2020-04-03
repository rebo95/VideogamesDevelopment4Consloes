#include "Sphere.h"
#include <math.h>
Sphere::Sphere()
{
	for (int i = 0; i < NUM_POINTS_SPHERE; i++) {
		posX[i] = findX((360.0f/ float(NUM_POINTS_SPHERE)) * i);
		posY[i] = findY((360.0f / float(NUM_POINTS_SPHERE)) * i);
	}
}

Sphere::~Sphere()
{
}

void Sphere::renderCircunference()
{
	for (int i = 0; i < NUM_POINTS_SPHERE; i++) {
		Renderer::putPixel(posX[i], posY[i], 0x00ff0000);
	}
}

void Sphere::renderCircle()
{
	buildSphere();
	int j = 0;
	for (int i = 0; i < NUM_POINTS_SPHERE/2; i++) {
		j = NUM_POINTS_SPHERE - 1 - i;
		for (int k = posY[j]; k < posY[i]; k++) {
			Renderer::putPixel(posX[i], k, 0x00ff0000);
		}
	}
}

void Sphere::rendeCircleFixed()	//Forma mucho menos elaborada y que implica recorrer toda la pantalla analizando si estamos dentro o no de la esfrea
{								//De tal manera que debemos hacer muchos más cálculos y por lo tanto ralentizar el proceso
	for (int i = 0; i < Renderer::getHeight(); i++) {
		for (int j = 0; j < Renderer::getWidth(); j++) {

			if (sphereRadius > DistanceToCenter(j, i)) {
				Renderer::putPixel(j, i ,0x00ff0000);
			}
		}
	}
}

float Sphere::DistanceToCenter(int x, int y){
	float h = 0;
	h = sqrtf(powf((x - posX_), 2) + powf((y - posY_), 2));
	return h;
}
void Sphere::sphereMovement()
{
	posX_ += vel;
	if (posX_ + sphereRadius >= Renderer::getWidth() || posX_ - sphereRadius <= 0) {
		vel = -vel;
	}

	posY_ += velY;
	if (posY_ + sphereRadius >= Renderer::getHeight() || posY_ - sphereRadius <= 0) {
		velY = -velY;
	}
}

void Sphere::buildSphere()
{
	for (int i = 0; i < NUM_POINTS_SPHERE; i++) {
		posX[i] = findX((360.0f / float(NUM_POINTS_SPHERE)) * i);
		posY[i] = findY((360.0f / float(NUM_POINTS_SPHERE)) * i);
	}
}



int Sphere::findX(float degrees)
{
	return posX_ + sphereRadius * cos(degrees*PI/180.0f);
}

int Sphere::findY(float degrees)
{
	return posY_ + sphereRadius * sin(degrees*PI / 180.0f);
}
