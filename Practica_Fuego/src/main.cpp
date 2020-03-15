
#include "Fire.h"

int main(int argc, char** argv) {

	Platform::init();
	Renderer::init();

	Fire fire;

	while (Platform::tick()) {

		Renderer::clear(0x00ff0000);

		for (int i = 0; i < 1080; i++) {
			for (int j = 200; j < 500; j++) {
				Renderer::putPixel(i, j, 0x00ffff00);
			}
		}

		fire.render();

		Renderer::present();
	}

	Renderer::release();
	Platform::release();
	return 0;
}