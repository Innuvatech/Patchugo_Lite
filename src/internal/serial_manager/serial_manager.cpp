/**
* File: serial_manager.cpp
* Created on: 2025-09-02 at 14:55
* Author: Andrea Rantin
* Description: Implementation file for serial_manager.h
*/

#include "internal/serial_manager/serial_manager.h"
#include "internal/common/global_define.h"

extern UART_HandleTypeDef rs485SerialHandle;
extern UART_HandleTypeDef usbSerialHandle;

//Timer used to "emulate" asynchronous DMA
HardwareTimer *dmaTimerRs485 = new HardwareTimer(TIM11);
//Flag to check if USART is transmitting
bool isRs485Transmitting = false;
//Pointer to a function to be used as "DMA" callback
DMA_CALLBACK_PTR rs485DmaCallback = NULL;
uint16_t rs485DmaRxLen = 0;
uint16_t rs485DmaRxCount = 0;
//"DMA" buffer
uint8_t rs485DmaBuf[RS485_MAX_RX_LEN] = {0};
//Result to be used in asynchronous operations
PatchugoStatusCode *rs485DmaClbkResult = nullptr;



/**
* @brief Flushes the USART used for bluetooth communication
* 
*/
static void RS485_USART_Flush(void) {
    __HAL_UART_CLEAR_OREFLAG(&rs485SerialHandle);
    __HAL_UART_FLUSH_DRREGISTER(&rs485SerialHandle);
}

/**
* @brief Interrupt attached to the dmaTimerRs485 used to "emulate"
* DMA behavior
*/
static void RS485_Internal_DMA_Interrupt(void) {
    if(isRs485Transmitting) return;

   //If USART has a byte to read then read it
   if (__HAL_UART_GET_FLAG(&rs485SerialHandle, UART_FLAG_RXNE)) {
      
      rs485DmaBuf[rs485DmaRxCount] = (uint8_t) rs485SerialHandle.Instance->DR;
      rs485DmaRxCount++;
   }

   if (__HAL_UART_GET_FLAG(&rs485SerialHandle, UART_FLAG_IDLE)) {
   __HAL_UART_CLEAR_IDLEFLAG(&rs485SerialHandle);
   dmaTimerRs485->pause();
   dmaTimerRs485->setCount(0);
   RS485_USART_Flush();
   rs485DmaCallback(rs485DmaBuf, rs485DmaRxCount, rs485DmaClbkResult);
   rs485DmaRxCount = 0;
   }
}

PatchugoStatusCode Serial_Manager::RS485_Serial_Init(SerialBaudRate baudRate, SerialAdvConfStruct advConfStruct) {

    PatchugoStatusCode checkError = RS485_Serial_HAL_Init(baudRate,advConfStruct);
    if(checkError != OK) return checkError;

    //Initialize timer user to "emulate" asynchronous DMA
    RS485_DMA_Timer_Init(dmaTimerRs485);
    dmaTimerRs485->attachInterrupt(RS485_Internal_DMA_Interrupt);

    return OK;
}

PatchugoStatusCode Serial_Manager::USB_Serial_Init(SerialBaudRate baudRate, SerialAdvConfStruct advConfStruct) {

    PatchugoStatusCode checkError = USB_Serial_HAL_Init(baudRate,advConfStruct);
    if(checkError != OK) return checkError;

    return OK;
}

PatchugoStatusCode Serial_Manager::RS485_Serial_Write(uint8_t* buf, uint16_t len) {
    HAL_GPIO_WritePin(GPIOA,GPIO_PIN_12,GPIO_PIN_SET);
    if(HAL_UART_Transmit(&rs485SerialHandle, buf, len, 0xFF) != HAL_OK){
        HAL_GPIO_WritePin(GPIOA,GPIO_PIN_12,GPIO_PIN_RESET);
        return ERROR_RS485_SERIAL_WRITE;
    }
    HAL_GPIO_WritePin(GPIOA,GPIO_PIN_12,GPIO_PIN_RESET);
    return OK;
}

PatchugoStatusCode Serial_Manager::RS485_Serial_Read(uint8_t* buf, uint16_t len, uint32_t timeout) {
    HAL_GPIO_WritePin(GPIOA,GPIO_PIN_12,GPIO_PIN_RESET);
    if(HAL_UART_Receive(&rs485SerialHandle, buf, len, timeout) != HAL_OK) return ERROR_RS485_SERIAL_READ;
    return OK;
}

PatchugoStatusCode Serial_Manager::RS485_Async_RX_Set_Callback(DMA_CALLBACK_PTR ptr, PatchugoStatusCode* result) {
    if(ptr == NULL) return ERROR_DMA_CALLBACK_NULL;
    rs485DmaCallback = ptr;
    if(result == nullptr) return ERROR_DMA_RESULT_NULL;
    rs485DmaClbkResult = result;
    return OK;
}

PatchugoStatusCode Serial_Manager::USB_Serial_Write(uint8_t* buf, uint16_t len) {
   if(HAL_UART_Transmit(&usbSerialHandle, buf, len, 0xFF) != HAL_OK) return ERROR_USB_SERIAL_WRITE;
   return OK;
}

PatchugoStatusCode Serial_Manager::USB_Serial_Read(uint8_t* buf, uint16_t len, uint32_t timeout) {
  if(HAL_UART_Receive(&usbSerialHandle, buf, len, timeout) != HAL_OK) return ERROR_USB_SERIAL_READ;
  return OK;
}

void Serial_Manager::RS485_Start_Async_Listen(void) {
    rs485DmaRxCount = 0;
    RS485_Start_Async_Timer(dmaTimerRs485);
}