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

void Ftm_QuadDecode_Init(FTM_Type *base);
void Ftm_PWM_Init(FTM_Type *base, ftm_chnl_t chnlNumber, uint32_t dutyFre, float dutyCycle);
void Ftm_PWM_Change(FTM_Type *base, ftm_chnl_t chnlNumber, uint32_t dutyFre, float dutyCycle);
void Ftm_QuadDecode_Init(FTM_Type *base);
int16_t Ftm_GetSpeed(FTM_Type *base);
void Ftm_ClearSpeed(FTM_Type *base);



#endif /* SC_FTM_H_ */
