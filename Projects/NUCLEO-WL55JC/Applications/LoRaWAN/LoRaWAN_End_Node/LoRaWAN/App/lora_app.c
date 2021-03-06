/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    lora_app.c
  * @author  MCD Application Team
  * @brief   Application of the LRWAN Middleware
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "platform.h"
#include "Region.h" /* Needed for LORAWAN_DEFAULT_DATA_RATE */
#include "sys_app.h"
#include "lora_app.h"
#include "stm32_seq.h"
#include "stm32_timer.h"
#include "utilities_def.h"
#include "lora_app_version.h"
#include "lorawan_version.h"
#include "subghz_phy_version.h"
#include "lora_info.h"
#include "LmHandler.h"
#include "stm32_lpm.h"
#include "adc_if.h"
#include "sys_conf.h"
#include "CayenneLpp.h"
#include "sys_sensors.h"
#include "vl53l0x_def.h"
#include "vl53l0x_api.h"
#include "vl53l0x_tof.h"
#include "stm32wlxx_hal.h"
#include "stm32wlxx_it.h"

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* External variables ---------------------------------------------------------*/
/* USER CODE BEGIN EV */


VL53L0X_RangingMeasurementData_t RangingData;
VL53L0X_Dev_t  vl53l0x_c; // center module
VL53L0X_DEV    Dev = &vl53l0x_c;

volatile uint8_t TofDataRead;
volatile uint8_t SendEpoch=0;
volatile uint8_t NightMode=0;

extern I2C_HandleTypeDef hI2cHandler;

extern RTC_HandleTypeDef hrtc;

#define PROXIMITY_I2C_ADDRESS         ((uint16_t)0x0052)
#define VL53L0X_ID                    ((uint16_t)0xEEAA)
#define VL53L0X_XSHUT_Pin GPIO_PIN_5
#define VL53L0X_XSHUT_GPIO_Port GPIOA
#define VL53L0X_INT_Pin GPIO_PIN_6
#define VL53L0X_INT_Port GPIOA
#define VL53L0X_INT_EXTI_IRQn EXTI2_IRQHandler

#define MAX_TS_SIZE (int) 16

uint16_t Proximity_Test(void);

static void VL53L0X_PROXIMITY_MspInit(void);
static void VL53L0X_PROXIMITY_DeMspInit(void);
static uint16_t VL53L0X_PROXIMITY_GetDistance(void);
static VL53L0X_Error VL53L0X_PROXIMITY_Init(void);
static void VL53L0X_PROXIMITY_DeInit(void);

/* USER CODE END EV */

/* Private typedef -----------------------------------------------------------*/
/**
  * @brief LoRa State Machine states
  */
typedef enum TxEventType_e
{
  /**
    * @brief Appdata Transmission issue based on timer every TxDutyCycleTime
    */
  TX_ON_TIMER,
  /**
    * @brief Appdata Transmission external event plugged on OnSendEvent( )
    */
  TX_ON_EVENT
  /* USER CODE BEGIN TxEventType_t */

  /* USER CODE END TxEventType_t */
} TxEventType_t;

/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private function prototypes -----------------------------------------------*/
/**
  * @brief  LoRa End Node send request
  */
static void SendTxData(void);

/**
  * @brief  TX timer callback function
  * @param  context ptr of timer context
  */
static void OnTxTimerEvent(void *context);

/**
  * @brief  join event callback function
  * @param  joinParams status of join
  */
static void OnJoinRequest(LmHandlerJoinParams_t *joinParams);

/**
  * @brief  tx event callback function
  * @param  params status of last Tx
  */
static void OnTxData(LmHandlerTxParams_t *params);

/**
  * @brief callback when LoRa application has received a frame
  * @param appData data received in the last Rx
  * @param params status of last Rx
  */
static void OnRxData(LmHandlerAppData_t *appData, LmHandlerRxParams_t *params);

