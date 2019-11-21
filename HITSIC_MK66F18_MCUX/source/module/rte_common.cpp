#include "rte_common.hpp"

/*
----------RTE Generic----------
*/

bool rte_lowLevelInitFlag = false;

status_t rte_lowLevelInit(void)
{
    status_t rStatus = kStatus_Success;

    uint32_t globalIrqPriMask = DisableGlobalIRQ();

    // BOARD_ConfigMPU();

    /* Init board hardware. */
    BOARD_ConfigMPU();
    BOARD_InitBootPins();
    BOARD_InitBootClocks();
    BOARD_InitBootPeripherals();

    rte_pwm_init();


    EnableGlobalIRQ(globalIrqPriMask);

    if(rStatus == kStatus_Success)
    {
        rte_lowLevelInitFlag = true;
    }

    return rStatus;
}

status_t rte_lowLevelDeInit(void)
{
    status_t rStatus = kStatus_Success;
    return rStatus;
}

/* MPU configuration. */
void BOARD_ConfigMPU(void)
{
    /* Disable I cache and D cache */
    if (SCB_CCR_IC_Msk == (SCB_CCR_IC_Msk & SCB->CCR))
    {
        SCB_DisableICache();
    }
    if (SCB_CCR_DC_Msk == (SCB_CCR_DC_Msk & SCB->CCR))
    {
        SCB_DisableDCache();
    }

    /* Disable MPU */
    ARM_MPU_Disable();

    /* MPU configure:
     * Use ARM_MPU_RASR(DisableExec, AccessPermission, TypeExtField, IsShareable, IsCacheable, IsBufferable,
     * SubRegionDisable, Size)
     * API in mpu_armv7.h.
     * param DisableExec       Instruction access (XN) disable bit,0=instruction fetches enabled, 1=instruction fetches
     * disabled.
     * param AccessPermission  Data access permissions, allows you to configure read/write access for User and
     * Privileged mode.
     *      Use MACROS defined in mpu_armv7.h:
     * ARM_MPU_AP_NONE/ARM_MPU_AP_PRIV/ARM_MPU_AP_URO/ARM_MPU_AP_FULL/ARM_MPU_AP_PRO/ARM_MPU_AP_RO
     * Combine TypeExtField/IsShareable/IsCacheable/IsBufferable to configure MPU memory access attributes.
     *  TypeExtField  IsShareable  IsCacheable  IsBufferable   Memory Attribtue    Shareability        Cache
     *     0             x           0           0             Strongly Ordered    shareable
     *     0             x           0           1              Device             shareable
     *     0             0           1           0              Normal             not shareable   Outer and inner write
     * through no write allocate
     *     0             0           1           1              Normal             not shareable   Outer and inner write
     * back no write allocate
     *     0             1           1           0              Normal             shareable       Outer and inner write
     * through no write allocate
     *     0             1           1           1              Normal             shareable       Outer and inner write
     * back no write allocate
     *     1             0           0           0              Normal             not shareable   outer and inner
     * noncache
     *     1             1           0           0              Normal             shareable       outer and inner
     * noncache
     *     1             0           1           1              Normal             not shareable   outer and inner write
     * back write/read acllocate
     *     1             1           1           1              Normal             shareable       outer and inner write
     * back write/read acllocate
     *     2             x           0           0              Device              not shareable
     *  Above are normal use settings, if your want to see more details or want to config different inner/outter cache
     * policy.
     *  please refer to Table 4-55 /4-56 in arm cortex-M7 generic user guide <dui0646b_cortex_m7_dgug.pdf>
     * param SubRegionDisable  Sub-region disable field. 0=sub-region is enabled, 1=sub-region is disabled.
     * param Size              Region size of the region to be configured. use ARM_MPU_REGION_SIZE_xxx MACRO in
     * mpu_armv7.h.
     */

    /* Region 0 setting: Memory with Device type, not shareable, non-cacheable. */
    MPU->RBAR = ARM_MPU_RBAR(0, 0xC0000000U);
    MPU->RASR = ARM_MPU_RASR(0, ARM_MPU_AP_FULL, 2, 0, 0, 0, 0, ARM_MPU_REGION_SIZE_512MB);

    /* Region 1 setting: Memory with Device type, not shareable,  non-cacheable. */
    MPU->RBAR = ARM_MPU_RBAR(1, 0x80000000U);
    MPU->RASR = ARM_MPU_RASR(0, ARM_MPU_AP_FULL, 2, 0, 0, 0, 0, ARM_MPU_REGION_SIZE_1GB);

/* Region 2 setting */
#if defined(XIP_EXTERNAL_FLASH) && (XIP_EXTERNAL_FLASH == 1)
    /* Setting Memory with Normal type, not shareable, outer/inner write back. */
    MPU->RBAR = ARM_MPU_RBAR(2, 0x60000000U);
    MPU->RASR = ARM_MPU_RASR(0, ARM_MPU_AP_RO, 0, 0, 1, 1, 0, ARM_MPU_REGION_SIZE_32MB);
#else
    /* Setting Memory with Device type, not shareable, non-cacheable. */
    MPU->RBAR = ARM_MPU_RBAR(2, 0x60000000U);
    MPU->RASR = ARM_MPU_RASR(0, ARM_MPU_AP_RO, 2, 0, 0, 0, 0, ARM_MPU_REGION_SIZE_32MB);
#endif

    /* Region 3 setting: Memory with Device type, not shareable, non-cacheable. */
    MPU->RBAR = ARM_MPU_RBAR(3, 0x00000000U);
    MPU->RASR = ARM_MPU_RASR(0, ARM_MPU_AP_FULL, 2, 0, 0, 0, 0, ARM_MPU_REGION_SIZE_1GB);

    /* Region 4 setting: Memory with Normal type, not shareable, outer/inner write back */
    MPU->RBAR = ARM_MPU_RBAR(4, 0x00000000U);
    MPU->RASR = ARM_MPU_RASR(0, ARM_MPU_AP_FULL, 0, 0, 1, 1, 0, ARM_MPU_REGION_SIZE_128KB);

    /* Region 5 setting: Memory with Normal type, not shareable, outer/inner write back */
    MPU->RBAR = ARM_MPU_RBAR(5, 0x20000000U);
    MPU->RASR = ARM_MPU_RASR(0, ARM_MPU_AP_FULL, 0, 0, 1, 1, 0, ARM_MPU_REGION_SIZE_128KB);

    /* Region 6 setting: Memory with Normal type, not shareable, outer/inner write back */
    MPU->RBAR = ARM_MPU_RBAR(6, 0x20200000U);
    MPU->RASR = ARM_MPU_RASR(0, ARM_MPU_AP_FULL, 0, 0, 1, 1, 0, ARM_MPU_REGION_SIZE_256KB);

/* The define sets the cacheable memory to shareable,
 * this suggestion is referred from chapter 2.2.1 Memory regions,
 * types and attributes in Cortex-M7 Devices, Generic User Guide */
#if defined(SDRAM_IS_SHAREABLE)
    /* Region 7 setting: Memory with Normal type, shareable, outer/inner write back */
    MPU->RBAR = ARM_MPU_RBAR(7, 0x80000000U);
    MPU->RASR = ARM_MPU_RASR(0, ARM_MPU_AP_FULL, 0, 1, 1, 1, 0, ARM_MPU_REGION_SIZE_32MB);
#else
    /* Region 7 setting: Memory with Normal type, not shareable, outer/inner write back */
    MPU->RBAR = ARM_MPU_RBAR(7, 0x80000000U);
    MPU->RASR = ARM_MPU_RASR(0, ARM_MPU_AP_FULL, 0, 0, 1, 1, 0, ARM_MPU_REGION_SIZE_32MB);
#endif

    /* Region 8 setting, set last 2MB of SDRAM can't be accessed by cache, glocal variables which are not expected to be
     * accessed by cache can be put here */
    /* Memory with Normal type, not shareable, non-cacheable */
    MPU->RBAR = ARM_MPU_RBAR(8, 0x81E00000U);
    MPU->RASR = ARM_MPU_RASR(0, ARM_MPU_AP_FULL, 1, 0, 0, 0, 0, ARM_MPU_REGION_SIZE_2MB);

    /* Enable MPU */
    ARM_MPU_Enable(MPU_CTRL_PRIVDEFENA_Msk);

    /* Enable I cache and D cache */
    SCB_EnableDCache();
    SCB_EnableICache();
}





