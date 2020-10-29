/******************************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2020,哈工大智能车创新俱乐部
 * All rights reserved.
 *
 * @file            FTM
 * @company         哈工大智能车创新俱乐部
 * @author          孙唯 qq2739499384
 * @version         v1.0
 * @Software        MCUXpresso IDE v11.1.1
 * @Target core     K66
 * @date            2020-9-27
 *
 * @note：
            哈尔滨工业大学智能车创新俱乐部专用，请勿泄露
***************************************************************************************************************************/

#include "sc_ftm.h"


void Ftm_PWM_Change(FTM_Type *base, ftm_chnl_t chnlNumber, uint32_t dutyFre, float dutyCycle)
{
      /* Disable channel output before updating the dutycycle */
      //FTM_UpdateChnlEdgeLevelSelect(base, chnlNumber, 0U);
      /* Update PWM duty cycle */
      FTM_UpdatePwmDutycycle(base, chnlNumber, kFTM_CenterAlignedPwm, dutyCycle);
      /* Software trigger to update registers */
      FTM_SetSoftwareTrigger(base, true);
      /* Start channel output with updated dutycycle */
      //FTM_UpdateChnlEdgeLevelSelect(base, chnlNumber, kFTM_HighTrue);//待定，不知道有没有问题
      return;
}


int16_t Ftm_GetSpeed(FTM_Type *base)
{
    return (int16_t)FTM_GetQuadDecoderCounterValue(base);
}


void Ftm_ClearSpeed(FTM_Type *base)
{
    FTM_ClearQuadDecoderCounterValue(base);
}






