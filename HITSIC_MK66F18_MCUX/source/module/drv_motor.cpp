#include "drv_motor.hpp"

void PWM_UpdatePwmDutycycleHiRes(PWM_Type *base,
                                 pwm_submodule_t subModule,
                                 pwm_channels_t pwmSignal,
                                 pwm_mode_t currPwmMode,
                                 float dutyCyclePercent)
{
    assert(dutyCyclePercent <= 100.0f);
    assert(pwmSignal < 2);
    uint32_t pulseCnt = 0, pwmHighPulse = 0;
    int16_t modulo = 0;

    switch (currPwmMode)
    {
    case kPWM_SignedCenterAligned:
        modulo = base->SM[subModule].VAL1;
        pulseCnt = modulo * 2;
        /* Calculate pulse width */
        pwmHighPulse = (((float)pulseCnt) * dutyCyclePercent) / 100.0f;

        /* Setup the PWM dutycycle */
        if (pwmSignal == kPWM_PwmA)
        {
            base->SM[subModule].VAL2 = (-(pwmHighPulse / 2));
            base->SM[subModule].VAL3 = (pwmHighPulse / 2);
        }
        else
        {
            base->SM[subModule].VAL4 = (-(pwmHighPulse / 2));
            base->SM[subModule].VAL5 = (pwmHighPulse / 2);
        }
        break;
    case kPWM_CenterAligned:
        pulseCnt = base->SM[subModule].VAL1;
        /* Calculate pulse width */
        pwmHighPulse = (pulseCnt * dutyCyclePercent) / 10000;

        /* Setup the PWM dutycycle */
        if (pwmSignal == kPWM_PwmA)
        {
            base->SM[subModule].VAL2 = ((pulseCnt - pwmHighPulse) / 2);
            base->SM[subModule].VAL3 = ((pulseCnt + pwmHighPulse) / 2);
        }
        else
        {
            base->SM[subModule].VAL4 = ((pulseCnt - pwmHighPulse) / 2);
            base->SM[subModule].VAL5 = ((pulseCnt + pwmHighPulse) / 2);
        }
        break;
    case kPWM_SignedEdgeAligned:
        modulo = base->SM[subModule].VAL1;
        pulseCnt = modulo * 2;
        /* Calculate pulse width */
        pwmHighPulse = (pulseCnt * dutyCyclePercent) / 10000;

        /* Setup the PWM dutycycle */
        if (pwmSignal == kPWM_PwmA)
        {
            base->SM[subModule].VAL2 = (-modulo);
            base->SM[subModule].VAL3 = (-modulo + pwmHighPulse);
        }
        else
        {
            base->SM[subModule].VAL4 = (-modulo);
            base->SM[subModule].VAL5 = (-modulo + pwmHighPulse);
        }
        break;
    case kPWM_EdgeAligned:
        pulseCnt = base->SM[subModule].VAL1;
        /* Calculate pulse width */
        pwmHighPulse = (pulseCnt * dutyCyclePercent) / 10000;

        /* Setup the PWM dutycycle */
        if (pwmSignal == kPWM_PwmA)
        {
            base->SM[subModule].VAL2 = 0;
            base->SM[subModule].VAL3 = pwmHighPulse;
        }
        else
        {
            base->SM[subModule].VAL4 = 0;
            base->SM[subModule].VAL5 = pwmHighPulse;
        }
        break;
    default:
        break;
    }
}

status_t motor_enable(bool b)
{
    if (b == false || (!motor_getFault()))
    {
        GPIO_PinWrite(RTE_MOTOR_EN_GPIO, RTE_MOTOR_EN_PIN, b);
        return kStatus_Success;
    }
    else
    {
        return kStatus_Fail;
    }
}
bool motor_getFault(void)
{
    return !(CMP_MOTOR_IL_ADDR->SCR & CMP_MOTOR_IR_ADDR->SCR & 0x01);
}
status_t motor_clearFault(void)
{
    if (!motor_getFault())
    {
        return kStatus_Success;
    }
    XBARA_SetSignalsConnection(XBARA1, kXBARA1_InputLogicHigh, kXBARA1_OutputAcmp1Sample); /* ACMP1_OUT output assigned to XBARA1_IN26 input is connected to XBARA1_OUT20 output assigned to ACMP1_SAMPLE */
    XBARA_SetSignalsConnection(XBARA1, kXBARA1_InputLogicHigh, kXBARA1_OutputAcmp4Sample); /* ACMP4_OUT output assigned to XBARA1_IN29 input is connected to XBARA1_OUT23 output assigned to ACMP4_SAMPLE */
    uint32_t wait = 1000;
    while (--wait)
    {
        if (!motor_getFault())
        {
            break;
        }
    }
    //set window back
    XBARA_SetSignalsConnection(XBARA1, kXBARA1_InputAcmp1Out, kXBARA1_OutputAcmp1Sample); /* ACMP1_OUT output assigned to XBARA1_IN26 input is connected to XBARA1_OUT20 output assigned to ACMP1_SAMPLE */
    XBARA_SetSignalsConnection(XBARA1, kXBARA1_InputAcmp4Out, kXBARA1_OutputAcmp4Sample); /* ACMP4_OUT output assigned to XBARA1_IN29 input is connected to XBARA1_OUT23 output assigned to ACMP4_SAMPLE */

    if (!motor_getFault())
    {
        return kStatus_Success;
    }
    else
    {
        return kStatus_Fail;
    }
}

