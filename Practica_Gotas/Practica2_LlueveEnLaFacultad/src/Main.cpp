
#include <SDL.h>
#include "Platform.h"
#include "Renderer.h"



int main(int arg, char** argv) {


	Platform::init();
	Renderer::init();

	int dim = Renderer::getHeight() * Renderer::getWidth();
	uint32_t* picture_ = (uint32_t*)malloc(sizeof(uint32_t) * Renderer::getHeight() * Renderer::getWidth());

	const char* c = "fdi.rgba";

	Platform::loadImage(c, picture_ );


	while (Platform::tick()) {
			Renderer::clear(0x00000000);
		////for (int i = 0; i < WINDOW_WIDTH * WINDOW_HEIGHT; i++) {

		////	int a = i % dim;
		////	int b = i / dim;
		////	uint32_t c = picture_[i];

		////	Renderer::putPixel(a, b, 0x00ff0000);
		////}
		for (int i = 0; i < WINDOW_WIDTH * WINDOW_HEIGHT; i++) {

				uint32_t c = picture_[i];

				int a = i % WINDOW_WIDTH;
				int b = i / WINDOW_WIDTH;

				Renderer::putPixel(a, b, c);
			}

		Renderer::present();
	}

	Renderer::release();
	Platform::release();
	return 0;
}