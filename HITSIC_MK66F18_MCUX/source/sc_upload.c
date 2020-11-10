/******************************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2020,哈工大智能车创新俱乐部
 * All rights reserved.
 *
 * @file            UART
 * @company         哈工大智能车创新俱乐部
 * @author          李洋qq2367381108
 * @version         v1.0
 * @Software        MCUXpresso IDE v11.1.1
 * @Target core     K66
 * @date            2020.11.09
 *
 * @note：
        NUM_VAR为需要发送到上位机的变量个数。Send_Variable()适用于名优科创上位机，
                void Img_Upload(void)适用于红树伟业上位机

        哈尔滨工业大学智能车创新俱乐部专用，请勿泄露
***************************************************************************************************************************/

#include "sc_upload.h"
#include "drv_cam_zf9v034.hpp"
#define NUM_VAR  7
#define MY_UART  UART0

extern uartMgr_t *uartMgr0;
float Variable[NUM_VAR];//发送缓存数组

void SCHOST_Tx_WithoutMgr(const uint8_t *data, size_t length)
{
    UART_WriteBlocking(MY_UART, data, length);
}

void SCHOST_Send_Begin(void)
{
  SCHOST_Putchar(0x55);
  SCHOST_Putchar(0xaa);
  SCHOST_Putchar(0x11);
}

void  SCHOST_Send_Variable(void)
{
  uint8_t i=0,ch=0;
  float temp=0;
  SCHOST_Send_Begin();

  Variable[0] = 0;          //changing your data here
  Variable[1] = 1;
  Variable[2] = 2;
  Variable[3] = 3;
  Variable[4] = 4;
  Variable[5] = 5;
  Variable[6] = 6;


  SCHOST_Putchar(0x55);
  SCHOST_Putchar(0xaa);
  SCHOST_Putchar(0x11);
  SCHOST_Putchar(0x55);
  SCHOST_Putchar(0xaa);
  SCHOST_Putchar(0xff);
  SCHOST_Putchar(0x01);
  SCHOST_Putchar(NUM_VAR);
 for(i=0;i<NUM_VAR;i++)
  {
    temp=Variable[i];
    ch=SCHOST_BYTE0(temp);
    SCHOST_Putchar(ch);
    ch=SCHOST_BYTE1(temp);
    SCHOST_Putchar(ch);
    ch=SCHOST_BYTE2(temp);
    SCHOST_Putchar(ch);
    ch=SCHOST_BYTE3(temp);
    SCHOST_Putchar(ch);
  }
 SCHOST_Putchar(0x01);
}

void SCHOST_Img_Upload_Largesize(uint8_t* upload_img)
{
    uint8_t cmd = 3;
    uint8_t cmdf[2] = { cmd, ~cmd };
    uint8_t cmdr[2] = { ~cmd, cmd };
    SCHOST_Tx_WithoutMgr(cmdf,sizeof(cmdf));
    SCHOST_Tx_WithoutMgr(upload_img, 22560);
    SCHOST_Tx_WithoutMgr(cmdr, sizeof(cmdr));

}

void SCHOST_Img_Upload_Smallsize(uint8_t* upload_img)
{
    uint8_t cmdf[2] = { 0x11, 0x22 };
    uint8_t cmdr[2] = { 0x00,0xFF };
    SCHOST_Tx_WithoutMgr(cmdf, sizeof(cmdf));
    SCHOST_Tx_WithoutMgr(upload_img, 13160);
    SCHOST_Tx_WithoutMgr(cmdr, sizeof(cmdr));
}
