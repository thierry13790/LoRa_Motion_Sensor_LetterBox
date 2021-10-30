/**
  ******************************************************************************
  * @file    bsp_ext_sensors.h
  * @author  Thierry
  * @brief   Boars sensors support
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2017 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM32WL_BSP_EXT_H
#define __STM32WL_BSP_EXT_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32wlxx_hal.h"

void     SENSOR_IO_Init(void);
void     SENSOR_IO_DeInit(void);



/* User can use this section to tailor I2Cx instance used and associated resources */
/* Definition for I2Cx resources */
#define DISCOVERY_I2Cx                             I2C2
#define DISCOVERY_I2Cx_CLK_ENABLE()                __HAL_RCC_I2C2_CLK_ENABLE()
#define DISCOVERY_I2Cx_CLK_DISABLE()               __HAL_RCC_I2C2_CLK_DISABLE()   
#define DISCOVERY_DMAx_CLK_ENABLE()                __HAL_RCC_DMA1_CLK_ENABLE()
#define DISCOVERY_I2Cx_SCL_SDA_GPIO_CLK_ENABLE()   __HAL_RCC_GPIOA_CLK_ENABLE()
#define DISCOVERY_I2Cx_SCL_SDA_GPIO_CLK_DISABLE()  __HAL_RCC_GPIOA_CLK_DISABLE()
   
#define DISCOVERY_I2Cx_FORCE_RESET()               __HAL_RCC_I2C2_FORCE_RESET()
#define DISCOVERY_I2Cx_RELEASE_RESET()             __HAL_RCC_I2C2_RELEASE_RESET()

/* Definition for I2Cx Pins */
#define DISCOVERY_I2Cx_SCL_PIN                     GPIO_PIN_10
#define DISCOVERY_I2Cx_SDA_PIN                     GPIO_PIN_11                                               
#define DISCOVERY_I2Cx_SCL_SDA_GPIO_PORT           GPIOB
#define DISCOVERY_I2Cx_SCL_SDA_AF                  GPIO_AF4_I2C2

/* I2C interrupt requests */
#define DISCOVERY_I2Cx_EV_IRQn                     I2C2_EV_IRQn
#define DISCOVERY_I2Cx_ER_IRQn                     I2C2_ER_IRQn

/* I2C clock speed configuration (in Hz)
  WARNING:
   Make sure that this define is not already declared in other files.
   It can be used in parallel by other modules. */
#ifndef DISCOVERY_I2C_SPEED
 #define DISCOVERY_I2C_SPEED                             100000
#endif /* DISCOVERY_I2C_SPEED */

#ifndef DISCOVERY_I2Cx_TIMING  
#define DISCOVERY_I2Cx_TIMING                     ((uint32_t)0x00702681)
#endif /* DISCOVERY_I2Cx_TIMING */ 

/**
  * @}
  */
#ifdef __cplusplus
}
#endif

#endif /* __STM32L475E_IOT01_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
