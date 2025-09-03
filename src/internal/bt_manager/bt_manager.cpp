/**
* File: bt_manager.cpp
* Created on: 2025-09-02 at 11:02
* Author: Andrea Rantin
* Description: Implementation file for bt_manager.h
*/

#include "internal/bt_manager/bt_manager.h"
#include "internal/bt_manager/bt_helpers.h"

extern  UART_HandleTypeDef btSerialHandle;

//Timer used to "emulate" asynchronous DMA
HardwareTimer *btDmaTimer = new HardwareTimer(TIM10);
//Flag to check if USART is transmitting
bool isBtTransmitting = false;
//Pointer to a function to be used as "DMA" callback
DMA_CALLBACK_PTR btDmaCallback = NULL;
uint16_t btDmaRxLen = 0;
uint16_t btDmaRxCount = 0;
//"DMA" buffer
uint8_t btDmaBuf[BT_MAX_RX_LEN] = {0};
//Result to be used in asynchronous operations
PatchugoStatusCode *btDmaClbkResult = nullptr;

/**
* @brief Flushes the USART used for bluetooth communication
* 
*/
static void BT_USART_Flush(void) {
    __HAL_UART_CLEAR_OREFLAG(&btSerialHandle);
    __HAL_UART_FLUSH_DRREGISTER(&btSerialHandle);
}

/**
* @brief Interrupt attached to the btDmaTimer used to "emulate"
* DMA behavior
*/
static void BT_Internal_DMA_Interrupt(void) {
    if(isBtTransmitting) return;

   //If USART has a byte to read then read it
   if (__HAL_UART_GET_FLAG(&btSerialHandle, UART_FLAG_RXNE)) {
      
      btDmaBuf[btDmaRxCount] = (uint8_t) btSerialHandle.Instance->DR;
      btDmaRxCount++;
   }

   if (__HAL_UART_GET_FLAG(&btSerialHandle, UART_FLAG_IDLE)) {
   __HAL_UART_CLEAR_IDLEFLAG(&btSerialHandle);
   btDmaTimer->pause();
   btDmaTimer->setCount(0);
   BT_USART_Flush();
   btDmaCallback(btDmaBuf, btDmaRxCount, btDmaClbkResult);
   btDmaRxCount = 0;
   }
}

/**
* @brief Sets the bluetooth operating mode to transparent mode
* 
* @return PatchugoStatusCode This function can return the following values:
* -OK: The bluetooth entered transparent mode correctly
* -ERROR_BT_SEND_AT: The AT command to enter transparent mode could not be sent
*/
static PatchugoStatusCode BTSetTransparentMode() {

   //if(BT_AT_Helpers::Get_BTConnState() == BT_CONNECTED) return ERROR_BT_MODE;

   isBtTransmitting = true;
   if (HAL_UART_Transmit(&btSerialHandle,(uint8_t*)BT_TRANSPARENT_MODE_CMD, strlen(BT_TRANSPARENT_MODE_CMD), 0xFF) != HAL_OK) return ERROR_BT_SEND_AT;
   isBtTransmitting = false;

   delay(10);

   BT_USART_Flush();


   return OK;
}

/**
* @brief Sets the bluetooth operating mode to command mode
* 
* @return PatchugoStatusCode This function can return the following values:
* -OK: The bluetooth entered command mode correctly 
* -ERROR_BT_MODE: The AT command to enterd command mode could not be sent
*/
static PatchugoStatusCode BTSetCommandMode() {

   isBtTransmitting = true;
   if(HAL_UART_Transmit(&btSerialHandle, (uint8_t*)BT_COMMAND_MODE_CMD, strlen(BT_COMMAND_MODE_CMD), 0xFF) != HAL_OK) return ERROR_BT_MODE;
   isBtTransmitting = false;

   delay(10);

   BT_USART_Flush();

   
   return OK;
}

PatchugoStatusCode BT_Manager::Init(void) {

    //Low level initialization of hardware
    PatchugoStatusCode checkError = BT_Serial_HAL_Init();
    if(checkError != OK) return checkError;

    //Initialize timer user to "emulate" asynchronous DMA
    BT_DMA_Timer_Init(btDmaTimer);
    btDmaTimer->attachInterrupt(BT_Internal_DMA_Interrupt);

    //Start bluetooth in command mode to use AT commands
    checkError = BT_Set_Mode(BT_MODE_COMMAND);
    if(checkError != OK) return checkError;

    //Turn echo OFF
    checkError = BT_Echo_Off();
    if(checkError != OK) return checkError;

    //Set default bluetooth name as "PatchugoLite"
    checkError = BT_Change_Name("PatchugoLite");
    if(checkError != OK) return checkError;

    //Start with a default MTU of 100
    //heckError = BT_Set_MTU(BT_DEFAULT_MTU);
    //if(checkError != OK) return checkError;

    BT_AT_Helpers::Set_BTState(BT_STATE_IDLE);
    
    //If state is IDLE like we set before this will detect connection/disconnections
    checkError = BT_Async_RX_Set_Callback(btAtHelpers.BT_Manage_AT_Resp, &checkError);
    if(checkError != OK) return checkError;

    BT_Start_Async_Listen();

    return OK;
}

