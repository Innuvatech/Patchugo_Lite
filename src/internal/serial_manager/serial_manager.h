/**
* File: serial_manager.h
* Created on: 2025-09-02 at 14:36
* Author: Andrea Rantin
* Description: This file contains the definition of the Serial_Manager class and its members/functions. The class
* allows to control all the serial peripherals of the PatchugoLite(RS485, USB) and it provides the following functionalities.
* - Initializing RS485 serial with customizable baudrate and optional advanced parameters
* - Initializing USB serial with customizable baudrate and optional advanced parameters
* - Writing trough RS485 serial
* - Reading trough RS485 serial
* - Having asyncrhonous RX callbacks from RS485 serial
* - Writing trough USB serial
* - Reading trough USB serial
*/

#pragma once

#include "internal/serial_manager/serial_types.h"
#include "internal/serial_manager/serial_helpers.h"

class Serial_Manager {
    public:
        /**
        * @brief Initializes the RS485 serial with the given baudrate
        * 
        * @param baudRate Baudrate to set
        * @param advConfStruct Optional advanced configuration structure with advanced parameters. If not provided this
        * defaults to a default structure of the library.
        * @return PatchugoStatusCode This function can return the following values:
        * - OK: The serial was initialized correctly
        * - ERROR_RS485_SERIAL_HAL_INIT: Low level initialization of RS485 peripherals failed
        * @note: It is HIGHLY RECOMMENDED not to override the default value of advConfStruct
        */
        PatchugoStatusCode RS485_Serial_Init(SerialBaudRate baudRate, SerialAdvConfStruct advConfStruct = SERIAL_DEFAULT_ADV_CONF_STRUCT);

        /**
        * @brief Performs a serial write trough RS485 serial
        * 
        * @param buf Buffer to write
        * @param len Length of the buffer to write
        * @return PatchugoStatusCode This function can return the following values:
        * - OK: The buffer was transmitter
        * - ERROR_RS485_SERIAL_WRITE: The serial could not write
        */
        PatchugoStatusCode RS485_Serial_Write(uint8_t* buf, uint16_t len);

        /**
        * @brief Performs a blocking read with the RS485 serial
        * 
        * @param buf Buffer where the read data will be put
        * @param len Length of the data to read
        * @param timeout Timeout of the read
        * @return PatchugoStatusCode This funcion can return the following values:
        * - OK: The read was completed successfully
        * - ERROR_RS485_SERIAL_READ: The read went into an error or timed out
        */
        PatchugoStatusCode RS485_Serial_Read(uint8_t* buf, uint16_t len, uint32_t timeout);

        /**
        * @brief Initializes the RS485 serial with the given baudrate
        * 
        * @param baudRate Baudrate to set
        * @param advConfStruct Optional advanced configuration structure with advanced parameters. If not provided this
        * defaults to a default structure of the library.
        * @return PatchugoStatusCode This function can return the following values:
        * - OK: The serial was initialized correctly
        * - ERROR_USB_SERIAL_HAL_INIT: Low level initialization of USB peripherals failed
        * @note: It is HIGHLY RECOMMENDED not to override the default value of advConfStruct
        */
        PatchugoStatusCode USB_Serial_Init(SerialBaudRate baudRate, SerialAdvConfStruct advConfStruct = SERIAL_DEFAULT_ADV_CONF_STRUCT);

        /**
        * @brief Sets the callback to be used when the next "DMA" rx is completed
        * 
        * @param ptr Function pointer to be called as callback
        * @param result Result of the elaboration inside the callback
        * @return PatchugoStatusCode This function can return the following values
        * - OK: The callback was set successfuly
        * - ERROR_DMA_CALLBACK_NULL: The funcion pointer provided to be used as callback is NULL
        * - ERROR_DMA_RESULT_NULL: The pointer to be filled with the result of the elaboration is NULL
        */
        PatchugoStatusCode RS485_Async_RX_Set_Callback(DMA_CALLBACK_PTR ptr, PatchugoStatusCode* result);

        /**
        * @brief Performs a serial write trough USB serial
        * 
        * @param buf Buffer to write
        * @param len Length of the buffer to write
        * @return PatchugoStatusCode This function can return the following values:
        * - OK: The buffer was transmitter
        * - ERROR_USB_SERIAL_WRITE: The serial could not write
        */
        PatchugoStatusCode USB_Serial_Write(uint8_t* buf, uint16_t len);

        /**
        * @brief Performs a blocking read with the USB serial
        * 
        * @param buf Buffer where the read data will be put
        * @param len Length of the data to read
        * @param timeout Timeout of the read
        * @return PatchugoStatusCode This funcion can return the following values:
        * - OK: The read was completed successfully
        * - ERROR_USB_SERIAL_READ: The read went into an error or timed out
        */
        PatchugoStatusCode USB_Serial_Read(uint8_t* buf, uint16_t len, uint32_t timeout);

        /**
        * @brief Resets the "DMA" count to 0 and starts listening again.
        * This can be considered a sort of rearm of RS485 "DMA"
        */
        void RS485_Start_Async_Listen(void);

};

