/**
* File: spi_types.h
* Created on: 2025-09-03 at 11:25
* Author: Andrea Rantin
* Description: This file contains definitions used for SPI functionalities such as Chip select definitions
*/

#pragma once

#include <Arduino.h>
#include "stm32f4xx_hal.h"

/**
* @brief Pins that can be used as SPI Chip select
* 
*/
enum class SPI_CS {
    N_CS_0 = D10,
    N_CS_1 = D8, 
};

//Utility constant expressions to ease usage of enum SPI_CS
static constexpr SPI_CS SPI_N_CS_0 = SPI_CS::N_CS_0;
static constexpr SPI_CS SPI_N_CS_1 = SPI_CS::N_CS_1;

/**
* @brief SPI clock polarity
* 
*/
enum class SPI_CPOL {
    CPOL_LOW = SPI_POLARITY_LOW,
    CPOL_HIGH = SPI_POLARITY_HIGH,
};

//Utility constant expressions to ease usage of enum SPI_CPOL
static constexpr SPI_CPOL SPI_CPOL_LOW = SPI_CPOL::CPOL_LOW;
static constexpr SPI_CPOL SPI_CPOL_HIGH = SPI_CPOL::CPOL_HIGH;

/**
* @brief SPI clock phase
* 
*/
enum class SPI_CPHA {
    CPHA_1EDGE = SPI_PHASE_1EDGE,
    CPHA_2EDGE = SPI_PHASE_2EDGE,
};

//Utility constant expressions to ease usage of enum SPI_CPHA
static constexpr SPI_CPHA SPI_CPHA_1EDGE = SPI_CPHA::CPHA_1EDGE;
static constexpr SPI_CPHA SPI_CPHA_2EDGE = SPI_CPHA::CPHA_2EDGE;

/**
* @brief SPI configuration structure
* @note: FOR ADVANCED USERS ONLY
*/
typedef struct {
    uint32_t mode;
    uint32_t direction;
    uint32_t dataSize;
    uint32_t baudratePre;
    uint32_t firstBit;
    uint32_t timMode;
    uint32_t crcCalc;
    uint32_t crcPoly;
}SPIConfigStruct;

//Default SPI configuration structure
static constexpr SPIConfigStruct SPI_DEFAULT_CONFIG_STRUCT = {
    .mode = SPI_MODE_MASTER,
    .direction = SPI_DIRECTION_2LINES,
    .dataSize = SPI_DATASIZE_8BIT,
    .baudratePre = SPI_BAUDRATEPRESCALER_64,
    .firstBit = SPI_FIRSTBIT_MSB,
    .timMode = SPI_TIMODE_DISABLE,
    .crcCalc = SPI_CRCCALCULATION_DISABLE,
    .crcPoly = 10
};