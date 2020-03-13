#include "PlatformPC.h"


SDL_Window* Platform::window_ = nullptr;

void Platform::init()
{
	srand(static_cast<unsigned int>(NULL));
	SDL_Init(SDL_INIT_EVERYTHING);
	window_ = SDL_CreateWindow("SDL Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDHT, WINDOW_HEIGHT, FULLSCREEN);
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

