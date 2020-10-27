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
        ADC_NUM为使用的ADC引脚数量
        .resolution为ADC位数，可调整精度
        .clockDivider为时钟预分频系数，值越低速度越快，ADC采集的值越不稳定
        上面两个参数的调整可参见芯片手册或MCUXpresso
    哈尔滨工业大学智能车创新俱乐部专用，请勿泄露
***************************************************************************************************************************/
#include "sc_adc.h"

#define ADC_NUM 2

Adc_t  Adcs[ADC_NUM] =
{
    {
      .PORT = PORTA,
      .PIN  = 7,
      .ADC  = ADC0
    },
    {
      .PORT = PORTA,
      .PIN  = 8,
      .ADC  = ADC0
    }
};


adc16_channel_config_t ADC_channelsConfig = {

    .enableDifferentialConversion = false,
    .enableInterruptOnConversionCompleted = false

};

const adc16_config_t ADC16config = {
  .referenceVoltageSource = kADC16_ReferenceVoltageSourceVref,
  .clockSource = kADC16_ClockSourceAsynchronousClock,
  .enableAsynchronousClock = true,
  .clockDivider = kADC16_ClockDivider2,
  .resolution = kADC16_ResolutionSE8Bit,
  .longSampleMode = kADC16_LongSampleDisabled,
  .enableHighSpeed = false,
  .enableLowPower = false,
  .enableContinuousConversion = false
};

const adc16_channel_mux_mode_t ADC16_1_muxMode = kADC16_ChannelMuxA;
const adc16_hardware_average_mode_t ADC16_1_hardwareAverageMode = kADC16_HardwareAverageDisabled;


void AD_Init(void)
{
  uint8_t i;
  for(i=0;i<ADC_NUM;i++)
  {
//  PORT_SetPinMux(Adcs[i].PORT, Adcs[i].PIN, kPORT_PinDisabledOrAnalog);
  ADC16_Init(Adcs[i].ADC, &ADC16config);
  /* Make sure, that software trigger is used */
  ADC16_EnableHardwareTrigger(Adcs[i].ADC, false);
  /* Configure hardware average mode */
  ADC16_SetHardwareAverage(Adcs[i].ADC, ADC16_1_hardwareAverageMode);
  /* Configure channel multiplexing mode */
  ADC16_SetChannelMuxMode(Adcs[i].ADC, ADC16_1_muxMode);
  }
}


uint32_t ADC_Get(ADC_Type *base, uint8_t channelGroup, uint8_t channel)
{

    ADC_channelsConfig.channelNumber = channel;
    ADC16_SetChannelConfig(base, channelGroup, &ADC_channelsConfig);
    while (0U == (kADC16_ChannelConversionDoneFlag &
        ADC16_GetChannelStatusFlags(base, channelGroup)));

    return  ADC16_GetChannelConversionValue(base, channelGroup);
}


