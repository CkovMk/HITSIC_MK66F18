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




void SCFTM_PWM_Change(FTM_Type *base, ftm_chnl_t chnlNumber, uint32_t dutyFreq, uint8_t dutyCycle)
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

/*!
 * brief Updates the duty cycle of an active PWM signal. High Resolution version by C.M.
 *
 * param base              FTM peripheral base address
 * param chnlNumber        The channel/channel pair number. In combined mode, this represents
 *                          the channel pair number
 * param currentPwmMode    The current PWM mode set during PWM setup
 * param dutyCyclePercent  New PWM pulse width; The value should be between 0 to 100
 *                          0=inactive signal(0% duty cycle)...
 *                          100=active signal (100% duty cycle)
 */
void FTM_UpdatePwmDutycycleHiRes(FTM_Type *base,
                            ftm_chnl_t chnlNumber,
                            ftm_pwm_mode_t currentPwmMode,
                            float dutyCyclePercent)
{
    uint32_t cnv, cnvFirstEdge = 0, mod;

    /* The CHANNEL_COUNT macro returns -1 if it cannot match the FTM instance */
    assert(-1 != FSL_FEATURE_FTM_CHANNEL_COUNTn(base));

    mod = base->MOD;
    if ((currentPwmMode == kFTM_EdgeAlignedPwm) || (currentPwmMode == kFTM_CenterAlignedPwm))
    {
        cnv = (uint16_t)((mod * dutyCyclePercent) / 100U);
        /* For 100% duty cycle */
        if (cnv >= mod)
        {
            cnv = mod + 1U;
        }
        base->CONTROLS[chnlNumber].CnV = cnv;
    }
    else
    {
        /* This check is added for combined mode as the channel number should be the pair number */
        if ((uint32_t)chnlNumber >= ((uint32_t)FSL_FEATURE_FTM_CHANNEL_COUNTn(base) / 2U))
        {
            return;
        }

        cnv = (uint16_t)((mod * dutyCyclePercent) / 100U);
        cnvFirstEdge = base->CONTROLS[((uint32_t)chnlNumber) * 2U].CnV;
        /* For 100% duty cycle */
        if (cnv >= mod)
        {
            cnv = mod + 1U;
        }
        base->CONTROLS[((uint32_t)chnlNumber * 2U) + 1U].CnV = cnvFirstEdge + cnv;
    }
}

void SCFTM_PWM_ChangeHiRes(FTM_Type *base, ftm_chnl_t chnlNumber, uint32_t dutyFreq, float dutyCycle)
{
      /* Disable channel output before updating the dutycycle */
      //FTM_UpdateChnlEdgeLevelSelect(base, chnlNumber, 0U);
      /* Update PWM duty cycle */
      FTM_UpdatePwmDutycycleHiRes(base, chnlNumber, kFTM_CenterAlignedPwm, dutyCycle);
      /* Software trigger to update registers */
      FTM_SetSoftwareTrigger(base, true);
      /* Start channel output with updated dutycycle */
      //FTM_UpdateChnlEdgeLevelSelect(base, chnlNumber, kFTM_HighTrue);//待定，不知道有没有问题
      return;
}


int16_t SCFTM_GetSpeed(FTM_Type *base)
{
    return (int16_t)FTM_GetQuadDecoderCounterValue(base);
}


void SCFTM_ClearSpeed(FTM_Type *base)
{
    FTM_ClearQuadDecoderCounterValue(base);
}






