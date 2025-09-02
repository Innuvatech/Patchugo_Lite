/**
* File: serial_types.h
* Created on: 2025-09-02 at 14:31
* Author: Andrea Rantin
* Description: //TODO
*/

#pragma once

#include <Arduino.h>
#include "stm32f4xx_hal.h"

/**
* @brief Baudrates assignable to a serial
* 
*/
enum class SerialBaudRate {
    BAUDRATE_110 = 110,
    BAUDRATE_150 = 150,
    BAUDRATE_2400 = 2400,
    BAUDRATE_4800 = 4800,
    BAUDRATE_9600 = 9600,
    BAUDRATE_19200 = 19200,
    BAUDRATE_38400 = 38400,
    BAUDRATE_57600 = 57600,
    BAUDRATE_115200 = 115200,
};

//Utility constant expressions to ease usage of SerialBaudRate
static constexpr SerialBaudRate BAUDRATE_110 = SerialBaudRate::BAUDRATE_110;
static constexpr SerialBaudRate BAUDRATE_150 = SerialBaudRate::BAUDRATE_150;
static constexpr SerialBaudRate BAUDRATE_2400 = SerialBaudRate::BAUDRATE_2400;
static constexpr SerialBaudRate BAUDRATE_4800 = SerialBaudRate::BAUDRATE_4800;
static constexpr SerialBaudRate BAUDRATE_9600 = SerialBaudRate::BAUDRATE_9600;
static constexpr SerialBaudRate BAUDRATE_19200 = SerialBaudRate::BAUDRATE_19200;
static constexpr SerialBaudRate BAUDRATE_38400 = SerialBaudRate::BAUDRATE_38400;
static constexpr SerialBaudRate BAUDRATE_57600 = SerialBaudRate::BAUDRATE_57600;
static constexpr SerialBaudRate BAUDRATE_115200 = SerialBaudRate::BAUDRATE_115200;

/**
* @brief Structure containing advanced configuration parameters for serials
* @note: FOR ADVANCED USER ONLY
*/
typedef struct {
    uint32_t wordLength;
    uint32_t stopBits;
    uint32_t parity;
    uint32_t mode;
    uint32_t oversampling;
}SerialAdvConfStruct;

/**
* @brief Mode of RS485(Transmit or Receive)
* 
*/
enum class RS485_Mode {
   RX = 0,
   TX = 1
};

//Utility constant expressions to ease use of enum RS485_Mode
static constexpr RS485_Mode RS485_MODE_RX = RS485_Mode::RX;
static constexpr RS485_Mode RS485_MODE_TX = RS485_Mode::TX;

typedef void (*Serial_RX_Callback)(uint8_t* buffer, uint8_t len);

static constexpr SerialAdvConfStruct SERIAL_DEFAULT_ADV_CONF_STRUCT = {
    .wordLength = UART_WORDLENGTH_8B,
    .stopBits = UART_STOPBITS_1,
    .parity = UART_PARITY_NONE,
    .mode = UART_MODE_TX_RX,
    .oversampling = UART_OVERSAMPLING_16
};

//Max length that RS485 serial can receive in asynchronous
static constexpr uint16_t RS485_MAX_RX_LEN = 512;