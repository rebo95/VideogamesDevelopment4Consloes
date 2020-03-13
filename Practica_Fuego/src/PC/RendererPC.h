
#include<cstdint>
#include<SDL.h>

class Renderer {

private:
	static SDL_Renderer* renderer_;

public :
	//Inicializa recursos necesarios para renderer de SDL
	static void init();
	//Permite liberar los recursos utilizados por el renderer de SDL
	static void release();
};