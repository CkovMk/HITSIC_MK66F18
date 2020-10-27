/*
 * sc_gpio.c
 *
 *  Created on: 2020年10月27日
 *      Author: 孙唯  2739499384
 */

#include "sc_gpio.h"

/*
 *五项按键
 */
 gpio_t key_right = { GPIOE, 9 };
 gpio_t key_enter = { GPIOE, 10};
 gpio_t key_up    = { GPIOE, 7 };
 gpio_t key_left  = { GPIOE, 8 };
 gpio_t key_down  = { GPIOE, 11};
/*
 *拨码开关1-4
 */
 gpio_t boma1 =  {GPIOA, 15};
 gpio_t boma2 =  {GPIOA, 13};
 gpio_t boma3 =  {GPIOA, 11};
 gpio_t boma4 =  {GPIOA, 9 };

uint32_t GPIO_Check(gpio_t *s)
{
     SDK_DelayAtLeastUs(50*1000, 180*1000*1000);
     return GPIO_PinRead(s->base, s->pin);
}
