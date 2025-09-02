/**
* File: i2c_helpers.h
* Created on: 2025-09-02 at 15:55
* Author: Andrea Rantin
* Description: //TODO
*/

#pragma once

#include "patchugo_core.h"
#include "internal/i2c_manager/i2c_types.h"

/**
* @brief Manages the low level initialization of peripherals needed for I2C communication
* 
* @param configStruct Optional configuration structure to provide with I2C configuration parameters. If not provided this has default values
* @return PatchugoStatusCode This function can return the following values:
* - OK: The I2C initialization was successful
* - ERROR_I2C_HAL_INIT: The I2C could not be initialized
*/
PatchugoStatusCode I2C_HAL_Init(I2CConfigStruct configStruct);