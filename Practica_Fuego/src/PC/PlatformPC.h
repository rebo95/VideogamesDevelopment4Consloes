
#include <SDL.h>
#include <ctime>
#include <random>
#include <iostream>


//Clase platform
//Que gestiona los procesos de inicialización y liberacion de recursos por parte de SDL


class Platform {
private :
	static SDL_Window* window_;				//Mnejador de la ventana de SDL
	static const int WINDOW_WIDHT = 1000;	//Ancho de la ventana
	static const int WINDOW_HEIGHT = 500;	//Alto de la ventana
	static const bool FULLSCREEN = 0;		//Opción pantalla completa No(0) - Si(1)

public :

	static void init();		//Inicializa recursos de SDL
	static void release();	//Libera los recursos específicos de SDL
	static bool tick();		//Gestiona los eventos de SDL


	static SDL_Window* getWindow() { return window_; };	//Devuelve el manejador de la ventana de SDL

};