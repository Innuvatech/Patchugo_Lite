/**
* File: serial_helpers.cpp
* Created on: 2025-09-02 at 14:41
* Author: Andrea Rantin
* Description: Implementation file for serial_helpers.h
*/

#include "internal/serial_manager/serial_helpers.h"
#include "stm32f4xx_hal.h"

UART_HandleTypeDef rs485SerialHandle;
UART_HandleTypeDef usbSerialHandle;

PatchugoStatusCode RS485_Serial_HAL_Init(SerialBaudRate baudRate, SerialAdvConfStruct advConfStruct) {
    uint32_t baudRateVal = static_cast<uint32_t>(baudRate);

    //Low level GPIOA clock and pins initialization for USART1
    __HAL_RCC_USART1_CLK_ENABLE();
    __HAL_RCC_GPIOA_CLK_ENABLE();

    GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Pin = GPIO_PIN_9|GPIO_PIN_10;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF7_USART1;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    //Initialize DE(PA12)
    GPIO_InitTypeDef GPIO_InitStructDE = {0};
    GPIO_InitStructDE.Pin = GPIO_PIN_12;
    GPIO_InitStructDE.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStructDE.Pull = GPIO_NOPULL;
    GPIO_InitStructDE.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStructDE);

    rs485SerialHandle.Instance = USART1;
    rs485SerialHandle.Init.BaudRate = baudRateVal;
    rs485SerialHandle.Init.WordLength = advConfStruct.wordLength;
    rs485SerialHandle.Init.StopBits = advConfStruct.stopBits;
    rs485SerialHandle.Init.Parity = advConfStruct.parity;
    rs485SerialHandle.Init.Mode = advConfStruct.mode;
    rs485SerialHandle.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    rs485SerialHandle.Init.OverSampling = advConfStruct.oversampling;

    if (HAL_UART_Init(&rs485SerialHandle) != HAL_OK){return ERROR_RS485_SERIAL_HAL_INIT;}

    return OK;
}

PatchugoStatusCode USB_Serial_HAL_Init(SerialBaudRate baudRate, SerialAdvConfStruct advConfStruct) {
    uint32_t baudRateVal = static_cast<uint32_t>(baudRate);

    __HAL_RCC_UART4_CLK_ENABLE();
    __HAL_RCC_GPIOA_CLK_ENABLE();

    GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Pin = GPIO_PIN_0 | GPIO_PIN_1;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF8_UART4;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    usbSerialHandle.Instance = UART4;
    usbSerialHandle.Init.BaudRate = baudRateVal;
    usbSerialHandle.Init.WordLength = advConfStruct.wordLength;
    usbSerialHandle.Init.StopBits = advConfStruct.stopBits;
    usbSerialHandle.Init.Parity = advConfStruct.parity;
    usbSerialHandle.Init.Mode = advConfStruct.mode;
    usbSerialHandle.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    usbSerialHandle.Init.OverSampling = advConfStruct.oversampling;
   
    if (HAL_UART_Init(&usbSerialHandle) != HAL_OK) return ERROR_USB_SERIAL_HAL_INIT;


    return OK;
}

void RS485_DMA_Timer_Init(HardwareTimer *timer) {
    timer->setPrescaleFactor(12-1);
    timer->setOverflow(14-1);
}

void RS485_Start_Async_Timer(HardwareTimer *timer) {
    timer->pause();
    timer->setCount(0);
    timer->resume();
}
