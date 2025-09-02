/**
* File: serial_helpers.h
* Created on: 2025-09-02 at 14:40
* Author: Andrea Rantin
* Description: This file contains definitions for functions used for low-level peripheral initialization
* for the RS485 such as USART initialization and timer initialization for our custom DMA implementation
*/

#pragma once

#include "internal/serial_manager/serial_types.h"
#include "patchugo_core.h"
#include "internal/common/global_define.h"

/**
* @brief Manages the low level initialization of peripheral needed for the USART used for RS485.
* This enabled clock on GPIOA pins and sets PA10 and PA11 with AF7 for USART usage. It then initializes the USART itself
* 
* @param baudRate User specified baudrate to set
* @param advConfStruct Advanced configuration structure to set advanced parameters. A default one is provided and is recommended
* not to override it
* @return PatchugoStatusCode This function can return the following values:
* - OK: The serial was initialized successfully
* - ERROR_RS485_SERIAL_HAL_INIT: An error occurred during USART initialization 
*/
PatchugoStatusCode RS485_Serial_HAL_Init(SerialBaudRate baudRate, SerialAdvConfStruct advConfStruct);

/**
* @brief Manages the low level initialization of peripheral needed for the USART used for USB.
* This enabled clock on GPIOA pins and sets PA10 and PA11 with AF7 for USART usage. It then initializes the USART itself
* 
* @param baudRate User specified baudrate to set
* @param advConfStruct Advanced configuration structure to set advanced parameters. A default one is provided and is recommended
* not to override it
* @return PatchugoStatusCode This function can return the following values:
* - OK: The serial was initialized successfully
* - ERROR_USB_SERIAL_HAL_INIT: An error occurred during USART initialization 
*/
PatchugoStatusCode USB_Serial_HAL_Init(SerialBaudRate baudRate, SerialAdvConfStruct advConfStruct);

/**
* @brief Initializes the timer used to "emulate" an asyncrhonous DMA.
* The timer will be initialized with a fixed 1uS period.
* 
* @param timer Timer that will be initialized
*/
void RS485_DMA_Timer_Init(HardwareTimer *timer);

/**
* @brief Starts the timer used to "emulate" an asyncrhonous DMA
* 
* @param timer Timer to start
*/
void RS485_Start_Async_Timer(HardwareTimer *timer);

