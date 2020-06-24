/*
 * button.c
 */

#include "stm32f4_discovery.h"
#include "ezRTOS.h"

osDevCallT btnInit(osDevIdT devId)
{
  BSP_PB_Init();
  return SYSOK;
}

void EXTI0_IRQHandler(void)
{
  osiEnterIrq();

  if((EXTI->PR & EXTI_Line0) != RESET)
  {
    /* Clear the EXTI line 0 pending bit */
    EXTI->PR = EXTI_Line0;
  }

  osiLeaveIrq();
}