/*
----------PWM peripheral----------
*/

bool rte_pwmInitFlag = false;

status_t rte_pwm_init(void)
{
    status_t rStatus = kStatus_Success;
//    if (rte_logicInitFlag)
    {
        XBARA_SetSignalsConnection(XBARA1, kXBARA1_InputLogicHigh, kXBARA1_OutputFlexpwm1Fault0);
        XBARA_SetSignalsConnection(XBARA1, kXBARA1_InputLogicHigh, kXBARA1_OutputFlexpwm1Fault1);
        XBARA_SetSignalsConnection(XBARA1, kXBARA1_InputLogicHigh, kXBARA1_OutputFlexpwm4Fault0);
        XBARA_SetSignalsConnection(XBARA1, kXBARA1_InputLogicHigh, kXBARA1_OutputFlexpwm4Fault1);
        XBARA_SetSignalsConnection(XBARA1, kXBARA1_InputLogicHigh, kXBARA1_OutputFlexpwm1234Fault2);
        XBARA_SetSignalsConnection(XBARA1, kXBARA1_InputLogicHigh, kXBARA1_OutputFlexpwm1234Fault3);
    }
//    else
//    {
//        rStatus = kStatus_Fail;
//        return rStatus;
//    }
    pwm_config_t pwm_cfg;
    pwm_signal_param_t pwm_pwmCfg[2];

    {
        pwm_cfg.enableDebugMode = true;
        pwm_cfg.enableWait = false;
        pwm_cfg.faultFilterCount = 0;
        pwm_cfg.faultFilterPeriod = 0;
        pwm_cfg.initializationControl = kPWM_Initialize_LocalSync;
        pwm_cfg.clockSource = kPWM_BusClock;
        pwm_cfg.prescale = kPWM_Prescale_Divide_1;
        pwm_cfg.pairOperation = kPWM_Independent;
        pwm_cfg.reloadLogic = kPWM_ReloadPwmFullCycle;
        pwm_cfg.reloadSelect = kPWM_LocalReload;
        pwm_cfg.reloadFrequency = kPWM_LoadEveryOportunity;
        pwm_cfg.forceTrigger = kPWM_Force_Local;
    }

    {
        pwm_pwmCfg[0].pwmChannel = kPWM_PwmA;
        pwm_pwmCfg[0].level = kPWM_HighTrue;
        pwm_pwmCfg[0].dutyCyclePercent = 0;
        pwm_pwmCfg[0].deadtimeValue = 0;
    }

    {
        pwm_pwmCfg[1].pwmChannel = kPWM_PwmB;
        pwm_pwmCfg[1].level = kPWM_HighTrue;
        pwm_pwmCfg[1].dutyCyclePercent = 0;
        pwm_pwmCfg[1].deadtimeValue = 0;
    }

    /* Init submodule 0 */
    rStatus = PWM_Init(RTE_PWM_ADDR, kPWM_Module_0, &pwm_cfg);
    rStatus = PWM_SetupPwm(RTE_PWM_ADDR, kPWM_Module_0, pwm_pwmCfg, 2, kPWM_CenterAligned, RTE_PWM_MODULE0_PWMFREQ, RTE_PWM_CLKFREQ);
    /* Init submodule 1 */
    rStatus = PWM_Init(RTE_PWM_ADDR, kPWM_Module_1, &pwm_cfg);
    rStatus = PWM_SetupPwm(RTE_PWM_ADDR, kPWM_Module_1, pwm_pwmCfg, 2, kPWM_CenterAligned, RTE_PWM_MODULE1_PWMFREQ, RTE_PWM_CLKFREQ);
    /* Init submodule 2 */
    rStatus = PWM_Init(RTE_PWM_ADDR, kPWM_Module_2, &pwm_cfg);
    rStatus = PWM_SetupPwm(RTE_PWM_ADDR, kPWM_Module_2, pwm_pwmCfg, 2, kPWM_EdgeAligned, RTE_PWM_MODULE2_PWMFREQ, RTE_PWM_CLKFREQ);


    PWM_SetPwmLdok(RTE_PWM_ADDR, kPWM_Control_Module_0 | kPWM_Control_Module_1 | kPWM_Control_Module_2, true);
    PWM_StartTimer(RTE_PWM_ADDR, kPWM_Control_Module_0 | kPWM_Control_Module_1 | kPWM_Control_Module_2);

    if(rStatus == kStatus_Success)
    {
        rte_pwmInitFlag = true;
    }
    return rStatus;
}
status_t rte_pwm_deInit(void)
{
    status_t rStatus = kStatus_Success;
    PWM_Deinit(RTE_PWM_ADDR, kPWM_Module_0);
    PWM_Deinit(RTE_PWM_ADDR, kPWM_Module_1);
    PWM_Deinit(RTE_PWM_ADDR, kPWM_Module_2);

    if (rStatus == kStatus_Success)
    {
        rte_pwmInitFlag = false;
    }
    return rStatus;
}





























