#include "RenderThread.h"
#include "Renderer.h"

std::thread* RenderThread::thread_ = nullptr;		//Inicialización hebra de renderizado
std::atomic<bool> RenderThread::quitRequested_;		//Inicialización controla el bucle de renderizado
std::atomic<int> RenderThread:: numFramesPending_;	//Inicialización número de frames pendientes de pintar
Queue<RenderCommand> RenderThread::commandsQueue_;	//Inicialización cola de comandos de renderizado


RenderThread::RenderThread()
{
}

RenderThread::~RenderThread()
{
	release();
}

void RenderThread::init()
{
	if (!thread_) {
		thread_ = new std::thread(&RenderThread::renderLoop);
		quitRequested_ = false;
	}
}

void RenderThread::enqueueCommand(RenderCommand c)
{
	if (c.type == END_FRAME) numFramesPending_++; 
	//Si nos piden que terminemos el frame sumamos uno al número de frames a imprimir en pantalla
	commandsQueue_.push(c);
}

void RenderThread::release()
{
	if (thread_) {
		quitRequested_ = true;
		//enqueueCommand(RenderCommand(END_FRAME)); // si descomento esto me sale el asertion fail
		thread_->join();
		delete thread_;
		thread_ = nullptr;
	}
}

void RenderThread::renderLoop()
{
	numFramesPending_ = 0;
	quitRequested_ = false; 
	//recordemos que son variables atómicas y que se van a modificar desde fuera de la hebra
	//de render en este caso

	while (!quitRequested_)
	{
		while (commandsQueue_.front().type != END_FRAME) {

			RenderCommand c = commandsQueue_.pop();
			if(c.type == CLEAR) Renderer::clear(0xff0000ff);
			else if (c.type == DRAW_POINT)Renderer::putPixel(c.params.ppParams.x, c.params.ppParams.y, c.params.ppParams.color);
			else if (c.type == DRAW_SIMULATION) drawSimulation(c);
		}
		commandsQueue_.pop();
		numFramesPending_--;
		Renderer::present();
	}
}

void RenderThread::drawSimulation(RenderCommand c)
{
	for (size_t i = 0; i < Renderer::getHeight()*Renderer::getWidth(); i++) {

		if (c.params.dsParams.forcedPaint || c.params.dsParams.changes[i]) {

			int offset = c.params.dsParams.heightBuffer[i - 1] - c.params.dsParams.heightBuffer[i + 1];

			uint8_t* color = Renderer::serializeColor(c.params.dsParams.backgroundBuff[i]);
			//recordemos que los colores los tenemos almacenados como ARGB en nuestro buffer (de ahi que empecemos en 1)
			color[1] = clamp(0, 225, (int)color[1] - (int)offset);
			color[2] = clamp(0, 225, (int)color[2] - (int)offset);
			color[3] = clamp(0, 255, (int)color[3] - (int)offset);
			uint32_t c = Renderer::deserializeColor(color[1], color[2], color[3]);

			int a = i % Renderer::getWidth();
			int b = i / Renderer::getWidth();


			Renderer::putPixel(a, b, c);
		}
	}


}

uint8_t RenderThread::clamp(int min, int max, int value)
{
	if (value > max) return max;
	else if (value < min)return min;
	else return value;
}
