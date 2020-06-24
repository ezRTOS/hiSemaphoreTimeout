/*
 * led.h
 */

#ifndef APP_DEVICES_LED_H_
#define APP_DEVICES_LED_H_

/* CONTROL FUNCTION */
#define LED_TOGGLE    0
#define LED_ON        1
#define LED_OFF       2

/* driver function */
osDevCallT ledInit(osDevIdT devId);
osDevCallT ledControl(osDevIdT devId, int32_t i32Func, int32_t i32Arg1, int32_t i32Arg2);

#endif /* APP_DEVICES_LED_H_ */
