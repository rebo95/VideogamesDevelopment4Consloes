
#ifndef __RENDERER_PC_H
#define __RENDERER_PC_H


typedef unsigned __int32 uint32_t;
typedef unsigned __int8 uint8_t;

struct SDL_Window;
struct SDL_Renderer;

class Renderer {

private:
	static SDL_Renderer* renderer_;
	static SDL_Window* window_;				//Manejador de la ventana de SDL

	static const int FULLSCREEN = 0;			// Pantalla completa; 0:No, 1:Sí
	static const int WINDOW_WIDTH = 1280;			// Ancho de la pantalla
	static const int WINDOW_HEIGHT = 720;			// Alto de la pantalla

public:
	//Inicializa recursos necesarios para renderer de SDL
	static void init();
	//Permite liberar los recursos utilizados por el renderer de SDL
	static void release();

	//Pinta todo el frameBuffer del color especificado
	static void clear(uint32_t color = 0x000000ff);		//lo inicializamos a un color por defecto (negro)

	//Pinta un pizel del FrameBufer del color especificado en la posición especificada
	static void putPixel(int x, int y, uint32_t color);

	static void drawSimulation(int* heightBuffer, uint32_t* backgroundBuff, bool forcedPaint, bool* changes);

	//Vuelca el contenido de la FrameBuffer en la pantalla
	static void present();

	//Devuelve el ancho de la ventana de SDL
	static int getWidth();
	//Devuelve el alto de la ventana de SDL
	static int getHeight();

	//Devuelve el número de FrameBuffers utilizados por SDL
	static int getNumBuffers();

	//static SDL_Window* getWindow() { return window_; };	//Devuelve el manejador de la ventana de SDL

	//static SDL_Renderer* getRenderer() { return renderer_; }//Devuelve el renderer

};

#endif // !__RENDERER_PC_H
