#include "PlatformPC.h"
#include "../Renderer.h"

SDL_Window* Platform::window_ = nullptr;

void Platform::init()
{
	srand(static_cast<unsigned int>(NULL));
	SDL_Init(SDL_INIT_EVERYTHING);
	window_ = SDL_CreateWindow("SDL Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, FULLSCREEN);
}

void Platform::release()
{
	SDL_DestroyWindow(window_);
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
	for (int i = 0; i < WINDOW_HEIGHT * WINDOW_WIDTH; i++) {
		r = fgetc(f);
		g = fgetc(f);
		b = fgetc(f);
		a = fgetc(f);

		//recordemos que nuestro putPixel funciona con los píxeles en formato uint32,
		//cada elemento de nuestra matriz buffer va a ser una combinación rgba, es decir
		//un color en el formato uint32

		buffer[i] = Renderer::deserializeColor(r, g, b); //RECORDAR AMPLIAR ESTE MËTODO PARA ALFA
	}

	fclose(f);
}
