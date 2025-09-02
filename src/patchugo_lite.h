/**
* File: patchugo_lite.h
* Created on: 2025-09-01 at 21:35
* Author: Andrea Rantin
* Description: //TODO
*/

#pragma once

#include "internal/io_manager/io_manager.h"
#include "internal/bt_manager/bt_manager.h"

class PatchugoLite {
    private:
        IO_Manager ioManager;
        BT_Manager btManager;
    public:
        //TODO
        PatchugoStatusCode Init(void);
};