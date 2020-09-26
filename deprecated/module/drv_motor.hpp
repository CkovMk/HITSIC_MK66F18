#pragma once
#ifndef _DRV_MOTOR_HPP_
#define _DRV_MOTOR_HPP_


#include "inc_fsl_rt1052.h"
#include "inc_stdlib.h"
#include "inc_gnc.h"

#include "rte_common.hpp"


#define PWM_MOTOR_PWM_ADDR PWM2
#define PWM_MOTOR_L_PWM_MODULE kPWM_Module_0
#define PWM_MOTOR_L_PWM_CTRLMODULE kPWM_Control_Module_0
#define PWM_MOTOR_PWM_ADDR PWM2
#define PWM_MOTOR_R_PWM_MODULE kPWM_Module_1
#define PWM_MOTOR_R_PWM_CTRLMODULE kPWM_Control_Module_1

#define ENC_MOTOR_L_ADDR ENC1
#define ENC_MOTOR_R_ADDR ENC2

#define CMP_MOTOR_IL_ADDR CMP4
#define CMP_MOTOR_IR_ADDR CMP1


#define PWM_SERVO_PWM_ADDR PWM2
#define PWM_SERVO_PWM_MODULE kPWM_Module_2
#define PWM_SERVO_PWM_CTRLMODULE kPWM_Control_Module_2
#define PWM_SERVO_F_PWM_Chnl kPWM_PwmA
#define PWM_SERVO_B_PWM_Chnl kPWM_PwmB

#define CMP_SERVO_IF_ADDR CMP2
#define CMP_SERVO_IB_ADDR CMP3

#define ADC_MOTORSERVO_I_ADDR ADC1
#define ADC_MOTORSERVO_IL_Chnl 5
#define ADC_MOTORSERVO_IR_Chnl 7
#define ADC_MOTORSERVO_IF_Chnl 5
#define ADC_MOTORSERVO_IB_Chnl 7

#define ADC_VOLT_Chnl 6


//motor
status_t motor_enable(bool b);
bool motor_getFault(void);
status_t motor_clearFault(void);
void motor_update(int8_t dutyL, int8_t dutyR);
void motor_update(float dutyL, float dutyR);
void motor_getEncCount(int32_t* cntL,int32_t* cntR);
void motor_getCurrent(float* IL,float* IR);

//servo
status_t servo_enable(bool b);
bool servo_getFault(void);
status_t servo_clearFault(void);
void servo_update(int8_t dutyF, int8_t dutyB);
void servo_update(float dutyF, float dutyB);
void servo_getCurrent(float* IF,float* IB);

//volt
void servo_getCurrent(float* v);






#endif // _DRV_MOTOR_HPP_
