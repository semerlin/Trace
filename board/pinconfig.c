/**
* This file is part of the auto-elevator project.
*
* Copyright 2018, Huang Yang <elious.huang@gmail.com>. All rights reserved.
*
* See the COPYING file for the terms of usage and distribution.
*/
#include "pinconfig.h"
#include "stm32f10x_cfg.h"

/* pin configure structure */
typedef struct
{
    char name[16];
    GPIO_Group group;
    GPIO_Config config;
} PIN_CONFIG;


typedef enum
{
    AHB,
    APB1,
    APB2,
} PIN_BUS;

typedef struct
{
    PIN_BUS bus;
    uint32_t reset_reg;
    uint32_t enable_reg;
} PIN_CLOCK;


/* pin arrays */
PIN_CONFIG pins[] =
{
    {"DEBUG_TX", GPIOB, 10, GPIO_Speed_50MHz, GPIO_Mode_AF_PP},
    {"DEBUG_RX", GPIOB, 11, GPIO_Speed_2MHz, GPIO_Mode_IN_FLOATING},
};

/* clock arrays */
PIN_CLOCK pin_clocks[] =
{
    {AHB, RCC_AHB_ENABLE_CRC, RCC_AHB_ENABLE_CRC},
    {APB2, RCC_APB2_RESET_IOPB, RCC_APB2_ENABLE_IOPB},
    {APB1, RCC_APB1_RESET_USART3, RCC_APB1_ENABLE_USART3},
};

/**
 * @brief init pins
 */
void pin_init(void)
{
    /* config pin clocks */
    uint32_t len = sizeof(pin_clocks) / sizeof(PIN_CLOCK);
    for (uint32_t i = 0; i < len; ++i)
    {
        switch (pin_clocks[i].bus)
        {
        case AHB:
            RCC_AHBPeripClockEnable(pin_clocks[i].enable_reg, TRUE);
            break;
        case APB1:
            RCC_APB1PeriphReset(pin_clocks[i].reset_reg, TRUE);
            RCC_APB1PeriphReset(pin_clocks[i].reset_reg, FALSE);
            RCC_APB1PeripClockEnable(pin_clocks[i].enable_reg, TRUE);
            break;
        case APB2:
            RCC_APB2PeriphReset(pin_clocks[i].reset_reg, TRUE);
            RCC_APB2PeriphReset(pin_clocks[i].reset_reg, FALSE);
            RCC_APB2PeripClockEnable(pin_clocks[i].enable_reg, TRUE);
            break;
        default:
            break;
        }
    }

    /* config pins */
    len = sizeof(pins) / sizeof(PIN_CONFIG);
    for (uint32_t i = 0; i < len; ++i)
    {
        GPIO_Setup(pins[i].group, &pins[i].config);
    }
}