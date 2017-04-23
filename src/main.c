/**
  ******************************************************************************
  * @file    GPIO/GPIO_IOToggle/Src/main.c 
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    18-June-2014
  * @brief   This example describes how to configure and use GPIOs through 
  *          the STM32F3xx HAL API.
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
#include "main.h"
#include "common/hal_common.h"
#include "common/delay.h"
#include "led/led.h"
#include <stm32f30x_gpio.h>
void assert_param(int param)
{

}

/** @addtogroup STM32F3xx_HAL_Examples
  * @{
  */

/** @addtogroup GPIO_IOToggle
  * @{
  */ 

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
static GPIO_InitTypeDef  GPIO_InitStruct;
/* Private function prototypes -----------------------------------------------*/
static void SystemClock_Config(void);
static void Error_Handler(void);

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Main program
  * @param  None
  * @retval None
  */

#include "ssd2828.h"

int main(void)
{
  /* This sample code shows how to use STM32F3xx GPIO HAL API to toggle PE8 to PE15 
  IOs (connected to LED3 to LED10 on STM323F3-DK board) in an infinite loop.
    To proceed, 3 steps are required: */
  
  /* STM32F3xx HAL library initialization:
       - Configure the Flash prefetch
       - Systick timer is configured by default as source of time base, but user 
         can eventually implement his proper time base source (a general purpose 
         timer for example or other time source), keeping in mind that Time base 
         duration should be kept 1ms since PPP_TIMEOUT_VALUEs are defined and 
         handled in milliseconds basis.
       - Set NVIC Group Priority to 4
       - Low Level Initialization
     */
  //HAL_Init();

  /* Configure the system clock to 72 Mhz */
  //SystemClock_Config();
  delay_init();

  const gpio_pin_t gpio[] =
  {
		  {GPIOE, GPIO_Pin_8, MODE_OUT},
		  {GPIOE, GPIO_Pin_9, MODE_OUT}
  };
  
  led_init(gpio, 2);

  /* -1- Enable GPIOE Clock (to be able to program the configuration registers) */
  //__GPIOE_CLK_ENABLE();

  /* -2- Configure PE.8 to PE.15 IOs in output push-pull mode to drive external LEDs */
  /*GPIO_InitStruct.Pin = (GPIO_PIN_15 |GPIO_PIN_14 |GPIO_PIN_13 |GPIO_PIN_12 |GPIO_PIN_11 | GPIO_PIN_10 | GPIO_PIN_9 | GPIO_PIN_8);
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
  
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct); 

  while (1)
  {
    HAL_GPIO_TogglePin(GPIOE, GPIO_PIN_15);
    HAL_Delay(100);
    HAL_GPIO_TogglePin(GPIOE, GPIO_PIN_14);
    HAL_Delay(100);
    HAL_GPIO_TogglePin(GPIOE, GPIO_PIN_13);
    HAL_Delay(100);
    HAL_GPIO_TogglePin(GPIOE, GPIO_PIN_12);
    HAL_Delay(100);
    HAL_GPIO_TogglePin(GPIOE, GPIO_PIN_11);
    HAL_Delay(100);
    HAL_GPIO_TogglePin(GPIOE, GPIO_PIN_10);
    HAL_Delay(100);
    HAL_GPIO_TogglePin(GPIOE, GPIO_PIN_9);
    HAL_Delay(100);
    HAL_GPIO_TogglePin(GPIOE, GPIO_PIN_8);
    HAL_Delay(100);
  }*/

  ssd2828_init();

  uint16_t id = SPI_READ_ID();

  while(1)
  {
	  led_enable(&gpio[0], 2, 0, 1);
	  led_enable(&gpio[0], 2, 1, 0);
	  delay_ms(500);
	  led_enable(&gpio[0], 2, 0, 0);
	  led_enable(&gpio[0], 2, 1, 1);
	  delay_ms(500);
  }
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @param  None
  * @retval None
  */
static void Error_Handler(void)
{
  /* User may add here some code to deal with this error */
  while(1)
  {
  }
}

#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
