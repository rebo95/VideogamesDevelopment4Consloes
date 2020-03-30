#ifdef PLATFORM_PC


#include "PlatformPC.h"

#include <SDL.h>
#include <random>


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


#endif // PLATFORM_PC


