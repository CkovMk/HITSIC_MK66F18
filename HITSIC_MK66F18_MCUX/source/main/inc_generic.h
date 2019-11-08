#ifndef _INC_GENERIC_H_
#define _INC_GENERIC_H_


#define  bitSet(value, bit)   ((value) |= (1UL << (bit))) 
#define  bitClr(value, bit)   ((value) &= ~(1UL << (bit))) 
#define  bitRd(value, bit)   (((value) >> (bit)) & 0x01)
#define  bitWr(value, bit, bitvalue)   (bitvalue ? bitSet(value, bit) : bitClr(value, bit))
#define  bit(b)   (1 << (b)) 

#define  CAM_IMG_R 120
#define  CAM_IMG_C 188

typedef struct _camera_img_t
{
	uint8_t img[CAM_IMG_R][CAM_IMG_C];
	uint64_t tStamp;//time stamp
}camera_img_t;


#endif // ! _INC_GENERIC_H_





