/**
* File: i2c_types.h
* Created on: 2025-09-02 at 15:55
* Author: Andrea Rantin
* Description: This file contains definitions used for advanced I2C configuration
*/

#pragma once

#include <Arduino.h>

/**
* @brief I2C Advanced configuration structure containing configuration parameters
* @note: FOR ADVANCED USERS ONLY
*/
typedef struct {
    uint32_t clockSpeed;
    uint32_t dutyCycle;
    uint32_t ownAddress1;
    uint32_t addressingMode;
    uint32_t dualAddressingMode;
    uint32_t ownAddress2;
    uint32_t generalCallMode;
    uint32_t noStretchMode;
}I2CConfigStruct;


//Default I2C configuration structure
static constexpr I2CConfigStruct DEFAULT_I2C_CONFIG_STRUCT = {
    .clockSpeed = 100000,
    .dutyCycle = I2C_DUTYCYCLE_2,
    .ownAddress1 = 0,
    .addressingMode = I2C_ADDRESSINGMODE_7BIT,
    .dualAddressingMode = I2C_DUALADDRESS_DISABLE,
    .ownAddress2 = 0,
    .generalCallMode = I2C_GENERALCALL_DISABLE,
    .noStretchMode = I2C_NOSTRETCH_DISABLE
};