/*!
 * Will be called each time a Radio IRQ is handled by the MAC layer
 *
 */
static void OnMacProcessNotify(void);

/* USER CODE BEGIN PFP */

/**
  * @brief  LED Tx timer callback function
  * @param  context ptr of LED context
  */
static void OnTxTimerLedEvent(void *context);

/**
  * @brief  LED Rx timer callback function
  * @param  context ptr of LED context
  */
static void OnRxTimerLedEvent(void *context);

/**
  * @brief  LED Join timer callback function
  * @param  context ptr of LED context
  */
static void OnJoinTimerLedEvent(void *context);

/* USER CODE END PFP */

/* Private variables ---------------------------------------------------------*/
static ActivationType_t ActivationType = LORAWAN_DEFAULT_ACTIVATION_TYPE;

/**
  * @brief LoRaWAN handler Callbacks
  */
static LmHandlerCallbacks_t LmHandlerCallbacks =
{
  .GetBatteryLevel =           GetBatteryLevel,
  .GetTemperature =            GetTemperatureLevel,
  .GetUniqueId =               GetUniqueId,
  .GetDevAddr =                GetDevAddr,
  .OnMacProcess =              OnMacProcessNotify,
  .OnJoinRequest =             OnJoinRequest,
  .OnTxData =                  OnTxData,
  .OnRxData =                  OnRxData
};

/**
  * @brief LoRaWAN handler parameters
  */
static LmHandlerParams_t LmHandlerParams =
{
  .ActiveRegion =             ACTIVE_REGION,
  .DefaultClass =             LORAWAN_DEFAULT_CLASS,
  .AdrEnable =                LORAWAN_ADR_STATE,
  .TxDatarate =               LORAWAN_DEFAULT_DATA_RATE,
  .PingPeriodicity =          LORAWAN_DEFAULT_PING_SLOT_PERIODICITY
};

/**
  * @brief Type of Event to generate application Tx
  */
static TxEventType_t EventType = TX_ON_TIMER;
// static TxEventType_t EventType = TX_ON_EVENT;
/**
  * @brief Timer to handle the application Tx
  */
static UTIL_TIMER_Object_t TxTimer;

/* USER CODE BEGIN PV */
/**
  * @brief User application buffer
  */
static uint8_t AppDataBuffer[LORAWAN_APP_DATA_BUFFER_MAX_SIZE];

/**
  * @brief User application data structure
  */
static LmHandlerAppData_t AppData = { 0, 0, AppDataBuffer };

/**
  * @brief Specifies the state of the application LED
  */
//static uint8_t AppLedStateOn = RESET;

/**
  * @brief Timer to handle the application Tx Led to toggle
  */
static UTIL_TIMER_Object_t TxLedTimer;

/**
  * @brief Timer to handle the application Rx Led to toggle
  */
static UTIL_TIMER_Object_t RxLedTimer;

/**
  * @brief Timer to handle the application Join Led to toggle
  */
static UTIL_TIMER_Object_t JoinLedTimer;

/* USER CODE END PV */


/* Exported functions ---------------------------------------------------------*/
/* USER CODE BEGIN EF */

/* USER CODE END EF */

