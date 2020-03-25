#include "RenderThread.h"
#include "Renderer.h"
#include "Queue.h"

std::thread* RenderThread::thread_ = nullptr;		//Inicialización hebra de renderizado
std::atomic<bool> RenderThread::quitRequested_;		//Inicialización controla el bucle de renderizado
std::atomic<int> RenderThread:: numFramesPending_;	//Inicialización número de frames pendientes de pintar
Queue<RenderCommand> RenderThread::commandsQueue_;	//Inicialización cola de comandos de renderizado


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
		enqueueCommand(RenderCommand(END_FRAME)); // si descomento esto me sale el asertion fail
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
			else if (c.type == DRAW_SIMULATION) Renderer::drawSimulation(c.params.dsParams.heightBuffer, c.params.dsParams.backgroundBuff, 
				c.params.dsParams.forcedPaint, c.params.dsParams.changes);
		}
		commandsQueue_.pop();
		numFramesPending_--;
		Renderer::present();
	}
}
