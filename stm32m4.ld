/*
*****************************************************************************
**
**  File        : STM32M4.ld
**
**  Target      : STMicroelectronics STM32 (Cortex-M3 & M4)
**
*****************************************************************************
*/

/* Entry Point */
start = 0x08000060;
ENTRY(start)

/* Specify the memory areas */
MEMORY
{
ROM_VECTOR (rx)     : ORIGIN = 0x08000000, LENGTH = 64
ROM_OS (rx)         : ORIGIN = 0x08000040, LENGTH = 24K
ROM_BOOT (rx)       : ORIGIN = 0x08010000, LENGTH = 4K
ROM_APP (rx)        : ORIGIN = 0x08011000, LENGTH = 64K
/* real ram for os and share */
RAM_BOOT (xrw)      : ORIGIN = 0x20000500, LENGTH = 32K
RAM_APP (xrw)       : ORIGIN = 0x20000400, LENGTH = 32K
}

/* Define output sections */
SECTIONS
{
  /***** RTOS *****/
  /* The startup code goes first into FLASH */
  .g_pfnVectors :
  {
    . = ALIGN(4);
    KEEP(*(.osVectors)) /* Startup code */
  } >ROM_VECTOR

  /***** ezRTOS *****/
  .ezrtos :
  {
    . = ALIGN(4);
    KEEP(*(.ezrtos))
  } >ROM_OS

  /*!=== Separator ===!*/
  /***** BOOTLOADER *****/
  /* The program code and other data goes into FLASH */
  .boot_text :
  {
    . = ALIGN(4);
    KEEP(*boot.o(.bootloader))
    KEEP(*boot.o(.text))
    KEEP(*boot.o(.text*))
    KEEP(*boot.o(.eh_frame))
  } >ROM_BOOT

  /* used by the "Bootloader" function to initialize .bss_data */
  _boot_data_rom = LOADADDR(.boot_data);

  /* Initialized .boot_data sections goes into RAM, load LMA copy after code */
  .boot_data : 
  {
    . = ALIGN(4);
    _boot_sdata_ram = .;
    KEEP(*boot.o(.data))
    KEEP(*boot.o(.data*))

    . = ALIGN(4);
    _boot_edata_ram = .;
  } >RAM_BOOT AT> ROM_BOOT

  /* Uninitialized data section */
  . = ALIGN(4);
  .boot_bss :
  {
    /* This is used by the "Bootloader" function in order to initialize the .boot_bss secion */
    _boot_sbss_ram = .;
    KEEP(*boot.o(.bss))
    KEEP(*boot.o(.bss*))
    KEEP(*boot.o(COMMON))

    . = ALIGN(4);
    _boot_ebss_ram = .;
  } >RAM_BOOT

  /* Constant data goes into FLASH */
  .boot_rodata :
  {
    . = ALIGN(4);
    KEEP(*boot.o(.rodata))
    KEEP(*boot.o(.rodata*))
  } >ROM_BOOT

  /*!=== Separator ===!*/
  /***** APPLICATION *****/
  /* The startup code goes first into FLASH */
  .isr_vector :
  {
    . = ALIGN(4);
    KEEP(*(.isr_vector)) /* Startup code */
  } >ROM_APP

  /* used by the "Initialization" function to initialize .app_data */
  _app_data_rom = LOADADDR(.app_data);

  /* Initialized data sections goes into RAM, load LMA copy after code */
  .app_data :
  {
    . = ALIGN(4);
    _app_sdata_ram = .;
    KEEP(*init.o(.data))
    KEEP(*init.o(.data*))
    KEEP(*main.o(.data))
    KEEP(*main.o(.data*))
    KEEP(*bsp.o(.data))
    KEEP(*bsp.o(.data*))
    KEEP(*devices.o(.data))
    KEEP(*devices.o(.data*))
    KEEP(*system_stm32f4xx.o(.data))
    KEEP(*system_stm32f4xx.o(.data*))
    KEEP(*startup_stm32f407xx.o(.data))
    KEEP(*startup_stm32f407xx.o(.data*))

    . = ALIGN(4);
    _app_edata_ram = .;
  } >RAM_APP AT> ROM_APP

  /* Uninitialized data section */
  . = ALIGN(4);
  .app_bss :
  {
    /* This is used by the "Initialization" function in order to initialize the .app_bss secion */
    _app_sbss_ram = .;
    KEEP(*init.o(.bss))
    KEEP(*init.o(.bss*))
    KEEP(*init.o(COMMON))
    KEEP(*main.o(.bss))
    KEEP(*main.o(.bss*))
    KEEP(*main.o(COMMON))
    KEEP(*bsp.o(.bss))
    KEEP(*bsp.o(.bss*))
    KEEP(*bsp.o(COMMON))
    KEEP(*devices.o(.bss))
    KEEP(*devices.o(.bss*))
    KEEP(*devices.o(COMMON))
    KEEP(*system_stm32f4xx.o(.bss))
    KEEP(*system_stm32f4xx.o(.bss*))
    KEEP(*system_stm32f4xx.o(COMMON))
    KEEP(*startup_stm32f407xx.o(.bss))
    KEEP(*startup_stm32f407xx.o(.bss*))
    KEEP(*startup_stm32f407xx.o(COMMON))
    
    . = ALIGN(4);
    _app_ebss_ram = .;
  } >RAM_APP

  /* The program code and other data goes into FLASH */
  .app_text :
  {
    . = ALIGN(4);
    KEEP(*init.o(.text))
    KEEP(*init.o(.text*))
    KEEP(*init.o(.eh_frame))
    KEEP(*main.o(.text))
    KEEP(*main.o(.text*))
    KEEP(*main.o(.eh_frame))
    KEEP(*bsp.o(.text))
    KEEP(*bsp.o(.text*))
    KEEP(*bsp.o(.eh_frame))
    KEEP(*devices.o(.text))
    KEEP(*devices.o(.text*))
    KEEP(*devices.o(.eh_frame))
    KEEP(*system_stm32f4xx.o(.text))
    KEEP(*system_stm32f4xx.o(.text*))
    KEEP(*system_stm32f4xx.o(.eh_frame))
    KEEP(*startup_stm32f407xx.o(.text))
    KEEP(*startup_stm32f407xx.o(.text*))
    KEEP(*startup_stm32f407xx.o(.eh_frame))
  } >ROM_APP

  /* Constant data goes into FLASH */
  .app_rodata :
  {
    . = ALIGN(4);
    KEEP(*init.o(.rodata))
    KEEP(*init.o(.rodata*))
    KEEP(*main.o(.rodata))
    KEEP(*main.o(.rodata*))
    KEEP(*bsp.o(.rodata))
    KEEP(*bsp.o(.rodata*))
    KEEP(*devices.o(.rodata))
    KEEP(*devices.o(.rodata*))
    KEEP(*system_stm32f4xx.o(.rodata))
    KEEP(*system_stm32f4xx.o(.rodata*))
    KEEP(*startup_stm32f407xx.o(.rodata))
    KEEP(*startup_stm32f407xx.o(.rodata*))
  } >ROM_APP

  /*** share ***/
  /* Initialized data sections goes into RAM, load LMA copy after code */
  .share : 
  {
    . = ALIGN(4);
    KEEP(*share.o(.share_header))      
    KEEP(*share.o(.share_data))           /* .data sections */
  } >ROM_APP

  /*** thread led ***/
  .thread_led :
  {
    . = ALIGN(4);
    KEEP(*thread_led.o(.thread_header))
    . = ALIGN(4);
    KEEP(*thread_led.o(.thread_data))           /* .data sections */
    KEEP(*thread_led.o(.data*))           /* .data sections */
    . = ALIGN(4);
    KEEP(*thread_led.o(.text))           /* .text sections (code) */
    KEEP(*thread_led.o(.text*))          /* .text* sections (code) */
    KEEP(*thread_led.o(.eh_frame))
    . = ALIGN(4);
    KEEP(*thread_led.o(.rodata))         /* .rodata sections (constants, strings, etc.) */
    KEEP(*thread_led.o(.rodata*))        /* .rodata* sections (constants, strings, etc.) */
  } >ROM_APP
}
