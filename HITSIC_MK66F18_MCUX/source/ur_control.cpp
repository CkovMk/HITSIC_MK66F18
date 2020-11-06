#include "ur_control.hpp"

/**
 * @brief   控制环PITMGR任务句柄
 * @ {
 */
pitMgr_t* ctrl_angCtrlHandle = nullptr;
pitMgr_t* ctrl_spdCtrlHandle = nullptr;
pitMgr_t* ctrl_dirCtrlHandle = nullptr;
/**
 * @ }
 */

void CTRL_Init(void)
{
    ctrl_spdCtrlHandle = pitMgr_t::insert(CTRL_SPD_CTRL_MS, 2U, CTRL_SpdCtrl, pitMgr_t::enable);
    assert(ctrl_spdCtrlHandle);
    ctrl_dirCtrlHandle = pitMgr_t::insert(CTRL_DIR_CTRL_MS, 3U, CTRL_DirCtrl, pitMgr_t::enable);
    assert(ctrl_dirCtrlHandle);
    ctrl_angCtrlHandle = pitMgr_t::insert(CTRL_ANG_CTRL_MS, 4U, CTRL_AngCtrl, pitMgr_t::enable);
    assert(ctrl_angCtrlHandle);
}

void CTRL_MenuInit(menu_list_t *menuList)
{
    static menu_list_t *ctrlMenuList =
            MENU_ListConstruct("Control", 32, menuList);
    assert(ctrlMenuList);
    MENU_ListInsert(menuList, MENU_ItemConstruct(menuType, ctrlMenuList, "Control", 0, 0));

    {
        MENU_ListInsert(ctrlMenuList, MENU_ItemConstruct(nullType, NULL, "ENB", 0, 0));

        MENU_ListInsert(ctrlMenuList, MENU_ItemConstruct(variType, &ctrl_angCtrlEn[0], "ang.en", 0U,
                menuItem_data_NoSave | menuItem_data_NoLoad | menuItem_dataExt_HasMinMax));
        MENU_ListInsert(ctrlMenuList, MENU_ItemConstruct(variType, &ctrl_spdCtrlEn[0], "spd.en", 0U,
                menuItem_data_NoSave | menuItem_data_NoLoad | menuItem_dataExt_HasMinMax));
        MENU_ListInsert(ctrlMenuList, MENU_ItemConstruct(variType, &ctrl_dirCtrlEn[0], "dir.en", 0U,
                menuItem_data_NoSave | menuItem_data_NoLoad | menuItem_dataExt_HasMinMax));

        MENU_ListInsert(ctrlMenuList, MENU_ItemConstruct(nullType, NULL, "ANG", 0, 0));

        MENU_ListInsert(ctrlMenuList, MENU_ItemConstruct(varfType, &ctrl_angSet, "angSet", 9U,
                menuItem_data_region));
        MENU_ListInsert(ctrlMenuList, MENU_ItemConstruct(varfType, &ctrl_angPid.kp, "ang.kp", 10U,
                menuItem_data_region));
        MENU_ListInsert(ctrlMenuList, MENU_ItemConstruct(varfType, &ctrl_angPid.ki, "ang.ki", 11U,
                menuItem_data_region));
        MENU_ListInsert(ctrlMenuList, MENU_ItemConstruct(varfType, &ctrl_angPid.kd, "ang.kd", 12U,
                menuItem_data_region));
        MENU_ListInsert(ctrlMenuList, MENU_ItemConstruct(varfType, &ctrl_angPidOutput, "ang.out", 0U,
                menuItem_data_NoSave | menuItem_data_NoLoad));

        MENU_ListInsert(ctrlMenuList, MENU_ItemConstruct(nullType, NULL, "SPD", 0, 0));

        MENU_ListInsert(ctrlMenuList, MENU_ItemConstruct(varfType, &ctrl_spdSet, "spdSet", 14U,
                menuItem_data_region));
        MENU_ListInsert(ctrlMenuList, MENU_ItemConstruct(varfType, &ctrl_spdPid.kp, "spd.kp", 15U,
                menuItem_data_region));
        MENU_ListInsert(ctrlMenuList, MENU_ItemConstruct(varfType, &ctrl_spdPid.ki, "spd.ki", 16U,
                menuItem_data_region));
        MENU_ListInsert(ctrlMenuList, MENU_ItemConstruct(varfType, &ctrl_spdPid.kd, "spd.kd", 17U,
                menuItem_data_region));
        MENU_ListInsert(ctrlMenuList, MENU_ItemConstruct(varfType, &ctrl_spdPidOutput, "spd.out", 0U,
                menuItem_data_NoSave | menuItem_data_NoLoad));

        MENU_ListInsert(ctrlMenuList, MENU_ItemConstruct(nullType, NULL, "DIR", 0, 0));
        static float dummyData = 2020.0f;//FIXME: Del This
        MENU_ListInsert(ctrlMenuList, MENU_ItemConstruct(varfType, &dummyData/*FIXME*/, "dir.in", 0U,
                menuItem_data_NoSave | menuItem_data_NoLoad));
        MENU_ListInsert(ctrlMenuList, MENU_ItemConstruct(varfType, &ctrl_dirPid.kp, "dir.kp", 20U,
                menuItem_data_region));
        MENU_ListInsert(ctrlMenuList, MENU_ItemConstruct(varfType, &ctrl_dirPid.ki, "dir.ki", 21U,
                menuItem_data_region));
        MENU_ListInsert(ctrlMenuList, MENU_ItemConstruct(varfType, &ctrl_dirPid.kd, "dir.kd", 22U,
                menuItem_data_region));
        MENU_ListInsert(ctrlMenuList, MENU_ItemConstruct(varfType, &ctrl_dirPidOutput, "dir.out", 0U,
                menuItem_data_NoSave | menuItem_data_NoLoad));
    }

    static menu_list_t *filterMenuList =
                MENU_ListConstruct("Filter", 32, menuList);
    assert(filterMenuList);
    MENU_ListInsert(menuList, MENU_ItemConstruct(menuType, filterMenuList, "Filter", 0, 0));
    {
        MENU_ListInsert(filterMenuList, MENU_ItemConstruct(nullType, NULL, "RAW", 0, 0));

        MENU_ListInsert(filterMenuList, MENU_ItemConstruct(varfType, &ctrl_accl[0], "accl.x", 0U,
                menuItem_data_NoSave | menuItem_data_NoLoad));
        MENU_ListInsert(filterMenuList, MENU_ItemConstruct(varfType, &ctrl_accl[1], "accl.y", 0U,
                menuItem_data_NoSave | menuItem_data_NoLoad));
        MENU_ListInsert(filterMenuList, MENU_ItemConstruct(varfType, &ctrl_accl[2], "accl.z", 0U,
                menuItem_data_NoSave | menuItem_data_NoLoad));
        MENU_ListInsert(filterMenuList, MENU_ItemConstruct(varfType, &ctrl_gyro[0], "gyro.x", 0U,
                menuItem_data_NoSave | menuItem_data_NoLoad));
        MENU_ListInsert(filterMenuList, MENU_ItemConstruct(varfType, &ctrl_gyro[1], "gyro.y", 0U,
                menuItem_data_NoSave | menuItem_data_NoLoad));
        MENU_ListInsert(filterMenuList, MENU_ItemConstruct(varfType, &ctrl_gyro[2], "gyro.z", 0U,
                menuItem_data_NoSave | menuItem_data_NoLoad));
        MENU_ListInsert(filterMenuList, MENU_ItemConstruct(nullType, NULL, "FILT", 0, 0));

        MENU_ListInsert(filterMenuList, MENU_ItemConstruct(varfType, &ctrl_accl[0], "accl.x", 0U,
                menuItem_data_NoSave | menuItem_data_NoLoad));
        MENU_ListInsert(filterMenuList, MENU_ItemConstruct(varfType, &ctrl_filterAngRef, "AngRef", 0U,
                menuItem_data_NoSave | menuItem_data_NoLoad));
        MENU_ListInsert(filterMenuList, MENU_ItemConstruct(varfType, &ctrl_filterAngAccl, "Ang.Accl", 0U,
                menuItem_data_NoSave | menuItem_data_NoLoad));
        MENU_ListInsert(filterMenuList, MENU_ItemConstruct(varfType, &ctrl_filterAngGyro, "Ang.Gyro", 0U,
                menuItem_data_NoSave | menuItem_data_NoLoad));
        MENU_ListInsert(filterMenuList, MENU_ItemConstruct(varfType, &ctrl_filterAngle, "AngFinal", 0U,
                menuItem_data_NoSave | menuItem_data_NoLoad));
        MENU_ListInsert(filterMenuList, MENU_ItemConstruct(varfType, &ctrl_filterCompTgReciprocal, "Tg-recip", 10U,
                menuItem_data_global));

    }
}

