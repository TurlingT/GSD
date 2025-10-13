/*
*********************************************************************************************************
*                                              EXAMPLE CODE
*
*                          (c) Copyright 2003-2006; Micrium, Inc.; Weston, FL
*
*               All rights reserved.  Protected by international copyright laws.
*               Knowledge of the source code may NOT be used to develop a similar product.
*               Please help us continue to provide the Embedded community with the finest
*               software available.  Your honesty is greatly appreciated.
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*
*                                           MASTER INCLUDES
*
*                                     ST Microelectronics STM32
*                                              with the
*                                   STM3210B-EVAL Evaluation Board
*
* Filename      : includes.h
* Version       : V1.10
* Programmer(s) : BAN
*********************************************************************************************************
*/

#ifndef  __INCLUDES_H__
#define  __INCLUDES_H__

#define	uint32          unsigned long	
#define   uint16          unsigned int
#define	uint8           unsigned char
#define	sint32          signed long	
#define   sint16          signed int
#define	sint8           signed char

#include "stm32f10x_conf.h"  
//包含所有的STM3库文件的头文件
//显示相关的头文件
//操作系统头文件
#include "..\bsp\bsp.h"
#include <math.h>
//自定义头文件
#include "..\user\MAIN\main.h"
#include "..\user\LOAD\LOAD.h"
#include "..\user\SYS_INIT\SYS_INIT.h"
#include "..\user\JIARE\JIARE.h"
#include "..\user\MODBUS\MODBUS.h"
#include "..\user\SENSOR\SENSOR.h"
#include "..\user\SHUCHU\shuchu.h"
#include "..\user\LCD\lcd.h"
#include "..\user\KEY\key.h"
#include "..\user\SHEZHI\shezhi.h"


#endif

