/**
* File: patchugo_lite.cpp
* Created on: 2025-09-01 at 21:36
* Author: Andrea Rantin
* Description: Implementation file for patchugo_lite.h
*/

#include "patchugo_lite.h"

PatchugoStatusCode PatchugoLite::Init(void) {
    ioManager.Init();

    //Initialize RS485 serial with a baudrate of 115200
    PatchugoStatusCode checkError = serialManager.RS485_Serial_Init(BAUDRATE_115200);
    if(checkError != OK) return checkError;

    //Initialize USB serial with a baudrate of 115200
    checkError = serialManager.USB_Serial_Init(BAUDRATE_115200);
    if(checkError != OK) return checkError;

    //Initialize I2C
    checkError = i2cManager.Init();
    if(checkError != OK) return checkError;

    //Initialize SPI
    checkError = spiManager.Init(SPI_CPOL_LOW, SPI_CPHA_2EDGE);
    if(checkError != OK) return checkError;

    //Initialize bluetooth management part of the library
    checkError = btManager.Init();
    if(checkError != OK) return checkError;

    checkError = flashManager.Flash_Init();
    if(checkError != OK) return checkError;

    return OK;
}

void PatchugoLite::ISO_IO_Write(ISO_OutputPin_Typedef pin, FlagStatus state) {
    ioManager.ISO_IO_Write(pin, state);
}

uint8_t PatchugoLite::ISO_IO_Read(ISO_InputPin_Typedef pin) {
    return ioManager.ISO_IO_Read(pin);
}

PatchugoStatusCode PatchugoLite::BT_Echo_Off(void) {
    return btManager.BT_Echo_Off();
}

PatchugoStatusCode PatchugoLite::BT_Change_Name(const char *name) {
    return btManager.BT_Change_Name(name);
}

PatchugoStatusCode PatchugoLite::BT_Set_MTU(uint16_t mtu) {
    return btManager.BT_Set_MTU(mtu);
}

PatchugoStatusCode PatchugoLite::BT_Set_Mode(BTMode mode) {
    return btManager.BT_Set_Mode(mode);
}

PatchugoStatusCode PatchugoLite::BT_Send_AT(uint8_t *cmdData,uint8_t len, DMA_CALLBACK_PTR callback) {
    return btManager.BT_Send_AT(cmdData, len, callback);
}

PatchugoStatusCode PatchugoLite::BT_Async_RX_Set_Callback(DMA_CALLBACK_PTR ptr, PatchugoStatusCode* result) {
    return btManager.BT_Async_RX_Set_Callback(ptr,result);
}

void PatchugoLite::BT_Start_Async_Listen(void) {
    btManager.BT_Start_Async_Listen();
}

PatchugoStatusCode PatchugoLite::RS485_Serial_Init(SerialBaudRate baudRate, SerialAdvConfStruct advConfStruct) {
    return serialManager.RS485_Serial_Init(baudRate,advConfStruct);
}

PatchugoStatusCode PatchugoLite::RS485_Serial_Write(uint8_t* buf, uint16_t len) {
    return serialManager.RS485_Serial_Write(buf, len);
}

PatchugoStatusCode PatchugoLite::RS485_Serial_Read(uint8_t* buf, uint16_t len, uint32_t timeout) {
    return serialManager.RS485_Serial_Read(buf, len, timeout);
}

PatchugoStatusCode PatchugoLite::USB_Serial_Init(SerialBaudRate baudRate, SerialAdvConfStruct advConfStruct) {
    return serialManager.USB_Serial_Init(baudRate,advConfStruct);
}

PatchugoStatusCode PatchugoLite::USB_Serial_Write(uint8_t* buf, uint16_t len) {
    return serialManager.USB_Serial_Write(buf, len);
}

PatchugoStatusCode PatchugoLite::USB_Serial_Read(uint8_t* buf, uint16_t len, uint32_t timeout) {
    return serialManager.USB_Serial_Read(buf, len, timeout);
}

PatchugoStatusCode PatchugoLite::RS485_Async_RX_Set_Callback(DMA_CALLBACK_PTR ptr, PatchugoStatusCode* result) {
    return serialManager.RS485_Async_RX_Set_Callback(ptr,result);
}

void PatchugoLite::RS485_Start_Async_Listen(void) {
    serialManager.RS485_Start_Async_Listen();
}

PatchugoStatusCode PatchugoLite::SPI_Write(SPI_CS cs, uint8_t *writeData, uint16_t len, uint32_t timeout) {
    return spiManager.SPI_Write(cs,writeData,len,timeout);
}

PatchugoStatusCode PatchugoLite::SPI_Read(SPI_CS cs, uint8_t *readData, uint16_t len, uint32_t timeout) {
    return spiManager.SPI_Read(cs,readData,len,timeout);
}

PatchugoStatusCode PatchugoLite::I2C_Init(I2CConfigStruct configStruct) {
    return i2cManager.Init(configStruct);
}

PatchugoStatusCode PatchugoLite::I2C_Write(uint8_t addr, uint8_t *data, uint16_t len, uint32_t timeout) {
    return i2cManager.I2C_Write(addr, data, len, timeout);
}

PatchugoStatusCode PatchugoLite::I2C_Read(uint8_t addr, uint8_t *readData, uint16_t len, uint32_t timeout) {
    return i2cManager.I2C_Read(addr, readData, len, timeout);
}

PatchugoStatusCode PatchugoLite::I2C_WriteReg(uint8_t addr, uint16_t regAddr, uint16_t regAddrSize, uint8_t *writeData, uint16_t len, uint32_t timeout) {
    return i2cManager.I2C_WriteReg(addr, regAddr, regAddrSize, writeData, len, timeout);
}

PatchugoStatusCode PatchugoLite::I2C_ReadReg(uint8_t addr, uint16_t regAddr, uint16_t regAddrSize, uint8_t *readData, uint16_t len, uint32_t timeout) {
    return i2cManager.I2C_ReadReg(addr, regAddr, regAddrSize, readData, len, timeout);
}

PatchugoStatusCode PatchugoLite::Flash_Read_Register(uint8_t reg, uint8_t *readValue) {
    return flashManager.Flash_Read_Register(reg, readValue);
}

PatchugoStatusCode PatchugoLite::Flash_Write_Instruction(uint8_t instruction) {
    return flashManager.Flash_Write_Instruction(instruction);
}

PatchugoStatusCode PatchugoLite::Flash_Reset(void) {
    return flashManager.Flash_Reset();
}

PatchugoStatusCode PatchugoLite::Flash_Erase(void) {
    return flashManager.Flash_Erase();
}

PatchugoStatusCode PatchugoLite::Flash_Erase_Sector(FlashSector sector) {
    return flashManager.Flash_Erase_Sector(sector);
}

PatchugoStatusCode PatchugoLite::Flash_Read_Data(FlashSector sector, FlashPage page, FlashPageOffset offset, uint8_t *readData, uint32_t len) {
    return flashManager.Flash_Read_Data(sector, page, offset, readData, len);
}

PatchugoStatusCode PatchugoLite::Flash_Write_Data(FlashSector sector, FlashPage page, FlashPageOffset offset,  uint8_t *writeData, uint8_t len) {
    return flashManager.Flash_Write_Data(sector, page, offset,  writeData, len);
}