/* ******************** 滤波器 ******************** */

/**
 * @brief   IMU传感器原始数据
 * @ {
 */
float ctrl_accl[3] = {0.0f, 0.0f, 0.0f};
float ctrl_gyro[3] = {0.0f, 0.0f, 0.0f};
/**
 * @ }
 */

float &ctrl_acclRefAxis = ctrl_accl[0]; //FIXME
float &ctrl_gyroRefAxis = ctrl_gyro[1]; //FIXME

float ctrl_filterAngAccl = 0.0f, ctrl_filterAngGyro = 0.0f; ///< 由加速度计、角速度计测出的角度

float ctrl_filterAngRef = 0.0f; ///< 角度参考点，初始化时读取。初始化时必须保持静止！

/**
 * @brief   角度滤波相关变量。
 * @note    借用PIDCTRL的结构体保存当前值、积分值、微分值、历史值。
 * @ {
 */
pidCtrl_t ctrl_angFilter =
{
    .kp = 0.0f, .ki = 0.0f, .kd = 0.0f,
    .errCurr = 0.0f, .errIntg = 0.0f, .errDiff = 0.0f, .errPrev = 0.0f,
};
/**
 * @ }
 */

float ctrl_filterCompTgReciprocal = 1.0f / 0.8f;    ///< Tg的倒数。除以Tg -> 乘Tg的倒数，优化运算速度。

