/*
 * module.c
 */

#include "thread.h"

__attribute__ ((section(".thread_data"))) const thread_led_data_t const_thread_led_data = {
  .delay = 500
};

__attribute__ ((section(".thread_header"))) const osThreadHeaderT thread_led_header = \
    {thread_led, 1500, 1024, (uint32_t)&const_thread_led_data, sizeof(thread_led_data_t), sizeof(thread_led_bss_t), 0, "thread_led"};


