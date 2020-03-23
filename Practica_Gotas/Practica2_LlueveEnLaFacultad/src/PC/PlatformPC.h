
#include <SDL.h>
#include <ctime>
#include <random>
#include <iostream>


//Clase platform
//Que gestiona los procesos de inicializaci�n y liberacion de recursos por parte de SDL

//#define FULLSCREEN 0				// Pantalla completa; 0:No, 1:S�
//#define WINDOW_WIDTH 1280			// Ancho de la pantalla
//#define WINDOW_HEIGHT 720			// Alto de la pantalla

class Platform {
private:
	static SDL_Window* window_;				//Mnejador de la ventana de SDL
	static const int FULLSCREEN = 0;			// Pantalla completa; 0:No, 1:S�
	static const int WINDOW_WIDTH = 1280;			// Ancho de la pantalla
	static const int WINDOW_HEIGHT = 720;			// Alto de la pantalla

public:

	static void init();		//Inicializa recursos de SDL
	static void release();	//Libera los recursos espec�ficos de SDL
	static bool tick();		//Gestiona los eventos de SDL

	static SDL_Window* getWindow() { return window_; };	//Devuelve el manejador de la ventana de SDL
	static void loadImage(const char* filename, uint32_t* buffer);


};