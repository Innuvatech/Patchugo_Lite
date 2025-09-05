/**
* File: i2c_manager.h
* Created on: 2025-09-02 at 16:03
* Author: Andrea Rantin
* Description: This file contains the definitions of the I2C_Manager class and its members/functions to control
* the I2C peripheral of the PatchugoLite board. It allows the following functionalities:
* - Initialize I2C with the optional possibility of providing custom configuration parameters
* - Writing trough I2C
* - Reading trough I2C
* - Writing to a specific register of a connected I2C device
* - Reading from a specific register of a connected I2C device
*/

#pragma once

#include "patchugo_core.h"
#include "internal/i2c_manager/i2c_helpers.h"

class I2C_Manager {
    public:
        /**
        * @brief Initialized the I2C peripheral of the board
        * 
        * @param configStruct Optional configuration structure to provide with I2C configuration parameters. If not provided this has default values
        * @return PatchugoStatusCode This function can return the following values:
        * - OK: The I2C was initialized correctly
        * - ERROR_I2C_HAL_INIT: An error occurred during low level I2C initialization
        */
        PatchugoStatusCode Init(I2CConfigStruct configStruct = DEFAULT_I2C_CONFIG_STRUCT);

        /**
        * @brief Performs a write on the I2C
        * 
        * @param addr Address of the I2C device to write to
        * @param data Data to write
        * @param len Length of the data to write
        * @param timeout Timeout in milliseconds
        * @return PatchugoStatusCode This function can return the following values:
        * - OK: I2C write was successful
        * - ERROR_I2C_WRITE: There was an error during I2C write
        */
        PatchugoStatusCode I2C_Write(uint8_t addr, uint8_t *data, uint16_t len, uint32_t timeout);

        /**
        * @brief Performs a read from the I2C device with the address specified
        * 
        * @param addr Address of the I2C device to read from
        * @param readData Buffer that will be filled with data read
        * @param len Length of the data to read
        * @param timeout Timeout in milliseconds
        * @return PathugoStatusCode This function can return the following values:
        * - OK: I2C read was successful, data is in readData
        * - ERROR_I2C_READ: There was an error during I2C read
        */
        PatchugoStatusCode I2C_Read(uint8_t addr, uint8_t *readData, uint16_t len, uint32_t timeout);

        /**
        * @brief Writes a register of the I2C device with the given address
        * 
        * @param addr I2C address of the device
        * @param regAddr Address of the register
        * @param regAddrSize Size of the register
        * @param writeData Buffer of data to write
        * @param len Length of data to write
        * @param timeout Timeout
        * @return PatchugoStatusCode This function can return the following values:
        * - OK: The I2C register write was successful
        * - ERROR_I2C_WRITE_REG: An error occurred during the I2C write of the register.
        */
        PatchugoStatusCode I2C_WriteReg(uint8_t addr, uint16_t regAddr, uint16_t regAddrSize, uint8_t *writeData, uint16_t len, uint32_t timeout);

        /**
        * @brief Reads a register of the I2C device with the given address
        * 
        * @param addr I2C address of the device
        * @param regAddr Address of the register
        * @param regAddrSize Size of the register
        * @param readData Buffer where read data will be put
        * @param len Length of data to read
        * @param timeout Timeout
        * @return PatchugoStatusCode PatchugoStatusCode This function can return the following values:
        * - OK: The I2C register write was successful
        * - ERROR_I2C_READ_REG: An error occurred during the I2C read of the register.
        */
        PatchugoStatusCode I2C_ReadReg(uint8_t addr, uint16_t regAddr, uint16_t regAddrSize, uint8_t *readData, uint16_t len, uint32_t timeout);
};


