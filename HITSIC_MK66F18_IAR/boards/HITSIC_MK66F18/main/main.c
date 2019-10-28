#include "stdafx.h"

#include "cm_backtrace.h"

//#include "rte_i2c.h"
//#include "rte_spi.h"
//#include "rte_softi2c.h"
//#include "rte_uart.h"

//#include "drv_ftfx_flash.h"
//#include "drv_disp_ssd1306.h"
#include "drv_imu_invensense.h"
//#include "drv_button.h"
#include "app_menu.h"


drvimu_inv_device_t imu;

void main()
{
    __disable_irq();
    
    
	RTECLK_HsRun_180MHz();
	RTEPIN_BasicPin();
	RTEPIN_Uart0_SWO();
	RTEPIP_BasicPip();
	RTEPIP_Digital();
	RTEPIP_ANALOG();
    
    DbgConsole_Init(0U, 115200U, kSerialPort_Uart, CLOCK_GetFreq(kCLOCK_CoreSysClk));
    cm_backtrace_init("HITSIC_MK66F18", "v1.1rc", "v1.0a");
    
    PITMGR_Init();
    EXTINT_Init();
    //UARTMGR_DataInit();
    
    //FLASH_SimpleInit();
    //OLED_Init();
    //DRVIMU_INV_GetDefaultConfig(&imu);
    
    
    __enable_irq();
	
	printf("Hello, World!");
	float f = arm_sin_f32(0.6f);
	
	while(1)
    {
        
    }
	
}

