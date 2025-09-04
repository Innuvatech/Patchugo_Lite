/**
* File: flash_helpers.h
* Created on: 2025-09-04 at 10:25
* Author: Andrea Rantin
* Description: This file contains definitions for helpers functions for low level initialization of peripherals needed
* for the external flash chip.
*/

#pragma once

#include "patchugo_core.h"

/**
* @brief Manages the low level initialization of peripherals for the SPI used for the external flash chip.
* This enabled the clock on GPIOB and GPIOC pins and sets PB4, PB5 and PB10 to their AF6 for SPI usage
* 
* @return PatchugoStatusCode This function can return the following values:
* - OK: The SPI was initialized correctly
* - ERROR_SPI_HAL_INIT: There was an error during SPI low level initialiation
*/
PatchugoStatusCode Flash_SPI_HAL_Init(void);
