/**
* File: spi_helpers.h
* Created on: 2025-09-03 at 11:29
* Author: Andrea Rantin
* Description: //TODO
*/

#pragma once

#include "patchugo_core.h"
#include "internal/spi_manager/spi_types.h"

/**
* @brief Manages the low level initialization of peripherals for the SPI.
* This enabled clock on GPIOB pins and sets PB13, PB14 and PB15 with AF5 for SPI usage
* 
* @param cpha SPI Clock phase
* @param cpol SPI Clock polarity
* @param cfgStruct SPI configuration structure. If not provided this has default values
* @return PatchugoStatusCode This function can return the following values:
* - OK: SPI was initialized correctly
* - ERROR_SPI_HAL_INIT: The low level initialization of SPI failed
*/
PatchugoStatusCode SPI_HAL_Init(SPI_CPHA cpha, SPI_CPOL cpol, SPIConfigStruct cfgStruct);