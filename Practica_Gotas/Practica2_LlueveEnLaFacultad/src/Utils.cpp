#include "Utils.h"

uint32_t Packcolor(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{

	uint32_t deserializedColor = 0;

	deserializedColor += r;
	deserializedColor <<= 8;
	deserializedColor += g;
	deserializedColor <<= 8;
	deserializedColor += b;
	deserializedColor <<= 8;
	deserializedColor += a;

	return deserializedColor;
}

void Unpackcolor(uint32_t color, uint8_t * result)
{

	result[1] = (color & 0xff000000) >> 24;
	result[2] = (color & 0x00ff0000) >> 16;
	result[3] = (color & 0x0000ff00) >> 8;
	result[0] = (color & 0x000000ff);
}


uint8_t Clamp(int min, int max, int value)
{
	if (value > max) return max;
	else if (value < min)return min;
	else return value;
}
