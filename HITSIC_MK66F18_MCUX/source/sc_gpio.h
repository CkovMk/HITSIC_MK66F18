/*
 * sc_gpio.h
 *
 *  Created on: 2020年10月27日
 *      Author: 孙唯
 */

#ifndef SC_GPIO_H_
#define SC_GPIO_H_

#include"fsl_gpio.h"
#include "pin_mux.h"
#include "fsl_common.h"


#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

typedef struct _gpio_class {
    GPIO_Type *base;
    uint32_t pin;
} gpio_t;//gpio_t的对象只能被引用，不能被复制

extern gpio_t key_up;
extern gpio_t key_right;
extern gpio_t key_left;
extern gpio_t key_down;
extern gpio_t key_enter;

extern gpio_t boma1;
extern gpio_t boma2;
extern gpio_t boma3;
extern gpio_t boma4;

/**********************************************************************************************************************
*  @brief      GPIO输入检测
*  @param      gpio_t *        GPIO外设
*  @return     uint32_t        0/1
*  Sample usage:          GPIO_Check(&key_up);
*                         GPIO_Check(&boma1);
**********************************************************************************************************************/
uint32_t GPIO_Check(gpio_t *s);



#if defined(__cplusplus)
}
#endif /* __cplusplus */
#endif /* SC_GPIO_H_ */

