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
 NUM_VAR为需要发送到上位机的变量个数。SCHOST_VarUpload()适用于名优科创上位机，
 void SCHOST_ImgUpload(void)适用于红树伟业上位机

 哈尔滨工业大学智能车创新俱乐部专用，请勿泄露
 ***************************************************************************************************************************/

#include "sc_host.h"

void SCHOST_VarUpload(float *my_var, uint8_t var_num)
{
    uint8_t cmdf[7] =
    { 0x55, 0xaa, 0x11, 0x55, 0xaa, 0xff, 0x01 };
    uint8_t cmdr = 0x01;
    uint8_t begin_cmd[3] =
    { 0x55, 0xaa, 0x11 };
    /*! 发送帧头 */
    SCHOST_UART_Tx(begin_cmd, sizeof(begin_cmd));
    /*! 发送数据个数 */
    SCHOST_UART_Tx(cmdf, sizeof(cmdf));
    SCHOST_UART_Tx(&var_num, 1);
    /*! 发送数据 */
    SCHOST_UART_Tx((uint8_t* )(my_var), var_num * 4U);
    /*! 发送帧尾 */
    SCHOST_UART_Tx(&cmdr, 1);
}

void SCHOST_ImgUpload(uint8_t *upload_img, uint8_t row, uint8_t col)
{
    uint8_t cmd = 3, icmd = ~3;
    uint8_t cmdf[2] =
    { cmd, icmd };
    uint8_t cmdr[2] =
    { icmd, cmd };
    /*! 发送帧头 */
    SCHOST_UART_Tx(cmdf, sizeof(cmdf));
    /*! 发送数据 */
    SCHOST_UART_Tx(upload_img, row * col);
    /*! 发送帧尾 */
    SCHOST_UART_Tx(cmdr, sizeof(cmdr));

}
