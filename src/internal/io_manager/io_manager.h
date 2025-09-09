/**
* File: io_manager.h
* Created on: 2025-09-01 at 21:46
* Author: Andrea Rantin
* Description: Description: This file contains the class IO_Manager to manage all I/O related functionalities such
* as initializing all isolated 24V pins to their respective functionality(INPUT/OUTPUT) and reading/writing them
* This file is only supposed to be included by patchugo_lite.h and thus will throw an error without PATCHUGO_INTERNAL_USE
* defined
*/

#pragma once

#include "internal/io_manager/io_types.h"

 /**
 * @brief Class to manage all I/O related functionalities of
 * the board like initializing all 24V isolated pins and reading/writing them
 * 
 */
 class IO_Manager {

    public:
        /**
        * @brief Initializes all 24V I/O pins to their respective function
        * 
        */
        void Init(void);

        /**
        * @brief Writes to a 24V isolated OUTPUT pin
        * 
        * @param pin Pin to write, this is a value of @ref ISO_OutputPin
        * @param state Value to write to the pin(can be RESET or SET)
        */
        void ISO_IO_Write(ISO_OutputPin pin, FlagStatus state);

        /**
        * @brief Reads a 24V isolated INPUT pin
        * 
        * @param pin Pin to read, this is a value of @ref ISO_InputPin
        * @return uint8_t Value read from the pin(0 or 1)
        */
        uint8_t ISO_IO_Read(ISO_InputPin pin);
 };