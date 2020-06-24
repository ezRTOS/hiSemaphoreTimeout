/*
 * share.h
 */

#ifndef APP_SHARE_SHARE_H_
#define APP_SHARE_SHARE_H_

#include "ezRTOS.h"

typedef struct _share_data_t{
  uint32_t appVersion;
  uint32_t SystemCoreClock;
}share_data_t;

typedef struct _share_bss_t{
  osThreadIdT thread_led;
  osSemaphoreIdT semLed;
}share_bss_t;

extern const osShareHeaderT share_header;

#define share_data ((share_data_t*)SHAREDATA)
#define share_bss ((share_bss_t*)SHAREBSS)

#endif /* APP_SHARE_SHARE_H_ */