float &ctrl_filterAngle = ctrl_angFilter.errCurr; ///< 滤波后的当前角度。引用ctrl_angFilter.errCurr即可

void CTRL_FilterInit(void)
{
    const uint32_t sampleTime = 1024;
    float intergration = 0.0f;
    for(uint32_t i = 0; i < sampleTime; ++i){
        imu_6050.ReadSensorBlocking();
        imu_6050.Convert(&ctrl_accl[0], &ctrl_accl[1], &ctrl_accl[2], &ctrl_gyro[0], &ctrl_gyro[1], &ctrl_gyro[2]);
        CTRL_FilterUpdate(0U);
        intergration += ctrl_filterAngAccl;
        SDK_DelayAtLeastUs(1000,CLOCK_GetFreq(kCLOCK_CoreSysClk)); // MPU6050更新速度没那么快，连续读取只会得到相同的值。
    }
    ctrl_filterAngRef = intergration / ((float)sampleTime);
    ctrl_filterAngle = ctrl_filterAngRef;
    ctrl_filterAngGyro = ctrl_filterAngRef;
}

void CTRL_FilterUpdate(uint32_t updateTime_ms)
{
    float dT = ((float)updateTime_ms) * 0.001f;
    /** 对加速度值进行限幅，防止进行asin计算时出错 */
    float acclAxis = ctrl_acclRefAxis;
    acclAxis = (acclAxis > CTRL_1G - 0.001) ? (CTRL_1G - 0.001) : acclAxis;
    acclAxis = (acclAxis < - (CTRL_1G - 0.001)) ? (- (CTRL_1G - 0.001)) : acclAxis;
    ctrl_filterAngAccl = CTRL_RAD2DEG(- CTRL_ASIN(acclAxis / CTRL_1G)); // - is pitch down , + is pitch up
    ctrl_filterAngGyro -= ctrl_gyroRefAxis * dT;
    /** 滤波运算 */
    float angleDiff = (ctrl_gyroRefAxis + ((ctrl_filterAngAccl - ctrl_filterAngle) * ctrl_filterCompTgReciprocal)) * dT;
    PIDCTRL_ErrUpdateByDiff(&ctrl_angFilter, angleDiff);
}

