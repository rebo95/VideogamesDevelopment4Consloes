

#include "Platform/Platform.h"
#include "Renderer/Renderer.h"
#include "Logic/Drops.h"
#include "Renderer/RenderThread.h"


int main() {


	Platform::init();
	Renderer::init();
	RenderThread::init();

	Drops drops;
	//int dim = Renderer::getHeight() * Renderer::getWidth();
	//uint32_t* picture_ = (uint32_t*)malloc(sizeof(uint32_t) * Renderer::getHeight() * Renderer::getWidth());

	//const char* c = "fdi.rgba";

	//Platform::loadImage(c, picture_ );
	int frames = 0;
	int numFrameBuffers = Renderer::getNumBuffers();

	while (Platform::tick()) {

		drops.update(frames);
		while (RenderThread::getNumFramesPending() > numFrameBuffers);
		frames++;
	}


	RenderThread::release();
	Renderer::release();
	Platform::release();

	return 0;
}