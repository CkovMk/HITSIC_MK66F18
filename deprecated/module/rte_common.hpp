/*
 * Beta-Cat Controll @ HSIC
 * @name	rte_common.hpp
 * Runtime Environment Common include file. 
 * Define all Common lowlevel definitions HERE!
*/
#pragma once
#ifndef _RTE_COMMON_H_
#define _RTE_COMMON_H_

//#include <include.hpp>
#include "inc_fsl_rt1052.h"
#include "inc_stdlib.h"
#include "inc_gnc.h"

//#include "rte_baseio.hpp"
//#include "rte_timer.hpp"
//#include "rte_senior.hpp"
//#include "rte_senior.h"

/*
----------RTE Generic----------
*/

extern bool rte_lowLevelInitFlag;

status_t rte_lowLevelInit(void);
status_t rte_lowLevelDeInit(void);

void BOARD_ConfigMPU(void);



/*
----------PWM peripheral----------
*/

//PWM Global Definition
#define RTE_PWM_CLKSRC	kCLOCK_IpgClk
#define RTE_PWM_CLKFREQ CLOCK_GetFreq(RTE_PWM_CLKSRC)

//PWM0 Definition
#define RTE_PWM_ADDR PWM2
#define RTE_PWM_MODULE0_PWMFREQ 10000 //MOTOR
#define RTE_PWM_MODULE1_PWMFREQ 10000 //MOTOR
#define RTE_PWM_MODULE2_PWMFREQ 250   //SERVO

extern bool rte_logicInitFlag;

extern bool rte_pwmInitFlag;

status_t rte_pwm_init(void);
status_t rte_pwm_deInit(void);





#endif // ! _RTE_COMMON_H_