/* *********************************************** */

/* ******************** 直立环 ******************** */
int32_t ctrl_angCtrlEn[3] = {0, 0, 1}; ///< 直立环使能

float ctrl_angSet = 0.0f; ///< 机械零点

pidCtrl_t ctrl_angPid =
{
    .kp = 0.0f, .ki = 0.0f, .kd = 0.0f,
    .errCurr = 0.0f, .errIntg = 0.0f, .errDiff = 0.0f, .errPrev = 0.0f,
};


float ctrl_angPidOutput = 0.0f; ///< 直立环输出

void CTRL_AngCtrl(void *userData)
{
    if(kStatus_Success == imu_6050.ReadSensorBlocking())
    {
        imu_6050.Convert(&ctrl_accl[0], &ctrl_accl[1], &ctrl_accl[2], &ctrl_gyro[0], &ctrl_gyro[1], &ctrl_gyro[2]);
        CTRL_FilterUpdate(CTRL_ANG_CTRL_MS);
        PRINTF("ang: %d,%d,%d\n", ctrl_filterAngAccl, ctrl_filterAngGyro,ctrl_filterAngle);
    }
    else
    {
        ctrl_angCtrlEn[0] = 0;
        PRINTF("\n[W] IMU Fail!\n");
    }
    if(1 == ctrl_angCtrlEn[0])
    {
        PIDCTRL_ErrUpdate(&ctrl_angPid, -(ctrl_filterAngle - ctrl_angSet + ctrl_spdPidOutput));
        ctrl_angPidOutput = PIDCTRL_CalcPIDGain(&ctrl_angPid);
        ctrl_angPidOutput = ctrl_angPidOutput < 60.0f ? ctrl_angPidOutput : 60.0f;  ///< 限幅
    }
    else
    {
        ctrl_angPidOutput = 0.0f;
    }

    CTRL_MotorUpdate(ctrl_angPidOutput + ctrl_dirPidOutput, ctrl_angPidOutput - ctrl_dirPidOutput);
}

/* *********************************************** */

/* ******************** 速度环 ******************** */
int32_t ctrl_spdCtrlEn[3] = {0, 0, 1}; ///< 速度环使能

float ctrl_spdSet = 0.0f; ///< 速度设置

pidCtrl_t ctrl_spdPid =
{
    .kp = 0.0f, .ki = 0.0f, .kd = 0.0f,
    .errCurr = 0.0f, .errIntg = 0.0f, .errDiff = 0.0f, .errPrev = 0.0f,
};

float ctrl_spdL = 0.0f, ctrl_spdR = 0.0f;
float ctrl_spdAvg = 0.0f;

float ctrl_spdPidOutput = 0.0f; ///< 速度环输出

void CTRL_SpdCtrl(void *userData)
{
    ctrl_spdL = ((float)SCFTM_GetSpeed(ENCO_L_PERIPHERAL)) * CTRL_ENCO_SPD_COEFF;
    SCFTM_ClearSpeed(ENCO_L_PERIPHERAL);
    ctrl_spdR = ((float)SCFTM_GetSpeed(ENCO_R_PERIPHERAL)) * CTRL_ENCO_SPD_COEFF;
    SCFTM_ClearSpeed(ENCO_R_PERIPHERAL);
    ctrl_spdAvg = (ctrl_spdL + ctrl_spdR) / 2.0f;
    if(1 == ctrl_spdCtrlEn[0])
    {
        PIDCTRL_ErrUpdate(&ctrl_spdPid, ctrl_spdAvg - ctrl_spdSet);
        ctrl_spdPidOutput = PIDCTRL_CalcPIDGain(&ctrl_spdPid);
    }
    else
    {
        ctrl_spdPidOutput = 0.0f;
    }
}

