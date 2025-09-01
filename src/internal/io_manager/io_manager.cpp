/**
* File: io_manager.cpp
* Created on: 2025-09-01 at 21:47
* Author: Andrea Rantin
* Description: Implementation file for io_manager.h
*/

#include "internal/io_manager/io_manager.h"

/**
* @brief Converts a @ref ISO_OutputPin_Typedef value to its 
* integer representation
* 
* @param pin Enum value to convert. This is a value of @ref ISO_OutputPin_Typedef
* @return uint32_t Integer representation of the enum
*/
 static inline uint32_t ISO_OutputPin_ToInt(ISO_OutputPin_Typedef pin) {
    return static_cast<uint32_t>(pin);
 }
 
 /**
 * @brief Converts a @ref ISO_InputPin_Typedef value to its 
 * integer representation
 * 
 * @param pin Enum value to convert. This is a value of @ref ISO_InputPin_Typedef
 * @return uint32_t Integer representation of the enum
 */
 static inline uint32_t ISO_InputPin_ToInt(ISO_InputPin_Typedef pin) {
    return static_cast<uint32_t>(pin);
 }

void IO_Manager::Init(void) {

    // Initialize all 24V isolated INPUT pins
    pinMode(ISO_InputPin_ToInt(ISO_IN1), INPUT);
    pinMode(ISO_InputPin_ToInt(ISO_IN2), INPUT);
    pinMode(ISO_InputPin_ToInt(ISO_IN3), INPUT);
    pinMode(ISO_InputPin_ToInt(ISO_IN4), INPUT);
    pinMode(ISO_InputPin_ToInt(ISO_IN5), INPUT);
    pinMode(ISO_InputPin_ToInt(ISO_IN6), INPUT);
    pinMode(ISO_InputPin_ToInt(ISO_IN7), INPUT);
    pinMode(ISO_InputPin_ToInt(ISO_IN8), INPUT);

    // Initialize all 24V isolated OUTPUT pins
    pinMode(ISO_OutputPin_ToInt(ISO_OUT1), OUTPUT);
    pinMode(ISO_OutputPin_ToInt(ISO_OUT2), OUTPUT);
    pinMode(ISO_OutputPin_ToInt(ISO_OUT3), OUTPUT);
    pinMode(ISO_OutputPin_ToInt(ISO_OUT4), OUTPUT);
    pinMode(ISO_OutputPin_ToInt(ISO_OUT5), OUTPUT);
    pinMode(ISO_OutputPin_ToInt(ISO_OUT6), OUTPUT);
    pinMode(ISO_OutputPin_ToInt(ISO_OUT7), OUTPUT);
    pinMode(ISO_OutputPin_ToInt(ISO_OUT8), OUTPUT);
}


void IO_Manager::ISO_IO_Write(ISO_OutputPin_Typedef pin, FlagStatus state) {
    digitalWrite(ISO_OutputPin_ToInt(pin), state);
}

uint8_t IO_Manager::ISO_IO_Read(ISO_InputPin_Typedef pin) {
    return digitalRead(ISO_InputPin_ToInt(pin));
}