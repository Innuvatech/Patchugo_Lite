/**
* File: spi_manager.cpp
* Created on: 2025-09-03 at 14:28
* Author: Andrea Rantin
* Description: Implementation file for spi_manager.h
*/

#include "internal/spi_manager/spi_manager.h"
#include "internal/spi_manager/spi_helpers.h"

extern SPI_HandleTypeDef hspi2;

PatchugoStatusCode SPI_Manager::Init(SPI_CPOL cpol, SPI_CPHA cpha, SPIConfigStruct cfgStruct) {

    PatchugoStatusCode checkError = SPI_HAL_Init(cpha, cpol, cfgStruct);
    if(checkError != OK) return checkError;
    return OK;
}

void SPI_Manager::SPI_CS_Init(SPI_CS cs) {
    uint32_t pin = static_cast<uint32_t>(cs);
    pinMode(pin, OUTPUT);
}

PatchugoStatusCode SPI_Manager::SPI_Write(SPI_CS cs, uint8_t *writeData, uint16_t len, uint32_t timeout) {
    uint32_t pin = static_cast<uint32_t>(cs);
    digitalWrite(pin, LOW);
    if(HAL_SPI_Transmit(&hspi2, writeData, len, timeout) != HAL_OK) return ERROR_SPI_WRITE;
    digitalWrite(pin, HIGH);
    return OK;
}

PatchugoStatusCode SPI_Manager::SPI_Read(SPI_CS cs, uint8_t *readData, uint16_t len, uint32_t timeout) {
    uint32_t pin = static_cast<uint32_t>(cs);
    digitalWrite(pin, LOW);
    if(HAL_SPI_Receive(&hspi2, readData, len, timeout) != HAL_OK) return ERROR_SPI_READ;
    digitalWrite(pin, HIGH);
    return OK;
}