void motor_update(int8_t dutyL, int8_t dutyR)
{
    dutyL = (dutyL < -100 ? -100 : (dutyL > 100 ? 100 : dutyL));
    dutyR = (dutyR < -100 ? -100 : (dutyR > 100 ? 100 : dutyR));
    if (dutyL < 0)
    {
        PWM_UpdatePwmDutycycle(PWM_MOTOR_PWM_ADDR, PWM_MOTOR_L_PWM_MODULE, kPWM_PwmA, kPWM_CenterAligned, 0);
        PWM_UpdatePwmDutycycle(PWM_MOTOR_PWM_ADDR, PWM_MOTOR_L_PWM_MODULE, kPWM_PwmB, kPWM_CenterAligned, -dutyL);
    }
    else
    {
        PWM_UpdatePwmDutycycle(PWM_MOTOR_PWM_ADDR, PWM_MOTOR_L_PWM_MODULE, kPWM_PwmA, kPWM_CenterAligned, dutyL);
        PWM_UpdatePwmDutycycle(PWM_MOTOR_PWM_ADDR, PWM_MOTOR_L_PWM_MODULE, kPWM_PwmB, kPWM_CenterAligned, 0);
    }
    if (dutyR < 0)
    {
        PWM_UpdatePwmDutycycle(PWM_MOTOR_PWM_ADDR, PWM_MOTOR_R_PWM_MODULE, kPWM_PwmA, kPWM_CenterAligned, 0);
        PWM_UpdatePwmDutycycle(PWM_MOTOR_PWM_ADDR, PWM_MOTOR_R_PWM_MODULE, kPWM_PwmB, kPWM_CenterAligned, -dutyR);
    }
    else
    {
        PWM_UpdatePwmDutycycle(PWM_MOTOR_PWM_ADDR, PWM_MOTOR_R_PWM_MODULE, kPWM_PwmA, kPWM_CenterAligned, dutyR);
        PWM_UpdatePwmDutycycle(PWM_MOTOR_PWM_ADDR, PWM_MOTOR_R_PWM_MODULE, kPWM_PwmB, kPWM_CenterAligned, 0);
    }
    PWM_SetPwmLdok(PWM_MOTOR_PWM_ADDR, PWM_MOTOR_L_PWM_CTRLMODULE | PWM_MOTOR_R_PWM_CTRLMODULE, true);
}

