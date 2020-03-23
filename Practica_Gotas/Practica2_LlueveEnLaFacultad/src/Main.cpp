
#include <SDL.h>
#include "Platform.h"
#include "Renderer.h"
#include "Drops.h"
#include "RenderThread.h"


int main(int arg, char** argv) {


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
		//for (int i = 0; i < dim; i++) {

		//		uint32_t c = picture_[i];

		//		int a = i % Renderer::getWidth();
		//		int b = i / Renderer::getWidth();

		//		Renderer::putPixel(a, b, c);
		//	}

		//Renderer::present();
	}

	Renderer::release();
	Platform::release();
	RenderThread::release();
	return 0;
}