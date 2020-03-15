
#include "Platform.h"
#include "Renderer.h"

//Definimos la macro RGB para la paleta dada por el cliente
#define RGB(a, b, c) Renderer::deserializeColor(a, b, c)
//Este macro est� cogiendo los elementos del array que nos han dado y los est� convirtiendo autom�ticamente
//al formato deserializado de 32 bits

//Clase Fire desde donde se gestiona la l�gica principal de la llamarada


class Fire {

private :
	int posX_;								//Posici�n X de la llamarada
	int posY_;								//Posici�n Y de la llamarada

	static const int FIRE_HEIGHT = 100;		//Alto de la llamarada
	static const int FIRE_WIDTH = 500;		//Ancho de la llamarada

	//atendiendo a la teor�a de que cargamos los buffers y plasmamos en pantalla los mismos
	int firePixelsBuffer[FIRE_HEIGHT][FIRE_WIDTH];

	static const int NUMBER_OF_COLORS = 38;
	static const uint32_t paletaFuego[NUMBER_OF_COLORS];

public:

	Fire();
	~Fire();

	//Para la simulaci�n se nos han pedido tres modos o estados 
	//Defecto, Encendido, Apagado

	enum SimulationState {
		DEFAULT,
		LIT,
		UNLIT
	};

	//M�todo update para la l�gica de la llamarada, dependera del estado de la simulaci�n
	void update(SimulationState State);

	//M�todo pintado o renderizado de la llamarada
	void render();

private:
	int updatePixel(int i, int j);
	void turnOnOffFire(SimulationState state, int j);
};