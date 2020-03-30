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
			firePixelsBuffer[i][j] = 0;
		}
	}
}

Fire::~Fire()
{
}

//Actualiza el valor de todos los pixeles de la llamarada
void Fire::update(SimulationState state)
{
	for (int i = Fire::FIRE_HEIGHT -1; i >= 0; i--) {
		for (int j = Fire::FIRE_WIDTH - 1; j >= 0; j--) {
			if (i == FIRE_HEIGHT - 1)turnOnOffFire(state, j);
			else firePixelsBuffer[i][j] = updatePixel(i, j);
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

			Renderer::putPixel(posX, posY, paletaFuego[firePixelsBuffer[i][j]]);
		}
	}
}

//Modifica el valor del pixel que va a ser pintado
int Fire::updatePixel(int i, int j)
{
	int rnd;
	int i_pixel_of_reference = i + 1;
	int j_pixel_of_reference = j;

	//lógica de actualización del color del pixel que se va a modificar

	//Si nos encontramos en la parte izda del rectángulo que conforma la llamarada
	if (j == 0) {
		rnd = rand() % 2;
		if (rnd == 0) j_pixel_of_reference++;
	}
	else if (j == FIRE_WIDTH - 1) { //Si nos encontramos en la parte izda del rectángulo que conforma la llamarada
		rnd = rand() % 2;
		if (rnd == 0) j_pixel_of_reference--;
	}
	else {
		rnd = rand() % 3;
		if (rnd == 0) {
			j_pixel_of_reference--;	//miramos el pixel a la izda del que estamos pasando como entrada
		}
		else if (rnd == 1) {
			j_pixel_of_reference++;	//miramos el pixel a la izda del que estamos pasando como entrada
		}
	}

	int newPixelColor = firePixelsBuffer[i_pixel_of_reference][j_pixel_of_reference];

	//Lógica de enfriamiento, el pixel seleccionado toma el color del que tiene debajo o lo disminuye en uno
	rnd = rand() % 2;
	if (rnd == 0 && newPixelColor > 0) {//nótese que si el pixel de referencia está a negro no hay ningún color más frío
		newPixelColor = firePixelsBuffer[i_pixel_of_reference][j_pixel_of_reference] - 1;
	}

	//en cualquier otro caso el color se mantiene igual al de el pixel correspondiete 
	//(izq,der ó centr)de referencia que está debajo

	return newPixelColor;
}

//Enciende o apaga la simulación de la llamarada
void Fire::turnOnOffFire(SimulationState state, int j)
{
	int rnd = 0;
	switch (state)
	{

	case Fire::LIT:
		rnd = rand() % 2;
		if (rnd == 0) {
			firePixelsBuffer[FIRE_HEIGHT - 1][j] = NUMBER_OF_COLORS - 1;
		}
		break;
	case Fire::UNLIT:
		rnd = rand() % 2;
		if (rnd == 0) {
			firePixelsBuffer[FIRE_HEIGHT - 1][j] = 0;
		}
		break;
	default:
		break;
	}
}
