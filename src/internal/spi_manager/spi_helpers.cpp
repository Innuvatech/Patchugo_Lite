/**
* File: spi_helpers.cpp
* Created on: 2025-09-03 at 11:46
* Author: Andrea Rantin
* Description: Implementation file for spi_helpers.h
*/

#include "internal/spi_manager/spi_helpers.h"
#include "stm32f4xx_hal.h"

SPI_HandleTypeDef hspi2;

PatchugoStatusCode SPI_HAL_Init(SPI_CPHA cpha, SPI_CPOL cpol, SPIConfigStruct cfgStruct) {

    __HAL_RCC_SPI2_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();
    /**SPI2 GPIO Configuration
    PB13     ------> SPI2_SCK
    PB14     ------> SPI2_MISO
    PB15     ------> SPI2_MOSI
    */
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Pin = GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF5_SPI2;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    hspi2.Instance = SPI2;
    hspi2.Init.Mode = cfgStruct.mode;
    hspi2.Init.Direction = cfgStruct.direction;
    hspi2.Init.DataSize = cfgStruct.dataSize;
    hspi2.Init.CLKPolarity = static_cast<uint32_t>(cpol);
    hspi2.Init.CLKPhase = static_cast<uint32_t>(cpha);
    hspi2.Init.NSS = SPI_NSS_SOFT;
    hspi2.Init.BaudRatePrescaler = cfgStruct.baudratePre;
    hspi2.Init.FirstBit = cfgStruct.firstBit;
    hspi2.Init.TIMode = cfgStruct.timMode;
    hspi2.Init.CRCCalculation = cfgStruct.crcCalc;
    hspi2.Init.CRCPolynomial = cfgStruct.crcPoly;

    if (HAL_SPI_Init(&hspi2) != HAL_OK) return ERROR_SPI_HAL_INIT;

    return OK;
}