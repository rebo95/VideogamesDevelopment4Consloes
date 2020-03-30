#ifndef __PLATFORM_PC_H__
#define __PLATFORM_PC_H__

//Clase platform
//Que gestiona los procesos de inicializaci�n y liberacion de recursos por parte de SDL


class Platform {

public :

	static void init();		//Inicializa recursos de SDL
	static void release();	//Libera los recursos espec�ficos de SDL
	static bool tick();		//Gestiona los eventos de SDL


};

#endif // !__PLATFORM_H__