void motor_update(float dutyL, float dutyR)
{
    dutyL = (dutyL < -100.0f ? -100.0f : (dutyL > 100.0f ? 100.0f : dutyL));
    dutyR = (dutyR < -100.0f ? -100.0f : (dutyR > 100.0f ? 100.0f : dutyR));
    if (dutyL < 0)
    {
        PWM_UpdatePwmDutycycleHiRes(PWM_MOTOR_PWM_ADDR, PWM_MOTOR_L_PWM_MODULE, kPWM_PwmA, kPWM_CenterAligned, 0);
        PWM_UpdatePwmDutycycleHiRes(PWM_MOTOR_PWM_ADDR, PWM_MOTOR_L_PWM_MODULE, kPWM_PwmB, kPWM_CenterAligned, -dutyL);
    }
    else
    {
        PWM_UpdatePwmDutycycleHiRes(PWM_MOTOR_PWM_ADDR, PWM_MOTOR_L_PWM_MODULE, kPWM_PwmA, kPWM_CenterAligned, dutyL);
        PWM_UpdatePwmDutycycleHiRes(PWM_MOTOR_PWM_ADDR, PWM_MOTOR_L_PWM_MODULE, kPWM_PwmB, kPWM_CenterAligned, 0);
    }
    if (dutyR < 0)
    {
        PWM_UpdatePwmDutycycleHiRes(PWM_MOTOR_PWM_ADDR, PWM_MOTOR_R_PWM_MODULE, kPWM_PwmA, kPWM_CenterAligned, 0);
        PWM_UpdatePwmDutycycleHiRes(PWM_MOTOR_PWM_ADDR, PWM_MOTOR_R_PWM_MODULE, kPWM_PwmB, kPWM_CenterAligned, -dutyR);
    }
    else
    {
        PWM_UpdatePwmDutycycleHiRes(PWM_MOTOR_PWM_ADDR, PWM_MOTOR_R_PWM_MODULE, kPWM_PwmA, kPWM_CenterAligned, dutyR);
        PWM_UpdatePwmDutycycleHiRes(PWM_MOTOR_PWM_ADDR, PWM_MOTOR_R_PWM_MODULE, kPWM_PwmB, kPWM_CenterAligned, 0);
    }
    PWM_SetPwmLdok(PWM_MOTOR_PWM_ADDR, PWM_MOTOR_L_PWM_CTRLMODULE | PWM_MOTOR_R_PWM_CTRLMODULE, true);
}

void motor_getEncCount(int32_t *cntL, int32_t *cntR)
{
    *cntL = (int32_t)ENC_GetPositionValue(ENC_MOTOR_L_ADDR);
    *cntR = (int32_t)ENC_GetPositionValue(ENC_MOTOR_R_ADDR);
}
void motor_getCurrent(float *IL, float *IR)
{
    adc_channel_config_t adc_chnlCfg;
    {
        adc_chnlCfg.channelNumber = ADC_MOTORSERVO_IL_Chnl;
        adc_chnlCfg.enableInterruptOnConversionCompleted = false;
    }
    ADC_SetChannelConfig(ADC_MOTORSERVO_I_ADDR, 0U, &adc_chnlCfg);
    while (0U == ADC_GetChannelStatusFlags(ADC_MOTORSERVO_I_ADDR, 0U));
    *IL =  ADC_GetChannelConversionValue(ADC_MOTORSERVO_I_ADDR, 0U);

    {
        adc_chnlCfg.channelNumber = ADC_MOTORSERVO_IR_Chnl;
        adc_chnlCfg.enableInterruptOnConversionCompleted = false;
    }
    ADC_SetChannelConfig(ADC_MOTORSERVO_I_ADDR, 0U, &adc_chnlCfg);
    while (0U == ADC_GetChannelStatusFlags(ADC_MOTORSERVO_I_ADDR, 0U));
    *IR =  ADC_GetChannelConversionValue(ADC_MOTORSERVO_I_ADDR, 0U);
}

//*************servo*************

status_t servo_enable(bool b)
{
    if (b == false || (!servo_getFault()))
    {
        GPIO_PinWrite(RTE_SERVO_EN_GPIO, RTE_SERVO_EN_PIN, b);
        return kStatus_Success;
    }
    else
    {
        return kStatus_Fail;
    }
}
bool servo_getFault(void)
{
    return !(CMP_SERVO_IF_ADDR->SCR & CMP_SERVO_IB_ADDR->SCR & 0x01);
}
status_t servo_clearFault(void)
{
    if (!servo_getFault())
    {
        return kStatus_Success;
    }
    XBARA_SetSignalsConnection(XBARA1, kXBARA1_InputLogicHigh, kXBARA1_OutputAcmp2Sample); /* ACMP1_OUT output assigned to XBARA1_IN26 input is connected to XBARA1_OUT20 output assigned to ACMP1_SAMPLE */
    XBARA_SetSignalsConnection(XBARA1, kXBARA1_InputLogicHigh, kXBARA1_OutputAcmp3Sample); /* ACMP4_OUT output assigned to XBARA1_IN29 input is connected to XBARA1_OUT23 output assigned to ACMP4_SAMPLE */
    uint32_t wait = 1000;
    while (--wait)
    {
        if (!servo_getFault())
        {
            break;
        }
    }
    //set window back

    XBARA_SetSignalsConnection(XBARA1, kXBARA1_InputAcmp2Out, kXBARA1_OutputAcmp2Sample); /* ACMP2_OUT output assigned to XBARA1_IN27 input is connected to XBARA1_OUT21 output assigned to ACMP2_SAMPLE */
    XBARA_SetSignalsConnection(XBARA1, kXBARA1_InputAcmp3Out, kXBARA1_OutputAcmp3Sample); /* ACMP3_OUT output assigned to XBARA1_IN28 input is connected to XBARA1_OUT22 output assigned to ACMP3_SAMPLE */

    if (!servo_getFault())
    {
        return kStatus_Success;
    }
    else
    {
        return kStatus_Fail;
    }
}

