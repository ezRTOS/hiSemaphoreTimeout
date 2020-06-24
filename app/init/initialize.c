/*
 * initialize.c
 */

#include "ezRTOS.h"
#include "devices/device.h"
#include "share/share.h"
#include "main/main.h"
#include "system_stm32f4xx.h"

int gAppData = 100;
int gAppBss;

static void startup(void)
{
  extern char _app_data_rom;
  extern char _app_sdata_ram;
  extern char _app_edata_ram;
  extern char _app_sbss_ram;
  extern char _app_ebss_ram;
  char *pSrc;
  char *pTag;

  /* Initialize data section. */
  for(pSrc = &_app_data_rom, pTag = &_app_sdata_ram; pTag < &_app_edata_ram; pSrc++, pTag++)
  {
    *pTag = *pSrc;
  }

  /* Initialize bss section. */
  for(pTag = &_app_sbss_ram; pTag < &_app_ebss_ram; pTag++)
  {
    *pTag = 0;
  }
}


void* initialize(void)
{
  /* initialize global variables. */
  startup();

  SystemInit();

  /* enable MPU */
  ezInitMcuFeature(MPUENABLED);
  /* set region size for tasks - 2K */
  ezInitMemRegionsize(11);
  /* set memory space for OS */
  ezInitOsMem(0x20000400, 0x20000800, 0x20001000);
  /* set share memory */
  ezInitShareMem((uint32_t)&share_header, 0x20004000, 0x2001C000);
  /* set user memory */
  ezInitUserMem(0x10000000, 0x10010000);
  ezInitUserMem(0x20001000, 0x20004000);
  ezInitUserMem(0x2001C000, 0x20020000);
  /* set thread list for 10 tasks */
  ezInitThreadList(10);
  /* set device list for 5 devices */
  ezInitDeviceList((uint32_t)ezDevList, NDEVS);
  /* set object list for 10 objects */
  ezInitObjectList(10);
  /* set mutex list for 4 mutexes */
  ezInitMutexList(4);
  /* set port list for 4 ports */
  ezInitPortList(4);
  /* set timer list for 4 timers */
  ezInitTimerList(4);
  /* set system clock */
  share_data->SystemCoreClock = SystemCoreClockUpdate();
  ezInitSysTicks(168000);
  /* set irq mask */
  ezInitIrqMask(0x20);

  return main;
}

