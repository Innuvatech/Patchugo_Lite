/**
* File: spi_manager.h
* Created on: 2025-09-03 at 11:25
* Author: Andrea Rantin
* Description: This file contains the definition of the SPI_Manager class and its members/functions. The class
* allows to control the SPI peripheral of the PatchugoLite board and provides the following functionalities:
* - Initializing the SPI peripheral with customizable Clock phase, Clock polarity and optional configuration parameters
* - Writing trough SPI
* - Reading trough SPI
*/

#pragma once

#include "internal/spi_manager/spi_helpers.h"

class SPI_Manager {
    public:
        /**
        * @brief Initializes the SPI functionalities of the board by setting SPI clock phase and polarity aswell
        * as configuring SPI parameters
        * 
        * @param cpol SPI Clock polarity
        * @param cpha SPI Clock phase
        * @param cfgStruct SPI Configuration structure. This is optional and defaults to predefined values if not providded
        * @return PatchugoStatusCode This function can return the following values:
        * - OK: SPI was initialized correctly
        * - ERROR_SPI_HAL_INIT: There was an error during the low level initialization of SPI
        * @note: It is STRONGLY RECOMMENDED not to override the default values of cfgStruct(by not providing it) It's for ADVANCED
        * USERS ONLY
        */
        PatchugoStatusCode Init(SPI_CPOL cpol, SPI_CPHA cpha, SPIConfigStruct cfgStruct = SPI_DEFAULT_CONFIG_STRUCT);

        /**
        * @brief Writes a buffer trough SPI
        * 
        * @param cs Chip select to use
        * @param writeData Buffer to write
        * @param len Length of data to write
        * @param timeout Timeout in milliseconds
        * @return PatchugoStatusCode This function can return the following values:
        * - OK: The SPI write was successful
        * - ERROR_SPI_WRITE: There was an error or timeout during the SPI write
        */
        PatchugoStatusCode SPI_Write(SPI_CS cs, uint8_t *writeData, uint16_t len, uint32_t timeout);

        /**
        * @brief Reads a buffer trough SPI
        * 
        * @param cs Chip select to use
        * @param readData Buffer to write
        * @param len Length of data to write
        * @param timeout Timeout in milliseconds
        * @return PatchugoStatusCode This function can return the following values:
        * - OK: The SPI read was successful
        * - ERROR_SPI_READ: There was an error or timeout during the SPI read
        */
        PatchugoStatusCode SPI_Read(SPI_CS cs, uint8_t *readData, uint16_t len, uint32_t timeout);
};

