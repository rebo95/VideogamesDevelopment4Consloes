#ifdef PLATFORM_PC


#include<SDL.h>
#include "RendererPC.h"
#include"../../Utils.h"


SDL_Renderer* Renderer::renderer_ = nullptr;
SDL_Window* Renderer::window_ = nullptr;

void Renderer::init()
{
	window_ = SDL_CreateWindow("SDL Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, FULLSCREEN);
	renderer_ = SDL_CreateRenderer(window_, -1, SDL_RENDERER_PRESENTVSYNC);

}

void Renderer::release()
{
	SDL_DestroyRenderer(renderer_);
	SDL_DestroyWindow(window_);
}

void Renderer::clear(uint32_t color)
{
	uint8_t c[4];
	Unpackcolor(color,c);
	SDL_SetRenderDrawColor(renderer_, c[1], c[2], c[3], c[0]);
	SDL_RenderClear(renderer_);
}

void Renderer::putPixel(int x, int y, uint32_t color)
{
	uint8_t c[4];
	Unpackcolor(color, c);
	SDL_SetRenderDrawColor(renderer_, c[1], c[2], c[3], c[0]);	//RGBA, recordar aquí que nosotros 
																//hemos estado almacenando el color como ARGB
	SDL_RenderDrawPoint(renderer_, x, y);
}

void Renderer::drawSimulation(int * heightBuffer, uint32_t * backgroundBuff, bool forcedPaint, bool * changes)
{
		for (int i = 0; i < Renderer::getHeight()*Renderer::getWidth(); i++) {

			if (forcedPaint || changes[i]) {

				int offset = heightBuffer[i - 1] - heightBuffer[i + 1];

				uint8_t color[4];
				Unpackcolor(backgroundBuff[i], color);
				//recordemos que los colores los tenemos almacenados como ARGB en nuestro buffer (de ahi que empecemos en 1)
				color[1] = Clamp(0, 225, (int)color[1] - (int)offset);
				color[2] = Clamp(0, 225, (int)color[2] - (int)offset);
				color[3] = Clamp(0, 255, (int)color[3] - (int)offset);

				uint32_t c = Packcolor(color[1], color[2], color[3]);

				int a = i % Renderer::getWidth();
				int b = i / Renderer::getWidth();

				Renderer::putPixel(a, b, c);
			}
		}
}

void Renderer::present()
{
	SDL_RenderPresent(renderer_);
}

int Renderer::getWidth()
{
	int w;
	SDL_GetWindowSize(window_, &w, NULL);
	return w;
}

int Renderer::getHeight()
{
	int h;
	SDL_GetWindowSize(window_, NULL, &h);
	return h;
}

int Renderer::getNumBuffers()
{
	Uint32 flags = SDL_GetWindowFlags(window_);
	return (flags & SDL_WINDOW_FULLSCREEN) ? 2 : 1;
	//condition ? result_if_true : result_if_false
	//esto es, si estamos en pantalla completa y los flags de la ventana marcan Fullscreen
	//tendremos 2 buffers, en el caso contrario (modo ventana pc) tendremos  buffer
}




#endif // PLATFORM_PC