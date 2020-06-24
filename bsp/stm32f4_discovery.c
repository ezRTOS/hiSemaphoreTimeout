/**
  ******************************************************************************
  * @file    stm32f4_discovery.c
  * @author  MCD Application Team
  * @version V2.0.3
  * @date    10-December-2014
  * @brief   This file provides set of firmware functions to manage Leds and
  *          push-button available on STM32F4-Discovery Kit from STMicroelectronics.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2014 STMicroelectronics</center></h2>
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
/* Includes ------------------------------------------------------------------*/
#include "stm32f4_discovery.h"

/** @addtogroup BSP
  * @{
  */ 

/** @addtogroup STM32F4_DISCOVERY
  * @{
  */   
    
/** @defgroup STM32F4_DISCOVERY_LOW_LEVEL 
  * @brief This file provides set of firmware functions to manage Leds and push-button
  *        available on STM32F4-Discovery Kit from STMicroelectronics.
  * @{
  */ 

/** @defgroup STM32F4_DISCOVERY_LOW_LEVEL_Private_TypesDefinitions
  * @{
  */ 
/**
  * @}
  */ 

/** @defgroup STM32F4_DISCOVERY_LOW_LEVEL_Private_Defines
  * @{
  */
  
  /**
  * @brief STM32F4 DISCO BSP Driver version number V2.0.2
  */
#define __STM32F4_DISCO_BSP_VERSION_MAIN   (0x02) /*!< [31:24] main version */
#define __STM32F4_DISCO_BSP_VERSION_SUB1   (0x00) /*!< [23:16] sub1 version */
#define __STM32F4_DISCO_BSP_VERSION_SUB2   (0x02) /*!< [15:8]  sub2 version */
#define __STM32F4_DISCO_BSP_VERSION_RC     (0x00) /*!< [7:0]  release candidate */ 
#define __STM32F4_DISCO_BSP_VERSION         ((__STM32F4_DISCO_BSP_VERSION_MAIN << 24)\
                                             |(__STM32F4_DISCO_BSP_VERSION_SUB1 << 16)\
                                             |(__STM32F4_DISCO_BSP_VERSION_SUB2 << 8 )\
                                             |(__STM32F4_DISCO_BSP_VERSION_RC)) 
/**
  * @}
  */ 


/** @defgroup STM32F4_DISCOVERY_LOW_LEVEL_Private_Macros
  * @{
  */ 
/**
  * @}
  */ 

/** @defgroup STM32F4_DISCOVERY_LOW_LEVEL_Private_Variables
  * @{
  */ 
/**
  * @}
  */ 

/** @defgroup STM32F4_DISCOVERY_LOW_LEVEL_Private_FunctionPrototypes
  * @{
  */ 
/**
  * @}
  */ 

/** @defgroup STM32F4_DISCOVERY_LOW_LEVEL_Private_Functions
  * @{
  */ 
/**
  * @}
  */

/** @defgroup STM32F4_DISCOVERY_LOW_LEVEL_LED_Functions
  * @{
  */ 

/**
  * @brief  This method returns the STM32F4 DISCO BSP Driver revision
  * @param  None
  * @retval version : 0xXYZR (8bits for each decimal, R for RC)
  */
uint32_t BSP_GetVersion(void)
{
  return __STM32F4_DISCO_BSP_VERSION;
}

/**
  * @brief  Configures LED GPIO.
  * @param  Led: Specifies the Led to be configured. 
  *   This parameter can be one of following parameters:
  *     @arg LED4
  *     @arg LED3
  *     @arg LED5
  *     @arg LED6
  * @retval None
  */
void BSP_LED_Init(void)
{
  /* Enable the GPIO_LED Clock */
  __GPIOD_CLK_ENABLE();

  /* Configure the GPIO_LED pin */
  GPIOD->MODER = 0x55000000;			/* output */
  GPIOD->OTYPER = 0x00000000;			/* push-pull */
  GPIOD->OSPEEDR = 0xAA000000;			/* high speed */
  GPIOD->PUPDR = 0x55000000;			/* pull up */
  GPIOD->ODR = 0x00000000;				/* clear output */
}

