/**
* File: bt_at_helpers.cpp
* Created on: 2025-09-02 at 11:26
* Author: Andrea Rantin
* Description: Implementation file for bt_at_helpers.h
*/

#include "internal/bt_manager/bt_at_helpers.h"
#include "internal/bt_manager/bt_helpers.h"

BTState BT_AT_Helpers::state = BT_STATE_IDLE;
BTConnState BT_AT_Helpers::connState = BT_NOT_CONNECTED;
extern  HardwareTimer *btDmaTimer;

void BT_AT_Helpers::Set_BTState(BTState newState) {
    state = newState;
}

BTConnState BT_AT_Helpers::Get_BTConnState(void) {
    return BT_AT_Helpers::connState;
}

void BT_AT_Helpers::BT_Manage_AT_Resp(uint8_t *buf, uint16_t len, PatchugoStatusCode* result) {
    switch(state) {
        case BT_STATE_IDLE:
            if (strstr((char*)buf, "BLE_CONNECTED") != NULL) {
                Serial.println("CONN");
                connState = BT_CONNECTED;
            }
            if(strstr((char*)buf, "DISCONNECT") != NULL) {
                Serial.println("DISCONN");
                connState = BT_NOT_CONNECTED;
            }
            BT_Start_Async_Timer(btDmaTimer);
            break;
        case BT_STATE_ECHO_OFF:
            if(strstr((char*)buf, "OK") == NULL) {
                state = BT_STATE_IDLE;
                *result = ERROR_BT_ECHO_OFF;
                return;
            }
            state = BT_STATE_IDLE;
            *result = OK;
            break;
        case BT_STATE_CHANGE_NAME:
            if(strstr((char*)buf, "OK") == NULL) {
                state = BT_STATE_IDLE;
                *result = ERROR_BT_CHANGE_NAME;
                return;
            }
            state = BT_STATE_IDLE;
            *result = OK;
            break;
        case BT_STATE_SET_MTU:
            if(strstr((char*)buf, "OK") == NULL) {
                state = BT_STATE_IDLE;
                *result = ERROR_BT_SET_MTU;
                return;
            }
            state = BT_STATE_IDLE;
            *result = OK;
            break;
        default:
            break;
    }
}