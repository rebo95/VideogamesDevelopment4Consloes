
#include "Logic/Fire.h"
#include "Logic/Sphere.h"
#include "Logic/WhiteBars.h"

#include "Renderer/Renderer.h"
#include "Platform/Platform.h"


int main(int argc, char** argv) {

	Platform::init();
	Renderer::init();

	int fireFrameCounter = 0;
	int frames = 0;

	const int NUM_FRAMES_FADE = 150;
	const int NUM_FRAMES_FLAME = 200;

	Fire fire;
	Sphere sphere;
	WhiteBars whiteBars;

	int num_frame_buffers = Renderer::getNumBuffers();

	while (Platform::tick()) {

		if (fireFrameCounter > NUM_FRAMES_FADE + NUM_FRAMES_FLAME)
			fire.update(Fire::UNLIT);
		else if (fireFrameCounter > NUM_FRAMES_FADE)
			fire.update(Fire::DEFAULT);
		else fire.update(Fire::LIT);

		fire.render();

		fireFrameCounter++;
		if (fireFrameCounter > NUM_FRAMES_FADE + NUM_FRAMES_FLAME + NUM_FRAMES_FADE) fireFrameCounter = 0;

		whiteBars.update();
		if (frames < num_frame_buffers) {
			Renderer::clear(0x00000000);
			whiteBars.render();
		}
		else
			whiteBars.render(num_frame_buffers);


		//sphere.sphereMovement();
		//sphere.renderCircle();

		frames++;
		Renderer::present();
	}

	Renderer::release();
	Platform::release();
	return 0;
}