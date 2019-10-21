#ifndef _INC_GENERIC_H_
#define _INC_GENERIC_H_


#define  bitSet(value, bit)   ((value) |= (1UL << (bit))) 
#define  bitClr(value, bit)   ((value) &= ~(1UL << (bit))) 
#define  bitRd(value, bit)   (((value) >> (bit)) & 0x01)
#define  bitWr(value, bit, bitvalue)   (bitvalue ? bitSet(value, bit) : bitClr(value, bit))
#define  bit(b)   (1 << (b)) 






#endif // ! _INC_GENERIC_H_





