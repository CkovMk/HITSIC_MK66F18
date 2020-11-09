/******************************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2020,哈工大智能车创新俱乐部
 * All rights reserved.
 *
 * @file            ADC
 * @company         哈工大智能车创新俱乐部
 * @author          孙唯 qq2739499384
 * @version         v1.0
 * @Software        MCUXpresso IDE v11.1.1
 * @Target core     K66
 * @date            2020-10-27
 *
 * @note：

    哈尔滨工业大学智能车创新俱乐部专用，请勿泄露
***************************************************************************************************************************/
#include "sc_adc.h"



adc16_channel_config_t ADC_channelsConfig = {

    .enableDifferentialConversion = false,
    .enableInterruptOnConversionCompleted = false

};


uint32_t SCADC_Sample(ADC_Type *base, uint8_t channelGroup, uint8_t channel)
{

    ADC_channelsConfig.channelNumber = channel;
    ADC16_SetChannelConfig(base, channelGroup, &ADC_channelsConfig);
    while (0U == (kADC16_ChannelConversionDoneFlag &
        ADC16_GetChannelStatusFlags(base, channelGroup)));

    return  ADC16_GetChannelConversionValue(base, channelGroup);
}


