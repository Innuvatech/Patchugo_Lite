/**
* File: bt_types.h
* Created on: 2025-09-02 at 11:05
* Author: Andrea Rantin
* Description: This file contains definitions needed for bluetooth management in this library
* such as operating modes, AT command strings, states for command state tracking
*/

#pragma once

#include <Arduino.h>

//Name is restricted to 20 characters to fit into normal advertising
static constexpr uint8_t BT_NAME_MAX_LEN = 20;
//Default MTU is 100
static constexpr uint8_t BT_DEFAULT_MTU = 100;
//Max length that bluetooth serial can receive in asynchronous
static constexpr uint16_t BT_MAX_RX_LEN = 512;

//AT command strings for PB-03F
static constexpr char* BT_CHANGE_NAME_CMD = "AT+BLENAME=";
static constexpr char* BT_SET_MTU_CMD = "AT+BLEMTU=%d\r\n";
static constexpr char* BT_TRANSPARENT_MODE_CMD = "AT+TRANSENTER\r\n";
static constexpr char* BT_COMMAND_MODE_CMD = "+++";
static constexpr char* BT_ECHO_OFF_CMD = "ATE0\r\n";
static constexpr char* BT_SET_AUTH_CMD = "AT+BLEAUTH=%s\r\n";

/**
* @brief Bluetooth operating modes. AT commands can be sent only while
* in COMMAND mode
*/
enum class BTMode {
    BT_MODE_COMMAND,
    BT_MODE_TRANSPARENT,
};

/**
* @brief States used for command response tracking and management
* 
*/
enum class BTState {
   BT_STATE_IDLE,
   BT_STATE_CHANGE_NAME,
   BT_STATE_SET_MTU,
   BT_STATE_ECHO_OFF,
};

/**
* @brief Bluetooth connection state
* 
*/
enum class BTConnState {
   BT_NOT_CONNECTED,
   BT_CONNECTED,
};

//Utility constant expressions to ease usage of enum BTMode
static constexpr BTMode BT_MODE_COMMAND = BTMode::BT_MODE_COMMAND;
static constexpr BTMode BT_MODE_TRANSPARENT = BTMode::BT_MODE_TRANSPARENT;

//Utility constant expressions to ease usage of enum BTState
static constexpr BTState BT_STATE_IDLE = BTState::BT_STATE_IDLE;
static constexpr BTState BT_STATE_CHANGE_NAME = BTState::BT_STATE_CHANGE_NAME;
static constexpr BTState BT_STATE_SET_MTU = BTState::BT_STATE_SET_MTU;
static constexpr BTState BT_STATE_ECHO_OFF = BTState::BT_STATE_ECHO_OFF;

//Utility constant expressions to ease usage of enum BTConnState
static constexpr BTConnState BT_NOT_CONNECTED = BTConnState::BT_NOT_CONNECTED;
static constexpr BTConnState BT_CONNECTED = BTConnState::BT_CONNECTED;