void LoRaWAN_Init(void)
{
  /* USER CODE BEGIN LoRaWAN_Init_1 */

  VL53L0X_Error error=VL53L0X_ERROR_UNDEFINED;

  BSP_LED_Init(LED_BLUE);
  BSP_LED_Init(LED_GREEN);
  BSP_LED_Init(LED_RED);
  BSP_PB_Init(BUTTON_SW2, BUTTON_MODE_EXTI);

  /* Get LoRa APP version*/
  APP_LOG(TS_OFF, VLEVEL_M, "APP_VERSION:        V%X.%X.%X\r\n",
          (uint8_t)(__LORA_APP_VERSION >> __APP_VERSION_MAIN_SHIFT),
          (uint8_t)(__LORA_APP_VERSION >> __APP_VERSION_SUB1_SHIFT),
          (uint8_t)(__LORA_APP_VERSION >> __APP_VERSION_SUB2_SHIFT));

  /* Get MW LoraWAN info */
  APP_LOG(TS_OFF, VLEVEL_M, "MW_LORAWAN_VERSION: V%X.%X.%X\r\n",
          (uint8_t)(__LORAWAN_VERSION >> __APP_VERSION_MAIN_SHIFT),
          (uint8_t)(__LORAWAN_VERSION >> __APP_VERSION_SUB1_SHIFT),
          (uint8_t)(__LORAWAN_VERSION >> __APP_VERSION_SUB2_SHIFT));

  /* Get MW SubGhz_Phy info */
  APP_LOG(TS_OFF, VLEVEL_M, "MW_RADIO_VERSION:   V%X.%X.%X\r\n",
          (uint8_t)(__SUBGHZ_PHY_VERSION >> __APP_VERSION_MAIN_SHIFT),
          (uint8_t)(__SUBGHZ_PHY_VERSION >> __APP_VERSION_SUB1_SHIFT),
          (uint8_t)(__SUBGHZ_PHY_VERSION >> __APP_VERSION_SUB2_SHIFT));

  UTIL_TIMER_Create(&TxLedTimer, 0xFFFFFFFFU, UTIL_TIMER_ONESHOT, OnTxTimerLedEvent, NULL);
  UTIL_TIMER_Create(&RxLedTimer, 0xFFFFFFFFU, UTIL_TIMER_ONESHOT, OnRxTimerLedEvent, NULL);
  UTIL_TIMER_Create(&JoinLedTimer, 0xFFFFFFFFU, UTIL_TIMER_PERIODIC, OnJoinTimerLedEvent, NULL);
  UTIL_TIMER_SetPeriod(&TxLedTimer, 500);
  UTIL_TIMER_SetPeriod(&RxLedTimer, 500);
  UTIL_TIMER_SetPeriod(&JoinLedTimer, 500);

  /* USER CODE END LoRaWAN_Init_1 */

  UTIL_SEQ_RegTask((1 << CFG_SEQ_Task_LmHandlerProcess), UTIL_SEQ_RFU, LmHandlerProcess);

  // Send data TX Task : SendTxData

  UTIL_SEQ_RegTask((1 << CFG_SEQ_Task_LoRaSendOnTxTimerOrButtonEvent), UTIL_SEQ_RFU, SendTxData);
  /* Init Info table used by LmHandler*/
  LoraInfo_Init();

  /* Init the Lora Stack*/
  LmHandlerInit(&LmHandlerCallbacks);

  LmHandlerConfigure(&LmHandlerParams);

  /* USER CODE BEGIN LoRaWAN_Init_2 */
  UTIL_TIMER_Start(&JoinLedTimer);

  /* USER CODE END LoRaWAN_Init_2 */

  LmHandlerJoin(ActivationType);

  error= VL53L0X_PROXIMITY_Init();

  if (error==VL53L0X_ERROR_NONE)
  {
	APP_LOG(TS_OFF, VLEVEL_M, "\r\nVL053x is enabled \r\n");
  }
  else
  {
	APP_LOG(TS_OFF, VLEVEL_M, "\r\nError during activation of VL053x\r\n");
  }

  if (EventType == TX_ON_TIMER)
  {
    /* send every time timer elapses */
    UTIL_TIMER_Create(&TxTimer,  0xFFFFFFFFU, UTIL_TIMER_ONESHOT, OnTxTimerEvent, NULL);
    UTIL_TIMER_SetPeriod(&TxTimer,  APP_TX_DUTYCYCLE);
    // UTIL_SEQ_SetTask((1 << CFG_SEQ_Task_LoRaSendOnTxTimerOrButtonEvent), CFG_SEQ_Prio_0);
    // UTIL_TIMER_Start(&TxTimer);
  }
  else
  {
    /* USER CODE BEGIN LoRaWAN_Init_3 */

    /* send every time button is pushed */
    BSP_PB_Init(BUTTON_SW1, BUTTON_MODE_EXTI);
    /* USER CODE END LoRaWAN_Init_3 */
  }

  /* USER CODE BEGIN LoRaWAN_Init_Last */

  /* USER CODE END LoRaWAN_Init_Last */
}

