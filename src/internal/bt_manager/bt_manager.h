/**
* File: bt_manager.h
* Created on: 2025-09-02 at 11:01
* Author: Andrea Rantin
* Description: This file contains the definition of the class responsible for managing the bluetooth functionalities of the board.
* The class allows to initialize the bluetooth with some default parameters aswell as changing bluetooth name, MTU, and sending AT commands
*/

#pragma once

#include "internal/bt_manager/bt_types.h"
#include "patchugo_core.h"
#include "internal/common/global_define.h"
#include "internal/bt_manager/bt_at_helpers.h"

class BT_Manager {
    private:
        BTMode currentMode; /*!<Current operating mode of bluetooth>*/
        BT_AT_Helpers btAtHelpers; /*!<Instance of bluetooth AT helpers class for AT commands management*/
    public:
        /**
        * @brief Initializes the bluetooth management functionality by sending AT commands to the bluetooth module to set it up
        * with some default parameters. This init function initializes the bluetooth with the following parameters:
        * - Name: PatchugoLite
        * - Mode: Command mode
        * - MTU: 100 bytes
        * 
        * @return PatchugoStatusCode This function can return the following values:
        * - OK: The bluetooth functionality was initialized correctly
        * - ERROR_BT_SERIAL_HAL_INIT: Low level initialization of bluetooth peripherals failed
        * - ERROR_BT_MODE: Bluetooth could not be started in command mode
        * - ERROR_BT_ECHO_OFF: Echo for bluetooth AT commands could not be turned off
        * - ERROR_BT_ECHO_OFF_SEND_CMD: The AT command for turning echo off could not be sent
        * - ERROR_BT_NAME_SEND_CMD: The AT command to set the default bluetooth name to "PatchugoLite" could not be sent
        * - ERROR_BT_NAME: The bluetooth default name "PatchugoLite" could not be set
        * - ERROR_BT_MTU_SEND_CMD: The AT command to set the MTU to our default of 100 could not be sent
        * - ERROR_BT_MTU: The starting MTU of 100 could not be set
        * - ERROR_DMA_CALLBACK_NULL: Error while setting internal callbacks
        * - ERROR_DMA_RESULT_NULL: Error while setting internal callbacks
        */
        PatchugoStatusCode Init(void);

        /**
        * @brief Turns the echo from AT commands OFF
        * 
        * @return PatchugoStatusCode 
        */
        PatchugoStatusCode BT_Echo_Off(void);

        /**
        * @brief Changes the bluetooth name to the given one
        * 
        * @param name Name to give the bluetooth
        * @return PatchugoStatusCode This function can return the following values:
        * - OK: The bluetooth name was changed correctly
        * - ERROR_BT_NAME_LEN: The gievn name exceeded the max possible length of 20 characters
        * - ERROR_BT_CHANGE_NAME: The name could not be changed
        * - ERROR_BT_NAME_SEND_CMD: The change name command could not be sent to the bluetooth
        * @note: The given name MUST NOT exceed 20 characters of length, otherwise this function will return an error!
        */
        PatchugoStatusCode BT_Change_Name(const char *name);

        /**
        * @brief Sets the bluetooth MTU to the given value
        * 
        * @param mtu MTU to set
        * @return PatchugoStatusCode This function can return the following values:
        * - OK: The MTU was changed successfully
        * - ERROR_BT_SET_MTU: The MTU could not be changed
        * - ERROR_BT_MTU_SEND_CMD: The AT command to change MTU could not be sent to the bluetooth
        */
        PatchugoStatusCode BT_Set_MTU(uint16_t mtu);

        /**
        * @brief Changes bluetooth operating mode
        * 
        * @param mode Mode to switch to
        * @return PatchugoStatusCode This function can return the following values:
        * - OK: The operating mode was changed correctly
        * - ERROR_BT_MODE: The mode could not be changed
        * @note: To switch to transparent mode, the bluetooth must be connected!
        */
        PatchugoStatusCode BT_Set_Mode(BTMode mode);

        /**
        * @brief Sends an user provided AT command to the bluetooth
        * 
        * @param cmdData Buffer of the AT command to send
        * @param len Length of the buffer
        * @param callback Callback to trigger on AT command response
        * @return PatchugoStatusCode This function can return the following values:
        * - OK: The AT command was executed correctly(note that this depends on the implementation of the user provided callback)
        * - ERROR_BT_SEND_AT: The AT command could not be sent
        * - ERROR_BT_AT: This is returned if the implementation of the callback given by the user is empty and does not return OK
        */
        PatchugoStatusCode BT_Send_AT(uint8_t *cmdData,uint8_t len, DMA_CALLBACK_PTR callback);

        /**
        * @brief Sets the callback to be used when the next "DMA" rx is completed
        * 
        * @param ptr Function pointer to be called as callback
        * @param result Result of the elaboration inside the callback
        * @return PatchugoStatusCode This function can return the following values
        * - OK: The callback was set successfuly
        * - ERROR_DMA_CALLBACK_NULL: The funcion pointer provided to be used as callback is NULL
        * - ERROR_DMA_RESULT_NULL: The pointer to be filled with the result of the elaboration is NULL
        */
        PatchugoStatusCode BT_Async_RX_Set_Callback(DMA_CALLBACK_PTR ptr, PatchugoStatusCode* result);

        /**
        * @brief Resets the "DMA" count to 0 and starts listening again.
        * This can be considered a sort of rearm of bluetooth "DMA"
        */
        void BT_Start_Async_Listen(void);

};

