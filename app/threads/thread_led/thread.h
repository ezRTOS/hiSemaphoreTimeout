/*
 * thread.h
 */

#ifndef APP_THREADS_THREAD_LED_THREAD_H_
#define APP_THREADS_THREAD_LED_THREAD_H_

#include "ezRTOS.h"

typedef struct _thread_led_data_t{
  int delay;
}thread_led_data_t;

typedef struct _thread_led_bss_t{
  int ledIndex;
}thread_led_bss_t;

extern const osThreadHeaderT thread_led_header;

#define thread_led_data ((thread_led_data_t *)THREADDATA)
#define thread_led_bss ((thread_led_bss_t *)THREADBSS)

void thread_led(void *arg);

#endif /* APP_THREADS_THREAD_LED_THREAD_H_ */
