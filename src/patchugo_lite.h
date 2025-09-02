/**
* File: patchugo_lite.h
* Created on: 2025-09-01 at 21:35
* Author: Andrea Rantin
* Description: //TODO
*/

#pragma once

#include "internal/io_manager/io_manager.h"
#include "internal/bt_manager/bt_manager.h"
#include "internal/serial_manager/serial_manager.h"
#include "internal/i2c_manager/i2c_manager.h"

class PatchugoLite {
    private:
        IO_Manager ioManager;
        BT_Manager btManager;
        Serial_Manager serialManager;
        I2C_Manager i2cManager;
    public:
        //TODO
        PatchugoStatusCode Init(void);
};