void servo_update(int8_t dutyF, int8_t dutyB)
{
    dutyF = (dutyF < 36 ? 36 : (dutyF > 84 ? 84 : dutyF));
    dutyB = (dutyB < 36 ? 36 : (dutyB > 84 ? 84 : dutyB));
    PWM_UpdatePwmDutycycle(PWM_SERVO_PWM_ADDR, PWM_SERVO_PWM_MODULE, PWM_SERVO_F_PWM_Chnl, kPWM_EdgeAligned, dutyF);
    PWM_UpdatePwmDutycycle(PWM_SERVO_PWM_ADDR, PWM_SERVO_PWM_MODULE, PWM_SERVO_B_PWM_Chnl, kPWM_EdgeAligned, dutyB);
    PWM_SetPwmLdok(PWM_MOTOR_PWM_ADDR, PWM_MOTOR_L_PWM_CTRLMODULE | PWM_MOTOR_R_PWM_CTRLMODULE, true);
}

void servo_update(float dutyF, float dutyB)
{
    dutyF = (dutyF < 36.0f ? 36.0f : (dutyF > 84.0f ? 84.0f : dutyF));
    dutyB = (dutyB < 36.0f ? 36.0f : (dutyB > 84.0f ? 84.0f : dutyB));
    PWM_UpdatePwmDutycycleHiRes(PWM_SERVO_PWM_ADDR, PWM_SERVO_PWM_MODULE, PWM_SERVO_F_PWM_Chnl, kPWM_EdgeAligned, dutyF);
    PWM_UpdatePwmDutycycleHiRes(PWM_SERVO_PWM_ADDR, PWM_SERVO_PWM_MODULE, PWM_SERVO_B_PWM_Chnl, kPWM_EdgeAligned, dutyB);
    PWM_SetPwmLdok(PWM_MOTOR_PWM_ADDR, PWM_MOTOR_L_PWM_CTRLMODULE | PWM_MOTOR_R_PWM_CTRLMODULE, true);
}



void servo_getCurrent(float *IF, float *IB)
{
    adc_channel_config_t adc_chnlCfg;
    {
        adc_chnlCfg.channelNumber = ADC_MOTORSERVO_IF_Chnl;
        adc_chnlCfg.enableInterruptOnConversionCompleted = false;
    }
    ADC_SetChannelConfig(ADC_MOTORSERVO_I_ADDR, 0U, &adc_chnlCfg);
    while (0U == ADC_GetChannelStatusFlags(ADC_MOTORSERVO_I_ADDR, 0U));
    *IF =  ADC_GetChannelConversionValue(ADC_MOTORSERVO_I_ADDR, 0U);

    {
        adc_chnlCfg.channelNumber = ADC_MOTORSERVO_IB_Chnl;
        adc_chnlCfg.enableInterruptOnConversionCompleted = false;
    }
    ADC_SetChannelConfig(ADC_MOTORSERVO_I_ADDR, 0U, &adc_chnlCfg);
    while (0U == ADC_GetChannelStatusFlags(ADC_MOTORSERVO_I_ADDR, 0U));
    *IB =  ADC_GetChannelConversionValue(ADC_MOTORSERVO_I_ADDR, 0U);
}


void servo_getCurrent(float* v)
{
    adc_channel_config_t adc_chnlCfg;
    {
        adc_chnlCfg.channelNumber = ADC_VOLT_Chnl;
        adc_chnlCfg.enableInterruptOnConversionCompleted = false;
    }
    ADC_SetChannelConfig(ADC_MOTORSERVO_I_ADDR, 0U, &adc_chnlCfg);
    while (0U == ADC_GetChannelStatusFlags(ADC_MOTORSERVO_I_ADDR, 0U));
    *v =  ((float)ADC_GetChannelConversionValue(ADC_MOTORSERVO_I_ADDR, 0U)) * (3.3f * 3.0f / 4096.0f);

}