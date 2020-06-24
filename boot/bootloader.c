/*
 * bootloader.c
 */

#include "bootloader.h"

int gBootData = 50;
int gBootBss;

static void startup(void)
{
  extern char _boot_data_rom;
  extern char _boot_sdata_ram;
  extern char _boot_edata_ram;
  extern char _boot_sbss_ram;
  extern char _boot_ebss_ram;
  char *pSrc;
  char *pTag;

  /* Initialize data section. */
  for(pSrc = &_boot_data_rom, pTag = &_boot_sdata_ram; pTag < &_boot_edata_ram; pSrc++, pTag++)
  {
    *pTag = *pSrc;
  }

  /* Initialize bss section. */
  for(pTag = &_boot_sbss_ram; pTag < &_boot_ebss_ram; pTag++)
  {
    *pTag = 0;
  }
}

__attribute__ ((section (".bootloader"))) void* bootloader(void)
{
  /* initialize global variables. */
  startup();

  return (void*)((*(uint32_t*)INITFUNC) | 0x01);
}

