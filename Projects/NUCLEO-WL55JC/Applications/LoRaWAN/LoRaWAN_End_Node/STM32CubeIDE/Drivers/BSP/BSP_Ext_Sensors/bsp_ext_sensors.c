/**
  ******************************************************************************
  * @file    bsp_ext_sensors.c
  * @author  Thierry
  * @brief   Sensors board support package
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

/* Includes ------------------------------------------------------------------*/
#include "bsp_ext_sensors.h"
/** @defgroup STM32L475E_IOT01_LOW_LEVEL_Private_FunctionPrototypes LOW LEVEL Private Function Prototypes
  * @{
  */

I2C_HandleTypeDef hI2cHandler;


static void     I2Cx_MspInit(I2C_HandleTypeDef *i2c_handler);
static void     I2Cx_MspDeInit(I2C_HandleTypeDef *i2c_handler);
static void     I2Cx_Init(I2C_HandleTypeDef *i2c_handler);
static void     I2Cx_DeInit(I2C_HandleTypeDef *i2c_handler);
static HAL_StatusTypeDef I2Cx_ReadMultiple(I2C_HandleTypeDef *i2c_handler, uint8_t Addr, uint16_t Reg, uint16_t MemAddSize, uint8_t *Buffer, uint16_t Length);
static HAL_StatusTypeDef I2Cx_WriteMultiple(I2C_HandleTypeDef *i2c_handler, uint8_t Addr, uint16_t Reg, uint16_t MemAddSize, uint8_t *Buffer, uint16_t Length);
static HAL_StatusTypeDef I2Cx_IsDeviceReady(I2C_HandleTypeDef *i2c_handler, uint16_t DevAddress, uint32_t Trials);
static void              I2Cx_Error(I2C_HandleTypeDef *i2c_handler, uint8_t Addr);

/* Sensors IO functions */
void     SENSOR_IO_Init(void);
void     SENSOR_IO_DeInit(void);
void     SENSOR_IO_Write(uint8_t Addr, uint8_t Reg, uint8_t Value);
uint8_t  SENSOR_IO_Read(uint8_t Addr, uint8_t Reg);
uint16_t SENSOR_IO_ReadMultiple(uint8_t Addr, uint8_t Reg, uint8_t *Buffer, uint16_t Length);
void     SENSOR_IO_WriteMultiple(uint8_t Addr, uint8_t Reg, uint8_t *Buffer, uint16_t Length);
HAL_StatusTypeDef SENSOR_IO_IsDeviceReady(uint16_t DevAddress, uint32_t Trials);
void     SENSOR_IO_Delay(uint32_t Delay);

/*******************************************************************************
                            BUS OPERATIONS
*******************************************************************************/

/******************************* I2C Routines *********************************/
/**
  * @brief  Initializes I2C MSP.
  * @param  i2c_handler  I2C handler
  * @retval None
  */
static void I2Cx_MspInit(I2C_HandleTypeDef *i2c_handler)
{
  GPIO_InitTypeDef  gpio_init_structure;

  /*** Configure the GPIOs ***/
  /* Enable GPIO clock */
  DISCOVERY_I2Cx_SCL_SDA_GPIO_CLK_ENABLE();

  /* Configure I2C Tx, Rx as alternate function */
  gpio_init_structure.Pin = DISCOVERY_I2Cx_SCL_PIN | DISCOVERY_I2Cx_SDA_PIN;
  gpio_init_structure.Mode = GPIO_MODE_AF_OD;
  gpio_init_structure.Pull = GPIO_PULLUP;
  gpio_init_structure.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  gpio_init_structure.Alternate = DISCOVERY_I2Cx_SCL_SDA_AF;
  HAL_GPIO_Init(DISCOVERY_I2Cx_SCL_SDA_GPIO_PORT, &gpio_init_structure);

  HAL_GPIO_Init(DISCOVERY_I2Cx_SCL_SDA_GPIO_PORT, &gpio_init_structure);

  /*** Configure the I2C peripheral ***/
  /* Enable I2C clock */
  DISCOVERY_I2Cx_CLK_ENABLE();

  /* Force the I2C peripheral clock reset */
  DISCOVERY_I2Cx_FORCE_RESET();

  /* Release the I2C peripheral clock reset */
  DISCOVERY_I2Cx_RELEASE_RESET();

  /* Enable and set I2Cx Interrupt to a lower priority */
  HAL_NVIC_SetPriority(DISCOVERY_I2Cx_EV_IRQn, 0x0F, 0);
  HAL_NVIC_EnableIRQ(DISCOVERY_I2Cx_EV_IRQn);

  /* Enable and set I2Cx Interrupt to a lower priority */
  HAL_NVIC_SetPriority(DISCOVERY_I2Cx_ER_IRQn, 0x0F, 0);
  HAL_NVIC_EnableIRQ(DISCOVERY_I2Cx_ER_IRQn);
}

