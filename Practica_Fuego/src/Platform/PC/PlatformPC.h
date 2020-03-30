#ifndef __PLATFORM_PC_H__
#define __PLATFORM_PC_H__

//Clase platform
//Que gestiona los procesos de inicialización y liberacion de recursos por parte de SDL


class Platform {

public :

	static void init();		//Inicializa recursos de SDL
	static void release();	//Libera los recursos específicos de SDL
	static bool tick();		//Gestiona los eventos de SDL


};

#endif // !__PLATFORM_H__