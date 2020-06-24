/*
 * device.h
 */

#ifndef APP_DEVICES_DEVICE_H_
#define APP_DEVICES_DEVICE_H_

#include "led.h"
#include "button.h"

extern const osDevT ezDevList[];

#define NDEVS         2

/* Device name definitions */
#define DEV_LED       0
#define DEV_BTN       1

#endif /* APP_DEVICES_DEVICE_H_ */