/**
  * @brief  DeInitializes I2C MSP.
  * @param  i2c_handler  I2C handler
  * @retval None
  */
static void I2Cx_MspDeInit(I2C_HandleTypeDef *i2c_handler)
{
  GPIO_InitTypeDef  gpio_init_structure;
  
  /* Configure I2C Tx, Rx as alternate function */
  gpio_init_structure.Pin = DISCOVERY_I2Cx_SCL_PIN | DISCOVERY_I2Cx_SDA_PIN;
  HAL_GPIO_DeInit(DISCOVERY_I2Cx_SCL_SDA_GPIO_PORT, gpio_init_structure.Pin);
  /* Disable GPIO clock */
  DISCOVERY_I2Cx_SCL_SDA_GPIO_CLK_DISABLE();
  
  /* Disable I2C clock */
  DISCOVERY_I2Cx_CLK_DISABLE();
}

/**
  * @brief  Initializes I2C HAL.
  * @param  i2c_handler  I2C handler
  * @retval None
  */
static void I2Cx_Init(I2C_HandleTypeDef *i2c_handler)
{
  /* I2C configuration */
  i2c_handler->Instance              = DISCOVERY_I2Cx;
  i2c_handler->Init.Timing           = DISCOVERY_I2Cx_TIMING;
  i2c_handler->Init.OwnAddress1      = 0;
  i2c_handler->Init.AddressingMode   = I2C_ADDRESSINGMODE_7BIT;
  i2c_handler->Init.DualAddressMode  = I2C_DUALADDRESS_DISABLE;
  i2c_handler->Init.OwnAddress2      = 0;
  i2c_handler->Init.GeneralCallMode  = I2C_GENERALCALL_DISABLE;
  i2c_handler->Init.NoStretchMode    = I2C_NOSTRETCH_DISABLE;

  /* Init the I2C */
  I2Cx_MspInit(i2c_handler);
  HAL_I2C_Init(i2c_handler);
  
  /**Configure Analogue filter */
  HAL_I2CEx_ConfigAnalogFilter(i2c_handler, I2C_ANALOGFILTER_ENABLE);  
}

/**
  * @brief  DeInitializes I2C HAL.
  * @param  i2c_handler  I2C handler
  * @retval None
  */
static void I2Cx_DeInit(I2C_HandleTypeDef *i2c_handler)
{  /* DeInit the I2C */
  I2Cx_MspDeInit(i2c_handler);
  HAL_I2C_DeInit(i2c_handler); 
}

/**
  * @brief  Reads multiple data.
  * @param  i2c_handler  I2C handler
  * @param  Addr  I2C address
  * @param  Reg  Reg address
  * @param  MemAddress  memory address
  * @param  Buffer  Pointer to data buffer
  * @param  Length  Length of the data
  * @retval HAL status
  */
static HAL_StatusTypeDef I2Cx_ReadMultiple(I2C_HandleTypeDef *i2c_handler, uint8_t Addr, uint16_t Reg, uint16_t MemAddress, uint8_t *Buffer, uint16_t Length)
{
  HAL_StatusTypeDef status = HAL_OK;

  status = HAL_I2C_Mem_Read(i2c_handler, Addr, (uint16_t)Reg, MemAddress, Buffer, Length, 1000);

  /* Check the communication status */
  if(status != HAL_OK)
  {
    /* I2C error occurred */
    I2Cx_Error(i2c_handler, Addr);
  }
  return status;
}


/**
  * @brief  Writes a value in a register of the device through BUS in using DMA mode.
  * @param  i2c_handler  I2C handler
  * @param  Addr  Device address on BUS Bus.
  * @param  Reg  The target register address to write
  * @param  MemAddress  memory address
  * @param  Buffer  The target register value to be written
  * @param  Length  buffer size to be written
  * @retval HAL status
  */
static HAL_StatusTypeDef I2Cx_WriteMultiple(I2C_HandleTypeDef *i2c_handler, uint8_t Addr, uint16_t Reg, uint16_t MemAddress, uint8_t *Buffer, uint16_t Length)
{
  HAL_StatusTypeDef status = HAL_OK;

  status = HAL_I2C_Mem_Write(i2c_handler, Addr, (uint16_t)Reg, MemAddress, Buffer, Length, 1000);

  /* Check the communication status */
  if(status != HAL_OK)
  {
    /* Re-Initiaize the I2C Bus */
    I2Cx_Error(i2c_handler, Addr);
  }
  return status;
}

