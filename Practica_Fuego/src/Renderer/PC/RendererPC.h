#ifndef __RENDERER_PC_H__
#define __RENDERER_PC_H__


typedef unsigned __int32 uint32_t;
typedef unsigned __int8 uint8_t;

struct SDL_Window;
struct SDL_Renderer;

class Renderer {

private:
	static SDL_Renderer* renderer_;

	static SDL_Window* window_;				//Mnejador de la ventana de SDL
	static const int WINDOW_WIDHT = 1000;	//Ancho de la ventana
	static const int WINDOW_HEIGHT = 500;	//Alto de la ventana
	static const bool FULLSCREEN = 0;		//Opción pantalla completa No(0) - Si(1)

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

	static SDL_Window* getWindow() { return window_; };	//Devuelve el manejador de la ventana de SDL
};

#endif // !__RENDERER_PC_H