/* USER CODE BEGIN PB_Callbacks */
/* Note: Current the stm32wlxx_it.c generated by STM32CubeMX does not support BSP for PB in EXTI mode. */
/* In order to get a push button IRS by code automatically generated */
/* HAL_GPIO_EXTI_Callback is today the only available possibility. */
/* Using HAL_GPIO_EXTI_Callback() shortcuts the BSP. */
/* If users wants to go through the BSP, stm32wlxx_it.c should be updated  */
/* in the USER CODE SESSION of the correspondent EXTIn_IRQHandler() */
/* to call the BSP_PB_IRQHandler() or the HAL_EXTI_IRQHandler(&H_EXTI_n);. */
/* Then the below HAL_GPIO_EXTI_Callback() can be replaced by BSP callback */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
  switch (GPIO_Pin)
  {
    case  BUTTON_SW1_PIN:
      /* Note: when "EventType == TX_ON_TIMER" this GPIO is not initialized */

    	VL53L0X_GetRangingMeasurementData(Dev, &RangingData);
    	VL53L0X_ClearInterruptMask(Dev, VL53L0X_REG_SYSTEM_INTERRUPT_GPIO_NEW_SAMPLE_READY);
    	TofDataRead = 1;
    	// UTIL_SEQ_SetTask((1 << CFG_SEQ_Task_LoRaSendOnTxTimerOrButtonEvent), CFG_SEQ_Prio_0);
      break;
    case  BUTTON_SW2_PIN:
      break;
    /*case  BUTTON_SW3_PIN:
      break;*/
    case VL53L0X_INT_Pin:
/*      VL53L0X_GetRangingMeasurementData(Dev, &RangingData);
      VL53L0X_ClearInterruptMask(Dev, VL53L0X_REG_SYSTEM_INTERRUPT_GPIO_NEW_SAMPLE_READY);
      TofDataRead = 1;*/
      break;
    default:
      break;

  }
}

/* USER CODE END PB_Callbacks */

/* Private functions ---------------------------------------------------------*/
/* USER CODE BEGIN PrFD */

/* USER CODE END PrFD */

static void OnRxData(LmHandlerAppData_t *appData, LmHandlerRxParams_t *params)
{
  /* USER CODE BEGIN OnRxData_1 */

  SysTime_t UnixEpoch;

  if ((appData != NULL) || (params != NULL))
  {
    BSP_LED_On(LED_BLUE) ;

    UTIL_TIMER_Start(&RxLedTimer);

    static const char *slotStrings[] = { "1", "2", "C", "C Multicast", "B Ping-Slot", "B Multicast Ping-Slot" };

    APP_LOG(TS_OFF, VLEVEL_M, "\r\n###### ========== MCPS-Indication ==========\r\n");
    APP_LOG(TS_OFF, VLEVEL_H, "###### D/L FRAME:%04d | SLOT:%s | PORT:%d | DR:%d | RSSI:%d | SNR:%d\r\n",
            params->DownlinkCounter, slotStrings[params->RxSlot], appData->Port, params->Datarate, params->Rssi, params->Snr);
    switch (appData->Port)
    {
      case LORAWAN_SWITCH_CLASS_PORT:
        /*this port switches the class*/
        if (appData->BufferSize == 1)
        {
          switch (appData->Buffer[0])
          {
            case 0:
            {
              LmHandlerRequestClass(CLASS_A);
              break;
            }
            case 1:
            {
              LmHandlerRequestClass(CLASS_B);
              break;
            }
            case 2:
            {
              LmHandlerRequestClass(CLASS_C);
              break;
            }
            default:
              break;
          }
        }
        break;
      case LORAWAN_USER_APP_PORT:

    	switch (appData->Buffer[0])
	    {
		  case 0:
		  {
			  /* UnixEpoch.Seconds=1654333930; Means 4 june 2022 */

			  UnixEpoch.Seconds = (uint32_t) appData->Buffer[1] << 24;
			  UnixEpoch.Seconds |=  (uint32_t) appData->Buffer[2] << 16;
			  UnixEpoch.Seconds |= (uint32_t) appData->Buffer[3] << 8;
			  UnixEpoch.Seconds |= (uint32_t) appData->Buffer[4];
			  UnixEpoch.SubSeconds=0;

			  APP_LOG(TS_OFF, VLEVEL_H, "Set Time %d \r\n",UnixEpoch.Seconds);

			  SysTimeSet(UnixEpoch);

		    break;
		  }
		  case 1:
		  {
			  SendEpoch=1; /* We will send Epoch time at next Sending of data's */
			  break;
		  }
		  case 2:
		  {
		    break;
		  }
		  default:
		    break;
	    }
        break;

      default:

        break;
    }
  }
  /* USER CODE END OnRxData_1 */
}

