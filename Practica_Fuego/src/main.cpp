
#include "Platform.h"
#include "Renderer.h"

int main(int argc, char** argv) {

	Platform::init();
	Renderer::init();

	while (Platform::tick()) {

		Renderer::clear(0x000000ff);
		Renderer::present();
	}

	Renderer::release();
	Platform::release();
	return 0;
}