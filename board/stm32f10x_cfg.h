/**
* This file is part of the auto-elevator project.
*
* Copyright 2018, Huang Yang <elious.huang@gmail.com>. All rights reserved.
*
* See the COPYING file for the terms of usage and distribution.
*/
#ifndef _STM32F10x_CFG_H
#define _STM32F10x_CFG_H

#include "assert.h"
#include "trace.h"

/**********************************************************
* library module inclue configure
***********************************************************/
/*********************************************************/
#define _MODULE_RCC
#define _MODULE_GPIO
#define _MODULE_USART
#define _MODULE_FLASH

/**********************************************************/
#ifdef _MODULE_RCC
#include "stm32f10x_rcc.h"
#endif

#ifdef _MODULE_GPIO
#include "stm32f10x_gpio.h"
#endif

#ifdef _MODULE_USART
#include "stm32f10x_usart.h"
#endif

#ifdef _MODULE_FLASH
#include "stm32f10x_flash.h"
#endif


#endif /* _STM32F10x_CFG_H_ */
