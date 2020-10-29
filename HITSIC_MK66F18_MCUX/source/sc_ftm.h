/*
 * sc_ftm.h
 *
 *  Created on: 2020年10月27日
 *      Author: 孙唯
 */

#ifndef SC_FTM_H_
#define SC_FTM_H_

#include "fsl_debug_console.h"
#include "board.h"
#include "fsl_ftm.h"
#include "clock_config.h"
#include "pin_mux.h"


/**********************************************************************************************************************
*  @brief      ftm设定占空比      用于PWM模式
*  @param      base            ftm模块选择
*  @param      chnlNumber      ftm通道选择
*  @param      dutyFre         ftm频率
*  @return     void
*  @since      v1.0
*  Sample usage:          Ftm_PWM_Change(FTM0,kFTM_Chnl_1,20000,10.5);
**********************************************************************************************************************/
void Ftm_PWM_Change(FTM_Type *base, ftm_chnl_t chnlNumber, uint32_t dutyFre, float dutyCycle);


/**********************************************************************************************************************
*  @brief      ftm获取编码器计数值
*  @param      base            ftm模块选择
*  @return     int16_t         编码器计数值
*  @since      v1.0
*  Sample usage:          Ftm_GetSpeed(FTM1);
**********************************************************************************************************************/
int16_t Ftm_GetSpeed(FTM_Type *base);

/**********************************************************************************************************************
*  @brief      ftm清除编码器计数值
*  @param      base            ftm模块选择
*  @return     void
*  @since      v1.0
*  Sample usage:          Ftm_ClearSpeed(FTM1);
**********************************************************************************************************************/
void Ftm_ClearSpeed(FTM_Type *base);



#endif /* SC_FTM_H_ */
