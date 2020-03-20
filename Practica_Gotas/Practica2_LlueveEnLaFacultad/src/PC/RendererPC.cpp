#include "RendererPC.h"
#include "..\Platform.h"

SDL_Renderer* Renderer::renderer_ = nullptr;

void Renderer::init()
{
	renderer_ = SDL_CreateRenderer(Platform::getWindow(), -1, SDL_RENDERER_PRESENTVSYNC);
}

void Renderer::release()
{
	SDL_DestroyRenderer(renderer_);
}

void Renderer::clear(uint32_t color)
{
	uint8_t* c = serializeColor(color);
	SDL_SetRenderDrawColor(renderer_, c[1], c[2], c[3], c[0]);
	SDL_RenderClear(renderer_);
}

void Renderer::putPixel(int x, int y, uint32_t color)
{
	uint8_t*c = serializeColor(color);
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
	SDL_GetWindowSize(Platform::getWindow(), &w, NULL);
	return w;
}

int Renderer::getHeight()
{
	int h;
	SDL_GetWindowSize(Platform::getWindow(), NULL, &h);
	return h;
}

int Renderer::getNumBuffers()
{
	Uint32 flags = SDL_GetWindowFlags(Platform::getWindow());
	return (flags & SDL_WINDOW_FULLSCREEN) ? 2 : 1;
	//condition ? result_if_true : result_if_false
	//esto es, si estamos en pantalla completa y los flags de la ventana marcan Fullscreen
	//tendremos 2 buffers, en el caso contrario (modo ventana pc) tendremos  buffer
}

uint8_t * Renderer::serializeColor(uint32_t color)
{
	uint8_t serializedResult[4];
	serializedResult[0] = (color & 0xff000000) >> 24;
	serializedResult[1] = (color & 0x00ff0000) >> 16;
	serializedResult[2] = (color & 0x0000ff00) >> 8;
	serializedResult[3] = (color & 0x000000ff);

	return serializedResult;
}

uint32_t Renderer::deserializeColor(uint8_t r, uint8_t g, uint8_t b)
{
	uint32_t deserializedColor = 0;
	deserializedColor += 0xff;
	deserializedColor <<= 8;

	deserializedColor += r;
	deserializedColor <<= 8;

	deserializedColor += g;
	deserializedColor <<= 8;

	deserializedColor += b;

	return deserializedColor;
}