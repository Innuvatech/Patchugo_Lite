/**
* File: bt_helpers.cpp
* Created on: 2025-09-02 at 10:10
* Author: Andrea Rantin
* Description: Implementation file for bt_helpers.cpp
*/

#include "bt_helpers.h"
#include "stm32f4xx_hal.h"

//Handle to the serial used by the bluetooth
UART_HandleTypeDef btSerialHandle;

PatchugoStatusCode BT_Serial_HAL_Init(void) {

    /*
        We don't allow changing any setting of the USART used by the bluetooth because it
        is not customizable.
    */

    btSerialHandle.Instance = USART2;
    btSerialHandle.Init.BaudRate = 115200;
    btSerialHandle.Init.WordLength = UART_WORDLENGTH_8B;
    btSerialHandle.Init.StopBits = UART_STOPBITS_1;
    btSerialHandle.Init.Parity = UART_PARITY_NONE;
    btSerialHandle.Init.Mode = UART_MODE_TX_RX;
    btSerialHandle.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    btSerialHandle.Init.OverSampling = UART_OVERSAMPLING_16;

    __HAL_RCC_USART2_CLK_ENABLE();
    __HAL_RCC_GPIOD_CLK_ENABLE();

    
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    //Initialize PD5 AND PD6 as AF7
    GPIO_InitStruct.Pin = GPIO_PIN_5|GPIO_PIN_6;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF7_USART2;
    HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

    if (HAL_UART_Init(&btSerialHandle) != HAL_OK) return ERROR_BT_SERIAL_HAL_INIT;

    //Clear IDLE flag to avoid IDLE interrupt to trigger randomly after initialization
    __HAL_UART_CLEAR_IDLEFLAG(&btSerialHandle);

    return OK;
}

void BT_DMA_Timer_Init(HardwareTimer *timer) {
    //Clock is 168Mhz these values will give a period of 1uS
    timer->setPrescaleFactor(12-1);
    timer->setOverflow(14-1);
}

void BT_Start_Async_Timer(HardwareTimer *timer) {
    timer->pause();
    timer->setCount(0);
    timer->resume();
}