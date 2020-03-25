#ifdef PLATFORM_PC

#include <ctime>
#include <random>
#include <iostream>

#include <SDL.h>
#include "../../Utils.h"

#include "PlatformPC.h"
#include "../../Renderer/PC/RendererPC.h"



void Platform::init()
{
	srand(static_cast<unsigned int>(NULL));
	SDL_Init(SDL_INIT_EVERYTHING);

}

void Platform::release()
{

	SDL_Quit();
}

bool Platform::tick()
{
	SDL_Event event;

	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT || event.type == SDL_KEYDOWN || event.type == SDL_MOUSEBUTTONDOWN)
			return false;
	}
	return true;
}

void Platform::loadImage(const char* filename, uint32_t * buffer)
{
	//nuestro buffer al igual que pasaba con el fuego va a ser la matriz que contenga la información de todos los
	//pixeles que van a ser renderizados posteriormente en la pantalla.

	//el método cargará eb un "buffer" (manera que nosotros tenemos de enteder la lógica de pintado)
	uint8_t r, g, b, a;
	FILE* f = fopen(filename, "rb");

	if (!f) { std::cerr << "No se pudo abrir el archivo o no se ha encontrado"; return; }
	//estilo de programación, si se cumple lo de arriba se abandona el método 
	for (int i = 0; i < Renderer::getHeight() * Renderer::getWidth(); i++) {
		r = fgetc(f);
		g = fgetc(f);
		b = fgetc(f);
		a = fgetc(f);

		//recordemos que nuestro putPixel funciona con los píxeles en formato uint32,
		//cada elemento de nuestra matriz buffer va a ser una combinación rgba, es decir
		//un color en el formato uint32

		buffer[i] = Packcolor(r, g, b, a);
	}

	fclose(f);
}


#endif // PLATFORM_PC