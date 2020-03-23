#include "Drops.h"
#include "Platform.h"
#include "Renderer.h"
#include "RenderThread.h"

Drops::Drops()
{
	int dim = Renderer::getHeight() * Renderer::getWidth();

	//reserva de memoria y asignación de espacios para los buffers
	picture_ = (uint32_t*)malloc(sizeof(uint32_t) * dim);
	heightBuffer1_ = (int*)calloc(dim, sizeof(int));
	heightBuffer2_ = (int*)calloc(dim, sizeof(int));
	changes_ = (bool*)calloc(dim, sizeof(bool));

	const char* c = "fdi.rgba";
	Platform::loadImage(c, picture_);
}

Drops::~Drops()
{

	free(heightBuffer1_);
	free(heightBuffer2_);
	free(picture_);
}

void Drops::update(int frames)
{
	if (frames % 2 == 0) simulate(heightBuffer1_, heightBuffer2_, frames);
	else simulate(heightBuffer2_, heightBuffer1_, frames);
}

void Drops::simulate(int * source, int * result, int frames)
{
	int h = Renderer::getHeight() ;
	int w = Renderer::getWidth();

	//int dim = h * w;

	//for (int i = 0; i < dim; i++) {

	//	uint32_t c = picture_[i];

	//	int a = i % Renderer::getWidth();
	//	int b = i / Renderer::getWidth();

	//	RenderThread::enqueueCommand(RenderCommand(DRAW_POINT, a, b, c));

	//}
	//RenderThread::enqueueCommand(RenderCommand(END_FRAME));


	//generación de gotas
	if (frames % DROP_TIMER == 0) {
		for (int i = 0; i < NUM_DROPS; i++) {
			int x = rand() % w;
			int y = rand() % h;

			int hg = MIN_INIT_HEIGHT + rand() % (MAX_INIT_HEIGHT - MIN_INIT_HEIGHT);

			source[y * w + x] = hg;
		}
	}

	//simulación de la gota
	for (size_t i = w; i < (w*h) - w; i++) { // vamos desde la primera fila sin contarla hasta la última sin tenerla en cuenta
		
		
		if (i % w == 0 || i % w == w - 1) continue; //Estamos eliminando los píxeles de la periferia de la gota


		//Simulamos las nuevas alturas
		result[i] = ((source[i - 1] + source[i + 1] + source[i - w] + source[i + w]) >> 1) - result[i];


		//Atenuamos la onda
		result[i] -= (result[i] >> 5);

		//Marcamos los píxeles que han cambiado 
		changes_[i] = (result[i] != source[i]);
	}

	if (frames < Renderer::getNumBuffers()) RenderThread::enqueueCommand(RenderCommand(DRAW_SIMULATION, picture_, result, changes_, true));
	else RenderThread::enqueueCommand(RenderCommand(DRAW_SIMULATION, picture_, result, changes_, false));
	RenderThread::enqueueCommand(RenderCommand(END_FRAME));

}
