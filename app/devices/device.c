/*
 * device.c
 */

#include "ezRTOS.h"
#include "device.h"

const osDevT ezDevList[NDEVS] =
{
    /* LED */
    { DEV_LED, 0, "LEDs",
      ledInit, (osDevOpen)ostDevIoNull, (osDevClose)ostDevIoNull,
      (osDevRead)ostDevIoNull, (osDevWrite)ostDevIoNull, (osDevSeek)ostDevIoNull,
      (osDevGetc)ostDevIoNull, (osDevPutc)ostDevIoNull, ledControl, (osDevExit)ostDevIoNull
    },
    /* BUTTON */
    { DEV_BTN, 0, "BTNs",
      btnInit, (osDevOpen)ostDevIoNull, (osDevClose)ostDevIoNull,
      (osDevRead)ostDevIoNull, (osDevWrite)ostDevIoNull, (osDevSeek)ostDevIoNull,
      (osDevGetc)ostDevIoNull, (osDevPutc)ostDevIoNull, (osDevControl)ostDevIoNull, (osDevExit)ostDevIoNull
    }
};
