#ifndef UR_CONTROL_HPP
#define UR_CONTROL_HPP
#include "hitsic_common.h"
#include "inc_stdlib.hpp"

#include "sys_pitmgr.hpp"
#include "sys_extint.hpp"
#include "drv_imu_invensense.hpp"
#include "lib_pidctrl.h"

#include "app_menu.hpp"
#include "sc_ftm.h"

#define CTRL_ANG_CTRL_MS    (5U)
#define CTRL_SPD_CTRL_MS    (100U)
#define CTRL_DIR_CTRL_MS    (20U)

#define CTRL_1G             (9.80f)
//#define CTRL_ASIN(x)        (arm_arcsin_f32(x))
#define CTRL_ASIN(x)        (asin(x))

#define CTRL_PI             (3.1415926f)

#define CTRL_DEG2RAD(x)     (x * (CTRL_PI / 180.0f))
#define CTRL_RAD2DEG(x)     (x * (180.0f / CTRL_PI))

#define CTRL_ENCO_SPD_COEFF (270.689 / ((float)CTRL_SPD_CTRL_MS))

extern inv::mpu6050_t imu_6050;

void CTRL_Init(void);



void CTRL_MenuInit(menu_list_t *menuList);

/* ******************** 滤波器 ******************** */
extern float ctrl_accl[3];
extern float ctrl_gyro[3];
extern float &ctrl_acclRefAxis;
extern float &ctrl_gyroRefAxis;
extern float ctrl_filterAngAccl, ctrl_filterAngGyro;
extern float ctrl_filterAngRef;
extern pidCtrl_t ctrl_angFilter;
extern float ctrl_filterCompTgReciprocal;
extern float &ctrl_filterAngle;

void CTRL_FilterInit(void);

void CTRL_FilterUpdate(uint32_t updateTime_ms);

/* *********************************************** */

/* ******************** 直立环 ******************** */
extern int32_t ctrl_angCtrlEn[3];
extern float ctrl_angSet;
extern pidCtrl_t ctrl_angPid;
extern float ctrl_angPidOutput;

void CTRL_AngCtrl(void *userData);

/* *********************************************** */

/* ******************** 速度环 ******************** */
extern int32_t ctrl_spdCtrlEn[3];
extern float ctrl_spdSet;
extern pidCtrl_t ctrl_spdPid;
extern float ctrl_spdL, ctrl_spdR;
extern float ctrl_spdAvg;
extern float ctrl_spdPidOutput;

void CTRL_SpdCtrl(void *userData);

/* *********************************************** */

/* ******************** 转向环 ******************** */
extern int32_t ctrl_dirCtrlEn[3];
extern pidCtrl_t ctrl_dirPid;
extern float ctrl_dirPidOutput;

void CTRL_DirCtrl(float *err);

/* *********************************************** */



void CTRL_MotorUpdate(float motorL, float motorR);


//@mqk

#endif // ! UR_CONTROL_HPP
