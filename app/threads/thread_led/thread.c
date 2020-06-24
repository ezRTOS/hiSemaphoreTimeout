/*
 * thread.c
 */

#include "thread.h"

#include "devices/device.h"
#include "share/share.h"

void thread_led(void *arg)
{
  uint32_t ui32LedIndex = 0;
  while(1)
  {
    if(SYSTIMEOUT == ostWait(share_bss->semLed, thread_led_data->delay))
    {
      ui32LedIndex = (ui32LedIndex + 1) % 4;
    }
    ostDevControl(DEV_LED, LED_TOGGLE, ui32LedIndex, 0);
  }
  return;
}
