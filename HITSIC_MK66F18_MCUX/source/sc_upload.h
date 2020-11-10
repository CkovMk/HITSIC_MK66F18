/**
 * Copyright 2018 - 2020 HITSIC
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
/*
 * sc_upload.h
 *
 *  Created on: 2020.11.09
 *      Author: 李洋
 */

#ifndef _SC_UPLOAD_H
#define _SC_UPLOAD_H
#include "sys_uartmgr.hpp"
#include "fsl_uart.h"

#define MY_UART UART0
#define SCHOST_UART_Tx(data,length)  (UART_WriteBlocking(MY_UART, data, length))//uartMgr0->txPoll(data,length)


/**
 * @brief : 发送数据
 *
 * @param       void        undefined
 */
void SCHOST_SendVariable(float *my_var, uint8_t var_num);

/**
 * @brief : 发送大小为120*188的数组数据
 *注意数组类型应该是uint8_t 或者   char
 *
 * @param       upload_img      待发送数组的头地址
 */
void SCHOST_ImgUpload(uint8_t* upload_img, uint8_t row, uint8_t col);

#endif//_SC_UPLOAD_H
