/*
 * sc_adc.h
 *
 *  Created on: 2020年10月27日
 *      Author: 孙唯
 */

#ifndef SC_ADC_H_
#define SC_ADC_H_

#include "fsl_adc16.h"
#include "peripherals.h"
#include "fsl_common.h"
#include "fsl_port.h"


/**********************************************************************************************************************
*  @brief      获取AD转化值
*  @param      base               ADC模块选择
*  @param      channelGroup       ADC模组，0或1，即A或B，按照MCUXpresso上选
*  @param      channel            ADC通道选择
*  @return     uint32_t   ADC采集数值
*  @since      v1.1
*  Sample usage:          SCADC_GetSample(ADC0,0,12);
**********************************************************************************************************************/
uint32_t SCADC_GetSample(ADC_Type *base, uint8_t channelGroup, uint8_t channel);



#endif /* SC_ADC_H_ */
