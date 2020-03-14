
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

	//Pinta todo el frameBuffer del color especificado
	static void clear(uint32_t color = 0x000000ff);		//lo inicializamos a un color por defecto (negro)

	//Pinta un pizel del FrameBufer del color especificado en la posición especificada
	static void putPixel(int x, int y, uint32_t color);
	//Vuelca el contenido de la FrameBuffer en la pantalla
	static void present();

	//Devuelve el ancho de la ventana de SDL
	static int getWidth();
	//Devuelve el alto de la ventana de SDL
	static int getHeight();

	//Devuelve el número de FrameBuffers utilizados por SDL
	static int getNumBuffers();


	//Descompone un color de 32 bytes en componentes ARGB de 8 bytes
	static uint8_t* serializeColor(uint32_t color);

	//Compone un color de 32 bytes a partir de valores de ARGB de 8 bytes
	static uint32_t deserializeColor(uint8_t r, uint8_t g, uint8_t b);

};