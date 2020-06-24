/*
 * main.c
 */

#include "main.h"

void main(void)
{
  osThreadParamT thrParam;

  /* initialize device driver */
  ostDevInit(DEV_LED);

  /* create semaphore for led */
  ostCreateSemaphore(0, &(share_bss->semLed));

  /* create task_led */
  thrParam.pvoidArg = NULL;
  thrParam.threadHeaderId = &thread_led_header;
  thrParam.ui16Priority = 100;
  thrParam.ui16TimeSlice = 100;
  thrParam.ui8Flags = USERENABLED | MPUENABLED;

  ostCreateThread(&thrParam, &(share_bss->thread_led));
  osResume(share_bss->thread_led, 0);

  return;
}

