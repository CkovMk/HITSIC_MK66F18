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

//#include "stdafx.h"

#include "rte_i2c.h"
#include "rte_spi.h"
#include "rte_softi2c.h"
#include "rte_uart.h"

#include "drv_ftfx_flash.h"
#include "drv_disp_ssd1306.h"
#include "drv_imu_invensense.h"
//#include "drv_cam.h"
#include "app_menu.h"

#include "sys_pitmgr.hpp"

//#include "cm_backtrace.h"

#include "easyflash.h"

drvimu_inv_device_t imu;

void FLASH_Demo(void);
void EF_Demo(void);

void main()
{
	/** 初始化阶段，关闭总中断 */
	HAL_EnterCritical();

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
	//cm_backtrace_init("HITSIC_MK66F18", "v1.1rc", "v1.0a");
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
	MENU_Data_NvmReadRegionConfig();
	MENU_Data_NvmRead_Boxed();
	MENU_PrintDisp();
	/** 初始化摄像头 */
	//CAMERA_Init();
	/** 初始化IMU */
	//DRVIMU_INV_GetDefaultConfig(&imu);

    /** 初始化结束，开启总中断 */
	HAL_ExitCritical();


	//FLASH_Demo();
    //EF_Demo();

	float f = arm_sin_f32(0.6f);

	while (true)
	{
	}
}


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
