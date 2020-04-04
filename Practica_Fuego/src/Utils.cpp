#include "Utils.h"

uint32_t PackColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a )
{
	uint32_t deserializedColor = 0;
	deserializedColor += a;
	deserializedColor <<= 8;

	deserializedColor += r;
	deserializedColor <<= 8;

	deserializedColor += g;
	deserializedColor <<= 8;

	deserializedColor += b;

	return deserializedColor;
}

void UnpackColor(uint32_t color, uint8_t* sorce)
{
	sorce[0] = (color & 0xff000000) >> 24;
	sorce[1] = (color & 0x00ff0000) >> 16;
	sorce[2] = (color & 0x0000ff00) >> 8;
	sorce[3] = (color & 0x000000ff);
}