/* *********************************************** */

/* ******************** 转向环 ******************** */
int32_t ctrl_dirCtrlEn[3] = {0, 0, 1}; ///< 转向环使能

pidCtrl_t ctrl_dirPid =
{
    .kp = 0.0f, .ki = 0.0f, .kd = 0.0f,
    .errCurr = 0.0f, .errIntg = 0.0f, .errDiff = 0.0f, .errPrev = 0.0f,
};

float ctrl_dirPidOutput = 0.0f; ///< 转向环输出

void CTRL_DirCtrl(float *err)
{
    if(1 == ctrl_dirCtrlEn[0])
    {
        PIDCTRL_ErrUpdate(&ctrl_dirPid, (*err));
        ctrl_dirPidOutput = PIDCTRL_CalcPIDGain(&ctrl_dirPid);
    }
    else
    {
        ctrl_dirPidOutput = 0.0f;
    }
}

/* *********************************************** */

float ctrl_motorLQ = 0.0f, ctrl_motorRQ = 0.0f;

void CTRL_MotorUpdate(float motorL, float motorR)
{
    /** 左电机满载 **/
    if(motorL > 100.0f)
    {
        motorR -= (motorL - 100.0f);
        motorL = 100.0f;
    }
    if(motorL < -100.0f)
    {
        motorR -= (motorL + 100.0f);
        motorL = -100.0f;
    }
    /** 右电机满载 **/
    if(motorR > 100.0f)
    {
        motorL -= (motorL - 100.0f);
        motorR = 100.0f;
    }
    if(motorR < -100.0f)
    {
        motorL -= (motorL + 100.0f);
        motorR = -100.0f;
    }
    /** 反转保护 **/
    if(motorL < 0.0f && motorR > 0.0f)
    {
        motorL = 0.0f;
    }
    if(motorL > 0.0f && motorR < 0.0f)
    {
        motorR = 0.0f;
    }
    /// 平滑
    ctrl_motorLQ = ctrl_motorLQ * 0.75f + motorL * 0.25f;
    ctrl_motorRQ = ctrl_motorRQ * 0.75f + motorR * 0.25f;

    if(ctrl_motorLQ > 0)
    {
        SCFTM_PWM_ChangeHiRes(MOTOR_PERIPHERAL, kFTM_Chnl_0, 20000U, ctrl_motorLQ);
        SCFTM_PWM_ChangeHiRes(MOTOR_PERIPHERAL, kFTM_Chnl_1, 20000U, 0.0f);
    }
    else
    {
        SCFTM_PWM_ChangeHiRes(MOTOR_PERIPHERAL, kFTM_Chnl_0, 20000U, 0.0f);
        SCFTM_PWM_ChangeHiRes(MOTOR_PERIPHERAL, kFTM_Chnl_1, 20000U, -ctrl_motorLQ);
    }

    if(ctrl_motorRQ > 0)
    {
        SCFTM_PWM_ChangeHiRes(MOTOR_PERIPHERAL, kFTM_Chnl_2, 20000U, ctrl_motorRQ);
        SCFTM_PWM_ChangeHiRes(MOTOR_PERIPHERAL, kFTM_Chnl_3, 20000U, 0.0f);
    }
    else
    {
        SCFTM_PWM_ChangeHiRes(MOTOR_PERIPHERAL, kFTM_Chnl_2, 20000U, 0.0f);
        SCFTM_PWM_ChangeHiRes(MOTOR_PERIPHERAL, kFTM_Chnl_3, 20000U, -ctrl_motorRQ);
    }
}

