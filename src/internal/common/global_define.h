/**
* File: global_define.h
* Created on: 2025-09-02 at 11:38
* Author: Andrea Rantin
* Description: File that contains definitions used globally across files
*/

#pragma once

#include <Arduino.h>

typedef void (*DMA_CALLBACK_PTR)(uint8_t*, uint16_t, PatchugoStatusCode*);

