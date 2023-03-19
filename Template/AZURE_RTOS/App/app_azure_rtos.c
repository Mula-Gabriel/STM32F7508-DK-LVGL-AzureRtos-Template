
/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    app_azure_rtos.c
  * @author  MCD Application Team
  * @brief   azure_rtos application implementation file
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/

#include "app_azure_rtos.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
TX_THREAD MainThread;
TX_THREAD LiveLedThread;
TX_BYTE_POOL SRAM_pool;

#include "stm32f7508_discovery.h"
#include "lvgl/lvgl.h"
#include "hal_stm_lvgl/tft/tft.h"
#include "hal_stm_lvgl/touchpad/touchpad.h"
#include "lvgl/demos/lv_demos.h"


void LvglThread_entry_function(ULONG id)
{
    // lv_demo_benchmark();
    // lv_demo_music();
    // lv_demo_stress();
    lv_demo_widgets();

	while(1)
	{
        lv_task_handler();
        tx_thread_sleep(4);
	}

}

void LiveLedThread_entry_function(ULONG id)
{
	BSP_LED_Init(LED_GREEN);
	while(1)
	{
		BSP_LED_Toggle(LED_GREEN);
		//HAL_Delay(1000);				//To check HAL_Tick delay
		tx_thread_sleep(1000);
	}

}

/**
  * @brief  Define the initial system.
  * @param  first_unused_memory : Pointer to the first unused memory
  * @retval None
  */

VOID tx_application_define(VOID *first_unused_memory)
{
  /* USER CODE BEGIN  tx_application_define */
	tx_byte_pool_create(&SRAM_pool,"SRAM",(void*) 0x20000000,256*1024);
  /* USER CODE END  tx_application_define */

  /* USER CODE BEGIN DYNAMIC_MEM_ALLOC */
	uint8_t *PMainThreadStack = NULL;
	tx_byte_allocate(&SRAM_pool,(void **) &PMainThreadStack, 8*1024 ,TX_NO_WAIT);
	tx_thread_create(&MainThread,"Lvgl",LvglThread_entry_function,0,PMainThreadStack,8*1024,10,0,0,1);

	uint8_t *PLiveLedThreadStack = NULL;
	tx_byte_allocate(&SRAM_pool,(void **) &PLiveLedThreadStack, 1*1024 ,TX_NO_WAIT);
	tx_thread_create(&LiveLedThread,"LiveLed",LiveLedThread_entry_function,0,PLiveLedThreadStack,1*1024,30,0,0,1);
  /* USER CODE END DYNAMIC_MEM_ALLOC */
}

