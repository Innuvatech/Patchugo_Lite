/**
* File: io_types.h
* Created on: 2025-09-01 at 21:44
* Author: Andrea Rantin
* Description: Description: This file contains definitions for IO management. It contains types for Isolated 24V INPUT
* and OUTPUT pins aswell as utility constant expressions to ease their use. This file is supposed to be only included by io_manager.h
* and thus will throw an error when the user tries to include it in any file without PATCHUGO_IO_TYPES defined.
*/

#pragma once

#include <Arduino.h>


/**
* @brief Isolated 24V INPUT pins of the board(U7 connector)
* 
*/
enum class ISO_InputPin {
    ISO_IN1 = PB2,
    ISO_IN2 = PB1,
    ISO_IN3 = PB0,
    ISO_IN4 = PA7,
    ISO_IN5 = PA6,
    ISO_IN6 = PA5,
    ISO_IN7 = PA4,
    ISO_IN8 = PA3,
};

/**
* @brief Isolated 24V OUTPUT pins of the board(U29 connector)
* 
*/
enum class ISO_OutputPin {
    ISO_OUT1 = PE14,
    ISO_OUT2 = PE13,
    ISO_OUT3 = PE11,
    ISO_OUT4 = PE9,
    ISO_OUT5 = PE15,
    ISO_OUT6 = PE12,
    ISO_OUT7 = PE8,
    ISO_OUT8 = PE7,
};

/**
* @brief Static constexpressions to ease the use of enum values for isolated 24V INPUT pins.
* This allows the user to call ISO_INx instead of having to call the enum class like
* ISO_InputPin_Typedef::ISO_INx
* 
*/
static constexpr ISO_InputPin ISO_IN1 = ISO_InputPin::ISO_IN1;
static constexpr ISO_InputPin ISO_IN2 = ISO_InputPin::ISO_IN2;
static constexpr ISO_InputPin ISO_IN3 = ISO_InputPin::ISO_IN3;
static constexpr ISO_InputPin ISO_IN4 = ISO_InputPin::ISO_IN4;
static constexpr ISO_InputPin ISO_IN5 = ISO_InputPin::ISO_IN5;
static constexpr ISO_InputPin ISO_IN6 = ISO_InputPin::ISO_IN6;
static constexpr ISO_InputPin ISO_IN7 = ISO_InputPin::ISO_IN7;
static constexpr ISO_InputPin ISO_IN8 = ISO_InputPin::ISO_IN8;

/**
* @brief Static  constexpressions to ease the use of enum values for isolated V24 OUTPUT pins.
* This allows the user to call ISO_OUTx instead of having to call the enum class like
* ISO_OutputPin::ISO_OUTx
* 
*/
static constexpr ISO_OutputPin ISO_OUT1 = ISO_OutputPin::ISO_OUT1;
static constexpr ISO_OutputPin ISO_OUT2 = ISO_OutputPin::ISO_OUT2;
static constexpr ISO_OutputPin ISO_OUT3 = ISO_OutputPin::ISO_OUT3;
static constexpr ISO_OutputPin ISO_OUT4 = ISO_OutputPin::ISO_OUT4;
static constexpr ISO_OutputPin ISO_OUT5 = ISO_OutputPin::ISO_OUT5;
static constexpr ISO_OutputPin ISO_OUT6 = ISO_OutputPin::ISO_OUT6;
static constexpr ISO_OutputPin ISO_OUT7 = ISO_OutputPin::ISO_OUT7;
static constexpr ISO_OutputPin ISO_OUT8 = ISO_OutputPin::ISO_OUT8;

