/**
* File: i2c_helpers.cpp
* Created on: 2025-09-02 at 15:55
* Author: Andrea Rantin
* Description: Implementation file for i2c_helpers.h
*/

#include "internal/i2c_manager/i2c_helpers.h"
#include "stm32f4xx_hal.h"

I2C_HandleTypeDef hi2c3;

PatchugoStatusCode I2C_HAL_Init(I2CConfigStruct configStruct) {

    //Initialize I2C GPIOs
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    __HAL_RCC_GPIOC_CLK_ENABLE();
    __HAL_RCC_GPIOA_CLK_ENABLE();
    /**I2C3 GPIO Configuration
    PC9     ------> I2C3_SDA
    PA8     ------> I2C3_SCL
    */
    GPIO_InitStruct.Pin = GPIO_PIN_9;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_OD;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF4_I2C3;
    HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_8;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_OD;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF4_I2C3;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    /* I2C3 clock enable */
    __HAL_RCC_I2C3_CLK_ENABLE();

    hi2c3.Instance = I2C3;
    hi2c3.Init.ClockSpeed = configStruct.clockSpeed;
    hi2c3.Init.DutyCycle = configStruct.dutyCycle;
    hi2c3.Init.OwnAddress1 = 0;
    hi2c3.Init.AddressingMode = configStruct.addressingMode;
    hi2c3.Init.DualAddressMode = configStruct.dualAddressingMode;
    hi2c3.Init.OwnAddress2 = 0;
    hi2c3.Init.GeneralCallMode = configStruct.generalCallMode;
    hi2c3.Init.NoStretchMode = configStruct.noStretchMode;
    if (HAL_I2C_Init(&hi2c3) != HAL_OK) return ERROR_I2C_HAL_INIT;

    return OK;
}

