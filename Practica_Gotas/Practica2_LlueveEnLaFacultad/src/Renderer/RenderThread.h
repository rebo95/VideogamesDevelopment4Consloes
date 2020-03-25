#ifndef __RENDER_THREAD_H__
#define __RENDER_THREAD_H__


#include <thread>
#include <atomic>

template<typename T>
class Queue;

//Para que el sistema funcione más cómodamente funcionaremos con modos de renderizado
//para esta hebra de render
enum RenderCommandType {
	CLEAR,
	DRAW_POINT,
	DRAW_SIMULATION,
	END_FRAME
};

//Parámetros del comando de renderizado DRAW_POINT
struct RenderCommandPutPixelParams {
	int x; 
	int y;
	uint32_t color;
};

//Parámetros del comando de renderizado DRAW_SIMULATION
struct RenderCommandDrawSimulationParams {
	int* heightBuffer;
	uint32_t* backgroundBuff;
	bool forcedPaint;
	bool* changes;
};

//Estructura que representa un comando de Renderizado
struct RenderCommand {

	RenderCommandType type;
	union RenderCommandParams {
		RenderCommandPutPixelParams ppParams;
		RenderCommandDrawSimulationParams dsParams;
	}params;


	//Constructora del struct por defecto
	RenderCommand(RenderCommandType t) : type(t) {};

	//Constructora del struct para RenderCommandParam de putPixelParams
	RenderCommand(RenderCommandType t, int x, int y, uint32_t color){
		type = t;
		params.ppParams.x = x;
		params.ppParams.y = y;
		params.ppParams.color = color;
	}

	//Constructora del struct para RenderCommandParam de DrawSimulationParams
	RenderCommand(RenderCommandType t, uint32_t* backgroundBuff, int* heightBuffer, bool* changes, bool forcedPaint) {
		type = t;
		params.dsParams.heightBuffer = heightBuffer;
		params.dsParams.backgroundBuff = backgroundBuff;
		params.dsParams.changes = changes;
		params.dsParams.forcedPaint = forcedPaint;
	}

};


//Fucnionaremos con una cola concurrente de comandos
//Creamos la clase RenderThread que nos va a pèrmitir 
//la creación, la ejecución y el liberado de la hebra

class RenderThread {

private: 
	static std::thread* thread_;				//Hebra de renderizado
	static std::atomic<bool> quitRequested_;	//Controla el bucle de renderizado
	static std::atomic<int> numFramesPending_;	//Número de frames pendientes de pintar
	static Queue<RenderCommand> commandsQueue_;	//Cola de comandos de renderizado


public:

	//Inicializado de la hebra de render
	static void init();
	//Encola comandos de renderizado
	static void enqueueCommand(RenderCommand c);
	//Libera la herbra de renderizado
	static void release();
	//Nos devuelve el número de frames pendientes por renderizar
	static int getNumFramesPending() { return numFramesPending_; }


private:
	//Bucle de renderizado
	static void renderLoop();


};

#endif // !__RENDER_THREAD_H__