/**
  * @brief  Checks if target device is ready for communication. 
  * @note   This function is used with Memory devices
  * @param  i2c_handler  I2C handler
  * @param  DevAddress  Target device address
  * @param  Trials  Number of trials
  * @retval HAL status
  */
static HAL_StatusTypeDef I2Cx_IsDeviceReady(I2C_HandleTypeDef *i2c_handler, uint16_t DevAddress, uint32_t Trials)
{ 
  return (HAL_I2C_IsDeviceReady(i2c_handler, DevAddress, Trials, 1000));
}

/**
  * @brief  Manages error callback by re-initializing I2C.
  * @param  i2c_handler  I2C handler
  * @param  Addr  I2C Address
  * @retval None
  */
static void I2Cx_Error(I2C_HandleTypeDef *i2c_handler, uint8_t Addr)
{
  /* De-initialize the I2C communication bus */
  HAL_I2C_DeInit(i2c_handler);
  
  /* Re-Initialize the I2C communication bus */
  I2Cx_Init(i2c_handler);
}

/**
  * @}
  */

/*******************************************************************************
                            LINK OPERATIONS
*******************************************************************************/
/******************************** LINK Sensors ********************************/

/**
  * @brief  Initializes Sensors low level.
  * @retval None
  */
void SENSOR_IO_Init(void)
{
  I2Cx_Init(&hI2cHandler);
}

/**
  * @brief  DeInitializes Sensors low level.
  * @retval None
  */
void SENSOR_IO_DeInit(void)
{
  I2Cx_DeInit(&hI2cHandler);
}

/**
  * @brief  Writes a single data.
  * @param  Addr  I2C address
  * @param  Reg  Reg address
  * @param  Value  Data to be written
  * @retval None
  */
void SENSOR_IO_Write(uint8_t Addr, uint8_t Reg, uint8_t Value)
{
  I2Cx_WriteMultiple(&hI2cHandler, Addr, (uint16_t)Reg, I2C_MEMADD_SIZE_8BIT,(uint8_t*)&Value, 1);
}

/**
  * @brief  Reads a single data.
  * @param  Addr  I2C address
  * @param  Reg  Reg address
  * @retval Data to be read
  */
uint8_t SENSOR_IO_Read(uint8_t Addr, uint8_t Reg)
{
  uint8_t read_value = 0;

  I2Cx_ReadMultiple(&hI2cHandler, Addr, Reg, I2C_MEMADD_SIZE_8BIT, (uint8_t*)&read_value, 1);

  return read_value;
}

/**
  * @brief  Reads multiple data with I2C communication
  *         channel from TouchScreen.
  * @param  Addr  I2C address
  * @param  Reg  Register address
  * @param  Buffer  Pointer to data buffer
  * @param  Length  Length of the data
  * @retval HAL status
  */
uint16_t SENSOR_IO_ReadMultiple(uint8_t Addr, uint8_t Reg, uint8_t *Buffer, uint16_t Length)
{
 return I2Cx_ReadMultiple(&hI2cHandler, Addr, (uint16_t)Reg, I2C_MEMADD_SIZE_8BIT, Buffer, Length);
}

/**
  * @brief  Writes multiple data with I2C communication
  *         channel from MCU to TouchScreen.
  * @param  Addr  I2C address
  * @param  Reg  Register address
  * @param  Buffer  Pointer to data buffer
  * @param  Length  Length of the data
  * @retval None
  */
void SENSOR_IO_WriteMultiple(uint8_t Addr, uint8_t Reg, uint8_t *Buffer, uint16_t Length)
{
  I2Cx_WriteMultiple(&hI2cHandler, Addr, (uint16_t)Reg, I2C_MEMADD_SIZE_8BIT, Buffer, Length);
}

/**
  * @brief  Checks if target device is ready for communication. 
  * @note   This function is used with Memory devices
  * @param  DevAddress  Target device address
  * @param  Trials  Number of trials
  * @retval HAL status
  */
HAL_StatusTypeDef SENSOR_IO_IsDeviceReady(uint16_t DevAddress, uint32_t Trials)
{ 
  return (I2Cx_IsDeviceReady(&hI2cHandler, DevAddress, Trials));
}

/**
  * @brief  Delay function used in Sensor low level driver.
  * @param  Delay  Delay in ms
  * @retval None
  */
void SENSOR_IO_Delay(uint32_t Delay)
{
  HAL_Delay(Delay);
}


/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