static void SendTxData(void)
{
  /* USER CODE BEGIN SendTxData_1 */
  uint16_t length = 65000;
  UTIL_TIMER_Time_t nextTxIn = 0;
  uint32_t i = 0;
  VL53L0X_Error error=VL53L0X_ERROR_UNDEFINED;
  struct tm localtime;
  SysTime_t  UnixEpoch;

  AppData.Port = LORAWAN_USER_APP_PORT;

  /* Let's check if call is during the night */

  UnixEpoch= SysTimeGet();

  SysTimeSetBKUPWrite(UnixEpoch); /* In case there's a POR or NVIC System Reset we store inside RTC Bkup register Value to be able */
   	   	   	   	   	   	   	   	  /* To restore it at next POR or next NVIC System Reset using function MX_RTC_Init */
  	  	  	  	  	  	  	  	  /* To be able to restore it's needed VBAT power supply at least if POR, thus VBAT pin must be
  	  	  	  	  	  	  	  	  *  Connected to a battery */

  /* It's because i'm living on UTC time */

  UnixEpoch.Seconds-=18; //removing leap seconds
  UnixEpoch.Seconds+=3600*2; // adding 2 hours

  SysTimeLocalTime(UnixEpoch.Seconds, &localtime);

  APP_LOG(TS_OFF, VLEVEL_M,"Epoch UTC it's %02dh%02dm%02ds on %02d/%02d/%04d\n\r",
  		  localtime.tm_hour, localtime.tm_min, localtime.tm_sec,
     	  localtime.tm_mday, localtime.tm_mon+1, localtime.tm_year + 1900);

  if ( (localtime.tm_hour>=20 || localtime.tm_hour<8) && ( localtime.tm_year + 1900)!=1970 )
  {
	 NightMode=0; //1
	 APP_LOG(TS_OFF, VLEVEL_M,"Night Mode : ZZZZZ...\n\r");
	 // BSP_LED_On(LED_BLUE);
  }
  else
  {
	 NightMode=0;
	 APP_LOG(TS_OFF, VLEVEL_M,"Day light Mode \n\r");
	 // BSP_LED_Off(LED_BLUE);
  }

  if (!NightMode)
  {

	  APP_LOG(TS_ON, VLEVEL_M, "status: %i, i2 address %x\n\r", Dev->I2cHandle->ErrorCode, Dev->I2cDevAddr);

	  SENSOR_IO_Init();

	  Dev->I2cHandle = &hI2cHandler;
	  Dev->I2cDevAddr = 0x52;

	  TofDataRead = 0;

	  HAL_NVIC_EnableIRQ(EXTI0_IRQn);

	  error=VL53L0X_StartMeasurement(Dev);

	  APP_LOG(TS_OFF, VLEVEL_M, "\r\nVL053x status %d \r\n",error);

	  HAL_Delay(50); /* We let 50 ms for measure only then will timeout in case no result and we will stop measure */

	  HAL_NVIC_DisableIRQ(EXTI0_IRQn);

	  if((TofDataRead == 1) && (error==VL53L0X_ERROR_NONE))
	  {
		  length=RangingData.RangeMilliMeter;
		  TofDataRead = 0;

		  APP_LOG(TS_ON, VLEVEL_M, "there's new data's, Measured distance: %i\n\r", length);

		  SENSOR_IO_DeInit();

		  AppData.Buffer[i++]=0; // No error

		  if (length<TOUCH_DISTANCE)
		  {
			AppData.Buffer[i++]=1; // Touch
			APP_LOG(TS_ON, VLEVEL_M, "\r\nENVOI !!!! DISTANCE is = %d mm\r\n",length);
		  }
		  else // No Touch
		  {
			AppData.Buffer[i++]=0; // Touch
		  } // End there's data and no errors

	  }
	  else /* TofDataRead != 1 && VL053 error*/
	  {
		  AppData.Buffer[i++]=1; // Error
		  AppData.Buffer[i++]=2; // no distance detected so error !!!!

		  APP_LOG(TS_OFF, VLEVEL_M, "Error getting measure or not time measure Measured distance is : %i, error TOF is : %i TofDataRead=%i \n\r", RangingData.RangeMilliMeter,error,TofDataRead);

		  HAL_Delay(2000);
		  error=VL53L0X_StopMeasurement(Dev);

		  APP_LOG(TS_ON, VLEVEL_L, "Stop measure status = %d\r\n", error);

		  error=VL53L0X_ClearInterruptMask(Dev, VL53L0X_REG_SYSTEM_INTERRUPT_GPIO_NEW_SAMPLE_READY);

		  HAL_NVIC_DisableIRQ(EXTI0_IRQn);

		  APP_LOG(TS_ON, VLEVEL_L, "Clear Interrupt on VL status = %d\r\n", error);

		  HAL_Delay(2000);
	  }

	  AppData.Buffer[i++] = GetBatteryLevel();       /* 1 (very low) to 100 (fully charged) */
	  APP_LOG(TS_ON, VLEVEL_M, "\r\nBattery level is = %d => 0 (very low = 0 volts ) to 100 (fully charged = 2,852 volts)\r\n",AppData.Buffer[i-1]);

	  if (SendEpoch) /* Need to send epoch Time */
	  {
		  APP_LOG(TS_OFF, VLEVEL_M,"Epoch Time =%02d\n\r",UnixEpoch.Seconds);

		  AppData.Buffer[i++] = UnixEpoch.Seconds >> 24;
		  AppData.Buffer[i++] = UnixEpoch.Seconds >> 16;
		  AppData.Buffer[i++] = UnixEpoch.Seconds >>  8;
		  AppData.Buffer[i++] = UnixEpoch.Seconds;

		  SendEpoch=0;
	  }

	  // AppData.Port = LORAWAN_USER_APP_PORT;
	  AppData.BufferSize = i;

	  // BSP_LED_On(LED_GREEN) ;

	  UTIL_TIMER_Start(&TxLedTimer);

	  if ( (LORAMAC_HANDLER_SUCCESS == LmHandlerSend(&AppData, LORAWAN_DEFAULT_CONFIRMED_MSG_STATE, &nextTxIn, false)) && (length < 100))
	  {
		  APP_LOG(TS_ON, VLEVEL_L, "SEND REQUEST\r\n");
	  }
	  else if (nextTxIn > 0)
	  {
			  APP_LOG(TS_ON, VLEVEL_L, "No Letter Next Tx in  : ~%d second(s)\r\n", (nextTxIn / 1000));
	  }
	  //BSP_LED_Off(LED_GREEN);
  } // Day mode
  else
  {
	// Nigh mode, nothing to do
  }
	  /* USER CODE END SendTxData_1 */
}

