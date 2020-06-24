/**
  *************** (C) COPYRIGHT 2017 STMicroelectronics ************************
  * @file      startup_stm32f107xc.s
  * @author    MCD Application Team
  * @version   V4.2.0
  * @date      31-March-2017
  * @brief     STM32F107xC Devices vector table for Atollic toolchain.
  *            This module performs:
  *                - Set the initial SP
  *                - Set the initial PC == Reset_Handler,
  *                - Set the vector table entries with the exceptions ISR address
  *                - Configure the clock system   
  *                - Branches to main in the C library (which eventually
  *                  calls main()).
  *            After Reset the Cortex-M3 processor is in Thread mode,
  *            priority is Privileged, and the Stack is set to Main.
  ******************************************************************************
  *
  * <h2><center>&copy; COPYRIGHT(c) 2017 STMicroelectronics</center></h2>
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */

  .syntax unified
  .cpu cortex-m4
  .arch armv7-m
  .fpu vfpv4
  .thumb

.global osVectors
.global Exception_Handler

  .section  .ezrtos, "ax"
  .incbin "ezRTOS/ezRTOS.bin"

  .section .text.Exception_Handler,"ax",%progbits
Exception_Handler:
Infinite_Loop:
  b Infinite_Loop
.size Exception_Handler, .-Exception_Handler

/******************************************************************************
*
* The minimal vector table for a Cortex M3.  Note that the proper constructs
* must be placed on this to ensure that it ends up at physical address
* 0x0000.0000.
*
******************************************************************************/
  .section .osVectors,"a",%progbits
  .type osVectors, %object
  .size osVectors, .-osVectors


osVectors:
  .word 0
  .word 0x08000061
  .word NMI_Handler
  .word HardFault_Handler
  .word MemManage_Handler
  .word BusFault_Handler
  .word UsageFault_Handler
  .word 0
  .word 0
  .word 0
  .word 0
  .word 0x08000065
  .word DebugMon_Handler
  .word 0
  .word 0x08000069
  .word 0x0800006D

/*  .word __initsetting
  .word _lstosapi
*/

/*  .word _lstlibapi
*/
/*  .rept VECTORS
  .word Normal_Handler
  .endr
*/

/*******************************************************************************
*
* Provide weak aliases for each Exception handler to the Default_Handler.
* As they are weak aliases, any function with the same name will override
* this definition.
*
*******************************************************************************/
  .weak  NMI_Handler
  .thumb_set NMI_Handler,Exception_Handler

  .weak  HardFault_Handler
  .thumb_set HardFault_Handler,Exception_Handler

  .weak  MemManage_Handler
  .thumb_set MemManage_Handler,Exception_Handler

  .weak  BusFault_Handler
  .thumb_set BusFault_Handler,Exception_Handler

  .weak  UsageFault_Handler
  .thumb_set UsageFault_Handler,Exception_Handler

//  .weak  SVC_Handler
//  .thumb_set SVC_Handler,Exception_Handler

  .weak  DebugMon_Handler
  .thumb_set DebugMon_Handler,Exception_Handler

//  .weak  PendSV_Handler
//  .thumb_set PendSV_Handler,Exception_Handler

//  .weak  SysTick_Handler
//  .thumb_set SysTick_Handler,Exception_Handler


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
