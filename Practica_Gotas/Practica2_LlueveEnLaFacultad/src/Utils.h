#ifndef __UTILS_H__
#define __UTILS_H__

typedef unsigned __int32 uint32_t;
typedef unsigned __int8 uint8_t;

uint32_t Packcolor(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 0xFF);
void Unpackcolor(uint32_t color, uint8_t* result);

//Función que limita un valor entre un mínimo y un máximo
uint8_t Clamp(int min, int max, int value);

#endif // !__UTILS_H__

