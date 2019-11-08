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

#include "stdafx.h"

#include "rte_i2c.h"
#include "rte_spi.h"
#include "rte_softi2c.h"
#include "rte_uart.h"

#include "drv_ftfx_flash.h"
#include "drv_disp_ssd1306.h"
#include "drv_imu_invensense.h"
#include "drv_cam.h"
//#include "drv_button.h"   //未使用
#include "app_menu.h"     //仍在开发中...

#include "cm_backtrace.h"

//#include "easyflash.h"

drvimu_inv_device_t imu;

void FLASH_Demo(void);
void EF_Demo(void);

void main()
{
	/** 初始化阶段，关闭总中断 */
	__disable_irq();

	/** 初始化时钟 */
	RTECLK_HsRun_180MHz();
	/** 初始化引脚路由 */
	RTEPIN_BasicPin();
	RTEPIN_Board();
	//RTEPIN_Uart0_SPP();
	RTEPIN_Uart0_SWO();
	/** 初始化外设 */
	RTEPIP_BasicPip();
	RTEPIP_Digital();
	RTEPIP_Analog();

	/** 初始化调试串口 */
	DbgConsole_Init(0U, 115200U, kSerialPort_Uart, CLOCK_GetFreq(kCLOCK_CoreSysClk));
	/** 初始化CMBackTrace */
	cm_backtrace_init("HITSIC_MK66F18", "v1.1rc", "v1.0a");
	printf("Hello, World!\n");
    
    /** 初始化ftfx_Flash */
	FLASH_SimpleInit();
	/** 初始化EasyFlash */
	//easyflash_init();
	/** 初始化PIT中断管理器 */
	PITMGR_Init();
	/** 初始化I/O中断管理器 */
	EXTINT_Init();
	/** 初始化串口管理器 */
	//UARTMGR_DataInit();

	/** 初始化OLED屏幕 */
	OLED_Init();
	/** 初始化菜单 */
	MENU_Init();
	MENU_PrintDisp();
	/** 初始化摄像头 */
	//CAMERA_Init();
	/** 初始化IMU */
	//DRVIMU_INV_GetDefaultConfig(&imu);
	//OLED_PrintStr_F6x8(10,0,"OLED Test !");
	//OLED_PrintStr_F6x8(10,2,"OLED Test !");
	//OLED_PrintStr_F6x8(10,4,"OLED Test !");

	__enable_irq();
    
	FLASH_Demo();
    //EF_Demo();

	float f = arm_sin_f32(0.6f);

	while (1)
	{
	}
}

void FLASH_Demo(void)
{
	int32_t whatData = 19981214;
	int32_t dataRead = 0;
	status_t result = kStatus_Success;
	result = FLASH_SectorErase(0);
	result = FLASH_AddressProgram(4, &whatData, sizeof(int32_t));
	result = FLASH_AddressRead(4, &dataRead, sizeof(int32_t));
	if(dataRead == whatData)
	{
		printf("Data Matched !\n");
	}
}
/*
void EF_Demo(void)
{
	int32_t read_ef_status = 0;
    size_t len = 0;
    ef_get_env_blob("ef_status", &read_ef_status, sizeof(int32_t), &len);
	if (4u == len)
	{
		printf("ef_status = %d\n", read_ef_status);
	}
	else
	{
		printf("ef_status error!len = %d\n",len);
		//return;
	}
	read_ef_status = 0x55 << 24u;
	ef_set_env_blob("ef_status", &read_ef_status, sizeof(int32_t));
	printf("ef_status set to %d\n", read_ef_status);
    ef_get_env_blob("ef_status", &read_ef_status, sizeof(int32_t), &len);
	if (4u == len)
	{
		printf("ef_status = %d\n", read_ef_status);
	}
	else
	{
		printf("ef_status error!len = %d\n",len);
	}
}
*/
