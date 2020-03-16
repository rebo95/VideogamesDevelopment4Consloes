
#include "Fire.h"
#include "Sphere.h"
#include "WhiteBars.h"


int main(int argc, char** argv) {

	Platform::init();
	Renderer::init();

	int fireFrameCounter = 0;

	const int NUM_FRAMES_FADE = 150;
	const int NUM_FRAMES_FLAME = 200;

	Fire fire;
	Sphere sphere;
	WhiteBars whiteBars;


	while (Platform::tick()) {

		Renderer::clear(0x00000000);



		if(fireFrameCounter > NUM_FRAMES_FADE + NUM_FRAMES_FLAME)
			fire.update(Fire::UNLIT);
		else if(fireFrameCounter > NUM_FRAMES_FADE)
			fire.update(Fire::DEFAULT);
		else fire.update(Fire::LIT);

		fire.render();

		fireFrameCounter++;
		if (fireFrameCounter > NUM_FRAMES_FADE + NUM_FRAMES_FLAME + NUM_FRAMES_FADE) fireFrameCounter = 0;

		sphere.sphereMovement();
		sphere.renderCircle();

		whiteBars.update();
		whiteBars.render();

		Renderer::present();
	}

	Renderer::release();
	Platform::release();
	return 0;
}