PatchugoStatusCode BT_Manager::BT_Async_RX_Set_Callback(DMA_CALLBACK_PTR ptr, PatchugoStatusCode* result) {
    if(ptr == NULL) return ERROR_DMA_CALLBACK_NULL;
    btDmaCallback = ptr;
    if(result == nullptr) return ERROR_DMA_RESULT_NULL;
    btDmaClbkResult = result;
    return OK;
}

void BT_Manager::BT_Start_Async_Listen(void) {
    btDmaRxCount = 0;
    BT_Start_Async_Timer(btDmaTimer);
}

PatchugoStatusCode BT_Manager::BT_Set_Mode(BTMode mode) {
   if(currentMode == mode) return OK;

   PatchugoStatusCode checkError = OK;

   switch(mode) {
      case BT_MODE_COMMAND:
         checkError =  BTSetCommandMode();
         if(checkError == OK) currentMode = BT_MODE_COMMAND;
         break;
      case BT_MODE_TRANSPARENT:
         checkError = BTSetTransparentMode();
         if(checkError == OK) currentMode = BT_MODE_TRANSPARENT;
         break;
      default:
         return ERROR_BT_MODE;
   }

   return checkError;
}

PatchugoStatusCode BT_Manager::BT_Send_AT(uint8_t *cmdData,uint8_t len, DMA_CALLBACK_PTR callback) {

    isBtTransmitting = true;
    if (HAL_UART_Transmit(&btSerialHandle,cmdData, len, 0xFF) != HAL_OK) return ERROR_BT_SEND_AT;
    isBtTransmitting = false;

    delay(10);

    BT_USART_Flush();

    PatchugoStatusCode result = ERROR_BT_AT;

    PatchugoStatusCode checkError = BT_Async_RX_Set_Callback(callback, &result);
    if(checkError != OK) return checkError;

    BT_Start_Async_Listen();

    delay(50);

    return result;
}

PatchugoStatusCode BT_Manager::BT_Echo_Off(void) {

    BT_AT_Helpers::Set_BTState(BT_STATE_ECHO_OFF);

    //Set result as error as it will be later overridden with OK if response is successful
    PatchugoStatusCode echoOffResult = ERROR_BT_ECHO_OFF;

    
    PatchugoStatusCode checkError = BT_Async_RX_Set_Callback(btAtHelpers.BT_Manage_AT_Resp, &echoOffResult);
    if (checkError != OK) return checkError;

   isBtTransmitting = true;
   if (HAL_UART_Transmit(&btSerialHandle, (uint8_t*)BT_ECHO_OFF_CMD, strlen(BT_ECHO_OFF_CMD), 0xFF) != HAL_OK) return ERROR_BT_ECHO_OFF_SEND_CMD;
   isBtTransmitting = false;

   delay(10);

   BT_USART_Flush();

   BT_Start_Async_Listen();

   delay(50);

   return echoOffResult;
}

PatchugoStatusCode BT_Manager::BT_Change_Name(const char *name) {

    uint8_t nameLen = strlen(name);
    if (nameLen > BT_NAME_MAX_LEN) return ERROR_BT_NAME_LEN;

    uint8_t atLen = strlen(BT_CHANGE_NAME_CMD);
    uint8_t cmdLen = atLen + nameLen + 2;
    uint8_t cmd[cmdLen] = {0};

    memcpy(cmd, BT_CHANGE_NAME_CMD, atLen);
    memcpy(cmd + atLen, name, nameLen);
    memcpy(cmd + atLen + nameLen, "\r\n", 2);

    BT_AT_Helpers::Set_BTState(BT_STATE_CHANGE_NAME);

    PatchugoStatusCode changeNameResult = ERROR_BT_CHANGE_NAME;

    PatchugoStatusCode checkError = BT_Async_RX_Set_Callback(btAtHelpers.BT_Manage_AT_Resp, &changeNameResult);
    if (checkError != OK) return checkError;

    isBtTransmitting = true;
    if (HAL_UART_Transmit(&btSerialHandle, cmd, cmdLen, 0xFF) != HAL_OK) return ERROR_BT_NAME_SEND_CMD;
    isBtTransmitting = false;

    delay(10);

    BT_USART_Flush();

    BT_Start_Async_Listen();

    delay(50);

    return changeNameResult;
}

PatchugoStatusCode BT_Manager::BT_Set_MTU(uint16_t mtu) {

    char cmd[20] = {0};
    snprintf(cmd, sizeof(cmd), BT_SET_MTU_CMD, mtu);

    uint8_t cmdLen = strlen(cmd);

    BT_AT_Helpers::Set_BTState(BT_STATE_SET_MTU);

    PatchugoStatusCode setMtuResult = ERROR_BT_SET_MTU;

    PatchugoStatusCode checkError = BT_Async_RX_Set_Callback(btAtHelpers.BT_Manage_AT_Resp, &setMtuResult);
    if(checkError != OK) return checkError;

    isBtTransmitting = true;
    if(HAL_UART_Transmit(&btSerialHandle, (uint8_t*)cmd, cmdLen, 0xFF) != HAL_OK) return ERROR_BT_MTU_SEND_CMD;
    isBtTransmitting = false;

    delay(10);

    BT_USART_Flush();

    BT_Start_Async_Listen();

    delay(50);

    return setMtuResult;
}

