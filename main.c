/**
* This file is part of the vendoring machine project.
*
* Copyright 2018, Huang Yang <elious.huang@gmail.com>. All rights reserved.
*
* See the COPYING file for the terms of usage and distribution.
*/
#include "trace.h"
#include "stm32f10x_cfg.h"
#include "pinconfig.h"
#include "dbgserial.h"

static void clock_init(void)
{
    //config rcc
    RCC_DeInit();
    bool flag = RCC_StartupHSE();

    //config flash latency
    FLASH_SetLatency(FLASH_LATENCY_TWO);
    FLASH_EnablePrefetch(TRUE);

    //config HCLK(72MHz), PCLK1(36MHz), PCLK2(72MHz)
    RCC_HCLKPrescalerFromSYSCLK(RCC_HPRE_SYSCLK);
    RCC_PCLK1PrescalerHCLK(RCC_PPRE1_HCLK_DIV2);
    RCC_PCLK2PrescalerFromHCLK(RCC_PPRE2_HCLK);

    //config PLL(72MHz)
    uint32_t retVal = RCC_SetSysclkUsePLL(72000000, TRUE, 8000000);
    RCC_SystemClockSwitch(RCC_SW_PLL);
    //Wait till PLL is used as system clock source
    while (RCC_GetSystemClock() != 0x02);

    //config adc slock(9MHz)
    RCC_ADCPrescalerFromPCLK2(RCC_ADC_PCLK_DIV8);
}

int main(int argc, char **argv)
{
    clock_init();
    pin_init();
    dbg_serial_setup();
}