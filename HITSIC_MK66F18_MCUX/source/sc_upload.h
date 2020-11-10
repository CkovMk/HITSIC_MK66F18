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

#define USE_UARTMGR_FOR_UART 0

#define SCHOST_BYTE0(Temp)       (*(char *)(&Temp))
#define SCHOST_BYTE1(Temp)       (*((char *)(&Temp) + 1))
#define SCHOST_BYTE2(Temp)       (*((char *)(&Temp) + 2))
#define SCHOST_BYTE3(Temp)       (*((char *)(&Temp) + 3))

#define SCHOST_putchar(temp)    UART_WriteBlocking(UART0,&temp,1)//uartMgr0->txPoll(&temp,1)
#define SCHOST_Tx_WithoutMgr(data, length)    SCHOST_Tx_WithoutMgr(data, length)//uartMgr0->(data, length)

/**
 * @brief : 串口发送数据
 *
 * @param       void        undefined
 */
void SCHOST_Tx_WithoutMgr(const uint8_t *data, size_t length);

/**
 * @brief : 发送一个字节的数据
 *
 * @param       temp        待发送的一字节数据
 */
void SCHOST_Putchar(char temp);

/**
 * @brief : 向上位机发送数据的开始帧
 *
 * @param       void        undefined
 */
void SCHOST_Send_Begin(void);

/**
 * @brief : 发送数据
 *
 * @param       void        undefined
 */
void SCHOST_Send_Variable(void);

/**
 * @brief : 发送大小为120*188的数组数据
 *注意数组类型应该是uint8_t 或者   char
 *
 * @param       upload_img      待发送数组的头地址
 */
void SCHOST_Img_Upload_Largesize(uint8_t* upload_img);

/**
 * @brief : 发送大小为70*188的数组数据
 *注意数组类型应该是uint8_t 或者   char
 *
 * @param       upload_img      待发送数组的头地址
 */
void SCHOST_Img_Upload_Smallsize(uint8_t* upload_img);
#endif//_SC_UPLOAD_H
