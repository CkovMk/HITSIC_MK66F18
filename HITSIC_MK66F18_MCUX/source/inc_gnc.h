/*
 * Beta-Cat Controll @ HSIC
 * @name	inc_gnc.h
 * Generic include file. Include ALL global varibles, golbal definitions HERE.
 * Warning: This file should be platform-independent.
*/

#ifndef _INC_GNC_H_
#define _INC_GNC_H_
/*
----------Global Definitions----------
*/
#define INC_USING_FREERTOS		0U



/*
----------Global Varible Definitions----------
*/
#ifndef _PI_ 
#define _PI_ 3.1415926f
#endif
#ifndef _G_ 
#define _G_ 9.8f
#endif

//original camera image size
#define GNC_CAM_IMG_R 400
#define GNC_CAM_IMG_C 640
//ipt image size, used for final digesting
#define GNC_IPT_IMG_R 100
#define GNC_IPT_IMG_C 160




/*
----------Bit Operation Definitions----------
*/
//#define  bitRd(value, bit)   (((value) >> (bit)) & 0x01)
//#define  bitWr(value, bit, bitvalue)   (bitvalue ? bitSet(value, bit) : bitClear(value, bit))
//#define  bitSet(value, bit)   ((value) |= (1UL << (bit)))
//#define  bitClr(value, bit)   ((value) &= ~(1UL << (bit)))
//#define  bit(b)   (1 << (b))





/*
----------Global Varible Type Definitions----------
*/
typedef float flt_t;
typedef int int_t;

struct gnc_rgb_t
{
	uint8_t r;
	uint8_t g;
	uint8_t b;
};

struct gnc_hsv_t
{
	uint8_t h;
	uint8_t s;
	uint8_t v;
};

struct gnc_rgbCamImg_t
{
	gnc_rgb_t pix[GNC_CAM_IMG_R][GNC_CAM_IMG_C];
};

struct gnc_rgbIptImg_t
{
	gnc_rgb_t pix[GNC_IPT_IMG_R][GNC_IPT_IMG_C];
};

struct gnc_hsvCamImg_t
{
	gnc_hsv_t pix[GNC_CAM_IMG_R][GNC_CAM_IMG_C];
};

struct gnc_hsvIptImg_t
{
	gnc_hsv_t pix[GNC_IPT_IMG_R][GNC_IPT_IMG_C];
};



/*
----------Global Function Linker Definitions----------
*/
//#define uart_putbuff UART_WriteBlocking






#endif // ! _INC_GNC_H_
