/**
* File: bt_helpers.h
* Created on: 2025-09-02 at 09:55
* Author: Andrea Rantin
* Description: This file contains definitions for functions used for low-level peripheral initialization
* for the bluetooth such as USART initialization and timer initialization for our custom DMA implementation
*/

#pragma once

#include "patchugo_core.h"

/**
* @brief Manages the low level initialization of peripherals needed for the USART connected to the bluetooth.
* This enables clock on GPIOD pins and sets PD5 and PD6 with AF7 for USART usage. It then initializes the USART itself
* 
* @return PatchugoStatusCode This function can return the following status codes:
* - OK: The low level initialization was completed successfully
* - ERROR_BT_SERIAL_HAL_INIT: An error occurred during USART HAL initialization
*/
PatchugoStatusCode BT_Serial_HAL_Init(void);

/**
* @brief Initializes the timer used to "emulate" an asyncrhonous DMA.
* The timer will be initialized with a fixed 1uS period.
* 
* @param timer Timer that will be initialized
*/
void BT_DMA_Timer_Init(HardwareTimer *timer);

/**
* @brief Starts the timer used to "emulate" an asyncrhonous DMA
* 
* @param timer Timer to start
*/
void BT_Start_Async_Timer(HardwareTimer *timer);

