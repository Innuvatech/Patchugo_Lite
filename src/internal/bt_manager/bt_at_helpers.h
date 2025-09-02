/**
* File: bt_at_helpers.h
* Created on: 2025-09-02 at 11:23
* Author: Andrea Rantin
* Description: This file contains a class with functionalities to help with bluetooth
* AT command helpers
*/

#pragma once

#include "internal/bt_manager/bt_types.h"
#include "patchugo_core.h"

class BT_AT_Helpers {
    private:
        static BTState state;
        static BTConnState connState;
    public:
        /**
        * @brief Sets the bluetooth state to the given one
        * 
        * @param newState State to set
        */
        static void Set_BTState(BTState newState);

        /**
        * @brief Gets the current bluetooth connection state
        * 
        * @return BTConnState current bluetooth connection state
        */
        static BTConnState Get_BTConnState(void);

        /**
        * @brief Function used as callback for AT command responses
        * 
        * @param buf Buffer of the response received
        * @param len Length of the response reeived
        * @param result Result of the elaboration of the response
        */
        static void BT_Manage_AT_Resp(uint8_t *buf, uint16_t len, PatchugoStatusCode *result);
};

