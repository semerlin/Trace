/**
* This file is part of the auto-elevator project.
*
* Copyright 2018, Huang Yang <elious.huang@gmail.com>. All rights reserved.
*
* See the COPYING file for the terms of usage and distribution.
*/
#include "stm32f10x_cfg.h"
#include "dbgserial.h"

/**
 * @brief init debug serial port
 */
void dbg_serial_setup(void)
{
    USART_Config config;
    USART_StructInit(&config);

    config.rxEnable = FALSE;
    USART_Setup(USART3, &config);
    USART_EnableInt(USART3, USART_IT_RXNE, FALSE);
    USART_EnableInt(USART3, USART_IT_TXE, FALSE);
    USART_Enable(USART3, TRUE);
}

/**
 * @brief put char
 * @param data - data to put
 */
void dbg_putchar(char data)
{
    USART_WriteData_Wait(USART3, data);
}

/**
 * @brief put string
 * @param string - string to put
 * @param length - string length
 */
void dbg_putstring(const char *string, uint32_t length)
{
    const char *pNext = string;
    while (length--)
    {
        dbg_putchar(*pNext++);
    }
}
