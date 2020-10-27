/*
 * sc_adc.h
 *
 *  Created on: 2020年10月27日
 *      Author: Administrator
 */

#ifndef SC_ADC_H_
#define SC_ADC_H_

#include "fsl_adc16.h"
#include "peripherals.h"
#include "fsl_common.h"
#include "fsl_port.h"

typedef struct _ADC
{
  PORT_Type* PORT;
  uint8_t    PIN;
  ADC_Type*  ADC;
} Adc_t;

/**********************************************************************************************************************
*  @brief      ADC初始化
*  @param      NULL
*  @return     void
*  @since      v1.0
*  Sample usage:          AD_Init();
**********************************************************************************************************************/
void AD_Init(void);
/**********************************************************************************************************************
*  @brief      获取AD转化值
*  @param      base              ADC模块选择
*  @param      channelGroup       ADC模组，0或1，即A或B，按照MCUXpresso上选
*  @param      channel            ADC通道选择
*  @return     uint32_t   ADC采集数值
*  @since      v1.1
*  Sample usage:          ADC_Get(ADC0,0,12);
**********************************************************************************************************************/
uint32_t ADC_Get(ADC_Type *base, uint8_t channelGroup, uint8_t channel);



#endif /* SC_ADC_H_ */