static void OnTxTimerEvent(void *context)
{
  /* USER CODE BEGIN OnTxTimerEvent_1 */

  /* USER CODE END OnTxTimerEvent_1 */
  UTIL_SEQ_SetTask((1 << CFG_SEQ_Task_LoRaSendOnTxTimerOrButtonEvent), CFG_SEQ_Prio_0);

  /*Wait for next tx slot*/
  UTIL_TIMER_Start(&TxTimer);
  /* USER CODE BEGIN OnTxTimerEvent_2 */

  /* USER CODE END OnTxTimerEvent_2 */
}

/* USER CODE BEGIN PrFD_LedEvents */
static void OnTxTimerLedEvent(void *context)
{
  BSP_LED_Off(LED_GREEN) ;
  if (AppData.Buffer[1]==2) // there was problem measuring distance
  {
    NVIC_SystemReset();
  }
}

static void OnRxTimerLedEvent(void *context)
{
  BSP_LED_Off(LED_BLUE) ;

}

static void OnJoinTimerLedEvent(void *context)
{
  BSP_LED_Toggle(LED_RED) ;
}

/* USER CODE END PrFD_LedEvents */

static void OnTxData(LmHandlerTxParams_t *params)
{
  /* USER CODE BEGIN OnTxData_1 */
  if ((params != NULL))
  {
    /* Process Tx event only if its a mcps response to prevent some internal events (mlme) */
    if (params->IsMcpsConfirm != 0)
    {
      //BSP_LED_On(LED_GREEN) ;
      // UTIL_TIMER_Start(&TxLedTimer);

      APP_LOG(TS_OFF, VLEVEL_M, "\r\n###### ========== MCPS-Confirm =============\r\n");
      APP_LOG(TS_OFF, VLEVEL_H, "###### U/L FRAME:%04d | PORT:%d | DR:%d | PWR:%d", params->UplinkCounter,
              params->AppData.Port, params->Datarate, params->TxPower);

      APP_LOG(TS_OFF, VLEVEL_H, " | MSG TYPE:");
      if (params->MsgType == LORAMAC_HANDLER_CONFIRMED_MSG)
      {
        APP_LOG(TS_OFF, VLEVEL_H, "CONFIRMED [%s]\r\n", (params->AckReceived != 0) ? "ACK" : "NACK");
      }
      else
      {
        APP_LOG(TS_OFF, VLEVEL_H, "UNCONFIRMED\r\n");
      }
    }
  }
  /* USER CODE END OnTxData_1 */
}

