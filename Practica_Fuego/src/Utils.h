#ifndef __UTILS_H__
#define __UTILS_H__

typedef unsigned __int32 uint32_t;
typedef unsigned __int8 uint8_t;


uint32_t PackColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 0xFF);
void UnpackColor(uint32_t color, uint8_t* sorce);



#endif // !__UTILS_H__

