#ifdef PLATFORM_PC

#include "RendererPC.h"
#include"../../Utils.h"
#include <SDL.h>

SDL_Renderer* Renderer::renderer_ = nullptr;
SDL_Window* Renderer::window_ = nullptr;

void Renderer::init()
{
	window_ = SDL_CreateWindow("SDL Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDHT, WINDOW_HEIGHT, FULLSCREEN);
	renderer_ = SDL_CreateRenderer(getWindow(), -1, SDL_RENDERER_PRESENTVSYNC);
}

void Renderer::release()
{
	SDL_DestroyRenderer(renderer_);
	SDL_DestroyWindow(window_);
}

void Renderer::clear(uint32_t color)
{
	uint8_t c[4];
	UnpackColor(color, c);
	SDL_SetRenderDrawColor(renderer_, c[1], c[2], c[3], c[0]);
	SDL_RenderClear(renderer_);
}

void Renderer::putPixel(int x, int y, uint32_t color)
{
	uint8_t c[4];
	UnpackColor(color, c);
	SDL_SetRenderDrawColor(renderer_, c[1], c[2], c[3], c[0]);	//RGBA, recordar aquí que nosotros 
																//hemos estado almacenando el color como ARGB
	SDL_RenderDrawPoint(renderer_, x, y);
}

void Renderer::present()
{
	SDL_RenderPresent(renderer_);
}

int Renderer::getWidth()
{
	int w;
	SDL_GetWindowSize(getWindow(), &w, NULL);
	return w;
}

int Renderer::getHeight()
{
	int h;
	SDL_GetWindowSize(getWindow(), NULL, &h);
	return h;
}

int Renderer::getNumBuffers()
{
	Uint32 flags = SDL_GetWindowFlags(getWindow());
	return (flags & SDL_WINDOW_FULLSCREEN) ? 2 : 1;
	//condition ? result_if_true : result_if_false
	//esto es, si estamos en pantalla completa y los flags de la ventana marcan Fullscreen
	//tendremos 2 buffers, en el caso contrario (modo ventana pc) tendremos  buffer
}


#endif // PLATFORM_PC