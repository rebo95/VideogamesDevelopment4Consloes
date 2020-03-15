#include "Fire.h"



const uint32_t Fire::paletaFuego[NUMBER_OF_COLORS] = {
		RGB(0x00,0x00,0x00),
		RGB(0x07,0x07,0x07),
		RGB(0x1F,0x07,0x07),
		RGB(0x2F,0x0F,0x07),
		RGB(0x47,0x0F,0x07),
		RGB(0x57,0x17,0x07),
		RGB(0x67,0x1F,0x07),
		RGB(0x77,0x1F,0x07),
		RGB(0x8F,0x27,0x07),
		RGB(0x9F,0x2F,0x07),
		RGB(0xAF,0x3F,0x07),
		RGB(0xBF,0x47,0x07),
		RGB(0xC7,0x47,0x07),
		RGB(0xDF,0x4F,0x07),
		RGB(0xDF,0x57,0x07),
		RGB(0xDF,0x57,0x07),
		RGB(0xD7,0x5F,0x07),
		RGB(0xD7,0x5F,0x07),
		RGB(0xD7,0x67,0x0F),
		RGB(0xCF,0x6F,0x0F),
		RGB(0xCF,0x77,0x0F),
		RGB(0xCF,0x7F,0x0F),
		RGB(0xCF,0x87,0x17),
		RGB(0xC7,0x87,0x17),
		RGB(0xC7,0x8F,0x17),
		RGB(0xC7,0x97,0x1F),
		RGB(0xBF,0x9F,0x1F),
		RGB(0xBF,0x9F,0x1F),
		RGB(0xBF,0xA7,0x27),
		RGB(0xBF,0xA7,0x27),
		RGB(0xBF,0xAF,0x2F),
		RGB(0xB7,0xAF,0x2F),
		RGB(0xB7,0xB7,0x2F),
		RGB(0xB7,0xB7,0x37),
		RGB(0xCF,0xCF,0x6F),
		RGB(0xDF,0xDF,0x9F),
		RGB(0xEF,0xEF,0xC7),
		RGB(0xFF,0xFF,0xFF)
};



Fire::Fire()
{
	//Colocamos el fuego en la posición inicial deseada
	posX_ = (Renderer::getWidth() - FIRE_WIDTH) / 2;
	posY_ = (Renderer::getHeight() - FIRE_HEIGHT);

	//inicializamos los colores del buffer de pixels que llevan la información del fuego

	for (int i = 0; i < Fire::FIRE_HEIGHT; i++) {
		for (int j = 0; j < Fire::FIRE_WIDTH; j++) {
			firePixelsBuffer[i][j] = paletaFuego[0];
		}
	}
}

Fire::~Fire()
{
}

//Actualiza el valor de todos los pixeles de la llamarada
void Fire::update(SimulationState State)
{
	for (int i = 0; i < Fire::FIRE_HEIGHT; i++) {
		for (int j = 0; j < Fire::FIRE_WIDTH; j++) {
			firePixelsBuffer[i][j] = updatePixel(firePixelsBuffer[i][j]);
		}
	}
}

void Fire::render()
{

	//A la hora de pintar el pixel en pantalla tenemos que tener en cuenta su posición y su color(temperatura)
	//La posición viene dada por la posición inicial y la posición dentro del bufer
	//La temperatura viene dada por el bufer de pixels del fuego
	int posX = 0;
	int posY = 0;

	for (int i = 0; i < Fire::FIRE_HEIGHT; i++) {
		for (int j = 0; j < Fire::FIRE_WIDTH; j++) {
			posX = posX_ + j;
			posY = posY_ + i;

			Renderer::putPixel(posX, posY, firePixelsBuffer[i][j]);
		}
	}
}

//Modifica el valor del pixel que va a ser pintado
uint32_t Fire::updatePixel(uint32_t currentColor)
{
	uint32_t newColor = 0;

	//lógica de actualización del color del pixel que se va a modificar

	return newColor;
}

//Enciende o apaga la simulación de la llamarada
void Fire::turnOnOffFire()
{
}
