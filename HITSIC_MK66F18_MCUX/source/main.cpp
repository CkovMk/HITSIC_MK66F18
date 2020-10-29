/*
 * Copyright 2016-2019 NXP
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of NXP Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */


/**
 * Copyright 2018 - 2019 HITSIC
 * All rights reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include "hitsic_common.h"

/** HITSIC_Module_DRV */
#include "drv_ftfx_flash.h"
#include "drv_disp_ssd1306.hpp"

/** HITSIC_Module_SYS */
#include "sys_pitmgr.hpp"
#include "sys_extint.hpp"
#include "cm_backtrace.h"
//#include "easyflash.h"

/** HITSIC_Module_APP */
#include "app_menu.h"

/** FATFS */
#include "ff.h"
#include "sdmmc_config.h"
#include "sc_gpio.h"
#include "sc_adc.h"
#include "sc_ftm.h"
void FLASH_Demo(void);
void EF_Demo(void);


FIL file;                                           //文件对象
FATFS fatfs;                                   //逻辑驱动器的工作区

/** HITSIC_Module_TEST */
#include "drv_cam_zf9v034_test.hpp"
#include "app_menu_test.hpp"
#include "sys_fatfs_test.hpp"
#include "sys_fatfs_diskioTest.hpp"

void main(void)
{
	/** 初始化阶段，关闭总中断 */
	HAL_EnterCritical();

	/** 初始化时钟 */
	RTECLK_HsRun_180MHz();
	/** 初始化引脚路由 */
	RTEPIN_Basic();
	RTEPIN_Digital();
    RTEPIN_Analog();
	RTEPIN_LPUART0_DBG();
	RTEPIN_UART0_WLAN();

	/** 初始化外设 */
	RTEPIP_Basic();
	RTEPIP_Device();

	/** 初始化调试串口 */
	DbgConsole_Init(0U, 921600U, kSerialPort_Uart, CLOCK_GetFreq(kCLOCK_CoreSysClk));
	/** 初始化CMBackTrace */
	cm_backtrace_init("HITSIC_MK66F18", "v1.1rc", "v1.0a");
	PRINTF("Hello World!\n");
	PRINTF("gcc version: %d.%d.%d\n",__GNUC__,__GNUC_MINOR__,__GNUC_PATCHLEVEL__);
    /** 初始化ftfx_Flash */
	FLASH_SimpleInit();
	/** 初始化EasyFlash */
	//easyflash_init();
	/** 初始化PIT中断管理器 */
	pitMgr_t::init();
	/** 初始化I/O中断管理器 */
	extInt_t::init();
	/** 初始化串口管理器 */
	//UARTMGR_DataInit();

	/** 初始化OLED屏幕 */
	DISP_SSD1306_Init();

	/** 初始化菜单 */
	MENU_Init();
	MENU_Data_NvmReadRegionConfig();
	MENU_Data_NvmRead(menu_currRegionNum);
//	MENU_PrintDisp();
	MENU_Suspend();
	extern const uint8_t DISP_image_100thAnniversary[8][128];
	DISP_SSD1306_BufferUpload((uint8_t*)DISP_image_100thAnniversary);
	SDK_DelayAtLeastUs(1000 * 1000,CLOCK_GetFreq(kCLOCK_CoreSysClk));
	/** 初始化摄像头 */

	/** 初始化IMU */

    /** 初始化结束，开启总中断 */
	HAL_ExitCritical();

	//FATFS_BasicTest();
	//FATFS_DiskioTest();
	CAM_ZF9V034_UnitTest();

	MENU_Resume();

	//CAM_ZF9V034_UnitTest();

	//result = SD_HostInit(&g_sd);
	//result = SD_CardInit(&g_sd);
	//result = f_mount(&fatfs,"sdcard:",1);                                   //挂载SD卡

	float f = arm_sin_f32(0.6f);

   // DISP_SSD1306_Fill(0);

    //DISP_SSD1306_Print_F6x8(0,0,"HITSIC!");

	uint8_t duty=0;
	uint8_t adc0,adc1,adc2,adc3,adc4,adc5,adc6,adc7;
	int speed1,speed2;
    uint8_t sw1_state = GPIO_PinRead(GPIOA, 9U);


	while (true)
	{

	    //DISP_SSD1306_Fill(0);
	    /*
	    adc0=ADC_Get(ADC0,0,10);
	    adc1=ADC_Get(ADC0,0,11);
	    adc2=ADC_Get(ADC0,0,12);
	    adc3=ADC_Get(ADC0,0,13);
	    adc4=ADC_Get(ADC0,0,16);
	    adc5=ADC_Get(ADC0,0,17);
	    adc6=ADC_Get(ADC0,0,18);
	    adc7=ADC_Get(ADC0,0,23);
	    DISP_SSD1306_Printf_F6x8(0,0,"%d",adc0);
	    DISP_SSD1306_Printf_F6x8(0,1,"%d",adc1);
	    DISP_SSD1306_Printf_F6x8(0,2,"%d",adc2);
	    DISP_SSD1306_Printf_F6x8(0,3,"%d",adc3);
	    DISP_SSD1306_Printf_F6x8(0,4,"%d",adc4);
	    DISP_SSD1306_Printf_F6x8(0,5,"%d",adc5);
	    DISP_SSD1306_Printf_F6x8(0,6,"%d",adc6);
	    DISP_SSD1306_Printf_F6x8(0,7,"%d",adc7);
	    */
/*
	    speed1=Ftm_GetSpeed(FTM1);
	    DISP_SSD1306_Printf_F6x8(60,0,"%d",speed1);
	    speed2=Ftm_GetSpeed(FTM2);
	    DISP_SSD1306_Printf_F6x8(60,1,"%d",speed2);
	    SDK_DelayAtLeastUs(500*1000, 180*1000*1000);
	    Ftm_ClearSpeed(FTM1);
	    Ftm_ClearSpeed(FTM2);
*/
	    if(GPIO_Check(&boma1))
	    {
	    GPIO_PinWrite(GPIOC, 19, 0);
	    SDK_DelayAtLeastUs(1000*1000, 180*1000*1000);
	    GPIO_PinWrite(GPIOC, 19, 1);
	    SDK_DelayAtLeastUs(1000*1000, 180*1000*1000);
	    }
	    else
	    {
	    GPIO_PinWrite(GPIOC, 19, 0);
	    }
	    //GPIO_PortToggle(GPIOC, 19);
	    //SDK_DelayAtLeastUs(2000*1000, 180*1000*1000);
	    /*
        if(GPIO_Check(&key_right))
        {
            duty+=5;
        }
        if(GPIO_Check(&key_left))
        {
            duty-=5;
        }
        if(duty<=0)
        {
            duty=0;
        }
        if(duty>=80)
        {
            duty=80;
        }
        DISP_SSD1306_Printf_F6x8(0,0,"%d",duty);
        Ftm_PWM_Change(FTM0,kFTM_Chnl_1,20000,duty);
        Ftm_PWM_Change(FTM0,kFTM_Chnl_3,20000,duty);
*/

	}
}
