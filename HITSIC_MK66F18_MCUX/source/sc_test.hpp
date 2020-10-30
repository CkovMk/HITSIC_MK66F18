/*
 * sc_test.hpp
 *
 *  Created on: 2020年10月30日
 *      Author: 孙唯
 */

#ifndef SC_TEST_HPP_
#define SC_TEST_HPP_

#include "hitsic_common.h"
#include "app_menu.hpp"
#include "sc_adc.h"
#include "sc_ftm.h"

namespace sc
{
int32_t adc[8] = {0,0,0,0,0,0,0,0};

float motorL[3] = {0.0f, 0.0f, 100.0f}, motorR[3] = {0.0f, 0.0f, 100.0f}, servo[3] = {30.0f, 10.0f, 50.0f};
int32_t encoL = 0, encoR = 0;

inline void SC_UnitTest_AdcRefreshPitTask(void)
{
    adc[0]=SCADC_Sample(ADC0,0,10);
    adc[1]=SCADC_Sample(ADC0,0,11);
    adc[2]=SCADC_Sample(ADC0,0,12);
    adc[3]=SCADC_Sample(ADC0,0,13);
    adc[4]=SCADC_Sample(ADC0,0,16);
    adc[5]=SCADC_Sample(ADC0,0,17);
    adc[6]=SCADC_Sample(ADC0,0,18);
    adc[7]=SCADC_Sample(ADC0,0,23);

    encoL = SCFTM_GetSpeed(ENCO_L_PERIPHERAL);
    SCFTM_ClearSpeed(ENCO_L_PERIPHERAL);
    encoR = SCFTM_GetSpeed(ENCO_R_PERIPHERAL);
    SCFTM_ClearSpeed(ENCO_R_PERIPHERAL);
}

inline void SC_UnitTest_FtmUpdateMenuHandler(menu_keyOp_t *_op)
{
    if(motorL > 0)
    {
        SCFTM_PWM_ChangeHiRes(MOTOR_PERIPHERAL, kFTM_Chnl_0, 20000U, motorL[0]);
        SCFTM_PWM_ChangeHiRes(MOTOR_PERIPHERAL, kFTM_Chnl_1, 20000U, 0.0f);
    }
    else
    {
        SCFTM_PWM_ChangeHiRes(MOTOR_PERIPHERAL, kFTM_Chnl_0, 20000U, 0.0f);
        SCFTM_PWM_ChangeHiRes(MOTOR_PERIPHERAL, kFTM_Chnl_1, 20000U, motorL[0]);
    }

    if(motorR > 0)
    {
        SCFTM_PWM_ChangeHiRes(MOTOR_PERIPHERAL, kFTM_Chnl_2, 20000U, motorR[0]);
        SCFTM_PWM_ChangeHiRes(MOTOR_PERIPHERAL, kFTM_Chnl_3, 20000U, 0.0f);
    }
    else
    {
        SCFTM_PWM_ChangeHiRes(MOTOR_PERIPHERAL, kFTM_Chnl_2, 20000U, 0.0f);
        SCFTM_PWM_ChangeHiRes(MOTOR_PERIPHERAL, kFTM_Chnl_3, 20000U, motorR[0]);
    }

    SCFTM_PWM_ChangeHiRes(SERVO_PERIPHERAL, kFTM_Chnl_7, 50U, servo[0]);

}

#if (defined(HITSIC_USE_APP_MENU) && (HITSIC_USE_APP_MENU > 0))
inline void SC_UnitTest_AutoRefreshAddMenu(menu_list_t *menu)
{
    static menu_list_t *scTestList = MENU_ListConstruct("SCLIB", 20, menu);
    assert(scTestList);
    MENU_ListInsert(menu, MENU_ItemConstruct(menuType, scTestList, "SCLIB", 0, 0));
    {
        MENU_ListInsert(scTestList, MENU_ItemConstruct(nullType, NULL, "EMAG", 0, 0));
        MENU_ListInsert(scTestList,
                MENU_ItemConstruct(variType, &adc[0], "adc0", 0, menuItem_data_ROFlag | menuItem_data_NoSave | menuItem_data_NoLoad));
        MENU_ListInsert(scTestList,
                MENU_ItemConstruct(variType, &adc[1], "adc1", 0, menuItem_data_ROFlag | menuItem_data_NoSave | menuItem_data_NoLoad));
        MENU_ListInsert(scTestList,
                MENU_ItemConstruct(variType, &adc[2], "adc2", 0, menuItem_data_ROFlag | menuItem_data_NoSave | menuItem_data_NoLoad));
        MENU_ListInsert(scTestList,
                MENU_ItemConstruct(variType, &adc[3], "adc3", 0, menuItem_data_ROFlag | menuItem_data_NoSave | menuItem_data_NoLoad));
        MENU_ListInsert(scTestList,
                MENU_ItemConstruct(variType, &adc[4], "adc4", 0, menuItem_data_ROFlag | menuItem_data_NoSave | menuItem_data_NoLoad));
        MENU_ListInsert(scTestList,
                MENU_ItemConstruct(variType, &adc[5], "adc5", 0, menuItem_data_ROFlag | menuItem_data_NoSave | menuItem_data_NoLoad));
        MENU_ListInsert(scTestList,
                MENU_ItemConstruct(variType, &adc[6], "adc6", 0, menuItem_data_ROFlag | menuItem_data_NoSave | menuItem_data_NoLoad));
        MENU_ListInsert(scTestList,
                MENU_ItemConstruct(variType, &adc[7], "adc7", 0, menuItem_data_ROFlag | menuItem_data_NoSave | menuItem_data_NoLoad));

        MENU_ListInsert(scTestList, MENU_ItemConstruct(nullType, NULL, "kFTM", 0, 0));
        MENU_ListInsert(scTestList,
                MENU_ItemConstruct(variType, &encoL, "encoL", 0, menuItem_data_ROFlag | menuItem_data_NoSave | menuItem_data_NoLoad));
        MENU_ListInsert(scTestList,
                MENU_ItemConstruct(variType, &encoR, "encoR", 0, menuItem_data_ROFlag | menuItem_data_NoSave | menuItem_data_NoLoad));

        MENU_ListInsert(scTestList,
                MENU_ItemConstruct(varfType, &motorL[0], "motorL", 0, menuItem_data_NoSave | menuItem_data_NoLoad | menuItem_dataExt_HasMinMax));
        MENU_ListInsert(scTestList,
                MENU_ItemConstruct(varfType, &motorR[0], "motorR", 0, menuItem_data_NoSave | menuItem_data_NoLoad | menuItem_dataExt_HasMinMax));
        MENU_ListInsert(scTestList,
                MENU_ItemConstruct(varfType, &servo[0], "servo", 0, menuItem_data_NoSave | menuItem_data_NoLoad | menuItem_dataExt_HasMinMax));
        MENU_ListInsert(scTestList,
                MENU_ItemConstruct(procType, SC_UnitTest_FtmUpdateMenuHandler, "PWM Update", 0, menuItem_proc_runOnce));

    }
}
#endif // ! HITSIC_USE_APP_MENU

inline void SC_UnitTest_AutoRefresh(void)
{

    pitMgr_t::insert(64U, 3U, sc::SC_UnitTest_AdcRefreshPitTask, pitMgr_t::enable);
}

} // namespace sc


#endif /* SC_TEST_HPP_ */
