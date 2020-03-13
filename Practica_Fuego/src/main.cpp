
#include "Platform.h"
#include "Renderer.h"

int main(int argc, char** argv) {

	Platform::init();
	Renderer::init();

	while (Platform::tick()) {

	}

	Renderer::release();
	Platform::release();
	return 0;
}