/**
  * @brief  Turns selected LED On.
  * @param  Led: Specifies the Led to be set on. 
  *   This parameter can be one of following parameters:
  *     @arg LED4
  *     @arg LED3
  *     @arg LED5
  *     @arg LED6  
  * @retval None
  */
void BSP_LED_On(Led_TypeDef Led)
{
  if(Led < 4)
  {
    GPIOD->BSRRL = 1 << (12 + Led);
  }
}

/**
  * @brief  Turns selected LED Off.
  * @param  Led: Specifies the Led to be set off. 
  *   This parameter can be one of following parameters:
  *     @arg LED4
  *     @arg LED3
  *     @arg LED5
  *     @arg LED6 
  * @retval None
  */
void BSP_LED_Off(Led_TypeDef Led)
{
  if(Led < 4)
  {
    GPIOD->BSRRH = 1 << (12 + Led);
  }
}

/**
  * @brief  Toggles the selected LED.
  * @param  Led: Specifies the Led to be toggled. 
  *   This parameter can be one of following parameters:
  *     @arg LED4
  *     @arg LED3
  *     @arg LED5
  *     @arg LED6  
  * @retval None
  */
void BSP_LED_Toggle(Led_TypeDef Led)
{
  if(Led < 4)
  {
    GPIOD->ODR ^= 1 << (12 + Led);
  }
}

void BSP_LED_Delay(uint32_t delay)
{
	uint32_t _delay = delay;
	while(_delay > 0)
	{
		_delay --;
	}
}

/**
  * @}
  */ 

/** @defgroup STM32F4_DISCOVERY_LOW_LEVEL_BUTTON_Functions
  * @{
  */ 

/**
  * @brief  Configures Button GPIO and EXTI Line.
  * @param  Button: Specifies the Button to be configured.
  *   This parameter should be: BUTTON_KEY
  * @param  Mode: Specifies Button mode.
  *   This parameter can be one of following parameters:   
  *     @arg BUTTON_MODE_GPIO: Button will be used as simple IO 
  *     @arg BUTTON_MODE_EXTI: Button will be connected to EXTI line with interrupt
  *                            generation capability  
  * @retval None
  */
void BSP_PB_Init(void)
{
  /* Enable the BUTTON Clock */
  __GPIOA_CLK_ENABLE();
  
  GPIOA->MODER = 0xA8000000;			/* input */
  GPIOA->PUPDR = 0x64000000;			/* NO PULL */
  SYSCFG->EXTICR[0] = 0x00000000;		/* PA0 is EXIT0 */
  EXTI->IMR = EXTI_IMR_MR0;				/* EXTI0 is enabled */
  EXTI->RTSR = EXTI_RTSR_TR0;			/* EXTI0 is triggerd by rising edge */
  EXTI->FTSR = 0;						/* falling edge is disabled */
    
  /* Enable and set Button EXTI Interrupt to the lowest priority */
  NVIC_SetPriority(KEY_BUTTON_EXTI_IRQn, 0x7F);
  NVIC_EnableIRQ(KEY_BUTTON_EXTI_IRQn);
}

/**
  * @brief  Returns the selected Button state.
  * @param  Button: Specifies the Button to be checked.
  *   This parameter should be: BUTTON_KEY  
  * @retval The Button GPIO pin value.
  */
uint32_t BSP_PB_GetState(Button_TypeDef Button)
{
  if(GPIOA->IDR & 1)
  {
	  return 1;
  }
  return 0;
}

/**
  * @}
  */ 

/** @defgroup STM32F4_DISCOVERY_LOW_LEVEL_BUS_Functions
  * @{
  */ 

/**
  * @}
  */ 

/**
  * @}
  */ 

/**
  * @}
  */ 

/**
  * @}
  */ 
    
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
