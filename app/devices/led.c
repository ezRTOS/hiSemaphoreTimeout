/*
 * led.c
 */

#include "ezRTOS.h"
#include "led.h"
#include "stm32f4_discovery.h"

osDevCallT ledInit(osDevIdT devId)
{
  BSP_LED_Init();
  return SYSOK;
}

osDevCallT ledControl(osDevIdT devId, int32_t i32Func, int32_t i32Arg1, int32_t i32Arg2)
{
  switch(i32Func)
  {
  case LED_TOGGLE:
    BSP_LED_Toggle(i32Arg1);
    break;
  case LED_ON:
    BSP_LED_On(i32Arg1);
    break;
  case LED_OFF:
    BSP_LED_Off(i32Arg1);
    break;
  default:
    break;
  }
  return SYSOK;
}