static void OnJoinRequest(LmHandlerJoinParams_t *joinParams)
{

  /* USER CODE BEGIN OnJoinRequest_1 */


  if (joinParams != NULL)
  {
    if (joinParams->Status == LORAMAC_HANDLER_SUCCESS)
    {
      UTIL_TIMER_Stop(&JoinLedTimer);
      BSP_LED_Off(LED_RED) ;

      APP_LOG(TS_OFF, VLEVEL_M, "\r\n###### = JOINED = ");
      if (joinParams->Mode == ACTIVATION_TYPE_ABP)
      {
        APP_LOG(TS_OFF, VLEVEL_M, "ABP ======================\r\n");
      }
      else
      {
        APP_LOG(TS_OFF, VLEVEL_M, "OTAA =====================\r\n");

        UTIL_TIMER_Start(&TxTimer);

        SendTxData();
      }
    }
    else
    {
      APP_LOG(TS_OFF, VLEVEL_M, "\r\n###### = JOIN FAILED, reset ... \r\n");

      NVIC_SystemReset();
    }
  }
  /* USER CODE END OnJoinRequest_1 */
}

static void OnMacProcessNotify(void)
{
  /* USER CODE BEGIN OnMacProcessNotify_1 */

  /* USER CODE END OnMacProcessNotify_1 */
  UTIL_SEQ_SetTask((1 << CFG_SEQ_Task_LmHandlerProcess), CFG_SEQ_Prio_0);

  /* USER CODE BEGIN OnMacProcessNotify_2 */

  /* USER CODE END OnMacProcessNotify_2 */
}

