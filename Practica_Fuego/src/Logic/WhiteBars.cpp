#include "WhiteBars.h"

#include "../Renderer/PC/RendererPC.h"

WhiteBars::WhiteBars()
{
	num_bars_horizontal = 1 + Renderer::getWidth() / (BAR_WIDHT + BAR_INTER_SPACE);
	num_bars_vertical = 1 + (Renderer::getHeight() - 150) / (BAR_HEIHGT + BAR_INTER_SPACE);
}

WhiteBars::~WhiteBars()
{
}

void WhiteBars::render()
{
	for (int i = 0; i < num_bars_vertical; i++) {
		for (int j = 0; j < num_bars_horizontal; j++) {
			drawBar(offset_ + j * (BAR_WIDHT + BAR_INTER_SPACE), BAR_INTER_SPACE + i * (BAR_HEIHGT + BAR_INTER_SPACE));
		}
	}
}

void WhiteBars::render(int delta)
{
	for (int i = 0; i < num_bars_vertical; i++) {
		for (int j = 0; j < num_bars_horizontal; j++) {
			drawBar(offset_ + j * (BAR_WIDHT + BAR_INTER_SPACE), BAR_INTER_SPACE + i * (BAR_HEIHGT + BAR_INTER_SPACE), delta);
		}
	}
}

void WhiteBars::drawBar(int x, int y)
{
	for (int i = 0; i < BAR_HEIHGT; i++) {
		for (int j = 0; j < BAR_WIDHT; j++) {
			if (x + j > num_bars_horizontal * (BAR_WIDHT + BAR_INTER_SPACE)) {
				Renderer::putPixel(x + j - (num_bars_horizontal * (BAR_WIDHT + BAR_INTER_SPACE)), y + i, 0x00ffffff);
			}
			else {
				Renderer::putPixel(x + j, y + i, 0x00ffffff);
			}
			
		}
	}
}

void WhiteBars::drawBar(int x, int y, int delta)
{
	for (int i = 0; i < BAR_HEIHGT; i++) {
		//pintamos el fragmento de blanco nuevo que se tiene que pintar
		for (int j = BAR_WIDHT - delta; j < BAR_WIDHT; j++) { 
			// en el anterior frame la barra estaba en - delta, esto es, el final de la barra estaba en BAR_WIDHT - delta
			if (x + j > num_bars_horizontal * (BAR_WIDHT + BAR_INTER_SPACE)) {
				Renderer::putPixel(x + j - (num_bars_horizontal * (BAR_WIDHT + BAR_INTER_SPACE)), y + i, 0x00ffffff);
			}
			else {
				Renderer::putPixel(x + j, y + i, 0x00ffffff);
			}
		}

		//pintamos de negro el fragmento que tenemos que borrar
		for (int j = - delta; j < 0; j++) {
			//en el frame anterior el principo de la barra estaba en -d, ahora tenemos que poner en negro desde el ppio de la anterior
			//hasta el principio de la que se va a pintar en este frame, es decir, hasta el 0 de este frame
			if (x + j > num_bars_horizontal * (BAR_WIDHT + BAR_INTER_SPACE)) {
				Renderer::putPixel(x + j - (num_bars_horizontal * (BAR_WIDHT + BAR_INTER_SPACE)), y + i, 0xff000000);
			}
			else {
				Renderer::putPixel(x + j, y + i, 0xff000000);
			}
		}
	}

}

void WhiteBars::update()
{
	offset_+= barsVel;
	if (offset_ > num_bars_horizontal * (BAR_WIDHT + BAR_INTER_SPACE))
		offset_ = 0;
}
