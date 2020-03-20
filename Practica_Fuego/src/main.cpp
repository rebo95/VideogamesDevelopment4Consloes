
#include "Fire.h"
#include "Sphere.h"
#include "WhiteBars.h"


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
		Renderer::clear(0x00000000);
		////for (int i = 0; i < WINDOW_WIDTH * WINDOW_HEIGHT; i++) {

		////	int a = i % dim;
		////	int b = i / dim;
		////	uint32_t c = picture_[i];

		////	Renderer::putPixel(a, b, 0x00ff0000);
		////}

		for (int i = 0; i < 200; i++) {
			for (int j = 0; j < 200; i++) {

				//uint32_t c = picture_[i];

				Renderer::putPixel(i, j, 0x000000ff);
			}
		}
		Renderer::present();
	}

	Renderer::release();
	Platform::release();
	return 0;
}