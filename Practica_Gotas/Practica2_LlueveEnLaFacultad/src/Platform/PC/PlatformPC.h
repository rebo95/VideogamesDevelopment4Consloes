#ifndef __PLATFORM_PC_H__
#define __PLATFORM_PC_H__


typedef unsigned __int32 uint32_t;
//Clase platform
//Que gestiona los procesos de inicializaci�n y liberacion de recursos por parte de SDL

//#define FULLSCREEN 0				// Pantalla completa; 0:No, 1:S�
//#define WINDOW_WIDTH 1280			// Ancho de la pantalla
//#define WINDOW_HEIGHT 720			// Alto de la pantalla

class Platform {


public:

	static void init();		//Inicializa recursos de SDL
	static void release();	//Libera los recursos espec�ficos de SDL
	static bool tick();		//Gestiona los eventos de SDL


	static void loadImage(const char* filename, uint32_t* buffer);

};

#endif // !__PLATFORM_PC_H__