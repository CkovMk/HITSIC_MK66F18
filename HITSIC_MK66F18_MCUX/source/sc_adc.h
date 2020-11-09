/**
 * Copyright 2018 - 2020 HITSIC
 * All rights reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
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
uint32_t SCADC_Sample(ADC_Type *base, uint8_t channelGroup, uint8_t channel);



#endif /* SC_ADC_H_ */