/**
  * @brief  Test of VL53L0X proximity sensor.
  */
uint16_t Proximity_Test(void)
{
  uint16_t prox_value = 0;
  prox_value = VL53L0X_PROXIMITY_GetDistance();
  VL53L0X_PROXIMITY_DeInit();

  return(prox_value);

}
/**
  * @brief  VL53L0X proximity sensor Initialization.
  */
static VL53L0X_Error VL53L0X_PROXIMITY_Init(void)
{
  uint32_t refSpadCount;
  uint8_t isApertureSpads;
  uint8_t VhvSettings;
  uint8_t PhaseCal;

  VL53L0X_Error error=VL53L0X_ERROR_UNDEFINED;

  /* Initialize IO interface */
  SENSOR_IO_Init(); /*i2c init  */

  VL53L0X_PROXIMITY_MspInit();

  HAL_NVIC_DisableIRQ(EXTI0_IRQn);

  Dev->I2cHandle = &hI2cHandler;
  Dev->I2cDevAddr = 0x52;

  error=VL53L0X_WaitDeviceBooted( Dev );
  error=VL53L0X_DataInit( Dev );
  error=VL53L0X_StaticInit( Dev );
  error=VL53L0X_PerformRefCalibration(Dev, &VhvSettings, &PhaseCal);
  error=VL53L0X_PerformRefSpadManagement(Dev, &refSpadCount, &isApertureSpads);

  error=VL53L0X_SetDeviceMode(Dev, VL53L0X_DEVICEMODE_SINGLE_RANGING);

  return (error);

}

/**
  * @brief  VL53L0X proximity sensor Initialization.
  */


static void VL53L0X_PROXIMITY_DeInit(void)
{

  /* DeInitialize IO interface */
  VL53L0X_PROXIMITY_DeMspInit();
}




/**
  * @brief  Get distance from VL53L0X proximity sensor.
  * @retval Distance in mm
  */
static uint16_t VL53L0X_PROXIMITY_GetDistance(void)
{
  VL53L0X_RangingMeasurementData_t RangingMeasurementData;

  VL53L0X_PerformSingleRangingMeasurement(Dev, &RangingMeasurementData);

  return RangingMeasurementData.RangeMilliMeter;
}

/**
  * @brief  VL53L0X proximity sensor Msp Initialization.
  */
static void VL53L0X_PROXIMITY_MspInit(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;

	  /*Configure GPIO pin : VL53L0X_XSHUT_Pin */
	  GPIO_InitStruct.Pin = VL53L0X_XSHUT_Pin;
	  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	  GPIO_InitStruct.Pull = GPIO_PULLUP;
	  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	  HAL_GPIO_Init(VL53L0X_XSHUT_GPIO_Port, &GPIO_InitStruct);

	  HAL_GPIO_WritePin(VL53L0X_XSHUT_GPIO_Port, VL53L0X_XSHUT_Pin, GPIO_PIN_SET);

	  HAL_Delay(50);

	  /*Configure GPIO pin : PtPin */

	  BSP_PB_Init(BUTTON_SW1, BUTTON_MODE_EXTI);
}

/**
  * @brief  VL53L0X proximity sensor Msp Initialization.
  */
static void VL53L0X_PROXIMITY_DeMspInit(void)
{
  HAL_GPIO_WritePin(VL53L0X_XSHUT_GPIO_Port, VL53L0X_XSHUT_Pin, GPIO_PIN_RESET);
  BSP_PB_DeInit(BUTTON_SW1);
  HAL_Delay(100);
}

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
